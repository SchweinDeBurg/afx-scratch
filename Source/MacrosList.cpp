// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// MacrosList.cpp - implementation of the CMacrosList class

#include "stdafx.h"
#include "CustomListCtrl.h"
#include "MacrosList.h"
#include "Resource.h"
#include "AuxTypes.h"
#include "ProjectsList.h"
#include "MainDialog.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// object model
IMPLEMENT_DYNAMIC(CMacrosList, CCustomListCtrl)

// message map
BEGIN_MESSAGE_MAP(CMacrosList, CCustomListCtrl)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
END_MESSAGE_MAP()

CMacrosList::CMacrosList(void)
{
}

CMacrosList::~CMacrosList(void)
{
}

void CMacrosList::InsertColumns(void)
{
	CRect rectClient;
	CString strHeading;

	GetClientRect(rectClient);
	int cxVScroll = ::GetSystemMetrics(SM_CXVSCROLL);
	int cxColumn = ((rectClient.Width() - cxVScroll) / NUM_COLUMNS);

	strHeading.LoadString(IDS_MACRO_NAME);
	InsertColumn(I_NAME, strHeading, LVCFMT_LEFT, cxColumn);
	strHeading.LoadString(IDS_MACRO_DESCRIPTION);
	InsertColumn(I_DESCRIPTION, strHeading, LVCFMT_LEFT, cxColumn);
	strHeading.LoadString(IDS_MACRO_VALUE);
	InsertColumn(I_VALUE, strHeading, LVCFMT_LEFT, cxColumn);
}

void CMacrosList::AutosizeColumns(void)
{
	CRect rectClient;

	SetColumnWidth(I_NAME, LVSCW_AUTOSIZE);
	SetColumnWidth(I_VALUE, LVSCW_AUTOSIZE);

	int cxName = GetColumnWidth(I_NAME);
	int cxValue = GetColumnWidth(I_VALUE);
	GetClientRect(rectClient);
	int cxVScroll = ::GetSystemMetrics(SM_CXVSCROLL);
	int cxDescription = std::max(20, rectClient.Width() - cxName - cxValue - cxVScroll);
	SetColumnWidth(I_DESCRIPTION, cxDescription);
}

void CMacrosList::InitContent(LPCTSTR pszConfigFile)
{
	LVITEM lvi;
	TCHAR szUserName[UNLEN + 1];

	ASSERT(AfxIsValidString(pszConfigFile));

	CMainDialog* pMainDlg = DYNAMIC_DOWNCAST(CMainDialog, GetParent());
	ASSERT_VALID(pMainDlg);

	memset(&lvi, 0, sizeof(lvi));
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.iImage = pMainDlg->m_iMacroIcon;

	// create the XML parser
	CPugXmlParser* pParser = new CPugXmlParser();

	if (pParser->ParseFile(pszConfigFile)) {
		CPugXmlBranch branchRoot = pParser->GetRoot();
		ASSERT(!branchRoot.IsNull());
		CPugXmlBranch branchMacros = branchRoot.FindByPath(_T("./Project/Macros"));
		ASSERT(!branchMacros.IsNull());
		int nNumMacros = branchMacros.GetChildrenCount();
		for (int i = 0; i < nNumMacros; ++i) {
			CPugXmlBranch branchMacro = branchMacros.GetChildAt(i);
			ASSERT(!branchMacro.IsNull());
			MACRO_DATA* pData = new MACRO_DATA;
			memset(pData, 0, sizeof(*pData));
			::lstrcpy(pData->szName, branchMacro.GetAttribute(_T("Name")));
			::lstrcpy(pData->szDescription, branchMacro.GetAttribute(_T("Description")));
			::lstrcpy(pData->szValue, branchMacro.GetAttribute(_T("Default")));
			if (::lstrlen(pData->szValue) == 0) {
				// no default value was specified - try to suggest
				CString strMacroName(pData->szName);
				if (strMacroName == _T("$AUTHOR$")) {
					// special case #1
					DWORD cchNameLength = UNLEN + 1;
					::GetUserName(szUserName, &cchNameLength);
					::lstrcpy(pData->szValue, szUserName);
				}
			}
			lvi.lParam = reinterpret_cast<LPARAM>(pData);
			VERIFY(InsertItem(&lvi) == lvi.iItem);
			for (int j = I_DESCRIPTION; j < NUM_COLUMNS; ++j) {
				SetItemText(lvi.iItem, j, LPSTR_TEXTCALLBACK);
			}
		}
	}

	if (GetItemCount() > 0) {
		SortContent(I_NAME, SORT_ASCENDING);
		AutosizeColumns();
		SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, 0xFFFFFFFF);
	}

	// destroy the XML parser
	delete pParser;
}

void CMacrosList::ResetContent(void)
{
	while (GetItemCount() > 0) {
		MACRO_DATA* pData = reinterpret_cast<MACRO_DATA*>(GetItemData(0));
		ASSERT(pData != NULL);
		DeleteItem(0);
		delete pData;
	}
}

int CMacrosList::CompareItems(int iItemLhs, int iItemRhs)
{
	MACRO_DATA* pDataLhs = reinterpret_cast<MACRO_DATA*>(GetItemData(iItemLhs));
	ASSERT(pDataLhs != NULL);
	MACRO_DATA* pDataRhs = reinterpret_cast<MACRO_DATA*>(GetItemData(iItemRhs));
	ASSERT(pDataRhs != NULL);

	switch (m_iSortColumn)
	{
	case I_NAME:
		return (::lstrcmp(pDataLhs->szName, pDataRhs->szName) * m_nSortOrder);
	case I_DESCRIPTION:
		return (::lstrcmp(pDataLhs->szDescription, pDataRhs->szDescription) * m_nSortOrder);
	case I_VALUE:
		return (::lstrcmp(pDataLhs->szValue, pDataRhs->szValue) * m_nSortOrder);
	default:
		// shouldn't be reached
		return (0);
	}
}

void CMacrosList::OnGetDispInfo(NMHDR* pHdr, LRESULT* /*pnResult*/)
{
	LVITEM& lvi = reinterpret_cast<NMLVDISPINFO*>(pHdr)->item;
	if ((lvi.mask & LVIF_TEXT) != 0) {
		ASSERT(I_NAME <= lvi.iSubItem && lvi.iSubItem <= I_VALUE);
		MACRO_DATA* pData = reinterpret_cast<MACRO_DATA*>(GetItemData(lvi.iItem));
		ASSERT(pData != NULL);
		switch (lvi.iSubItem)
		{
		case I_NAME:
			::lstrcpyn(lvi.pszText, pData->szName, lvi.cchTextMax);
			break;
		case I_DESCRIPTION:
			::lstrcpyn(lvi.pszText, pData->szDescription, lvi.cchTextMax);
			break;
		case I_VALUE:
			::lstrcpyn(lvi.pszText, pData->szValue, lvi.cchTextMax);
			break;
		}
	}
}

#if defined(_DEBUG)

void CMacrosList::AssertValid(void) const
{
	// first perform inherited validity check...
	CCustomListCtrl::AssertValid();
	// ...and then verify our own state as well
}

void CMacrosList::Dump(CDumpContext& dumpCtx) const
{
	try {
		// first invoke inherited dumper...
		CCustomListCtrl::Dump(dumpCtx);
		// ...and then dump own unique members
	}
	catch (CFileException* pXcpt) {
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif	// _DEBUG

// end of file
