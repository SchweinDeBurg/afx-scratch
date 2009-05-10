// AfxScratch application.
// Copyright (c) 2004-2006 by Elijah Zarezky,
// All rights reserved.

// ProjectsList.h - interface of the CProjectsList class

#if !defined(__ProjectsList_h)
#define __ProjectsList_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif	// _MSC_VER

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
	enum {
		// column indices
		I_NAME,
		I_DESCRIPTION,
		NUM_COLUMNS		// should be the LAST enumerator!
	};
	CCustomHeaderCtrl m_headerCustom;

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif	// __ProjectsList_h

// end of file