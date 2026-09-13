@echo off
setlocal
if "%~1"=="" (
  echo Usage: RUN_MATCHING_AUDIT.bat C:\path\to\NPJH50333_EBOOT.BIN
  exit /b 2
)

python tools\kurohyou\toolchain_probe.py
if errorlevel 1 exit /b %errorlevel%

where psp-gcc >nul 2>nul
if not errorlevel 1 (
  for /f "tokens=*" %%V in ('psp-gcc --version ^| findstr /i "gcc"') do set PSPGCCVER=%%V
  echo Found psp-gcc: %PSPGCCVER%
  echo Running PSPDEV EABI diagnostic profile...
  python tools\kurohyou\matching.py --eboot "%~1" --toolchain pspdev_gcc_eabi_probe --output matching\MATCHING_REPORT_PSPGCC.md --json matching\MATCHING_REPORT_PSPGCC.json
  if errorlevel 1 exit /b %errorlevel%
) else (
  echo psp-gcc not found. Running Clang O32 diagnostic only.
)

python tools\kurohyou\matching.py --eboot "%~1" --toolchain clang17_psp_o32_probe --output matching\MATCHING_REPORT.md --json matching\MATCHING_REPORT.json
if errorlevel 1 exit /b %errorlevel%
python tools\kurohyou\source_sweep_001E63D8.py
if errorlevel 1 exit /b %errorlevel%

echo.
echo Reports:
echo   matching\MATCHING_REPORT.md
echo   matching\TOOLCHAIN_PROBE.md
echo   matching\CLANG_SOURCE_SWEEP_001E63D8.md
if exist matching\MATCHING_REPORT_PSPGCC.md echo   matching\MATCHING_REPORT_PSPGCC.md
endlocal
