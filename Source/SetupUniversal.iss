;; AfxScratch application.
;; Copyright (c) 2004-2009 by Elijah Zarezky,
;; All rights reserved.

;; Licensed under the Apache License, Version 2.0 (the "License");
;; you may not use this file except in compliance with the License.
;; You may obtain a copy of the License at
;;
;; http://www.apache.org/licenses/LICENSE-2.0
;;
;; Unless required by applicable law or agreed to in writing, software
;; distributed under the License is distributed on an "AS IS" BASIS,
;; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;; See the License for the specific language governing permissions and
;; limitations under the License.

;; SetupUniversal.iss - setup script for Inno Setup compiler
;; NOTE that this file is generated automatically by NAnt.exe

[Setup]
AppName=AfxScratch
AppVerName=AfxScratch 1.1.4877
AppID={{9BE84A05-C061-49C5-BAFF-6D6E2737AAE7}
AppPublisher=Elijah Zarezky
AppPublisherURL=http://zarezky.spb.ru/
AppSupportURL=http://zarezky.spb.ru/projects/afx_scratch.html
AppUpdatesURL=http://zarezky.spb.ru/projects/afx_scratch.html
AppVersion=1.1.4877
DefaultDirName={pf}\Elijah Zarezky\AfxScratch
DefaultGroupName=Elijah Zarezky\AfxScratch
AllowNoIcons=true
Compression=lzma
SolidCompression=true
OutputDir=..\Setup
OutputBaseFilename=AfxScratch-1.1.4877-setup-universal
VersionInfoVersion=1.1.4877
MinVersion=4.90.3000,5.0.2195
WizardImageFile=compiler:WizModernImage-IS.bmp
WizardSmallImageFile=compiler:WizModernSmallImage-IS.bmp
LicenseFile=ApacheLicense.rtf
AppMutex=AfxScratch.Instance.655393D6-3C2F-43E5-AEC3-29FCDC0AA439

[LangOptions]
DialogFontName=MS Shell Dlg 2
DialogFontSize=8

[InstallDelete]
;; from 1.0 release
Type: files; Name: "{app}\msvcr71.dll"
Type: files; Name: "{app}\msvcp71.dll"
Type: files; Name: "{app}\mfc71.dll"
;; from 1.1 pre-release
Type: filesandordirs; Name: "{app}\Microsoft.VC90.CRT"
Type: filesandordirs; Name: "{app}\Microsoft.VC90.MFC"
;; application sources
Type: filesandordirs; Name: "{app}\Sources"

[Types]
Name: "typical"; Description: "Typical Installation"
Name: "compact"; Description: "Compact Installation"
Name: "full"; Description: "Full Installation"
Name: "custom"; Description: "Custom Installation"; Flags: iscustom

[Components]
Name: "core"; Description: "AfxScratch Core Files"; Types: compact typical full custom; Flags: fixed
Name: "runtimes"; Description: "Application Runtimes"; Types: typical full custom
Name: "sources"; Description: "Source Code"; Types: full custom

[Files]
;; core application files
Source: "..\Output.2008\x86\Release\MBCS\AfxScratch.exe"; Components: core; DestDir: "{app}"
Source: "..\HTML\AfxScratch.chm"; DestDir: "{app}"; Components: core; Flags: ignoreversion
Source: "..\AppData\*"; Excludes: ".svn, *.aps"; DestDir: "{commonappdata}\Elijah Zarezky\AfxScratch"; Components: core; Flags: ignoreversion recursesubdirs
Source: ".\ApacheLicense.rtf"; DestDir: "{app}"; Components: core; Flags: ignoreversion

;; CRT redistributables
Source: "..\Redist\Microsoft.VC90.CRT\msvcr90.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.CRT\msvcp90.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.CRT\msvcm90.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.CRT\Microsoft.VC90.CRT.manifest"; DestDir: "{app}"; Components: runtimes; MinVersion: 0,5.01.2600

;; MFC library redistributables
Source: "..\Redist\Microsoft.VC90.MFC\mfc90.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.MFC\mfcm90.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.MFC\Microsoft.VC90.MFC.manifest"; DestDir: "{app}"; Components: runtimes; MinVersion: 0,5.01.2600

;; MFC library localizations
Source: "..\Redist\Microsoft.VC90.MFCLOC\mfc90enu.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.MFCLOC\mfc90rus.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.MFCLOC\Microsoft.VC90.MFCLOC.manifest"; DestDir: "{app}"; Components: runtimes; MinVersion: 0,5.01.2600

;; AfxGadgets library sources
Source: "..\..\Repository\AfxGadgets\AfxGadgets.2008.vcproj"; DestDir: "{app}\Sources\Repository\AfxGadgets"; Components: sources; Flags: ignoreversion
Source: "..\..\Repository\AfxGadgets\Source\*"; Excludes: ".svn, *.aps"; DestDir: "{app}\Sources\Repository\AfxGadgets\Source"; Components: sources; Flags: ignoreversion

;; CodeProject library sources
Source: "..\..\Repository\CodeProject\CodeProject.2008.vcproj"; DestDir: "{app}\Sources\Repository\CodeProject"; Components: sources; Flags: ignoreversion
Source: "..\..\Repository\CodeProject\Help\*"; Excludes: ".svn"; DestDir: "{app}\Sources\Repository\CodeProject\Help"; Components: sources; Flags: ignoreversion
Source: "..\..\Repository\CodeProject\Source\*"; Excludes: ".svn, *.aps"; DestDir: "{app}\Sources\Repository\CodeProject\Source"; Components: sources; Flags: ignoreversion

;; CRT/MFC redistributables
Source: "..\Redist\*"; Excludes: ".svn"; DestDir: "{app}\Sources\AfxScratch\Redist"; Components: sources; Flags: ignoreversion recursesubdirs

;; AfxScratch application sources
Source: "..\AfxScratch.2008.vcproj"; DestDir: "{app}\Sources\AfxScratch"; Components: sources; Flags: ignoreversion
Source: "..\AfxScratch.2008.sln"; DestDir: "{app}\Sources\AfxScratch"; Components: sources; Flags: ignoreversion
Source: "..\AfxScratch.2008.build"; DestDir: "{app}\Sources\AfxScratch"; Components: sources; Flags: ignoreversion
Source: "..\AppData\*"; Excludes: ".svn, *.aps"; DestDir: "{app}\Sources\AfxScratch\AppData"; Components: sources; Flags: ignoreversion recursesubdirs
Source: "..\HTML\*"; Excludes: ".svn, *.chm"; DestDir: "{app}\Sources\AfxScratch\HTML"; Components: sources; Flags: ignoreversion
Source: "..\HTML\images\*"; Excludes: ".svn"; DestDir: "{app}\Sources\AfxScratch\HTML\images"; Components: sources; Flags: ignoreversion
Source: "..\Source\*"; Excludes: ".svn, *.aps"; DestDir: "{app}\Sources\AfxScratch\Source"; Components: sources; Flags: ignoreversion recursesubdirs
Source: "..\Templates\*"; Excludes: ".svn, *.aps"; DestDir: "{app}\Sources\AfxScratch\Templates"; Components: sources; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\AfxScratch"; Filename: "{app}\AfxScratch.exe"
Name: "{group}\Documentation"; Filename: "{app}\AfxScratch.chm"
Name: "{group}\License Agreement"; Filename: "{app}\ApacheLicense.rtf"
Name: "{group}\AfxScratch on the Web"; Filename: "{app}\AfxScratch.url"
Name: "{group}\Build AfxScratch"; FileName: "{app}\Sources\AfxScratch\AfxScratch.2008.sln"; Components: sources
Name: "{group}\Uninstall AfxScratch"; Filename: "{uninstallexe}"
Name: "{userdesktop}\AfxScratch"; Filename: "{app}\AfxScratch.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\AfxScratch"; Filename: "{app}\AfxScratch.exe"; Tasks: quicklaunchicon

[INI]
Filename: "{app}\AfxScratch.url"; Section: "InternetShortcut"; Key: "URL"; String: "http://zarezky.spb.ru/projects/afx_scratch.html"

[Registry]
Root: HKCU; Subkey: "Software\Elijah Zarezky"; Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: "Software\Elijah Zarezky\AfxScratch"; Flags: uninsdeletekey

[Tasks]
Name: desktopicon; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; Flags: unchecked
Name: quicklaunchicon; Description: "Create a &Quick Launch icon"; GroupDescription: "Additional icons:"; Flags: unchecked

[Run]
Filename: "{app}\AfxScratch.exe"; Description: "Launch AfxScratch"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: files; Name: "{app}\AfxScratch.url"

;; end of file
