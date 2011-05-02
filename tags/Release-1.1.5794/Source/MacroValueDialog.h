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

// MacroValueDialog.h - interface of the CMacroValueDialog class

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif   // _MSC_VER

#if !defined(__MacroValueDialog_h)
#define __MacroValueDialog_h

//////////////////////////////////////////////////////////////////////////////////////////////
// dependent includes

#include "AuxTypes.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// CMacroValueDialog

class CMacroValueDialog: public CDialog
{
	DECLARE_DYNAMIC(CMacroValueDialog)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	CMacroValueDialog(const MACRO_DATA* pData, CWnd* pParentWnd = NULL);
	virtual ~CMacroValueDialog(void);

// overridables
public:
	virtual BOOL OnInitDialog(void) override;
protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;

// message map functions
protected:
	afx_msg void OnChangeEditValue(void);

// attributes
public:
	CString m_strName;
	CString m_strDescription;
	MACRO_DATA::TYPE m_eTypeID;
	CString m_strValue;

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const override;
	virtual void Dump(CDumpContext& dumpCtx) const override;
#endif
};

#endif   // __MacroValueDialog_h

// end of file
