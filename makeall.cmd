@echo off
echo.
echo Building executable - "Win32 Debug"...
echo.
msdev.com AfxScratch.dsw /MAKE "AfxScratch - Win32 Debug" /REBUILD
echo.
echo Building executable - "Win32 Release"...
echo.
msdev.com AfxScratch.dsw /MAKE "AfxScratch - Win32 Release" /REBUILD
echo.
