# Retail compiler / ABI research checkpoint

## Proven from NPJH50333_EBOOT.BIN

`readelf -h` reports ELF flags `0x10a23001`: `noreorder`, `eabi32`, `mips2` plus the PSP/Allegrex machine bits.  This is stronger evidence than inferring ABI from source behavior.

The two floating-point leaf functions in the current corpus reinforce that result:

- `0x001A88C4` enters with four scalar float arguments already in `f12/f13/f14/f15`.
- `0x001C58E4` uses odd single-precision registers (`f13`) and hand-scheduled branch delay slots.

The available Clang PSP target in this environment only accepts O32.  It therefore cannot be used to certify the retail code generator.

## Historical PSP GCC candidate

Historical PSPDEV GCC 4.3.2 patches define the PSP target as Allegrex and set:

- `MIPS_ISA_DEFAULT=2`
- `MIPS_CPU_STRING_DEFAULT="allegrex"`
- `MIPS_ABI_DEFAULT=ABI_EABI`
- single-float target defaults

This makes PSPDEV GCC 4.3.2 a materially better ABI probe than the local Clang/O32 backend.  It is **not** assumed to be the retail compiler merely because the ABI matches.

Source reference:
`https://github.com/badboy/ps2dev-psptoolchain/blob/master/patches/gcc-4.3.2-PSP.patch`

An archived PSP GCC 4.3.2 package also exists at SourceForge:
`https://sourceforge.net/projects/psp1and2sdk/files/gcc-psp-4.3.2.tar.gz/download`

## GCC3003 strings

The `GCC3003 SCE06020010` strings in the EBOOT are attached to CRI middleware version records. They prove the toolchain label for those CRI objects, but not for all game-owned translation units. GCC 3.0.3 remains a useful fingerprint candidate, not an established fact.

## Current decision

No compiler profile is marked `certifying` yet.  A profile can be promoted only after it reproduces several independent game-owned leaf functions exactly, including at least one integer function and one hard-float EABI function.
