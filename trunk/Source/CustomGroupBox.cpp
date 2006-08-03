// AfxScratch application.
// Copyright (c) 2004-2005 by Elijah Zarezky,
// All rights reserved.

// CustomGroupBox.cpp - implementation of the CCustomGroupBox class

#include "stdafx.h"
#include "CustomGroupBox.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// object model
IMPLEMENT_DYNAMIC(CCustomGroupBox, CButton)

// message map
BEGIN_MESSAGE_MAP(CCustomGroupBox, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CCustomGroupBox::OnEraseBkgnd(CDC* /*pDC*/)
{
	return (TRUE);
}

void CCustomGroupBox::OnPaint(void)
{
	CPaintDC dcPaint(this);
	CMemDC dcMem(&dcPaint);
	enum { fuOptions = PRF_CLIENT };
	SendMessage(WM_PRINT, reinterpret_cast<WPARAM>(dcMem.GetSafeHdc()), fuOptions);
}

// end of file
