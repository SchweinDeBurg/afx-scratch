// AfxScratch application.
// Copyright (c) 2004-2011 by Elijah Zarezky,
// All rights reserved.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// stdafx.cpp - source file that includes just the standard includes

//////////////////////////////////////////////////////////////////////////////////////////////
// PCH includes

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// debugging support

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////
// import libraries

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "version.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "rpcrt4.lib")

//////////////////////////////////////////////////////////////////////////////////////////////
// Detours libraries

#if defined(AFXSCRATCH_DETOURED)
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "detoured.lib")
#endif   // AFXSCRATCH_DETOURED

//////////////////////////////////////////////////////////////////////////////////////////////
// linker options

#if (_MSC_VER < 1300)
#pragma comment(linker, "/ignore:4089")   // all references to DLL discarded by /opt:ref
#pragma comment(linker, "/opt:ref")
#endif   // _MSC_VER

//////////////////////////////////////////////////////////////////////////////////////////////
// entry-point symbol for the Unicode builds

#if defined(UNICODE) || defined(_UNICODE)
#pragma comment(linker, "/entry:wWinMainCRTStartup")
#endif	// UNICODE

//////////////////////////////////////////////////////////////////////////////////////////////
// manifest dependencies

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

// VC-2008 RTM                       9.0.21022.8
// VC-2008 Feature Pack              9.0.30411.0
// VC-2008 SP1                       9.0.30729.1
// VC-2008 SP1 ATL Security Update   9.0.30729.4148
// VC-2008 SP1 MFC Security Update   9.0.30729.5570

#if defined(_DEBUG)
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.VC90.DebugCRT' version='9.0.30729.5570' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.VC90.DebugMFC' version='9.0.30729.5570' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.VC90.PrivateCRT' version='9.0.30729.5570' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.VC90.PrivateMFC' version='9.0.30729.5570' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#endif   // _DEBUG

// end of file