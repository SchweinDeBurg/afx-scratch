// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// CustomListCtrl.cpp - implementation of the CCustomListCtrl class

#include "stdafx.h"
#include "CustomListCtrl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// object model
IMPLEMENT_DYNAMIC(CCustomListCtrl, CListCtrl)

// message map
BEGIN_MESSAGE_MAP(CCustomListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
END_MESSAGE_MAP()

CCustomListCtrl::CCustomListCtrl(void):
m_iSortColumn(-1),
m_nSortOrder(0)
{
}

CCustomListCtrl::~CCustomListCtrl(void)
{
}

void CCustomListCtrl::SortContent(int iColumn, SORT_ORDER eOrder)
{
	m_iSortColumn = iColumn;
	m_nSortOrder = eOrder;
	ASSERT(sizeof(this) <= sizeof(DWORD));
	ListView_SortItemsEx(GetSafeHwnd(), CompareProc, reinterpret_cast<LPARAM>(this));
}

void CCustomListCtrl::OnColumnClick(NMHDR* pHdr, LRESULT* /*pnResult*/)
{
	int iColumn = reinterpret_cast<NMLISTVIEW*>(pHdr)->iSubItem;
	if (m_iSortColumn != iColumn) {
		// sort by another column in ascending order
		m_iSortColumn = iColumn;
		m_nSortOrder = SORT_ASCENDING;
	}
	else {
		// reverse sort order for the current column
		m_nSortOrder *= -1;
	}
	ASSERT(sizeof(this) <= sizeof(DWORD));
	ListView_SortItemsEx(GetSafeHwnd(), CompareProc, reinterpret_cast<LPARAM>(this));
}

int CALLBACK CCustomListCtrl::CompareProc(LPARAM iItemLhs, LPARAM iItemRhs, LPARAM nData)
{
	CCustomListCtrl* pListCtrl = reinterpret_cast<CCustomListCtrl*>(nData);
	ASSERT_VALID(pListCtrl);
	return (pListCtrl->CompareItems(iItemLhs, iItemRhs));
}

#if defined(_DEBUG)

void CCustomListCtrl::AssertValid(void) const
{
	// first perform inherited validity check...
	CListCtrl::AssertValid();
	// ...and then verify our own state as well
}

void CCustomListCtrl::Dump(CDumpContext& dumpCtx) const
{
	try {
		// first invoke inherited dumper...
		CListCtrl::Dump(dumpCtx);
		// ...and then dump own unique members
		dumpCtx << "m_iSortColumn = " << m_iSortColumn;
		dumpCtx << "\nm_nSortOrder = " << m_nSortOrder;
	}
	catch (CFileException* pXcpt) {
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif	// _DEBUG

// end of file
