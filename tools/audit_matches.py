"""Compile reconstructed functions and certify exact text against the fixed retail ELF."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
from datetime import datetime, timezone

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
from tools.kurohyou.matching import extract_va,patch_text_relocations,compare,executable_sections
from audit_evidence import manifest_digest,input_hashes
EXPECTED='f82d09615506fd0aaa4a792844f0fb6908b0c07e5bb4fea1c992d4c7827f1975'
def sha(data):return hashlib.sha256(data).hexdigest()

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--compiler',type=Path,required=True)
    ap.add_argument('--only',nargs='*',help='Hex function addresses; a subset audit cannot replace global progress')
    ap.add_argument('--output',type=Path)
    a=ap.parse_args()
    if a.output is None:
        a.output=ROOT/('local/audit-subset.json' if a.only else 'config/NPJH50333/matching_audit.json')
    eboot=(ROOT/'orig/NPJH50333_EBOOT.BIN').read_bytes()
    if sha(eboot)!=EXPECTED:raise SystemExit('Wrong reference ELF: target verification failed')
    manifest=json.loads((ROOT/'matching/functions.json').read_text())
    functions=manifest['functions'];selected={int(x,16) for x in a.only} if a.only else None
    build=ROOT/'build/matching';build.mkdir(parents=True,exist_ok=True)
    rows=[];covered=[]
    for f in functions:
        address=int(f['address'],0);size=int(f['size'],0)
        if selected is not None and address not in selected:continue
        source=ROOT/f['source'];flags=f.get('snc_flags',['-td=.','-O2','-G0','-Xsched=2'])
        obj=build/f'{address:08X}.o'
        # Remove only this prior compiler output, never a build tree. No stale-object certification.
        if obj.exists():obj.unlink()
        command=[str(a.compiler.resolve()),*flags,'-c',str(source),'-o',str(obj)]
        cp=subprocess.run(command,cwd=ROOT,capture_output=True,text=True)
        row=dict(address=f['address'],name=f['name'],source=f['source'],source_sha256=sha(source.read_bytes()),
                 tu=f.get('tu','unassigned'),flags=flags,returncode=cp.returncode,log=cp.stdout+cp.stderr,exact=False)
        if cp.returncode==0 and obj.exists():
            candidate,relocations=patch_text_relocations(obj.read_bytes(),f.get('relocation_targets'),address)
            reference=extract_va(eboot,address,size)
            row.update(comparison=compare(reference,candidate),relocations=relocations,
                       reference_sha256=sha(reference),candidate_sha256=sha(candidate),object_sha256=sha(obj.read_bytes()))
            row['exact']=row['comparison']['exact'] and all(r.get('resolved',False) for r in relocations)
            # Switch tables also require independent data/target verification before certification.
            if any(r['symbol'].startswith('$LSW') for r in relocations):
                row['exact']=False;row['certification_blocker']='Switch table relocation requires table-byte audit'
            if row['exact']:
                for lo,hi in covered:
                    if address<hi and address+size>lo:raise RuntimeError('Overlapping exact function ranges')
                covered.append((address,address+size))
        rows.append(row)
        c=row.get('comparison',{})
        print(f"{f['address']} {'EXACT' if row['exact'] else 'NON_MATCHING'} {c.get('equal_words',0)}/{size//4} {f['name']}",flush=True)
    total=sum(s.size for s in executable_sections(eboot));matched=sum(hi-lo for lo,hi in covered)
    report=dict(schema=1,target_sha256=EXPECTED,compiler_sha256=sha(a.compiler.read_bytes()),
                manifest_digest=manifest_digest(manifest),inputs_sha256=input_hashes(manifest),
                compiler_components_sha256={p.name:sha(p.read_bytes()) for p in sorted(a.compiler.parent.glob('*.exe'))},
                utc=datetime.now(timezone.utc).isoformat(),scope='subset' if selected is not None else 'all_reconstructed_candidates',
                counted='unique byte-exact reconstructed C/C++ function ranges; assembly and generated pseudocode excluded',
                total_executable_bytes=total,matched_code_bytes=matched,code_percent=100*matched/total,
                matching_functions=sum(r['exact'] for r in rows),candidate_functions=len(rows),functions=rows)
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_text(json.dumps(report,indent=2)+'\n')
    print(f"Verified {matched}/{total} code bytes = {report['code_percent']:.6f}%")
    return 0 if all(r['exact'] for r in rows) else 1
if __name__=='__main__':sys.exit(main())
