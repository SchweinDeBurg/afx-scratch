// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// stdafx.h - include file for standard system include files

#if !defined(__stdafx_h)
#define __stdafx_h

// unreferenced inline/local function has been removed
#pragma warning(disable: 4514)
// function not inlined
#pragma warning(disable: 4710)
// identifier was truncated in the debug information
#pragma warning(disable: 4786)

// MFC headers
#include <afxwin.h>			// MFC core and standard components
#include <afxcmn.h>			// MFC common control classes
#include <afxtempl.h>		// MFC collection template classes
#include <afxdlgs.h>			// MFC standard dialogs

#if _MFC_VER > 0x0600
#include <../src/mfc/afximpl.h>
#else
#include <../src/afximpl.h>
#endif	// _MFC_VER

// PSDK headers
#include <shlobj.h>
#include <lmcons.h>
#include <shlwapi.h>

// STL headers
#pragma warning(push, 3)
#if _MSC_VER <= 1200
#include <typeinfo.h>
namespace std { using ::bad_cast; }
#else
#include <typeinfo>
#endif	// _MSC_VER
#include <iostream>
#pragma warning(disable: 4706)	// assignment within conditional expression
#include <fstream>
#pragma warning(default: 4706)
#pragma warning(pop)

// for compatibility with Dinkumware STL
#if !defined(_IOSTREAM_)
#define _IOSTREAM_
#endif

// additional headers
#include "PugXML.h"
#include "../../Repository/AfxGadgets/Source/StringConv.h"
#include "../../Repository/AfxGadgets/Source/Win32Error.h"
#include "../../Repository/CodeProject/Source/FolderDlg.h"

#endif	// __stdafx_h

// end of file
