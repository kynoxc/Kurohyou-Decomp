"""Refresh human-readable status only from a current complete matching audit."""
import json
from audit_evidence import ROOT, load_verified_audit


def main():
    audit, manifest = load_verified_audit()
    rows = {int(r['address'], 0): r for r in audit['functions']}
    for f in manifest['functions']:
        f['block01_matching_state'] = 'MATCHING_EXACT' if rows[int(f['address'], 0)]['exact'] else 'NON_MATCHING'
    (ROOT / 'matching/functions.json').write_text(json.dumps(manifest, indent=2) + '\n')
    status = dict(schema=2, target='NPJH50333', retail_sha256=audit['target_sha256'],
                  compiler='SN Systems pspsnc 1.2.7503.0', evidence='matching_audit.json',
                  audited_functions=audit['candidate_functions'], matching_exact=audit['matching_functions'],
                  nonmatching=audit['candidate_functions']-audit['matching_functions'],
                  matched_code_bytes=audit['matched_code_bytes'], total_executable_bytes=audit['total_executable_bytes'],
                  strict_code_percent=audit['code_percent'], matched_data_bytes=0,
                  goal_one_percent_bytes=(audit['total_executable_bytes']+99)//100,
                  verification_scope='individual reconstructed C/C++ functions; not full linked TUs')
    (ROOT / 'config/NPJH50333/status.json').write_text(json.dumps(status, indent=2) + '\n')
    lines = ['# Estado verificado', '',
             f"{audit['matching_functions']}/{audit['candidate_functions']} candidatas exactas; "
             f"{audit['matched_code_bytes']:,}/{audit['total_executable_bytes']:,} bytes de código ({audit['code_percent']:.6f}%).", '',
             'El porcentaje incluye todo el código ejecutable del EBOOT, incluidas bibliotecas. No cuenta pseudocódigo, ensamblado ni similitud parcial.', '',
             'Los porcentajes por grupo se refieren a sus funciones inventariadas. Solo el menú principal tiene un intervalo continuo completo inventariado.', '']
    units = json.loads((ROOT / 'config/NPJH50333/translation_units.json').read_text())['units']
    for unit in units:
        lines.extend([f"## {unit['class_name']}", '', unit.get('inventory_scope', 'Agrupación provisional de funciones.'), '',
                      '| Dirección | Función | Bytes | Resultado |', '|---|---|---:|---|'])
        for f in unit['functions']:
            row = rows.get(int(f['address'], 0))
            if row is None:
                result = 'Sin candidata C/C++'
            elif row['exact']:
                result = 'EXACTO'
            else:
                c = row.get('comparison', {})
                result = f"NO MATCH: {c.get('equal_words',0)}/{f['size']//4} palabras; objeto {c.get('candidate_size',0)} bytes"
            lines.append(f"| `{f['address']}` | {f['name']} | {f['size']} | {result} |")
        lines.append('')
    lines.extend(['', 'Los límites de TU son agrupaciones provisionales basadas en RTTI, vtables y continuidad del código. '
                  'Las certificaciones compilan una función seleccionada con `MATCH_FUNCTION`; la TU enlazada completa aún no está verificada.', '',
                  'Regeneración: `python tools/update_status.py`, después de ejecutar `tools/audit_matches.py` sin `--only`.'])
    (ROOT / 'docs/STATUS.md').write_text('\n'.join(lines) + '\n', encoding='utf-8')


if __name__ == '__main__':
    main()
