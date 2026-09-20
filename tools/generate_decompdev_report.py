#!/usr/bin/env python3
"""Generate a public objdiff Report-v2 compatible progress report.

This report is generated from a current source-validated audit, including local
uncommitted work. It contains no retail bytes and does not upload anything.

Until the full TU/object pipeline is automated in CI, this is the bootstrap
report consumed by decomp.dev. Overall CODE progress uses every executable
section in the verified ELF as the denominator. Report units are function
verification units, not complete original translation units.
"""
from __future__ import annotations
import json
from audit_evidence import load_verified_audit
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
VERSION = "NPJH50333"

def u64(n:int)->str:
    # Proto3 JSON represents uint64 as decimal strings.
    return str(int(n))

def pct(a:int,b:int)->float:
    return 0.0 if not b else (a/b)*100.0

def code_measures(total:int, matched:int, complete:int=0, total_units:int=1, complete_units:int=0):
    return {
        "fuzzy_match_percent": pct(matched,total),
        "total_code": u64(total),
        "matched_code": u64(matched),
        "matched_code_percent": pct(matched,total),
        "complete_code": u64(complete),
        "complete_code_percent": pct(complete,total),
        "total_units": total_units,
        "complete_units": complete_units,
    }

def data_measures(total:int, matched:int=0, complete:int=0, total_units:int=1, complete_units:int=0):
    return {
        "total_data": u64(total),
        "matched_data": u64(matched),
        "matched_data_percent": pct(matched,total),
        "complete_data": u64(complete),
        "complete_data_percent": pct(complete,total),
        "total_units": total_units,
        "complete_units": complete_units,
    }

def main():
    layout=json.loads((ROOT/f"config/{VERSION}/elf_layout.json").read_text())
    audit,manifest=load_verified_audit()
    if layout['sha256'] != audit['target_sha256']:
        raise ValueError('ELF layout and audit target differ')
    verified={int(f["address"],0) for f in audit["functions"] if f["exact"]}
    funcs=sorted(manifest["functions"],key=lambda f:int(f["address"],0))
    exec_secs=[s for s in layout["sections"] if s["type"]==1 and (s["flags"]&4) and s["size"]]
    data_secs=[s for s in layout["sections"]
               if (s["flags"]&2) and not(s["flags"]&4) and s["size"] and s["type"] in (1,8)]

    total_code=sum(int(s["size"]) for s in exec_secs)
    if total_code != audit['total_executable_bytes']:
        raise ValueError('ELF layout and audit code totals differ')
    total_data=sum(int(s["size"]) for s in data_secs)

    units=[]
    matched_total=0
    complete_total=0
    known_total=0

    # These are function verification units, not proof of original compiler TU boundaries.
    # Keep every unknown executable range in the denominator.
    for sec in sorted(exec_secs,key=lambda s:s["addr"]):
        lo=int(sec["addr"]); hi=lo+int(sec["size"])
        inside=[f for f in funcs if lo <= int(f["address"],0) and int(f["address"],0)+int(f["size"],0) <= hi]
        cur=lo
        for f in inside:
            addr=int(f["address"],0); size=int(f["size"],0)
            if addr < cur: raise ValueError("overlapping candidate function ranges")
            if addr>cur:
                gap=addr-cur
                units.append({
                    "name":f"unassigned/code_{cur:08X}_{addr:08X}",
                    "measures":code_measures(gap,0),
                    "sections":[{"name":".text","size":u64(gap),"fuzzy_match_percent":0.0}],
                    "functions":[],
                    "metadata":{"complete":False,"progress_categories":["unassigned"],"auto_generated":True},
                })
            exact=addr in verified
            matched=size if exact else 0
            matched_total+=matched
            complete_total+=matched
            known_total+=size
            sim=100.0 if exact else 0.0
            units.append({
                "name":f"{f.get('tu','legacy')}/{addr:08X}_{f['name']}",
                "measures":code_measures(size,matched,matched,1,1 if exact else 0),
                "sections":[{"name":".text","size":u64(size),"fuzzy_match_percent":sim}],
                "functions":[{
                    "name":f.get("symbol",f["name"]),
                    "size":u64(size),
                    "fuzzy_match_percent":sim,
                    "metadata":{"demangled_name":f["name"],"virtual_address":u64(addr)},
                    "address":u64(0),
                }],
                "metadata":{
                    "complete":exact,
                    "source_path":f["source"],
                    "progress_categories":["block01"],
                },
            })
            cur=addr+size
        if cur<hi:
            gap=hi-cur
            units.append({
                "name":f"unassigned/code_{cur:08X}_{hi:08X}",
                "measures":code_measures(gap,0),
                "sections":[{"name":".text","size":u64(gap),"fuzzy_match_percent":0.0}],
                "functions":[],
                "metadata":{"complete":False,"progress_categories":["unassigned"],"auto_generated":True},
            })

    # Data/rodata/bss are all currently unmatched, but counted honestly.
    for sec in sorted(data_secs,key=lambda s:s["addr"]):
        size=int(sec["size"]); addr=int(sec["addr"])
        units.append({
            "name":f"unassigned/data_section_{sec['index']:02d}_{addr:08X}",
            "measures":data_measures(size,0),
            "sections":[{
                "name":".bss" if sec["type"]==8 else ".data",
                "size":u64(size),
                "fuzzy_match_percent":0.0,
            }],
            "functions":[],
            "metadata":{"complete":False,"progress_categories":["data"],"auto_generated":True},
        })

    unassigned_code=total_code-known_total
    block01_meas=code_measures(known_total,matched_total,complete_total,len(funcs),
                               len(verified))
    unassigned_meas=code_measures(unassigned_code,0,0,
                                  sum(1 for u in units if "unassigned" in u.get("metadata",{}).get("progress_categories",[])),0)
    data_meas=data_measures(total_data,0,0,len(data_secs),0)

    total_units=len(units)
    complete_units=sum(1 for u in units if u.get("metadata",{}).get("complete"))
    report={
        "version":2,
        "measures":{
            "fuzzy_match_percent":pct(matched_total,total_code),
            "total_code":u64(total_code),
            "matched_code":u64(matched_total),
            "matched_code_percent":pct(matched_total,total_code),
            "total_data":u64(total_data),
            "matched_data":u64(0),
            "matched_data_percent":0.0 if total_data else 100.0,
            "complete_code":u64(complete_total),
            "complete_code_percent":pct(complete_total,total_code),
            "complete_data":u64(0),
            "complete_data_percent":0.0 if total_data else 100.0,
            "total_units":total_units,
            "complete_units":complete_units,
        },
        "units":units,
        "categories":[
            {"id":"block01","name":"Audited C/C++ function ranges","measures":block01_meas},
            {"id":"unassigned","name":"Unassigned executable code","measures":unassigned_meas},
            {"id":"data","name":"Data / rodata / bss","measures":data_meas},
        ],
    }
    out=ROOT/"build/publish/report.json"
    out.parent.mkdir(parents=True,exist_ok=True)
    out.write_text(json.dumps(report,separators=(",",":"))+"\n",encoding="utf-8")

    print(f"wrote {out.relative_to(ROOT)}")
    print(f"code: {matched_total}/{total_code} ({pct(matched_total,total_code):.6f}%)")
    print(f"data: 0/{total_data} (0.000000%)")
    print(f"units: {total_units}, complete: {complete_units}")

if __name__=="__main__":
    main()
