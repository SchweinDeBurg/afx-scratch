@echo off
echo.
echo Building executable...
echo.
msdev.com AfxScratch.dsw /MAKE "AfxScratch - Win32 Release" /REBUILD
echo.
echo.
echo Compiling documentation...
echo.
cd .\HTML
if exist AfxScratch.chm del AfxScratch.chm
hhc.exe AfxScratch.hhp
echo.
echo.
echo Creating installer...
echo.
cd ..\Source
if exist ..\Setup\*.exe del ..\Setup\*.exe
iscc.exe Setup.iss
cd ..
