#!/usr/bin/env python3
from __future__ import annotations
import json, re, shutil, subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
CFG=ROOT/'matching/toolchains.json'
OUT=ROOT/'matching/TOOLCHAIN_PROBE.md'

def run(cmd):
    return subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)

def main():
    cfg=json.loads(CFG.read_text())['toolchains']
    rows=[]
    for name,tc in cfg.items():
        path=shutil.which(tc['compiler'])
        version='missing'
        if path:
            p=run([path,'--version']); version=(p.stdout.splitlines() or ['unknown'])[0].strip()
        expected=tc.get('expected_version_regex')
        version_ok=None if not expected or not path else bool(re.search(expected,version,re.I))
        rows.append((name,tc.get('kind','unknown'),tc['compiler'],path or '—',version,expected or '—',version_ok,tc.get('description','')))
    md=['# PSP matching toolchain probe','',
        'A compiler being present does not make it certifying. It must first reproduce multiple retail fingerprints exactly.','',
        '| profile | kind | compiler | resolved path | version | expected version | version check |','|---|---|---|---|---|---|---|']
    for r in rows:
        chk='—' if r[6] is None else ('PASS' if r[6] else 'FAIL')
        md.append(f'| `{r[0]}` | {r[1]} | `{r[2]}` | `{r[3]}` | `{r[4]}` | `{r[5]}` | {chk} |')
    md += ['', '## Notes','']
    for r in rows:
        md.append(f'- `{r[0]}`: {r[7]}')
    OUT.write_text('\n'.join(md)+'\n')
    print(OUT)
if __name__=='__main__': main()
