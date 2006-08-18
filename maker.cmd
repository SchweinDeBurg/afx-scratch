@echo off
echo.
echo Building executable...
echo.
devenv.com AfxScratch70.sln /rebuild MBCS_Release /project AfxScratch /nologo
echo Compiling documentation...
echo.
chdir .\HTML
if exist AfxScratch.chm del AfxScratch.chm
hhc.exe AfxScratch.hhp
chdir ..\
echo.
echo.
echo Creating installer...
echo.
if not exist .\Setup mkdir .\Setup
chdir .\Source
if exist ..\Setup\*.exe del ..\Setup\*.exe
iscc.exe Setup.iss
echo.
echo Creating full installer...
echo.
iscc.exe SetupFull.iss
chdir ..
