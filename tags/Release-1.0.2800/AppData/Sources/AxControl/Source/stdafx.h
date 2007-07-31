// Ax$CONTROL$ ActiveX control.
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
#include <afxctl.h>			// MFC support for ActiveX controls

#pragma hdrstop

#undef IMPLEMENT_OLECREATE_EX

#define IMPLEMENT_OLECREATE_EX(class_name, external_name) \
	const AFX_DATADEF GUID class_name::guid = __uuidof(class_name); \
	const TCHAR _szProgID_##class_name[] = _T(external_name); \
	AFX_DATADEF class_name::class_name##Factory class_name::factory( \
		class_name::guid, RUNTIME_CLASS(class_name), FALSE, \
		_szProgID_##class_name); \
	HRESULT class_name::GetClassID(LPCLSID pclsid) \
		{ *pclsid = guid; return (NOERROR); }

// shared globals
extern const WORD g_wVerMajor;
extern const WORD g_wVerMinor;

#endif	// __stdafx_h

// end of file