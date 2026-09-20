# Kurohyou 1: decompilación con coincidencia binaria

Trabajo local sobre NPJH50333. El objetivo es reconstruir C/C++ que SNC compile a los mismos bytes que el ejecutable original y, posteriormente, preparar un port. Este árbol todavía no es un port nativo jugable.

El estado reproducible está en [docs/STATUS.md](docs/STATUS.md). No se cuentan ensamblador, pseudocódigo exportado, porcentajes de similitud parcial ni funciones pendientes de validación de tablas de salto.

## Referencia y compilador

- Referencia local: `orig/NPJH50333_EBOOT.BIN`, 9.747.152 bytes.
- SHA-256: `f82d09615506fd0aaa4a792844f0fb6908b0c07e5bb4fea1c992d4c7827f1975`.
- SNC: `pspsnc 1.2.7503.0`; ejecutable SHA-256 `b02e70f0319f1309171deeac730e6b821a0a91afb536e65ee61e2a85962621c2`.
- También puede usarse una instalación propia pasando su ruta a `--compiler`.
- Copia local de trabajo: `local/toolchain/pspsnc.exe`, con sus componentes hermanos.

El binario, el compilador, los proyectos Ghidra y los objetos están excluidos de Git. Este trabajo parte de `d76929f`. La auditoría publicada puede validarse sin esos archivos privados; para volver a compilar se necesitan el EBOOT de referencia y SNC.

## Organización

- `src/game/scene/title/scene_title_mainmenu.c`: menú principal.
- `src/game/scene/title/scene_title_base.c`: selección persistida del título.
- `src/game/scene/scene_common.c`: transiciones, nodos y utilidades compartidas.
- `src/engine/cse/cse_node.c`: animación, transformación, visibilidad y color de nodos.
- `src/engine/ui/menu_selector.c`: selección y desplazamiento de opciones.
- `src/engine/audio/audio_events.c`: despacho y parada de eventos de audio.
- `include/`: prefijos y estructuras reconstruidos a partir de accesos observados.
- `matching/src/`: candidatas anteriores aún pendientes de reagrupar.
- `matching/functions.json`: tamaños, símbolos, opciones SNC y destinos de reubicación por función.
- `config/NPJH50333/translation_units.json`: inventario y evidencia de las agrupaciones propuestas.

Las TU son una organización de trabajo. Los límites de los objetos originales aún no están demostrados. La comprobación actual compila una función seleccionada mediante `MATCH_FUNCTION`; no certifica una TU completa enlazada. Los nombres descriptivos y tipos reconstruidos no pretenden recuperar los nombres originales.

## Compilar y comparar

Se necesita Python 3. La auditoría y sus pruebas no requieren Capstone ni Ghidra.

```powershell
python tools/audit_matches.py --compiler local/toolchain/pspsnc.exe
python tools/update_status.py
python tools/progress.py
python -m unittest discover -s tests -v
```

La auditoría devuelve código 1 cuando quedan candidatas sin match; el informe completo se escribe igualmente. `update_status.py` rechaza informes incompletos o desactualizados. Los scripts históricos de exploración de compiladores no sustituyen esta auditoría.

Para trabajar en una función:

```powershell
python tools/audit_matches.py --compiler local/toolchain/pspsnc.exe --only 003752EC
python tools/diff_function.py 003752EC --limit 30
```

El segundo comando usa Capstone; esta sesión lo tiene instalado en `local/python`. El informe parcial se escribe en `local/audit-subset.json` y no sustituye el progreso global. Los flags efectivos están en el manifiesto; `-g` puede cambiar la disposición del código de SNC.

`.gitattributes` fija los archivos de texto a LF para conservar los hashes de fuentes entre Windows y Linux. GitHub Actions valida los metadatos, las pruebas del comparador y el informe público; no recompila con SNC ni necesita el juego.

La auditoría verifica el hash del EBOOT, elimina el objeto anterior de cada candidata, compila, aplica las reubicaciones ELF declaradas y compara todo el texto generado. Guarda hashes de fuentes, cabeceras, herramientas, compilador, objetos y bytes de referencia. Solo suma intervalos exactos sin solapamiento. Las tablas de salto con `$LSW` siguen bloqueadas hasta verificar también sus datos.

El denominador global son **6.040.516 bytes ejecutables**, incluidas las bibliotecas del EBOOT. El 1% requiere **60.406 bytes exactos**. Los porcentajes por grupo parcial no son porcentajes de una TU original completa.

## Análisis local

`tools/analyze_title.py` genera semillas a partir de llamadas y referencias. Los scripts de `tools/ghidra` permiten exportar grupos concretos sin autoanalizar todo el binario. Las semillas y sus límites son candidatos; hay que contrastarlos con llamadas, retornos, delay slots y referencias virtuales.

Ghidra puede mostrar direcciones ya reubicadas de un PRX. La comparación utiliza los bytes del archivo. Un ejemplo documentado en el manifiesto es `SceneCommon_PrepareRenderState`: el addend `0x2E4D8` y la base del segundo segmento `0x68D378` producen `0x6BB850`. No se debe sustituir silenciosamente un addend del archivo por una dirección de la vista de Ghidra.

La siguiente prioridad es cerrar las funciones pendientes del menú principal, sus tablas de salto y sus constructores/destructores con manejo de excepciones C++, además de completar las dependencias ya inventariadas.
