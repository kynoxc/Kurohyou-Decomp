#!/usr/bin/env python3
"""Clang source-shape sweep for retail function 0x001E63D8.

This is a compiler fingerprint experiment, not a decomp matcher. It demonstrates
whether common equivalent C spellings and optimization modes can reproduce the
retail leaf under the available Clang PSP/O32 backend.
"""
from pathlib import Path
import subprocess, tempfile, shutil, json

ROOT=Path(__file__).resolve().parents[2]
REF=ROOT/'matching/reference/001E63D8_0020.bin'
OUT=ROOT/'matching/CLANG_SOURCE_SWEEP_001E63D8.md'

VARIANTS={
'base':'int c=s->cur; if(c==n)return; s->cur=n; s->dirty=1;',
'neq':'if(s->cur!=n){s->cur=n;s->dirty=1;}',
'localptr':'volatile int *p=&s->cur; int c=*p; if(c==n)return; *p=n; s->dirty=1;',
'localn':'int x=n; int c=s->cur; if(c==x)return; s->cur=x; s->dirty=1;',
'assignn':'int c=s->cur; if(c==n)return; s->cur=n; n=1; s->dirty=(u8)n;',
'uassign':'unsigned c=(unsigned)s->cur; if(c==(unsigned)n)return; s->cur=n; n=(int)1u; s->dirty=(u8)n;',
'comma':'int c=s->cur; if(c==n)return; (s->cur=n),(s->dirty=1);',
'while':'int c=s->cur; while(c!=n){s->cur=n;s->dirty=1;break;}',
'goto':'int c=s->cur; if(c==n)goto out; s->cur=n; s->dirty=1; out:;',
'directtwice':'if(s->cur==n)return; s->cur=n; s->dirty=(u8)1u;',
}
FLAGS=[
['-O1'],['-O2'],['-O3'],['-Os'],['-Oz'],
['-O2','-fno-inline'],['-O2','-fno-strict-aliasing'],['-O2','-fwrapv'],
['-O2','-fno-vectorize'],['-O2','-fno-slp-vectorize'],
]
BASE=['clang','--target=mipsel-sony-psp','-mips2','-mabi=o32','-fno-pic','-mno-abicalls',
      '-fomit-frame-pointer','-ffreestanding','-fno-builtin','-fno-stack-protector']

def extract(obj:Path, out:Path):
    subprocess.run(['llvm-objcopy','-O','binary','--only-section=.text',str(obj),str(out)],check=True,
                   stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
    return out.read_bytes()

def main():
    if not shutil.which('clang') or not shutil.which('llvm-objcopy'):
        raise SystemExit('clang/llvm-objcopy required')
    ref=REF.read_bytes(); rows=[]
    with tempfile.TemporaryDirectory() as td:
        td=Path(td)
        for name,body in VARIANTS.items():
            src=td/(name+'.c')
            src.write_text('typedef unsigned char u8; typedef struct { volatile u8 dirty; u8 p[3]; volatile int cur;} S;\nvoid f(S*s,int n){'+body+'}\n')
            for flags in FLAGS:
                tag=' '.join(flags)
                obj=td/(name+'_'+str(len(rows))+'.o'); raw=obj.with_suffix('.bin')
                cp=subprocess.run(BASE+flags+['-c',str(src),'-o',str(obj)],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
                if cp.returncode:
                    rows.append((0.0,False,name,tag,0,'compile failed'))
                    continue
                cand=extract(obj,raw); denom=max(len(ref),len(cand),1)
                equal=sum(a==b for a,b in zip(ref,cand)); score=100.0*equal/denom
                rows.append((score,ref==cand,name,tag,len(cand),''))
    rows.sort(reverse=True)
    md=['# Clang source-shape sweep — 0x001E63D8','',
        'This experiment tested common semantically equivalent C shapes under the available Clang PSP/O32 backend. It does **not** replace a retail EABI compiler test.','',
        f'Total candidates: **{len(rows)}**. Exact C matches: **{sum(1 for r in rows if r[1])}**. Best positional byte similarity: **{rows[0][0]:.2f}%**.','',
        '| score | exact | source shape | flags | bytes |','|---:|:---:|---|---|---:|']
    for r in rows[:30]:
        md.append(f'| {r[0]:.2f}% | {"YES" if r[1] else "no"} | `{r[2]}` | `{r[3]}` | {r[4]} |')
    md += ['', 'Conclusion: the 32-byte shape is stable, but Clang consistently chooses `$1` for the load/immediate temporary and `addiu` for literal `1`, whereas retail uses `$6`, then reuses `$5` with `ori`. Source spelling is not the remaining issue for this backend.']
    OUT.write_text('\n'.join(md)+'\n')
    print(OUT)

if __name__=='__main__': main()
