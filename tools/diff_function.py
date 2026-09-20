"""Compile a manifest candidate and print its MIPS instruction differences."""
import argparse
import json
from pathlib import Path
import subprocess
import sys
from audit_evidence import ROOT, TARGET_SHA256, DEFAULT_FLAGS, digest
sys.path[:0] = [str(ROOT), str(ROOT / 'local/python')]
from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN
from tools.kurohyou.matching import extract_va, patch_text_relocations, compare


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('addresses', nargs='+', help='Hex addresses')
    ap.add_argument('--compiler', type=Path, default=ROOT / 'local/toolchain/pspsnc.exe')
    ap.add_argument('--start', type=lambda s: int(s, 0), default=0)
    ap.add_argument('--end', type=lambda s: int(s, 0), default=0xffffffff)
    ap.add_argument('--limit', type=int, default=30)
    a = ap.parse_args()
    manifest = json.loads((ROOT / 'matching/functions.json').read_text())
    elf = (ROOT / 'orig/NPJH50333_EBOOT.BIN').read_bytes()
    if digest(elf) != TARGET_SHA256:
        raise SystemExit('wrong retail ELF')
    cs = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 | CS_MODE_LITTLE_ENDIAN)
    for address in a.addresses:
        address = int(address, 16)
        f = next(f for f in manifest['functions'] if int(f['address'], 0) == address)
        obj = ROOT / f'build/diff/{address:08X}.o'
        obj.parent.mkdir(parents=True, exist_ok=True)
        if obj.exists():
            obj.unlink()
        subprocess.run([str(a.compiler.resolve()), *f.get('snc_flags', DEFAULT_FLAGS),
                        '-c', str(ROOT / f['source']), '-o', str(obj)], cwd=ROOT, check=True)
        reference = extract_va(elf, address, int(f['size'], 0))
        candidate, relocs = patch_text_relocations(obj.read_bytes(), f.get('relocation_targets'), address)
        print(f"{address:08X} {compare(reference, candidate)}")
        ref = {i.address - address: i for i in cs.disasm(reference, address)}
        got = {i.address - address: i for i in cs.disasm(candidate, address)}
        count = 0
        for off in range(a.start, min(max(len(reference), len(candidate)), a.end), 4):
            x, y = ref.get(off), got.get(off)
            if x and y and x.bytes == y.bytes:
                continue
            sx = f'{x.mnemonic} {x.op_str}' if x else '<missing>'
            sy = f'{y.mnemonic} {y.op_str}' if y else '<missing>'
            print(f'{off:04X} {sx:38} | {sy}')
            count += 1
            if count >= a.limit:
                break
        if not all(r['resolved'] for r in relocs):
            print('Unresolved relocations:', [r for r in relocs if not r['resolved']])


if __name__ == '__main__':
    main()
