// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// ProjectsList.h - interface of the CProjectsList class

#if !defined(__ProjectsList_h)
#define __ProjectsList_h

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
	afx_msg void OnGetDispInfo(NMHDR* pHdr, LRESULT* pnResult);

// attributes
public:
	enum {
		// column indices
		I_NAME,
		I_DESCRIPTION,
		NUM_COLUMNS		// should be the LAST enumerator!
	};

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif	// __ProjectsList_h

// end of file
