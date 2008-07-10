;; AfxScratch application.
;; Copyright (c) 2004-2008 by Elijah Zarezky,
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

;; Setup.iss - setup script for Inno Setup compiler

[Setup]
AppName=AfxScratch
AppVerName=AfxScratch 1.1.4330
AppID={{9BE84A05-C061-49C5-BAFF-6D6E2737AAE7}
AppPublisher=Elijah Zarezky
AppPublisherURL=http://zarezky.spb.ru/
AppSupportURL=http://zarezky.spb.ru/projects/afx_scratch.html
AppUpdatesURL=http://zarezky.spb.ru/projects/afx_scratch.html
AppVersion=1.1.4330
DefaultDirName={pf}\PowerGadgets\AfxScratch
DefaultGroupName=PowerGadgets\AfxScratch
AllowNoIcons=true
Compression=lzma
SolidCompression=true
OutputDir=..\Setup
OutputBaseFilename=AfxScratch-1.1.4330-setup
VersionInfoVersion=1.1.4330
MinVersion=4.90.3000,5.0.2195
WizardImageFile=compiler:WizModernImage-IS.bmp
WizardSmallImageFile=compiler:WizModernSmallImage-IS.bmp
LicenseFile=ApacheLicense.rtf

[LangOptions]
DialogFontName=Tahoma
DialogFontSize=8

[Files]
Source: "..\Output.2008\x86\Release\MBCS\AfxScratch.exe"; DestDir: "{app}"
Source: "..\HTML\AfxScratch.chm"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\AppData\*"; Excludes: ".svn"; DestDir: "{commonappdata}\Elijah Zarezky\AfxScratch"; Flags: ignoreversion recursesubdirs
Source: ".\ApacheLicense.rtf"; DestDir: "{app}"; Flags: ignoreversion

Source: "..\Redist\Microsoft.VC90.CRT\msvcr90.dll"; DestDir: "{app}"; OnlyBelowVersion: 0,5.01.2600; Flags: ignoreversion
Source: "..\Redist\Microsoft.VC90.CRT\msvcp90.dll"; DestDir: "{app}"; OnlyBelowVersion: 0,5.01.2600; Flags: ignoreversion
Source: "..\Redist\Microsoft.VC90.CRT\msvcm90.dll"; DestDir: "{app}"; OnlyBelowVersion: 0,5.01.2600; Flags: ignoreversion

Source: "..\Redist\Microsoft.VC90.CRT\msvcr90.dll"; DestDir: "{app}\Microsoft.VC90.CRT"; MinVersion: 0,5.01.2600
Source: "..\Redist\Microsoft.VC90.CRT\msvcp90.dll"; DestDir: "{app}\Microsoft.VC90.CRT"; MinVersion: 0,5.01.2600
Source: "..\Redist\Microsoft.VC90.CRT\msvcm90.dll"; DestDir: "{app}\Microsoft.VC90.CRT"; MinVersion: 0,5.01.2600
Source: "..\Redist\Microsoft.VC90.CRT\Microsoft.VC90.CRT.manifest"; DestDir: "{app}\Microsoft.VC90.CRT"; MinVersion: 0,5.01.2600

Source: "..\Redist\Microsoft.VC90.MFC\mfc90.dll"; DestDir: "{app}"; OnlyBelowVersion: 0,5.01.2600; Flags: ignoreversion
Source: "..\Redist\Microsoft.VC90.MFC\mfcm90.dll"; DestDir: "{app}"; OnlyBelowVersion: 0,5.01.2600; Flags: ignoreversion

Source: "..\Redist\Microsoft.VC90.MFC\mfc90.dll"; DestDir: "{app}\Microsoft.VC90.MFC"; MinVersion: 0,5.01.2600
Source: "..\Redist\Microsoft.VC90.MFC\mfcm90.dll"; DestDir: "{app}\Microsoft.VC90.MFC"; MinVersion: 0,5.01.2600
Source: "..\Redist\Microsoft.VC90.MFC\Microsoft.VC90.MFC.manifest"; DestDir: "{app}\Microsoft.VC90.MFC"; MinVersion: 0,5.01.2600

Source: "..\Redist\Microsoft.VC90.MFCLOC\mfc90enu.dll"; DestDir: "{app}"; OnlyBelowVersion: 0,5.01.2600; Flags: ignoreversion
Source: "..\Redist\Microsoft.VC90.MFCLOC\mfc90rus.dll"; DestDir: "{app}"; OnlyBelowVersion: 0,5.01.2600; Flags: ignoreversion

Source: "..\Redist\Microsoft.VC90.MFCLOC\mfc90enu.dll"; DestDir: "{app}\Microsoft.VC90.MFC\Microsoft.VC90.MFCLOC"; MinVersion: 0,5.01.2600
Source: "..\Redist\Microsoft.VC90.MFCLOC\mfc90rus.dll"; DestDir: "{app}\Microsoft.VC90.MFC\Microsoft.VC90.MFCLOC"; MinVersion: 0,5.01.2600
Source: "..\Redist\Microsoft.VC90.MFCLOC\Microsoft.VC90.MFCLOC.manifest"; DestDir: "{app}\Microsoft.VC90.MFC\Microsoft.VC90.MFCLOC"; MinVersion: 0,5.01.2600

[Icons]
Name: "{group}\AfxScratch"; Filename: "{app}\AfxScratch.exe"
Name: "{group}\AfxScratch Documentation"; Filename: "{app}\AfxScratch.chm"
Name: "{group}\AfxScratch License"; Filename: "{app}\ApacheLicense.rtf"
Name: "{group}\AfxScratch on the Web"; Filename: "{app}\AfxScratch.url"
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
