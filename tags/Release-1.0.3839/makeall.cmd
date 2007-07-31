@echo off
echo.
echo Building executable - "Win32 MBCS Debug"...
echo.
devenv.com AfxScratch71.sln /rebuild "MBCS Debug" /project AfxScratch /nologo
echo Building executable - "Win32 MBCS Release"...
echo.
devenv.com AfxScratch71.sln /rebuild "MBCS Release" /project AfxScratch /nologo
echo.
