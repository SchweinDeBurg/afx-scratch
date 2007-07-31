@echo off

echo.
echo Building executable...
echo.
devenv.com AfxScratch71.sln /rebuild "MBCS Release" /project AfxScratch /nologo

echo Compiling documentation...
echo.
chdir .\HTML
if exist AfxScratch.chm del AfxScratch.chm
hhc.exe AfxScratch.hhp
chdir ..\

if not exist .\Setup mkdir .\Setup
if exist .\Setup\*.exe del .\Setup\*.exe

echo.
echo.
echo Creating installer...
echo.
chdir .\Source
iscc.exe Setup.iss
chdir ..\

echo.
echo.
echo Creating full installer...
echo.
chdir .\Source
iscc.exe SetupFull.iss
chdir ..\
