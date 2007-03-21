@echo off
echo.
echo Building executable...
echo.
devenv.com AfxScratch70.sln /rebuild MBCS_Release /project AfxScratch /nologo
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
echo.
echo Creating full installer...
echo.
iscc.exe SetupFull.iss
cd ..
