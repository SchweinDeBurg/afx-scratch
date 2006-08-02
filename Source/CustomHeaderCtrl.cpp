// AfxScratch application.
// Copyright (c) 2004-2005 by Elijah Zarezky,
// All rights reserved.

// CustomHeaderCtrl.cpp - implementation of the CCustomHeaderCtrl class

#include "stdafx.h"
#include "CustomHeaderCtrl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// object model
IMPLEMENT_DYNAMIC(CCustomHeaderCtrl, CHeaderCtrl)

// message map
BEGIN_MESSAGE_MAP(CCustomHeaderCtrl, CHeaderCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CCustomHeaderCtrl::OnEraseBkgnd(CDC* /*pDC*/)
{
	return (FALSE);
}

void CCustomHeaderCtrl::OnPaint(void)
{
	CPaintDC dcPaint(this);
	CMemDC dcMem(&dcPaint);
	enum { fuOptions = PRF_NONCLIENT | PRF_CLIENT };
	SendMessage(WM_PRINTCLIENT, reinterpret_cast<WPARAM>(dcMem.GetSafeHdc()), fuOptions);
}

// end of file
