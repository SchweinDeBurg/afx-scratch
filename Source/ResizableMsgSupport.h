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

// ResizableMsgSupport.h: some declarations to support custom resizable wnds
//
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2002 by Paolo Messina
// (http://www.geocities.com/ppescher - ppescher@yahoo.com)
//
// The contents of this file are subject to the Artistic License (the "License").
// You may not use this file except in compliance with the License. 
// You may obtain a copy of the License at:
// http://www.opensource.org/licenses/artistic-license.html
//
// If you find this code useful, credits would be nice!
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIZABLEMSGSUPPORT_H__INCLUDED_)
#define AFX_RESIZABLEMSGSUPPORT_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagRESIZEPROPERTIES
{
	// wether to ask for resizing properties every time
	BOOL bAskClipping;
	BOOL bAskRefresh;
	// otherwise, use the cached properties
	BOOL bCachedLikesClipping;
	BOOL bCachedNeedsRefresh;

	// initialize with valid data
	tagRESIZEPROPERTIES() : bAskClipping(TRUE), bAskRefresh(TRUE) {}

} RESIZEPROPERTIES, *PRESIZEPROPERTIES, *LPRESIZEPROPERTIES;


typedef struct tagCLIPPINGPROPERTY
{
	BOOL bLikesClipping;

	// initialize with valid data
	tagCLIPPINGPROPERTY() : bLikesClipping(FALSE) {}

} CLIPPINGPROPERTY, *PCLIPPINGPROPERTY, *LPCLIPPINGPROPERTY;


typedef struct tagREFRESHPROPERTY
{
	BOOL bNeedsRefresh;
	RECT rcOld;
	RECT rcNew;

	// initialize with valid data
	tagREFRESHPROPERTY() : bNeedsRefresh(TRUE) {}

} REFRESHPROPERTY, *PREFRESHPROPERTY, *LPREFRESHPROPERTY;


// registered message to communicate with the library
extern const UINT WMU_RESIZESUPPORT;

// if the message is implemented the returned value must be non-zero
// the default window procedure returns zero for unhandled messages

// wParam is one of the following RSZSUP_* values, lParam as specified
enum ResizeSupport
{
	RSZSUP_QUERYPROPERTIES	= 101,	// lParam = LPRESIZEPROPERTIES
	RSZSUP_LIKESCLIPPING	= 102,	// lParam = LPCLIPPINGPROPERTY
	RSZSUP_NEEDSREFRESH		= 103,	// lParam = LPREFRESHPROPERTY
	RSZSUP_SHEETPAGEEXHACK	= 104,	// lParam = HWND (source prop.page)
};

/////////////////////////////////////////////////////////////////////////////
// utility functions

inline BOOL Send_QueryProperties(HWND hWnd, LPRESIZEPROPERTIES pResizeProperties)
{
	return (0 != SendMessage(hWnd, WMU_RESIZESUPPORT,
		RSZSUP_QUERYPROPERTIES, (LPARAM)pResizeProperties));
}

inline BOOL Send_LikesClipping(HWND hWnd, LPCLIPPINGPROPERTY pClippingProperty)
{
	return (0 != SendMessage(hWnd, WMU_RESIZESUPPORT,
		RSZSUP_LIKESCLIPPING, (LPARAM)pClippingProperty));
}

inline BOOL Send_NeedsRefresh(HWND hWnd, LPREFRESHPROPERTY pRefreshProperty)
{
	return (0 != SendMessage(hWnd, WMU_RESIZESUPPORT,
		RSZSUP_NEEDSREFRESH, (LPARAM)pRefreshProperty));
}

inline void Post_SheetPageExHack(HWND hWndSheet, HWND hWndPage)
{
	PostMessage(hWndSheet, WMU_RESIZESUPPORT,
		RSZSUP_SHEETPAGEEXHACK, (LPARAM)hWndPage);
}

#endif // !defined(AFX_RESIZABLEMSGSUPPORT_H__INCLUDED_)
