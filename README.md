# Kurohyou-Decomp

Matching decompilation of **Kurohyou: Ryu ga Gotoku Shinsho** for Sony PSP
(`NPJH50333`).

Repository target: `kynoxc/Kurohyou-Decomp`.

## Current status

- Audited Block 01 functions: **30**
- Byte-exact C/C++ functions: **27/30**
- Byte-exact reconstructed code: **1,992 bytes**
- Total executable code in the verified retail ELF: **6,040,516 bytes**
- Whole-program strict code progress: **0.032977%**
- Data / rodata / bss progress: **0 / 1,092,989 bytes**
- Retail compiler used by current matches: **SN Systems pspsnc 1.2.7503.0**

The three remaining Block 01 functions are:

- `0x001937A4` — `RetailAngleScalarSetTarget`
- `0x001E2810` — `CPlayerController_ActorPredicate`
- `0x003748EC` — `SceneTitleMainmenu_BindRows`

## Matching definition

`MATCHING_EXACT` means reconstructed C/C++ compiled with the recorded SNC profile,
with declared relocations resolved to the audited retail addresses, produces the
same machine-code bytes as the retail EBOOT range.

Assembly oracles, host behavior, screenshots and semantic equivalence do **not**
count as decompiled matching progress.

## Target

- SHA-256: `f82d09615506fd0aaa4a792844f0fb6908b0c07e5bb4fea1c992d4c7827f1975`
- ELF flags: `0x10A23001` (MIPS-II / EABI32)
- Entrypoint: `0x00389E7C`

The retail executable is not included. Supply your own legally obtained copy at:

```text
orig/NPJH50333_EBOOT.BIN
```

Verify it with:

```bash
python tools/verify_target.py
```

## Local matching

To verify all current Block 01 profiles on Windows:

```powershell
python tools/kurohyou/verify_block01_profiles.py `
  --eboot .\orig\NPJH50333_EBOOT.BIN `
  --compiler C:\path\to\pspsnc.exe
```

To prepare local normalized objects for objdiff:

```powershell
python tools/prepare_objdiff.py `
  --eboot .\orig\NPJH50333_EBOOT.BIN `
  --compiler C:\path\to\pspsnc.exe
```

Then open the generated `objdiff.json` with objdiff.

## decomp.dev

The GitHub workflow `.github/workflows/decomp-report.yml` publishes:

```text
artifact: NPJH50333_report
file:     report.json
```

The public report uses **all executable sections** as the code denominator. It does
not claim that the 30 audited functions are the whole game.

At the current 0.032977% code progress, decomp.dev can register the project
but will keep it hidden from the public Projects list until it reaches 0.5%.

See `docs/DECOMP_DEV.md`.
