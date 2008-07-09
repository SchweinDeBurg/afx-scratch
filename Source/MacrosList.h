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

// MacrosList.h - interface of the CMacrosList class

#if !defined(__MacrosList_h)
#define __MacrosList_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif   // _MSC_VER

class CMacrosList: public CSortingListCtrl
{
	DECLARE_DYNAMIC(CMacrosList)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	CMacrosList(void);
	virtual ~CMacrosList(void);

// operations
public:
	void InsertColumns(void);
	void AutosizeColumns(void);
	void InitContent(LPCTSTR pszConfigFile);
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
		I_NAME,
		I_DESCRIPTION,
		I_TYPE,
		I_VALUE,
		NUM_COLUMNS   // should be the LAST enumerator!
	};
	CCustomHeaderCtrl m_headerCustom;

// implementation helpers
private:
	BOOL IsMacroValueExists(MACRO_DATA* pData);
	void SuggestMacroValue(MACRO_DATA* pData);
	typedef void(CMacrosList::* PMF_SUGGEST)(LPTSTR);
	CMap<CString, LPCTSTR, PMF_SUGGEST, PMF_SUGGEST> m_mapSuggest;
	void Suggest_AUTHOR(LPTSTR pszDest);
	void Suggest_COMPANY(LPTSTR pszDest);
	void Suggest_VERMAJOR(LPTSTR pszDest);
	void Suggest_VERBUILD(LPTSTR pszDest);
	void Suggest_UUID(LPTSTR pszDest);

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif   // __MacrosList_h

// end of file
