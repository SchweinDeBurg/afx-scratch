// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// CustomListCtrl.h - interface of the CCustomListCtrl class

#if !defined(__CustomListCtrl_h)
#define __CustomListCtrl_h

class CCustomListCtrl: public CListCtrl
{
	DECLARE_DYNAMIC(CCustomListCtrl)
	DECLARE_MESSAGE_MAP()

// construction/destruction
protected:
	CCustomListCtrl(void);
	virtual ~CCustomListCtrl(void);

// operations
public:
	enum SORT_ORDER { SORT_ASCENDING = 1, SORT_DESCENDING = -1 };
	void SortContent(int iColumn, SORT_ORDER eOrder);

// overridables
protected:
	virtual int CompareItems(int iItemLhs, int iItemRhs) = 0;

// message map functions
protected:
	afx_msg void OnColumnClick(NMHDR* pHdr, LRESULT* pnResult);

// attributes
protected:
	int m_iSortColumn;
	int m_nSortOrder;		// magic: +1 if ascending, -1 if descending

// implementation helpers
private:
	static int CALLBACK CompareProc(LPARAM iItemLhs, LPARAM iItemRhs, LPARAM nData);

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif	// __CustomListCtrl_h

// end of file
