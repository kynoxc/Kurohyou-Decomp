"""Validate that a saved matching audit still describes the current sources."""
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_FLAGS = ['-td=.', '-O2', '-G0', '-Xsched=2']
TARGET_SHA256 = 'f82d09615506fd0aaa4a792844f0fb6908b0c07e5bb4fea1c992d4c7827f1975'


def digest(data):
    return hashlib.sha256(data).hexdigest()


def manifest_digest(manifest):
    fields = ('address', 'size', 'source', 'symbol', 'snc_flags', 'relocation_targets', 'tu')
    rows = [{k: f.get(k, DEFAULT_FLAGS if k == 'snc_flags' else None) for k in fields}
            for f in manifest['functions']]
    return digest(json.dumps(rows, sort_keys=True, separators=(',', ':')).encode())


def input_hashes(manifest):
    paths = {f['source'] for f in manifest['functions']}
    paths.update(p.relative_to(ROOT).as_posix() for p in (ROOT / 'include').rglob('*.h'))
    paths.update(('tools/audit_matches.py', 'tools/kurohyou/matching.py', 'tools/audit_evidence.py'))
    return {p: digest((ROOT / p).read_bytes()) for p in sorted(paths)}


def load_verified_audit(path=None):
    path = Path(path) if path else ROOT / 'config/NPJH50333/matching_audit.json'
    audit = json.loads(path.read_text())
    manifest = json.loads((ROOT / 'matching/functions.json').read_text())
    if audit['scope'] != 'all_reconstructed_candidates' or audit['target_sha256'] != TARGET_SHA256:
        raise ValueError('progress requires a full audit of the selected retail ELF')
    if audit.get('manifest_digest') != manifest_digest(manifest):
        raise ValueError('matching manifest changed; rerun tools/audit_matches.py')
    if audit.get('inputs_sha256') != input_hashes(manifest):
        raise ValueError('source/header/auditor changed; rerun tools/audit_matches.py')
    rows = {int(f['address'], 0): f for f in audit['functions']}
    if len(rows) != len(manifest['functions']):
        raise ValueError('incomplete or duplicate audit rows')
    ranges = []
    for f in manifest['functions']:
        address, size = int(f['address'], 0), int(f['size'], 0)
        row = rows[address]
        if row['exact']:
            if not row['comparison']['exact'] or row['comparison']['reference_size'] != size:
                raise ValueError('invalid exact comparison')
            if not all(r['resolved'] for r in row['relocations']):
                raise ValueError('unresolved relocation in exact function')
            if any(address < hi and address + size > lo for lo, hi in ranges):
                raise ValueError('overlapping exact ranges')
            ranges.append((address, address + size))
    if sum(hi - lo for lo, hi in ranges) != audit['matched_code_bytes']:
        raise ValueError('incorrect audited byte total')
    return audit, manifest
