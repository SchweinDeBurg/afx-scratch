;; AfxScratch application.
;; Copyright (c) 2004-2011 by Elijah Zarezky,
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
AppVerName=AfxScratch 1.1.5668
AppID={{9BE84A05-C061-49C5-BAFF-6D6E2737AAE7}
AppPublisher=Elijah Zarezky
AppPublisherURL=http://zarezky.spb.ru/
AppSupportURL=http://zarezky.spb.ru/projects/afx_scratch.html
AppUpdatesURL=http://zarezky.spb.ru/projects/afx_scratch.html
AppVersion=1.1.5668
AppCopyright=Copyright © 2004–2011 by Elijah Zarezky
DefaultDirName={pf}\Elijah Zarezky\AfxScratch
DefaultGroupName=Elijah Zarezky\AfxScratch
AllowNoIcons=true
Compression=lzma
SolidCompression=true
OutputDir=..\Setup
OutputBaseFilename=AfxScratch-1.1.5668-setup-universal
VersionInfoVersion=1.1.5668.183
VersionInfoProductName=Power Gadgets
VersionInfoProductVersion=1.1
MinVersion=0,5.0.2195
WizardImageFile=compiler:WizModernImage-IS.bmp
WizardSmallImageFile=compiler:WizModernSmallImage-IS.bmp
LicenseFile=ApacheLicense.rtf
AppMutex=AfxScratch.Instance.655393D6-3C2F-43E5-AEC3-29FCDC0AA439

[LangOptions]
DialogFontName=MS Shell Dlg 2
DialogFontSize=8

[Code]
//  Code Page default values
const
	CP_ACP = 0;
	CP_OEMCP = 1;
	CP_MACCP = 2;
	CP_THREAD_ACP = 3;
	CP_SYMBOL = 42;
	CP_UTF7 = 65000;
	CP_UTF8 = 65001;

// MBCS and Unicode translation flags
const
	MB_PRECOMPOSED = $0001;
	MB_COMPOSITE = $0002;
	MB_USEGLYPHCHARS = $0004;
	MB_ERR_INVALID_CHARS = $0008;

	WC_COMPOSITECHECK = $0200;
	WC_DISCARDNS = $0010;
	WC_SEPCHARS = $0020;
	WC_DEFAULTCHAR = $0040;
	WC_ERR_INVALID_CHARS = $0080;
	WC_NO_BEST_FIT_CHARS = $0400;

	DefFlagsMB = MB_PRECOMPOSED;
	DefFlagsWC = WC_COMPOSITECHECK or WC_DISCARDNS or WC_SEPCHARS or WC_DEFAULTCHAR;

function MultiByteToWideChar(CodePage, Flags: Integer; SrcStr: AnsiString; SrcLen: Integer; DestStr: String; DestLen: Integer): Integer;
external 'MultiByteToWideChar@kernel32.dll stdcall';
function WideCharToMultiByte(CodePage, Flags: Integer; SrcStr: String; SrcLen: Integer; DestStr: AnsiString; DestLen: Integer; DefChar: Integer; DefCharUsed: Integer): Integer;
external 'WideCharToMultiByte@kernel32.dll stdcall';

function AnsiStringToString(const SrcStr: AnsiString; CodePage: Integer): String;
var
	WideLen: Integer;
begin
	if (SrcStr <> '') then
	begin
		WideLen := MultiByteToWideChar(CodePage, DefFlagsMB, SrcStr, -1, Result, 0);
		SetLength(Result, WideLen - 1);
		MultiByteToWideChar(CodePage, DefFlagsMB, SrcStr, -1, Result, WideLen - 1);
	end
	else begin
		Result := '';
	end;
end;

function StringToAnsiString(const SrcStr: String; CodePage: Integer): AnsiString;
var
	AnsiLen: Integer;
begin
	if (SrcStr <> '') then
	begin
		AnsiLen := WideCharToMultiByte(CodePage, DefFlagsWC, SrcStr, -1, Result, 0, 0, 0);
		SetLength(Result, AnsiLen - 1);
		WideCharToMultiByte(CodePage, DefFlagsWC, SrcStr, -1, Result, AnsiLen - 1, 0, 0);
	end
	else begin
		Result := '';
	end;
end;

function IsWinSxS(): Boolean;
var
	osVersion: TWindowsVersion;
begin
	GetWindowsVersionEx(osVersion);
	Result := ((osVersion.Major = 5) and (osVersion.Minor >= 1)) or (osVersion.Major > 5);
end;

const
	MagicStr = '{6DF4C042-C237-46b2-A205-C41DAAA4A0F5}';

procedure AdjustAfxConfig();
var
	AfxConfigPath: String;
	AfxConfigXML: AnsiString;
	WideXML: String;
begin
	if (IsWinSxS()) then
	begin
		AfxConfigPath := ExpandConstant(CurrentFileName());
		if (LoadStringFromFile(AfxConfigPath, AfxConfigXML)) then
		begin
			WideXML := AnsiStringToString(AfxConfigXML, CP_ACP);
			StringChangeEx(WideXML, MagicStr, ExpandConstant('{app}'), True);
			SaveStringToFile(AfxConfigPath, StringToAnsiString(WideXML, CP_ACP), False);
		end;
	end;
end;

function PrepareToInstall(var NeedsRestart: Boolean): String;
var
	AppDataDir: String;
	BackupDir: String;
begin
	AppDataDir := ExpandConstant('{commonappdata}\Elijah Zarezky\AfxScratch');
	if (DirExists(AppDataDir)) then
	begin
		BackupDir := AppDataDir + GetDateTimeString('.yyyy/mm/dd.hh:nn:ss', '-', '-');
		if (RenameFile(AppDataDir, BackupDir)) then
		begin
			Result := '';
		end
		else begin
			Result := 'Unable to create backup copy of the application data.'
		end;
	end
	else begin
		Result := '';
	end;
	NeedsRestart := False;
end;

[InstallDelete]
;; from 1.0 release
Type: files; Name: "{app}\msvcr71.dll"
Type: files; Name: "{app}\msvcp71.dll"
Type: files; Name: "{app}\mfc71.dll"
;; from 1.1 pre-release
Type: filesandordirs; Name: "{app}\Microsoft.VC90.CRT"
Type: filesandordirs; Name: "{app}\Microsoft.VC90.MFC"
Type: files; Name: "{app}\Microsoft.VC90.MFC.manifest"
;; from 1.1 non-Unicode pre-release
Type: files; Name: "{app}\mfc90.dll"
Type: files; Name: "{app}\mfcm90.dll"
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
Source: "..\Output.2008\x86\Release\Unicode\AfxScratch.exe"; Components: core; DestDir: "{app}"
Source: "..\Detours\Bin\detoured.dll"; Components: core; DestDir: "{app}"
Source: "..\HTML\AfxScratch.chm"; DestDir: "{app}"; Components: core; Flags: ignoreversion
Source: "..\AppData\*"; Excludes: ".svn, *.aps"; DestDir: "{commonappdata}\Elijah Zarezky\AfxScratch"; Components: core; Flags: ignoreversion recursesubdirs
Source: ".\ApacheLicense.rtf"; DestDir: "{app}"; Components: core; Flags: ignoreversion

;; CRT redistributables
Source: "..\Redist\Microsoft.VC90.CRT\msvcr90.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.CRT\msvcp90.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.CRT\msvcm90.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.CRT\Microsoft.VC90.PrivateCRT.manifest"; DestDir: "{app}"; Components: runtimes; MinVersion: 0,5.01.2600
Source: "..\Redist\Microsoft.VC90.CRT\Microsoft.VC90.CRT.manifest"; DestDir: "{app}"; Components: runtimes; MinVersion: 0,5.01.2600

;; MFC library redistributables
Source: "..\Redist\Microsoft.VC90.MFC\mfc90u.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.MFC\mfc90u.dll.1000.config"; DestDir: "{app}"; Components: runtimes; MinVersion: 0,5.01.2600; AfterInstall: AdjustAfxConfig
Source: "..\Redist\Microsoft.VC90.MFC\mfcm90u.dll"; DestDir: "{app}"; Components: runtimes
Source: "..\Redist\Microsoft.VC90.MFC\Microsoft.VC90.PrivateMFC.manifest"; DestDir: "{app}"; Components: runtimes; MinVersion: 0,5.01.2600

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
Source: "..\Detours\*"; Excludes: ".svn, *.aps"; DestDir: "{app}\Sources\AfxScratch\Detours"; Components: sources; Flags: ignoreversion recursesubdirs

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
Root: HKCU; Subkey: "Software\Elijah Zarezky\AfxScratch\Catchpit"; Flags: uninsdeletekey
Root: HKCU; Subkey: "Software\Elijah Zarezky\AfxScratch\Catchpit"; ValueType: dword; ValueName: "TortoiseShell.dll"; ValueData: "1"; Flags: createvalueifdoesntexist
Root: HKCU; Subkey: "Software\Elijah Zarezky\AfxScratch\Catchpit"; ValueType: dword; ValueName: "TortoiseOverlays.dll"; ValueData: "1"; Flags: createvalueifdoesntexist
Root: HKCU; Subkey: "Software\Elijah Zarezky\AfxScratch\Catchpit"; ValueType: dword; ValueName: "TortoiseSVN.dll"; ValueData: "1"; Flags: createvalueifdoesntexist
Root: HKCU; Subkey: "Software\Elijah Zarezky\AfxScratch\Catchpit"; ValueType: dword; ValueName: "TortoiseStub.dll"; ValueData: "1"; Flags: createvalueifdoesntexist
Root: HKCU; Subkey: "Software\Elijah Zarezky\AfxScratch\Catchpit"; ValueType: dword; ValueName: "PhoneBrowser.dll"; ValueData: "1"; Flags: createvalueifdoesntexist

[Tasks]
Name: desktopicon; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; Flags: unchecked
Name: quicklaunchicon; Description: "Create a &Quick Launch icon"; GroupDescription: "Additional icons:"; Flags: unchecked

[Run]
Filename: "{app}\AfxScratch.exe"; Description: "Launch AfxScratch"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: files; Name: "{app}\AfxScratch.url"

;; end of file
