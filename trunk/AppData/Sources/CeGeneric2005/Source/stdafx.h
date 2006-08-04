// $PROJECT$ application.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// stdafx.h - include file for standard system include files

// initially generated by $GENERATOR$ on $DATE$ at $TIME$
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

#if !defined(__stdafx_h)
#define __stdafx_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif	// _MSC_VER

// unreferenced inline/local function has been removed
#pragma warning(disable: 4514)
// function not inlined
#pragma warning(disable: 4710)
// identifier was truncated in the debug information
#pragma warning(disable: 4786)

#define WINVER _WIN32_WCE

#pragma warning(push)

// nonstandard extension used: nameless struct/union
#pragma warning(disable: 4201)

// PSDK headers
#include <windows.h>
#include <aygshell.h>

// CRT headers
#include <altcecrt.h>
#include <tchar.h>
#include <typeinfo>

// DRA headers
#include <DeviceResolutionAware.h>

#pragma warning(pop)

// force ISO/IEC 14882 conformance in for loop scope
#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif	// _MSC_VER

#endif	// __stdafx_h

// end of file
