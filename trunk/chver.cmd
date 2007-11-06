@echo off

REM AfxScratch application.
REM Copyright (c) 2004-2007 by Elijah Zarezky,
REM All rights reserved.

REM Licensed under the Apache License, Version 2.0 (the "License");
REM you may not use this file except in compliance with the License.
REM You may obtain a copy of the License at
REM
REM http://www.apache.org/licenses/LICENSE-2.0
REM
REM Unless required by applicable law or agreed to in writing, software
REM distributed under the License is distributed on an "AS IS" BASIS,
REM WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
REM See the License for the specific language governing permissions and
REM limitations under the License.

REM chver.cmd - NT command script to change version numbers

copy /Y .\Source\AfxScratch.manifest.munge .\Source\AfxScratch.manifest
.\Tools\munge.exe .\Source\MungeScript.txt -k -t -L .\Source\AfxScratch.manifest

copy /Y .\Source\VersionInfo.rc.munge .\Source\VersionInfo.rc
.\Tools\munge.exe .\Source\MungeScript.txt -k -t -L .\Source\VersionInfo.rc

copy /Y .\Source\Setup.iss.munge .\Source\Setup.iss
.\Tools\munge.exe .\Source\MungeScript.txt -k -t -L .\Source\Setup.iss

copy /Y .\Source\SetupFull.iss.munge .\Source\SetupFull.iss
.\Tools\munge.exe .\Source\MungeScript.txt -k -t -L .\Source\SetupFull.iss

REM end of file
