#!/usr/bin/env python3
from __future__ import annotations
import argparse, json, struct
from pathlib import Path
import sys

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str((ROOT/'tools/kurohyou').resolve()))
import matching as mh

def hx(v): return int(v,0) if isinstance(v,str) else int(v)

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--eboot',type=Path,required=True)
    ap.add_argument('--manifest',type=Path,default=ROOT/'matching/functions.json')
    ap.add_argument('--force',action='store_true')
    args=ap.parse_args()
    data=args.eboot.read_bytes(); manifest=json.loads(args.manifest.read_text())
    count=0
    for fn in manifest['functions']:
        rel=fn.get('oracle_asm')
        if not rel: continue
        out=ROOT/rel
        if out.exists() and not args.force: continue
        addr,size=hx(fn['address']),hx(fn['size'])
        blob=mh.extract_va(data,addr,size)
        if len(blob)%4: raise SystemExit(f'{fn["name"]}: size not word aligned')
        sym=f'oracle_{addr:08X}'
        lines=['    .set noreorder','    .text',f'    .globl {sym}',f'    .type {sym},@function',f'{sym}:']
        for i in range(0,len(blob),4):
            lines.append(f'    .word 0x{struct.unpack_from("<I",blob,i)[0]:08x}')
        lines.append(f'    .size {sym},.-{sym}')
        out.parent.mkdir(parents=True,exist_ok=True)
        out.write_text('\n'.join(lines)+'\n')
        print(f'wrote {out.relative_to(ROOT)} {size} bytes')
        count+=1
    print(f'generated {count} oracle(s)')
if __name__=='__main__': main()
