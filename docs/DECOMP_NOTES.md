# Notas de continuidad: título y dependencias

El estado cuantitativo vigente se genera en `STATUS.md`; estas notas describen la evidencia y los siguientes problemas de matching.

## Menú principal

El intervalo `0x00372A38..0x00376248` contiene 40 entradas inventariadas. Se agrupan por RTTI `SceneTitleMainmenu`, referencias de vtable, llamadas y continuidad, sin afirmar que coincidan con una única TU original.

La función de actualización `0x003752EC` coincide en sus 820 bytes. La entrada `0x00375620` tiene una candidata de 2.944 bytes y 665/736 palabras iguales, pero no está certificada. Su tabla de salto también necesita validación independiente. `0x0037311C` mejoró a 111/117 palabras con el tamaño correcto de 468 bytes: quedan seis instrucciones del prólogo diferentes y la validación de la tabla.

Faltan candidatas C/C++ para el constructor `0x00372A38`, destructor `0x00372CFC`, limpieza `0x00372FB8` y preparación de recursos `0x00374F58`. La tercera es limpieza, no la actualización por frame. Esas funciones tienen manejo de excepciones y referencias compartidas; copiar las variables artificiales de Ghidra no reconstruye el C++ original.

## Selector de opciones

`0x002E10C0` coincide en sus 540 bytes: ajusta la selección, resuelve el salto entre extremos, desplaza las filas visibles y guarda el tipo de movimiento. También coinciden configuración, actualización, reinicio, posición visible, primera fila y reinicio de movimiento.

`0x002E1454` tiene 46/49 palabras iguales en 196 bytes. Las diferencias están en la asignación de registros inicial y un destino de salto. No está certificada. La selección directa y las lecturas de pulsación/repetición tampoco están terminadas. Los calificadores de memoria en esas candidatas aún son provisionales.

## Nodos y audio

El prefijo de nodo tiene una pose empaquetada de 52 bytes en `+0x0C`, animador en `+0x40` y vtable en `+0xA8`. La asignación completa de la pose y la llamada virtual en `0x0032BCA0` coinciden. El color local usa escrituras desalineadas; la lectura `0x0032BD9C` usa una carga alineada. Tratar ambas rutas como el mismo acceso empaquetado impide el match.

La consulta `0x0032C4EC` mide 24 bytes. En `0x0032C504` comienza otra entrada virtual vacía de ocho bytes, referenciada por el dato en `0x00685DBC`. Se separaron las funciones en vez de agregar relleno artificial.

Las funciones de audio certificadas incluyen wrappers por nombre, programación de parámetros y parada/fundido por evento y grupo. Esto no equivale a un backend de audio nativo ni a un motor de audio completo. Los despachos `0x00311F78` y `0x00312030` siguen sin match.

## Direcciones PRX y referencia correcta

Ghidra aplica reubicaciones al importar. El certificador compara contra el archivo con SHA-256 `f82d09615506fd0aaa4a792844f0fb6908b0c07e5bb4fea1c992d4c7827f1975`.

En `0x0038936C`, las instrucciones de `0x0038938C` y `0x00389390` codifican `0x2E4D8`. La sección de reubicaciones PRX contiene respectivamente `(r_offset=0x0038938C, r_info=0x00010005)` y `(r_offset=0x00389390, r_info=0x00010006)`. El segmento PT_LOAD 1 empieza en `0x68D378`: la suma es `0x6BB850`, que muestra Ghidra. El manifiesto conserva el addend del archivo y documenta esta relación. No debe interpretarse `0x2E4D8` como la dirección final del objeto gráfico.

La comparación de texto no certifica todavía todas las reubicaciones del PRX final, su enlazado, las tablas de salto ni sus datos.

## Verificación y siguiente pasada

Se corrigió el tratamiento de addends HI16/LO16, R26 y R32 del comparador. Ocho pruebas cubren acarreo y signo, múltiples HI16, símbolos locales, addends de salto y rechazo de entradas sin resolver o de regiones inválidas. No se parchean instrucciones generadas para forzar coincidencias: solo se aplican reubicaciones ELF declaradas.

Se retiró el ensamblador vacío heredado de `0x001E2810`; sigue pendiente. La similitud parcial de esa candidata bajó, pero no afecta a los bytes exactos certificados.

Prioridades: cerrar el despacho y entrada del menú; auditar sus tablas de salto; reconstruir el C++ de recursos/limpieza; completar lectura direccional y límites del selector; terminar los despachos de audio y las operaciones recursivas de nodos. Mantener el inventario parcial de dependencias separado de una afirmación de TU original completa.
