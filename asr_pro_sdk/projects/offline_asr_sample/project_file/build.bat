
@echo off
setlocal enabledelayedexpansion
set path=%~dp0..\..\..\..\gcc\bin;%~dp0..\..\..\..\asr_pro_sdk\tools\build-tools\bin;%~dp0..\..\..\..\..\twen-asr\RISCV-GCC\bin;%path%;



make
cd ..\..\..\..\
makebin


