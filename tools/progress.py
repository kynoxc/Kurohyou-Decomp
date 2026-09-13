#!/usr/bin/env python3
import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
layout=json.loads((ROOT/"config/NPJH50333/elf_layout.json").read_text())
funcs=json.loads((ROOT/"matching/functions.json").read_text())["functions"]
exec_bytes=sum(s["size"] for s in layout["sections"] if s["type"]==1 and (s["flags"]&4) and s["size"])
data_bytes=sum(s["size"] for s in layout["sections"] if (s["flags"]&2) and not(s["flags"]&4)
               and s["size"] and s["type"] in (1,8))
exact=[f for f in funcs if f.get("block01_matching_state")=="MATCHING_EXACT"]
matched=sum(int(f["size"],0) for f in exact)
tracked=sum(int(f["size"],0) for f in funcs)
print("Kurohyou NPJH50333 decomp progress")
print("="*42)
print(f"Block 01 exact C/C++ : {len(exact)}/{len(funcs)}")
print(f"Audited code bytes   : {matched}/{tracked} exact")
print(f"Whole executable     : {matched}/{exec_bytes} ({matched/exec_bytes*100:.6f}%)")
print(f"Data/rodata/bss      : 0/{data_bytes} (0.000000%)")
print("Only byte-exact reconstructed C/C++ counts as matched code.")
