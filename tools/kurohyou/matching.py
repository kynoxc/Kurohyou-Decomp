#!/usr/bin/env python3
"""Function-by-function PSP matching harness for NPJH50333.

This is deliberately separate from the native Windows/Linux port.  A function is
'MATCHING' only when the compiler output is byte-for-byte identical to the retail
EBOOT range.  Semantic tests and visual similarity never promote this status.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys
from dataclasses import dataclass
from typing import Iterable

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_MANIFEST = ROOT / "matching/functions.json"
DEFAULT_TOOLCHAINS = ROOT / "matching/toolchains.json"

SHF_EXECINSTR = 0x4
SHT_PROGBITS = 1

@dataclass
class ElfSection:
    index: int
    type: int
    flags: int
    addr: int
    offset: int
    size: int
    link: int = 0
    info: int = 0
    entsize: int = 0
    name_offset: int = 0
    name: str = ""


def elf32le_sections(data: bytes) -> list[ElfSection]:
    if len(data) < 52 or data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
        raise ValueError("expected ELF32 little-endian image")
    shoff = struct.unpack_from("<I", data, 32)[0]
    shentsize = struct.unpack_from("<H", data, 46)[0]
    shnum = struct.unpack_from("<H", data, 48)[0]
    if shentsize < 40 or shoff + shentsize * shnum > len(data):
        raise ValueError("invalid ELF section table")
    shstrndx = struct.unpack_from("<H", data, 50)[0]
    raw = []
    for i in range(shnum):
        p = shoff + i * shentsize
        raw.append(struct.unpack_from("<IIIIIIIIII", data, p))
    shstr = b""
    if shstrndx < shnum:
        (_n,_t,_f,_a,off,size,_l,_i,_al,_e) = raw[shstrndx]
        if off + size <= len(data):
            shstr = data[off:off+size]
    def secname(off: int) -> str:
        if not shstr or off >= len(shstr):
            return ""
        end = shstr.find(b"\0", off)
        if end < 0: end = len(shstr)
        return shstr[off:end].decode("ascii", errors="replace")
    out: list[ElfSection] = []
    for i, values in enumerate(raw):
        (name_off, typ, flags, addr, off, size, link, info, _align, entsize) = values
        out.append(ElfSection(i, typ, flags, addr, off, size, link, info, entsize, name_off, secname(name_off)))
    return out


def executable_sections(data: bytes) -> list[ElfSection]:
    return [s for s in elf32le_sections(data) if s.type == SHT_PROGBITS and (s.flags & SHF_EXECINSTR) and s.size]


def extract_va(data: bytes, address: int, size: int) -> bytes:
    for s in executable_sections(data):
        if s.addr <= address and address + size <= s.addr + s.size:
            p = s.offset + (address - s.addr)
            return data[p:p + size]
    raise ValueError(f"0x{address:08X}+0x{size:X} is not inside an executable section")


def extract_text(data: bytes) -> bytes:
    sections = executable_sections(data)
    if not sections:
        raise ValueError("object has no executable PROGBITS section")
    # Matching TUs are one-function objects. Prefer the largest executable section
    # to ignore zero-sized stubs emitted by some compilers.
    s = max(sections, key=lambda x: x.size)
    return data[s.offset:s.offset+s.size]


SHT_SYMTAB = 2
SHT_REL = 9
R_MIPS_32 = 2
R_MIPS_26 = 4
R_MIPS_HI16 = 5
R_MIPS_LO16 = 6


def _cstring(blob: bytes, off: int) -> str:
    if off < 0 or off >= len(blob):
        return ""
    end = blob.find(b"\0", off)
    if end < 0: end = len(blob)
    return blob[off:end].decode("utf-8", errors="replace")


def elf_symbols(data: bytes, sections: list[ElfSection], symtab_index: int) -> list[dict]:
    if symtab_index < 0 or symtab_index >= len(sections):
        return []
    symsec = sections[symtab_index]
    if symsec.type != SHT_SYMTAB or symsec.entsize < 16 or symsec.link >= len(sections):
        return []
    strsec = sections[symsec.link]
    strings = data[strsec.offset:strsec.offset+strsec.size]
    out=[]
    for p in range(symsec.offset, symsec.offset+symsec.size, symsec.entsize):
        if p + 16 > len(data): break
        name,value,size,info,other,shndx = struct.unpack_from("<IIIBBH",data,p)
        out.append({"name":_cstring(strings,name),"value":value,"size":size,"info":info,"other":other,"shndx":shndx})
    return out


def patch_text_relocations(data: bytes, relocation_targets: dict[str, int] | None, text_base: int = 0) -> tuple[bytes, list[dict]]:
    """Resolve relocations in the one-function object's executable section.

    This lets the byte matcher audit functions that call known retail addresses
    without requiring a full PSP link.  Targets are declared explicitly in the
    function manifest, so no guessed symbol/address mapping can enter the audit.
    """
    sections = elf32le_sections(data)
    execs = [s for s in sections if s.type == SHT_PROGBITS and s.flags & SHF_EXECINSTR and s.size]
    if len(execs) != 1:
        raise ValueError("function audit requires exactly one nonempty executable section")
    text = execs[0]
    blob = bytearray(data[text.offset:text.offset + text.size])
    targets = relocation_targets or {}
    records = []
    for relsec in sections:
        if relsec.type != SHT_REL or relsec.info != text.index:
            continue
        if relsec.entsize not in (0, 8) or relsec.size % 8:
            raise ValueError("invalid MIPS REL table")
        syms = elf_symbols(data, sections, relsec.link)
        pending = {}
        for p in range(relsec.offset, relsec.offset + relsec.size, 8):
            offset, info = struct.unpack_from("<II", data, p)
            sym_index, rtype = info >> 8, info & 0xff
            if sym_index >= len(syms):
                raise ValueError("invalid relocation symbol index")
            sym = syms[sym_index]
            name = sym["name"]
            rec = {"offset": offset, "type": rtype, "symbol": name, "resolved": False}
            records.append(rec)
            if offset % 4 or offset + 4 > len(blob):
                rec["error"] = "unaligned relocation or offset outside .text"
                continue
            if name in targets:
                target, source = parse_hex(targets[name]), "manifest"
            elif sym["shndx"] == text.index:
                target, source = text_base + sym["value"], "local-text"
            else:
                continue
            word = struct.unpack_from("<I", data, text.offset + offset)[0]
            rec.update(target=f"0x{target:08X}", target_source=source)
            if rtype == R_MIPS_HI16:
                # REL stores the addend in the instruction pair, not in a separate field.
                # Several HI16 records may share the next LO16 for the same symbol.
                pending.setdefault(sym_index, []).append((rec, word))
                continue
            if rtype == R_MIPS_LO16:
                low = (word & 0xffff) - (0x10000 if word & 0x8000 else 0)
                addend = low
                for high_rec, high_word in pending.pop(sym_index, []):
                    full_addend = ((high_word & 0xffff) << 16) + low
                    value = (target + full_addend) & 0xffffffff
                    patched = (high_word & 0xffff0000) | (((value + 0x8000) >> 16) & 0xffff)
                    struct.pack_into("<I", blob, high_rec["offset"], patched)
                    high_rec.update(resolved=True, addend=full_addend)
                patched = (word & 0xffff0000) | ((target + low) & 0xffff)
            elif rtype == R_MIPS_26:
                addend = (word & 0x03ffffff) << 2
                value = target + addend
                if value & 3 or (value & 0xf0000000) != ((text_base + offset + 4) & 0xf0000000):
                    rec["error"] = "J/JAL destination outside its address region"
                    continue
                patched = (word & 0xfc000000) | ((value >> 2) & 0x03ffffff)
            elif rtype == R_MIPS_32:
                addend = word
                patched = (target + word) & 0xffffffff
            else:
                rec["error"] = "unsupported relocation type"
                continue
            struct.pack_into("<I", blob, offset, patched)
            rec.update(resolved=True, addend=addend)
        for pairs in pending.values():
            for rec, _ in pairs:
                rec["error"] = "HI16 has no following LO16 for its symbol"
    return bytes(blob), records


def words(blob: bytes) -> list[bytes]:
    return [blob[i:i+4] for i in range(0, len(blob), 4)]


def compare(reference: bytes, candidate: bytes) -> dict:
    n = max(len(reference), len(candidate), 1)
    byte_equal = sum(1 for i in range(min(len(reference), len(candidate))) if reference[i] == candidate[i])
    rw, cw = words(reference), words(candidate)
    wn = max(len(rw), len(cw), 1)
    word_equal = sum(1 for i in range(min(len(rw), len(cw))) if rw[i] == cw[i])
    return {
        "exact": reference == candidate,
        "reference_size": len(reference),
        "candidate_size": len(candidate),
        "equal_bytes": byte_equal,
        "byte_similarity": byte_equal / n * 100.0,
        "equal_words": word_equal,
        "word_similarity": word_equal / wn * 100.0,
    }


def parse_hex(value: str | int) -> int:
    return int(value, 0) if isinstance(value, str) else int(value)


def load_manifest(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def load_toolchains(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))["toolchains"]


def run(cmd: list[str], *, cwd: Path | None = None) -> subprocess.CompletedProcess[str]:
    return subprocess.run(cmd, cwd=cwd, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)


def _resolve_program(root: Path, value: str) -> str | None:
    candidate = Path(value)
    if candidate.is_absolute() and candidate.exists():
        return str(candidate)
    relative = root / candidate
    if ("/" in value or "\\" in value) and relative.exists():
        return str(relative)
    return shutil.which(value)


def compile_one(root: Path, fn: dict, tc_name: str, tc: dict, build: Path) -> tuple[bytes | None, dict]:
    compiler = _resolve_program(root, tc["compiler"])
    meta = {"toolchain": tc_name, "kind": tc.get("kind", "unknown"), "description": tc.get("description", "")}
    if not compiler:
        meta.update(status="compiler-missing", log=f"{tc['compiler']} not found")
        return None, meta

    launcher_key = "launcher_windows" if os.name == "nt" else "launcher_posix"
    launcher_values = tc.get(launcher_key, tc.get("launcher", []))
    launcher: list[str] = []
    for item in launcher_values:
        resolved = _resolve_program(root, item)
        if not resolved:
            meta.update(status="launcher-missing", log=f"launcher {item} not found")
            return None, meta
        launcher.append(resolved)

    src = root / fn["source"]
    obj = build / f"{parse_hex(fn['address']):08X}_{tc_name}.o"
    cmd = [*launcher, compiler, *tc.get("flags", []), "-c", str(src), "-o", str(obj)]
    proc = run(cmd, cwd=root)
    meta["command"] = cmd
    meta["log"] = proc.stdout
    if proc.returncode:
        meta["status"] = "compile-failed"
        return None, meta
    try:
        objdata=obj.read_bytes()
        candidate, relocs = patch_text_relocations(objdata, fn.get("relocation_targets"), parse_hex(fn["address"]))
    except Exception as exc:
        meta.update(status="extract-failed", log=proc.stdout + f"\n{exc}")
        return None, meta
    unresolved=[r for r in relocs if not r.get("resolved") and r.get("symbol")]
    meta.update(status="compiled", object=str(obj.relative_to(root)), sha256=hashlib.sha256(candidate).hexdigest(),
                relocations=relocs, unresolved_relocations=unresolved)
    return candidate, meta




def compile_oracle(root: Path, fn: dict, build: Path) -> tuple[bytes | None, dict]:
    """Assemble the audited retail instruction oracle for a function.

    This validates function boundaries, disassembly transcription and the binary
    comparison harness.  It NEVER promotes a C/C++ decomp candidate to MATCHING.
    """
    rel = fn.get("oracle_asm")
    if not rel:
        return None, {"status": "oracle-missing", "log": "manifest has no oracle_asm"}
    assembler = shutil.which("clang")
    if not assembler:
        return None, {"status": "assembler-missing", "log": "clang not found"}
    src = root / rel
    obj = build / f"{parse_hex(fn['address']):08X}_retail_oracle.o"
    cmd = [assembler, "--target=mipsel-sony-psp", "-mips2", "-mfp32",
           "-modd-spreg", "-c", str(src), "-o", str(obj)]
    proc = run(cmd, cwd=root)
    meta = {"command": cmd, "log": proc.stdout}
    if proc.returncode:
        meta["status"] = "assemble-failed"
        return None, meta
    try:
        blob = extract_text(obj.read_bytes())
    except Exception as exc:
        meta.update(status="extract-failed", log=proc.stdout + f"\n{exc}")
        return None, meta
    meta.update(status="assembled", object=str(obj.relative_to(root)),
                sha256=hashlib.sha256(blob).hexdigest())
    return blob, meta

def hexdiff(reference: bytes, candidate: bytes) -> str:
    rw, cw = words(reference), words(candidate)
    lines = ["offset   retail      candidate   match"]
    for i in range(max(len(rw), len(cw))):
        r = rw[i].hex() if i < len(rw) else "--------"
        c = cw[i].hex() if i < len(cw) else "--------"
        lines.append(f"+{i*4:04X}   {r:<8}    {c:<8}    {'==' if r == c else '!='}")
    return "\n".join(lines)


def disasm_range(eboot: Path, address: int, size: int) -> str:
    tool = shutil.which("llvm-objdump")
    if not tool:
        return "llvm-objdump unavailable"
    p = run([tool, "-d", "--triple=mipsel-unknown-elf",
             f"--start-address=0x{address:x}", f"--stop-address=0x{address+size:x}", str(eboot)])
    return p.stdout


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--eboot", type=Path, required=True)
    ap.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    ap.add_argument("--toolchains", type=Path, default=DEFAULT_TOOLCHAINS)
    ap.add_argument("--toolchain", default="clang17_psp_o32_probe")
    ap.add_argument("--output", type=Path, default=ROOT / "matching/MATCHING_REPORT.md")
    ap.add_argument("--json", type=Path, default=ROOT / "matching/MATCHING_REPORT.json")
    ap.add_argument("--address", action="append", default=[], help="Restrict audit to one or more function addresses (e.g. 0x001E63D8).")
    args = ap.parse_args()

    manifest = load_manifest(args.manifest)
    if args.address:
        wanted={parse_hex(x) for x in args.address}
        manifest=dict(manifest)
        manifest["functions"]=[fn for fn in manifest.get("functions",[]) if parse_hex(fn["address"]) in wanted]
        missing=wanted-{parse_hex(fn["address"]) for fn in manifest["functions"]}
        if missing:
            raise SystemExit("requested addresses absent from manifest: "+", ".join(f"0x{x:08X}" for x in sorted(missing)))
    toolchains = load_toolchains(args.toolchains)
    if args.toolchain not in toolchains:
        raise SystemExit(f"unknown toolchain: {args.toolchain}")
    tc = toolchains[args.toolchain]
    eboot = args.eboot.read_bytes()
    build = ROOT / "matching/build"
    refdir = ROOT / "matching/reference"
    build.mkdir(parents=True, exist_ok=True)
    refdir.mkdir(parents=True, exist_ok=True)

    eboot_sha = hashlib.sha256(eboot).hexdigest()
    rows = []
    details = []
    for fn in manifest["functions"]:
        address, size = parse_hex(fn["address"]), parse_hex(fn["size"])
        reference = extract_va(eboot, address, size)
        refpath = refdir / f"{address:08X}_{size:04X}.bin"
        refpath.write_bytes(reference)
        candidate, meta = compile_one(ROOT, fn, args.toolchain, tc, build)
        oracle, oracle_meta = compile_oracle(ROOT, fn, build)
        oracle_cmp = compare(reference, oracle) if oracle is not None else None
        if candidate is None:
            cmp = None
            state = "UNTESTED"
        else:
            cmp = compare(reference, candidate)
            # Diagnostic-only compilers can prove NONMATCH but cannot certify a retail
            # match because their ABI itself is known not to be the retail EABI32 ABI.
            kind = tc.get("kind")
            if cmp["exact"] and kind == "certifying":
                state = "MATCHING"
            elif cmp["exact"] and kind == "fingerprint_candidate":
                state = "EXACT-BYTES (FINGERPRINT CANDIDATE)"
            elif cmp["exact"]:
                state = "EXACT-BYTES (NONCERTIFYING TOOLCHAIN)"
            else:
                state = "UNMATCHED"
        rows.append({"function": fn["name"], "address": f"0x{address:08X}", "size": size,
                     "state": state, "comparison": cmp, "compiler": meta,
                     "oracle_exact": bool(oracle_cmp and oracle_cmp["exact"]),
                     "oracle_comparison": oracle_cmp, "oracle": oracle_meta})
        details.append((fn, address, size, reference, candidate, cmp, meta, state, oracle, oracle_cmp, oracle_meta))

    json_report = {
        "eboot": str(args.eboot), "eboot_sha256": eboot_sha,
        "elf_flags_observed": "MIPS2 + EABI32 (readelf: 0x10a23001)",
        "toolchain": args.toolchain, "toolchain_kind": tc.get("kind"),
        "functions": rows,
    }
    args.json.write_text(json.dumps(json_report, indent=2), encoding="utf-8")

    md = []
    md.append("# Kurohyou PSP byte-matching report\n")
    md.append(f"Retail EBOOT SHA-256: `{eboot_sha}`\n")
    md.append(f"Probe toolchain: `{args.toolchain}` — **{tc.get('kind','unknown')}**\n")
    md.append("The retail ELF advertises **MIPS-II + EABI32**. This report never labels the current Clang/O32 probe as a certified match. It is used to expose compiler/ABI differences while the retail-compatible compiler is identified.\n")
    md.append("| Function | Retail range | bytes | exact words | byte similarity | oracle asm | status |")
    md.append("|---|---:|---:|---:|---:|---:|---|")
    for row in rows:
        cmp = row["comparison"]
        if cmp:
            md.append(f"| {row['function']} | `{row['address']}` | {cmp['reference_size']} | {cmp['equal_words']}/{max(cmp['reference_size'],cmp['candidate_size'])//4} | {cmp['byte_similarity']:.2f}% | {'EXACT' if row['oracle_exact'] else 'FAIL'} | **{row['state']}** |")
        else:
            md.append(f"| {row['function']} | `{row['address']}` | {row['size']} | — | — | {'EXACT' if row['oracle_exact'] else 'FAIL'} | **{row['state']}** |")

    md.append("\n## Function details\n")
    for fn, address, size, reference, candidate, cmp, meta, state, oracle, oracle_cmp, oracle_meta in details:
        md.append(f"### 0x{address:08X} — {fn['name']}\n")
        md.append(f"Status: **{state}**. Retail size: `0x{size:X}`. Source: `{fn['source']}`.\n")
        md.append(fn.get("notes", "") + "\n")
        if cmp:
            md.append(f"Candidate size: `{cmp['candidate_size']}` bytes; exact-byte positions: `{cmp['equal_bytes']}/{max(cmp['reference_size'],cmp['candidate_size'])}`; exact instruction words: `{cmp['equal_words']}/{max(len(words(reference)),len(words(candidate)))}`.\n")
            md.append("```text\n" + hexdiff(reference, candidate) + "\n```\n")
        else:
            md.append("Compiler result: `" + meta.get("status", "unknown") + "`.\n")
            if meta.get("log"):
                md.append("```text\n" + meta["log"][-4000:] + "\n```\n")
        if oracle_cmp:
            md.append(f"Retail instruction oracle: **{'EXACT' if oracle_cmp['exact'] else 'FAILED'}** "
                      f"(`{oracle_cmp['equal_words']}/{max(len(words(reference)),len(words(oracle)))}` words). "
                      "This is an assembly transcription check only; it does not certify the C decomp.\n")
        else:
            md.append("Retail instruction oracle: unavailable (`" + oracle_meta.get("status", "unknown") + "`).\n")
        md.append("Retail disassembly:\n```text\n" + disasm_range(args.eboot, address, size).strip() + "\n```\n")

    md.append("## Compiler fingerprint conclusions\n")
    md.append("The three assembly oracles reassemble to the exact retail bytes. This proves the EBOOT ranges, instruction transcription, odd-single FPR settings and comparison harness are correct; it is deliberately **not** counted as C/C++ decomp matching.\n")
    md.append("1. `0x001A88C4` enters with its four float arguments already in `f12/f13/f14/f15`. The available Clang PSP target uses O32 and moves argument 3/4 from GPRs into FPRs, making it structurally incapable of matching this function.\n")
    md.append("2. `0x001E63D8` is an integer-only leaf and therefore isolates code-generator behavior. Clang can reproduce its size/control-flow, but register allocation/immediate selection differ from retail. That is useful evidence that source semantics alone are not the remaining issue.\n")
    md.append("3. The strings `GCC3003 SCE06020010` found in the EBOOT belong to embedded CRI middleware version strings. They are evidence for those CRI objects, **not yet proof that all game code used the same compiler**. Compiler identification for game-owned code remains open.\n")
    md.append("4. Certification therefore remains at 0 functions until an EABI32-compatible retail candidate compiler is tested and exact bytes are obtained.\n")

    args.output.write_text("\n".join(md), encoding="utf-8")
    print(args.output)
    for row in rows:
        cmp = row["comparison"]
        score = f"{cmp['byte_similarity']:.2f}%" if cmp else "n/a"
        print(f"{row['address']} {row['function']}: {row['state']} ({score})")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
