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

#define NOMINMAX

// The threading model for device project is Free by default. However, Windows CE does
// not fully support COM marshalling and associated definitions, if the DCOM option is
// not chosen when you are building your CE OS image. Therefore, on certain CE platforms,
// the compiler may generate warnings about DCOM support and single and multithreading
// definition. This warning is to advise you to handle threading and synchronization in
// your own code. For example, when compiling an ATL device project, the compiler may
// issue a warning about defining _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA. This is also
// the case for scenarios such as creating COM objects, consuming Web services, as well
// as ATL COM objects on the Windows Mobile platform. You can define this flag in your
// main header file for single-threaded objects. If your code is handling multithreading,
// you can safely ignore this warning.
#define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA

#define _ATL_NO_COM_SUPPORT
#define _ATL_NO_HOSTING
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES
#define _WTL_NO_AUTOMATIC_NAMESPACE

// ATL/WTL headers
#include <atlbase.h>
#include <atlstr.h>
#include <atltypes.h>
#include <atlapp.h>
extern WTL::CAppModule _Module;
#include <atlwin.h>
#include <atlframe.h>
#include <atlcrack.h>
#include <atlscrl.h>
#include <atlctrls.h>
#include <atlwince.h>

namespace ATL
{
// introduce these types into the ATL namespace for code uniformity
using ::CSize;
using ::CPoint;
using ::CRect;
}

// DRA headers
#include <DeviceResolutionAware.h>
#pragma message("*** Note that <DeviceResolutionAware.h> header just included is buggy!")
#pragma message("*** Use <atldra.h> from myWTL project instead.")
#pragma message("*** Visit http://zarezky.spb.ru/projects/my_wtl.html for more info.")

// force ISO/IEC 14882 conformance in for loop scope
#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif	// _MSC_VER

#endif	// __stdafx_h

// end of file
