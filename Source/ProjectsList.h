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

// ProjectsList.h - interface of the CProjectsList class

#if !defined(__ProjectsList_h)
#define __ProjectsList_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif   // _MSC_VER

class CProjectsList: public CSortingListCtrl
{
	DECLARE_DYNAMIC(CProjectsList)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	CProjectsList(void);
	virtual ~CProjectsList(void);

// operations
public:
	void InsertColumns(void);
	void AutosizeColumns(void);
	void InitContent(LPCTSTR pszAppData);
	void ResetContent(void);

// overridables
protected:
	virtual int CompareItems(int iItemLhs, int iItemRhs);

// message map functions
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint(void);
	afx_msg void OnGetDispInfo(NMHDR* pHdr, LRESULT* pnResult);

// attributes
public:
	enum
	{
		// column indices
		I_DEVENV,
		I_FRAMEWORK,
		I_NAME,
		I_DESCRIPTION,
		NUM_COLUMNS   // should be the LAST enumerator!
	};
	CCustomHeaderCtrl m_headerCustom;

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif   // __ProjectsList_h

// end of file
