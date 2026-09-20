#!/usr/bin/env python3
"""Show reproducible progress; never count hand-maintained matching labels."""
import json
from audit_evidence import ROOT, load_verified_audit


def main():
    audit, manifest = load_verified_audit()
    total = audit['total_executable_bytes']
    matched = audit['matched_code_bytes']
    print(f"Exact C/C++ functions: {audit['matching_functions']}/{audit['candidate_functions']}")
    print(f"Whole executable: {matched}/{total} bytes ({100 * matched / total:.6f}%)")
    print(f"Required for 1%: {(total + 99) // 100} bytes; remaining: {(total + 99) // 100 - matched}")
    exact = {int(f['address'], 0) for f in audit['functions'] if f['exact']}
    units = json.loads((ROOT / 'config/NPJH50333/translation_units.json').read_text())['units']
    for unit in units:
        done = [f for f in unit['functions'] if int(f['address'], 0) in exact]
        size = sum(f['size'] for f in unit['functions'])
        count = sum(f['size'] for f in done)
        print(f"{unit['class_name']}: {len(done)}/{len(unit['functions'])} inventoried functions; {count}/{size} inventoried bytes ({100*count/size:.2f}%)")
    print('Data matching: not certified. TU boundaries provisional; verification is per function.')


if __name__ == '__main__':
    main()
