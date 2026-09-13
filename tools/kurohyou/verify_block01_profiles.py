#!/usr/bin/env python3
"""Verify the current Block 01 SNC source/profile assignments.

This is a thin wrapper around tools.kurohyou.matching. It compiles each function
with its per-function `snc_flags` from matching/functions.json and compares the
relocated .text directly against the retail EBOOT range.
"""
from __future__ import annotations
import argparse, hashlib, json, os, shutil, subprocess, sys
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from tools.kurohyou.matching import extract_va, patch_text_relocations, parse_hex, compare

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("--eboot",type=Path,required=True)
    ap.add_argument("--compiler",type=Path,default=ROOT/"matching/compilers/pspsnc_1.2.7503.0/pspsnc.exe")
    ap.add_argument("--only-unmatched",action="store_true")
    args=ap.parse_args()
    manifest=json.loads((ROOT/"matching/functions.json").read_text(encoding="utf-8"))
    build=ROOT/"matching/build/profiled_block01"
    if build.exists():shutil.rmtree(build)
    build.mkdir(parents=True)
    rows=[]
    for fn in manifest["functions"]:
        if args.only_unmatched and fn.get("block01_matching_state")=="MATCHING_EXACT":
            continue
        flags=fn.get("snc_flags",["-td=.","-O2","-G0","-Xsched=2"])
        src=ROOT/fn["source"];obj=build/(fn["address"][2:]+"_"+src.stem+".o")
        cmd=[str(args.compiler),*flags,"-c",str(src),"-o",str(obj)]
        cp=subprocess.run(cmd,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        row={"address":fn["address"],"name":fn["name"],"source":fn["source"],"flags":flags,"returncode":cp.returncode,"log":cp.stdout}
        if cp.returncode==0 and obj.exists():
            cand,rels=patch_text_relocations(obj.read_bytes(),fn.get("relocation_targets"),parse_hex(fn["address"]))
            ref=extract_va(args.eboot.read_bytes(),parse_hex(fn["address"]),parse_hex(fn["size"]))
            row["comparison"]=compare(ref,cand)
            row["relocations"]=rels
        rows.append(row)
        c=row.get("comparison",{})
        print(f'{fn["address"]} {fn["name"]}: {"MATCH" if c.get("exact") else "NO MATCH"} '
              f'{c.get("equal_words","-")}/{len(ref)//4 if "ref" in locals() else "-"} words flags={" ".join(flags)}')
    out=ROOT/"matching/BLOCK01_PROFILED_VERIFY.json"
    out.write_text(json.dumps(rows,indent=2),encoding="utf-8")
    print("Wrote",out)
if __name__=="__main__":
    main()
