;; AfxScratch application.
;; Copyright (c) 2004-2005 by Elijah Zarezky,
;; All rights reserved.

;; Setup.iss - setup script for Inno Setup compiler

[Setup]
AppName=AfxScratch
AppVerName=AfxScratch 1.0.3345
AppID={{9BE84A05-C061-49C5-BAFF-6D6E2737AAE7}
AppPublisher=Elijah Zarezky
AppPublisherURL=http://zarezky.spb.ru/
AppSupportURL=http://zarezky.spb.ru/projects/afx_scratch.html
AppUpdatesURL=http://zarezky.spb.ru/projects/afx_scratch.html
AppVersion=1.0.3345
DefaultDirName={pf}\PowerGadgets\AfxScratch
DefaultGroupName=PowerGadgets\AfxScratch
AllowNoIcons=true
Compression=lzma
SolidCompression=true
OutputDir=..\Setup
OutputBaseFilename=AfxScratch-1.0.3345-setup
VersionInfoVersion=1.0.3345
MinVersion=4.90.3000,5.0.2195
WizardImageFile=compiler:WizModernImage-IS.bmp
WizardSmallImageFile=compiler:WizModernSmallImage-IS.bmp

[LangOptions]
DialogFontName=Tahoma
DialogFontSize=8

[Files]
Source: "..\70_ReleaseA\AfxScratch.exe"; DestDir: "{app}"
Source: "..\HTML\AfxScratch.chm"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\AppData\*"; Excludes: ".svn"; DestDir: "{commonappdata}\Elijah Zarezky\AfxScratch"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\AfxScratch"; Filename: "{app}\AfxScratch.exe"
Name: "{group}\AfxScratch Documentation"; Filename: "{app}\AfxScratch.chm"
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
