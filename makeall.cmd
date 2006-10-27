@echo off
echo.
echo Building executable - "Win32 MBCS Debug"...
echo.
devenv.com AfxScratch71.sln /rebuild MBCS_Debug /project AfxScratch /nologo
echo Building executable - "Win32 MBCS Release"...
echo.
devenv.com AfxScratch71.sln /rebuild MBCS_Release /project AfxScratch /nologo
echo.
