// $PROJECT$ application.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// stdafx.cpp - source file that includes just the standard includes

// initially generated by $GENERATOR$ on $DATE$ at $TIME$
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

//////////////////////////////////////////////////////////////////////////////////////////////
// PCH includes

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// debugging support

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif   // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////
// linker options

#if defined(_MSC_VER) && (_MSC_VER < 1300)
#pragma comment(linker, "/opt:ref")
// all references to DLL discarded by /opt:ref
#pragma comment(linker, "/ignore:4089")
#endif   // _MSC_VER

//////////////////////////////////////////////////////////////////////////////////////////////
// entry-point symbol for the Unicode builds

#if (_MSC_VER < 1300)
#if defined(UNICODE) || defined(_UNICODE)
#pragma comment(linker, "/entry:wWinMainCRTStartup")
#endif   // UNICODE
#endif   // _MSC_VER

//////////////////////////////////////////////////////////////////////////////////////////////
// manifest dependencies

#if defined(_DEBUG)
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.VC90.DebugCRT' version='9.0.21022.8' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.VC90.DebugMFC' version='9.0.21022.8' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.VC90.CRT' version='9.0.21022.8' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.VC90.MFC' version='9.0.21022.8' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#endif   // _DEBUG
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

// end of file
