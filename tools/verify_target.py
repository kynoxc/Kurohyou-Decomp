#!/usr/bin/env python3
from pathlib import Path
import argparse,hashlib
EXPECTED="f82d09615506fd0aaa4a792844f0fb6908b0c07e5bb4fea1c992d4c7827f1975"
ap=argparse.ArgumentParser()
ap.add_argument("eboot",nargs="?",default="orig/NPJH50333_EBOOT.BIN")
args=ap.parse_args()
p=Path(args.eboot)
if not p.is_file():
    raise SystemExit(f"missing {p}")
h=hashlib.sha256(p.read_bytes()).hexdigest()
print("sha256:",h)
if h!=EXPECTED:
    raise SystemExit("WRONG TARGET")
print("TARGET VERIFIED")
