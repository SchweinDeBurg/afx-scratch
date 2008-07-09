// AfxScratch application.
// Copyright (c) 2004-2008 by Elijah Zarezky,
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

// CustomGroupBox.cpp - implementation of the CCustomGroupBox class

//////////////////////////////////////////////////////////////////////////////////////////////
// PCH includes

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// other includes

#include "CustomGroupBox.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// debugging support

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif   // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////
// object model

IMPLEMENT_DYNAMIC(CCustomGroupBox, CButton)

//////////////////////////////////////////////////////////////////////////////////////////////
// message map

BEGIN_MESSAGE_MAP(CCustomGroupBox, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////
// message map functions

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
