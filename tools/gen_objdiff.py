#!/usr/bin/env python3
"""Generate objdiff.json for the 30 audited Block 01 units.

Run tools/prepare_objdiff.py locally first to create expected/current objects.
The public decomp.dev report covers the entire executable denominator; objdiff
is used for interactive function matching on the audited units.
"""
import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
VERSION="NPJH50333"
funcs=json.loads((ROOT/"matching/functions.json").read_text())["functions"]
units=[]
for f in sorted(funcs,key=lambda x:int(x["address"],0)):
    addr=int(f["address"],0)
    safe="".join(c if c.isalnum() or c in "_-" else "_" for c in f["name"])
    stem=f"block01/{addr:08X}_{safe}"
    u={
        "name":stem,
        "target_path":f"expected/{VERSION}/{stem}.o",
        "metadata":{"source_path":f["source"],"progress_categories":["block01"]},
    }
    cur=ROOT/f"build/{VERSION}/current/{stem}.o"
    if cur.is_file():
        u["base_path"]=str(cur.relative_to(ROOT)).replace("\\","/")
    units.append(u)
cfg={
    "min_version":"2.7.0",
    "progress_categories":[{"id":"block01","name":"Block 01 audited C/C++"}],
    "units":units,
}
(ROOT/"objdiff.json").write_text(json.dumps(cfg,indent=2)+"\n")
print(f"wrote objdiff.json ({len(units)} units)")
