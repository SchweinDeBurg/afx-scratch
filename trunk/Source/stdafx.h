// AfxScratch application.
// Copyright (c) 2004-2009 by Elijah Zarezky,
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
#endif   // _MSC_VER

//////////////////////////////////////////////////////////////////////////////////////////////
// unwanted warnings

// unreferenced inline/local function has been removed
#pragma warning(disable: 4514)
// function not inlined
#pragma warning(disable: 4710)
// identifier was truncated in the debug information
#pragma warning(disable: 4786)

// C4996: function or variable may be unsafe
#define _CRT_SECURE_NO_WARNINGS

//////////////////////////////////////////////////////////////////////////////////////////////
// use WinXP/IE6 features

#define WINVER 0x0501
#define _WIN32_WINDOWS 0x0500
#define _WIN32_IE 0x0600
#define _WIN32_WINNT 0x0501

//////////////////////////////////////////////////////////////////////////////////////////////
// remove automatic CRT/MFC dependencies generation

// see http://www.codeproject.com/KB/cpp/PrivateAssemblyProjects.aspx and
// http://blog.m-ri.de/index.php/2008/05/06/hotfix-fuer-usemsprivateassembliesh-und-vc-2008/
// by by Martin Richter for more information

#define _STL_NOFORCE_MANIFEST
#define _CRT_NOFORCE_MANIFEST
#define _AFX_NOFORCE_MANIFEST
#define _ATL_NOFORCE_MANIFEST

#ifdef __cplusplus
extern "C"
{
#endif

__declspec(selectany) int _forceCRTManifest;
__declspec(selectany) int _forceMFCManifest;
__declspec(selectany) int _forceAtlDllManifest;

// the next symbols are used by the several versions of VC++ 9.0
__declspec(selectany) int _forceCRTManifestRTM;
__declspec(selectany) int _forceMFCManifestRTM;
__declspec(selectany) int _forceMFCManifestCUR;

#ifdef __cplusplus
}   // extern "C"
#endif

//////////////////////////////////////////////////////////////////////////////////////////////
// MFC headers

#if (_MSC_VER >= 1300)
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#endif   // _MSC_VER

#define RPC_USE_NATIVE_WCHAR

#include <afxwin.h>        // MFC core and standard components
#include <afxcmn.h>        // MFC common control classes
#include <afxtempl.h>      // MFC collection template classes
#include <afxdlgs.h>       // MFC standard dialogs
#include <afxext.h>        // MFC extensions and customizable classes
#include <afxdisp.h>       // MFC IDispatch & ClassFactory support

//////////////////////////////////////////////////////////////////////////////////////////////
// ATL headers

#include <atlbase.h>       // basic ATL classes

//////////////////////////////////////////////////////////////////////////////////////////////
// PSDK headers

#include <shlobj.h>
#include <lmcons.h>
#include <shlwapi.h>       // light-weight utility APIs

//////////////////////////////////////////////////////////////////////////////////////////////
// remove stupid macros in order to use STL templates

#if defined(min)
#undef min
#endif   // min
#if defined(max)
#undef max
#endif   // max

//////////////////////////////////////////////////////////////////////////////////////////////
// STL headers

#pragma warning(push, 3)
#include <iostream>
#pragma warning(disable: 4706)   // assignment within conditional expression
#include <fstream>
#pragma warning(default: 4706)
#pragma warning(pop)

// for compatibility with Dinkumware STL
#if !defined(_IOSTREAM_)
#define _IOSTREAM_
#endif   // _IOSTREAM_
#if !defined(_FSTREAM_)
#define _FSTREAM_
#endif   // _FSTREAM_

//////////////////////////////////////////////////////////////////////////////////////////////
// additional headers

#include "../../Repository/CodeProject/Source/PugXML.h"
#include "../../Repository/AfxGadgets/Source/StringConv.h"
#include "../../Repository/AfxGadgets/Source/Win32Error.h"
#include "../../Repository/AfxGadgets/Source/SortingListCtrl.h"
#include "../../Repository/AfxGadgets/Source/PugXMLplus.h"
#include "../../Repository/CodeProject/Source/FolderDlg.h"
#include "../../Repository/CodeProject/Source/ETSLayout.h"
#include "../../Repository/CodeProject/Source/memdc.h"

#if defined(UNICODE) || defined(_UNICODE)
#include "../../Repository/CodeProject/Source/textfile.h"
#endif	// UNICODE

//////////////////////////////////////////////////////////////////////////////////////////////
// Detours headers

#define AFXSCRATCH_DETOURED

#include "../Detours/Include/detours.h"
#include "../Detours/Include/detoured.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// some tricks

// force ISO/IEC 14882 conformance in for loop scope
#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif   // _MSC_VER

// helper macro STRINGIZE
// converts the parameter 'text' to a string after
// macro replacement on 'text' has been performed
#define STRINGIZE(text) STRINGIZE_IMPL(text)
#define STRINGIZE_IMPL(text) #text

#endif   // __stdafx_h

// end of file
