@echo off
setlocal
cd /d "%~dp0"
if "%~1"=="" (
  echo Usage: MATCHING_FINGERPRINT.bat C:\path\to\NPJH50333_EBOOT.BIN
  exit /b 2
)
python tools\kurohyou\fingerprint_toolchains.py --eboot "%~1" --toolchains clang17_psp_o32_probe snc_1_2_7503_o2_sched2 snc_1_2_7503_o2_sched1 mwccpsp_3_0_1_219_probe
if errorlevel 1 exit /b %errorlevel%
echo.
echo Report: matching\FINGERPRINT_MATRIX.md
pause
