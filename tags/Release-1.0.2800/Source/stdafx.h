// AfxScratch application.
// Copyright (c) 2004-2005 by Elijah Zarezky,
// All rights reserved.

// stdafx.h - include file for standard system include files

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
#include <afxcmn.h>			// MFC common control classes
#include <afxtempl.h>		// MFC collection template classes
#include <afxdlgs.h>			// MFC standard dialogs

// ATL headers
#include <atlbase.h>

// PSDK headers
#include <shlobj.h>
#include <lmcons.h>
#include <shlwapi.h>			// light-weight utility APIs

// STL headers
#pragma warning(push, 3)
#include <iostream>
#pragma warning(disable: 4706)	// assignment within conditional expression
#include <fstream>
#pragma warning(default: 4706)
#pragma warning(pop)

// for compatibility with Dinkumware STL
#if !defined(_IOSTREAM_)
#define _IOSTREAM_
#endif	// _IOSTREAM_
#if !defined(_FSTREAM_)
#define _FSTREAM_
#endif	// _FSTREAM_

// additional headers
#include "../../Repository/CodeProject/Source/PugXML.h"
#include "../../Repository/AfxGadgets/Source/StringConv.h"
#include "../../Repository/AfxGadgets/Source/Win32Error.h"
#include "../../Repository/AfxGadgets/Source/SortingListCtrl.h"
#include "../../Repository/CodeProject/Source/FolderDlg.h"

#endif	// __stdafx_h

// end of file
