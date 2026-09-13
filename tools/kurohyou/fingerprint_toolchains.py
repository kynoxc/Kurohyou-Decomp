#!/usr/bin/env python3
"""Run the Kurohyou matching corpus across compiler candidates.

No compiler is promoted automatically.  This tool only fingerprints codegen and
reports exact-byte hits.  A human-reviewed profile must later be changed to
`kind=certifying` after multiple non-trivial functions match retail.
"""
from __future__ import annotations
import argparse, json, subprocess, sys
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]
MATCH=ROOT/'tools/kurohyou/matching.py'
TCFILE=ROOT/'matching/toolchains.json'


def main()->int:
    ap=argparse.ArgumentParser()
    ap.add_argument('--eboot',type=Path,required=True)
    ap.add_argument('--toolchains',nargs='*',default=[])
    ap.add_argument('--output',type=Path,default=ROOT/'matching/FINGERPRINT_MATRIX.md')
    args=ap.parse_args()
    tcs=json.loads(TCFILE.read_text())['toolchains']
    names=args.toolchains or list(tcs)
    reports=[]
    for name in names:
        if name not in tcs:
            print(f'unknown toolchain: {name}',file=sys.stderr); return 2
        out_json=ROOT/f'matching/fingerprints/{name}.json'
        out_md=ROOT/f'matching/fingerprints/{name}.md'
        out_json.parent.mkdir(parents=True,exist_ok=True)
        cmd=[sys.executable,str(MATCH),'--eboot',str(args.eboot),'--toolchain',name,
             '--output',str(out_md),'--json',str(out_json)]
        print('===',name,'===')
        proc=subprocess.run(cmd,cwd=ROOT)
        if proc.returncode:
            print(f'{name}: matching.py failed ({proc.returncode})')
            continue
        reports.append(json.loads(out_json.read_text()))

    funcs=[]
    seen=set()
    for rep in reports:
        for row in rep.get('functions',[]):
            key=(row['address'],row['function'])
            if key not in seen: seen.add(key); funcs.append(key)
    funcs.sort(key=lambda x:int(x[0],16))
    bytc={r['toolchain']:r for r in reports}
    md=['# Kurohyou compiler fingerprint matrix','',
        'Exact bytes in this matrix do **not** automatically identify the retail compiler. '
        'Profiles remain diagnostic/fingerprint candidates until multiple non-trivial functions match and the ABI/codegen family is corroborated.','']
    md.append('| Function | Address | '+' | '.join(bytc)+' |')
    md.append('|---|---:|'+'|'.join(['---:' for _ in bytc])+'|')
    for addr,fn in funcs:
        cells=[]
        for tc,rep in bytc.items():
            row=next((x for x in rep['functions'] if x['address']==addr),None)
            if not row: cells.append('—'); continue
            cmp=row.get('comparison')
            status=row.get('state','UNTESTED')
            if not cmp: cells.append(row.get('compiler',{}).get('status','UNTESTED')); continue
            if cmp.get('exact'): cells.append('**100% exact**')
            else: cells.append(f"{cmp.get('byte_similarity',0):.2f}%")
        md.append(f'| {fn} | `{addr}` | '+' | '.join(cells)+' |')
    md.append('')
    md.append('## Candidate ranking')
    md.append('')
    for tc,rep in bytc.items():
        rows=rep['functions']
        exact=[r for r in rows if (r.get('comparison') or {}).get('exact')]
        nontrivial=[r for r in exact if int(r.get('size',0))>8]
        tested=[r for r in rows if r.get('comparison') is not None]
        avg=(sum(r['comparison']['byte_similarity'] for r in tested)/len(tested)) if tested else 0.0
        md.append(f"- `{tc}` ({rep.get('toolchain_kind')}): exact {len(exact)}/{len(rows)}, "
                  f"non-trivial exact {len(nontrivial)}, mean positional byte similarity {avg:.2f}%.")
    md.append('')
    md.append('**Promotion rule:** do not change a profile to `certifying` from a trivial exact function. '
              'Require several non-trivial exact functions spanning integer control flow, EABI floating-point arguments, and at least one relocation-aware caller.')
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text('\n'.join(md)+'\n',encoding='utf-8')
    print(args.output)
    return 0

if __name__=='__main__':
    raise SystemExit(main())
