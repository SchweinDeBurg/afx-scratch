// AfxScratch application.
// Copyright (c) 2004-2007 by Elijah Zarezky,
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

#define _WIN32_WINNT 0x0500	// use Windows 2000 features

// MFC headers
#include <afxwin.h>			// MFC core and standard components
#include <afxcmn.h>			// MFC common control classes
#include <afxtempl.h>		// MFC collection template classes
#include <afxdlgs.h>			// MFC standard dialogs
#include <afxext.h>			// MFC extensions and customizable classes

// ATL headers
#include <atlbase.h>

// PSDK headers
#include <shlobj.h>
#include <lmcons.h>
#include <shlwapi.h>			// light-weight utility APIs

// remove stupid macros in order to use STL templates
#if defined(min)
#undef min
#endif	// min
#if defined(max)
#undef max
#endif	// max

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
#include "../../Repository/AfxGadgets/Source/PugXMLplus.h"
#include "../../Repository/CodeProject/Source/FolderDlg.h"
#include "../../Repository/CodeProject/Source/ETSLayout.h"
#include "../../Repository/CodeProject/Source/memdc.h"

// force ISO/IEC 14882 conformance in for loop scope
#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif	// _MSC_VER

#endif	// __stdafx_h

// end of file
