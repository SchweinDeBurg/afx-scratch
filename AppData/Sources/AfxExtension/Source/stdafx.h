// $PROJECT$ MFC extension DLL.
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

// MFC headers
#include <afxwin.h>			// MFC core and standard components
#include <afxdllx.h>			// MFC extension DLL helpers

// force ISO/IEC 14882 conformance in for loop scope
#if _MSC_VER < 1300
#define for if(false); else for
#else
#pragma conform(forScope, on)
#endif	// _MSC_VER

#endif	// __stdafx_h

// end of file
