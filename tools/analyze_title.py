"""Generate local Ghidra seeds and public RTTI evidence from the verified ELF."""
import json
from pathlib import Path
import re
import struct
import sys
from audit_evidence import ROOT, TARGET_SHA256, digest
sys.path.insert(0, str(ROOT))
from tools.kurohyou.matching import elf32le_sections, executable_sections, extract_va


def main():
    data = (ROOT / 'orig/NPJH50333_EBOOT.BIN').read_bytes()
    if digest(data) != TARGET_SHA256:
        raise SystemExit('incorrect EBOOT hash')
    sections = elf32le_sections(data)
    allocated = [s for s in sections if s.type == 1 and s.flags & 2]
    code = executable_sections(data)
    lo, hi = 0x369000, 0x38a000
    seeds = {hi}
    for section in code:
        for offset in range(0, section.size - 3, 4):
            word = struct.unpack_from('<I', data, section.offset + offset)[0]
            if word >> 26 == 3:  # JAL; indirect-only leaf methods may be missing.
                pc = section.addr + offset
                target = ((pc + 4) & 0xf0000000) | ((word & 0x3ffffff) << 2)
                if lo <= target < hi:
                    seeds.add(target)
    for section in allocated:
        if section.flags & 4:
            continue
        for offset in range(0, section.size - 3, 4):
            value = struct.unpack_from('<I', data, section.offset + offset)[0]
            if lo <= value < hi and not value & 3:
                word = struct.unpack('<I', extract_va(data, value, 4))[0]
                if word >> 16 == 0x27bd and word & 0x8000:  # addiu sp,sp,negative
                    seeds.add(value)
    out = ROOT / 'local/title-seeds.tsv'
    out.parent.mkdir(exist_ok=True)
    out.write_text(''.join(f'{a:08X}\n' for a in sorted(seeds)))
    rows = []
    for section in allocated:
        if section.flags & 4:
            continue
        payload = data[section.offset:section.offset + section.size]
        for match in re.finditer(rb'SceneTitle[A-Za-z0-9_]*\x00', payload):
            address = section.addr + match.start()
            references = []
            for candidate in allocated:
                if candidate.flags & 4:
                    continue
                for off in range(0, candidate.size - 3, 4):
                    if struct.unpack_from('<I', data, candidate.offset + off)[0] == address:
                        start = max(0, off - 32)
                        size = min(48, candidate.size - start) // 4
                        words = struct.unpack_from('<' + 'I' * size, data, candidate.offset + start)
                        references.append(dict(address=f'0x{candidate.addr + off:08X}',
                                               context_start=f'0x{candidate.addr + start:08X}',
                                               words=[f'0x{x:08X}' for x in words]))
            rows.append(dict(name=match.group()[:-1].decode(), string_address=f'0x{address:08X}', references=references))
    (ROOT / 'config/NPJH50333/title_rtti.json').write_text(json.dumps(rows, indent=2) + '\n')
    print(f'{len(seeds)-1} candidate entries; {len(rows)} title RTTI names; boundaries require manual audit')


if __name__ == '__main__':
    main()
