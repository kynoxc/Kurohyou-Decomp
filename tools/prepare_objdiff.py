#!/usr/bin/env python3
"""Build local objdiff expected/current object wrappers.

Requires:
- your own verified NPJH50333_EBOOT.BIN
- SN Systems pspsnc 1.2.7503.0 for candidate compilation

No retail bytes produced by this script are intended for git.
"""
from __future__ import annotations
import argparse,json,os,shutil,struct,subprocess,sys,tempfile
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
from tools.kurohyou.matching import extract_va, patch_text_relocations, parse_hex

EXPECTED_SHA="f82d09615506fd0aaa4a792844f0fb6908b0c07e5bb4fea1c992d4c7827f1975"

def align(x,a): return (x+a-1)&~(a-1)

def make_mips_obj(code:bytes,symbol:str,out:Path):
    # Minimal ET_REL MIPS32 LE object: NULL, .text, .symtab, .strtab, .shstrtab.
    shstr=b"\0.text\0.symtab\0.strtab\0.shstrtab\0"
    sh_name_text=1
    sh_name_sym=7
    sh_name_str=15
    sh_name_shstr=23
    strtab=b"\0"+symbol.encode()+b"\0"
    symtab=bytearray(32)  # null + one global function
    struct.pack_into("<IIIBBH",symtab,16,1,0,len(code),(1<<4)|2,0,1)

    ehsize=52
    text_off=align(ehsize,4)
    sym_off=align(text_off+len(code),4)
    str_off=sym_off+len(symtab)
    shstr_off=str_off+len(strtab)
    shoff=align(shstr_off+len(shstr),4)
    shnum=5
    size=shoff+shnum*40
    b=bytearray(size)
    b[:16]=b"\x7fELF"+bytes([1,1,1,0])+bytes(8)
    struct.pack_into("<HHIIIIIHHHHHH",b,16,1,8,1,0,0,shoff,0x10A23001,52,0,0,40,shnum,4)
    b[text_off:text_off+len(code)]=code
    b[sym_off:sym_off+len(symtab)]=symtab
    b[str_off:str_off+len(strtab)]=strtab
    b[shstr_off:shstr_off+len(shstr)]=shstr
    # section headers
    struct.pack_into("<IIIIIIIIII",b,shoff+40*1,sh_name_text,1,0x6,0,text_off,len(code),0,0,4,0)
    struct.pack_into("<IIIIIIIIII",b,shoff+40*2,sh_name_sym,2,0,0,sym_off,len(symtab),3,1,4,16)
    struct.pack_into("<IIIIIIIIII",b,shoff+40*3,sh_name_str,3,0,0,str_off,len(strtab),0,0,1,0)
    struct.pack_into("<IIIIIIIIII",b,shoff+40*4,sh_name_shstr,3,0,0,shstr_off,len(shstr),0,0,1,0)
    out.parent.mkdir(parents=True,exist_ok=True)
    out.write_bytes(b)

def launcher(compiler:Path):
    if os.name=="nt":
        return [str(compiler)]
    if compiler.suffix.lower()==".exe":
        wibo=shutil.which("wibo")
        if not wibo:
            raise RuntimeError("wibo required to run pspsnc.exe on this platform")
        return [wibo,str(compiler)]
    return [str(compiler)]

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("--eboot",type=Path,required=True)
    ap.add_argument("--compiler",type=Path,required=True)
    args=ap.parse_args()

    import hashlib
    data=args.eboot.read_bytes()
    if hashlib.sha256(data).hexdigest()!=EXPECTED_SHA:
        raise SystemExit("wrong EBOOT SHA-256")

    funcs=json.loads((ROOT/"matching/functions.json").read_text())["functions"]
    temp=ROOT/"build/NPJH50333/compiler_raw"
    shutil.rmtree(temp,ignore_errors=True); temp.mkdir(parents=True)
    exact=0
    for f in funcs:
        addr=parse_hex(f["address"]); size=parse_hex(f["size"])
        name=f["name"]; symbol=f["symbol"]
        safe="".join(c if c.isalnum() or c in "_-" else "_" for c in name)
        stem=Path("block01")/f"{addr:08X}_{safe}"
        ref=extract_va(data,addr,size)
        target=ROOT/"expected/NPJH50333"/stem.with_suffix(".o")
        make_mips_obj(ref,symbol,target)

        raw_obj=temp/f"{addr:08X}.o"
        flags=f.get("snc_flags",["-td=.","-O2","-G0","-Xsched=2"])
        cmd=launcher(args.compiler)+flags+["-c",str(ROOT/f["source"]),"-o",str(raw_obj)]
        cp=subprocess.run(cmd,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        if cp.returncode:
            print(f"{f['address']} compile failed\n{cp.stdout}")
            continue
        cand,rels=patch_text_relocations(raw_obj.read_bytes(),f.get("relocation_targets"),addr)
        current=ROOT/"build/NPJH50333/current"/stem.with_suffix(".o")
        make_mips_obj(cand,symbol,current)
        is_exact=(cand==ref)
        exact+=is_exact
        print(f"{f['address']} {name}: {'MATCH' if is_exact else 'NO MATCH'} {len(cand)}/{len(ref)} bytes")
    print(f"prepared objdiff objects: {exact}/{len(funcs)} exact")
    subprocess.run([sys.executable,str(ROOT/"tools/gen_objdiff.py")],cwd=ROOT,check=True)

if __name__=="__main__":
    main()
