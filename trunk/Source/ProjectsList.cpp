// AfxScratch application.
// Copyright (c) 2004-2005 by Elijah Zarezky,
// All rights reserved.

// ProjectsList.cpp - implementation of the CProjectsList class

#include "stdafx.h"
#include "ProjectsList.h"
#include "Resource.h"
#include "AuxTypes.h"
#include "MacrosList.h"
#include "MainDialog.h"
#include "AfxScratchApp.h"

#if (_MFC_VER > 0x0600)
#include <../src/mfc/afximpl.h>
#else
#include <../src/afximpl.h>
#endif	// _MFC_VER

#if defined(__INTEL_COMPILER)
// remark #171: invalid type conversion
#pragma warning(disable: 171)
// remark #279: controlling expression is constant
#pragma warning(disable: 279)
// remark #383: value copied to temporary, reference to temporary used
#pragma warning(disable: 383)
// remark #981: operands are evaluated in unspecified order
#pragma warning(disable: 981)
#endif	// __INTEL_COMPILER

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// object model
IMPLEMENT_DYNAMIC(CProjectsList, CSortingListCtrl)

// message map
BEGIN_MESSAGE_MAP(CProjectsList, CSortingListCtrl)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
END_MESSAGE_MAP()

CProjectsList::CProjectsList(void)
{
}

CProjectsList::~CProjectsList(void)
{
}

void CProjectsList::InsertColumns(void)
{
	CRect rectClient;
	CString strHeading;

	GetClientRect(rectClient);
	int cxVScroll = ::GetSystemMetrics(SM_CXVSCROLL);
	int cxColumn = ((rectClient.Width() - cxVScroll) / NUM_COLUMNS);

	strHeading.LoadString(IDS_PROJECT_NAME);
	InsertColumn(I_NAME, strHeading, LVCFMT_LEFT, cxColumn);
	strHeading.LoadString(IDS_PROJECT_DESCRIPTION);
	InsertColumn(I_DESCRIPTION, strHeading, LVCFMT_LEFT, cxColumn);
}

void CProjectsList::AutosizeColumns(void)
{
	CRect rectClient;

	SetColumnWidth(I_NAME, LVSCW_AUTOSIZE);
	int cxName = GetColumnWidth(I_NAME);
	GetClientRect(rectClient);
	int cxDescription = std::max(20, rectClient.Width() - cxName);
	SetColumnWidth(I_DESCRIPTION, cxDescription);
}

void CProjectsList::InitContent(LPCTSTR pszAppData)
{
	LVITEM lvi;
	CFileFind finder;
	MSG msg;
	TCHAR szErrMsg[256];

	ASSERT(AfxIsValidString(pszAppData));

	CMainDialog* pMainDlg = DYNAMIC_DOWNCAST(CMainDialog, GetParent());
	ASSERT_VALID(pMainDlg);

	memset(&lvi, 0, sizeof(lvi));
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvi.pszText = LPSTR_TEXTCALLBACK;

	// create the XML parser
	CPugXmlParser* pParser = new CPugXmlParser();

	// walk through the configuration files
	CString strFileMask = CString(pszAppData) + _T("\\Config\\*.xml");
	BOOL fStop = !finder.FindFile(strFileMask);
	while (!fStop) {
		fStop = !finder.FindNextFile();
		if (!finder.IsDots() && !finder.IsDirectory()) {
			CString strFilePath = finder.GetFilePath();
			if (pParser->ParseFile(strFilePath)) {
				PROJECT_DATA* pData = new PROJECT_DATA;
				memset(pData, 0, sizeof(*pData));
				::lstrcpy(pData->szConfigFile, strFilePath);
				CPugXmlBranch branchRoot = pParser->GetRoot();
				ASSERT(!branchRoot.IsNull());
				CPugXmlBranch branchProject = branchRoot.FindByPath(_T("./Project"));
				ASSERT(!branchProject.IsNull());
				::lstrcpy(pData->szName, branchProject.GetAttribute(_T("Name")));
				::lstrcpy(pData->szDescription, branchProject.GetAttribute(_T("Description")));
				CString strIcon(branchProject.GetAttribute(_T("Icon")));
				if (!strIcon.IsEmpty()) {
					CAfxScratchApp* pApp = DYNAMIC_DOWNCAST(CAfxScratchApp, AfxGetApp());
					ASSERT_VALID(pApp);
					CString strIconPath = CString(pszAppData) + _T("\\Config\\") + strIcon;
					HICON hCustomIcon = pApp->LoadSmIconFromFile(strIconPath);
					if (hCustomIcon != NULL) {
						// use specified custom icon
						CImageList* pImageList = GetImageList(LVSIL_SMALL);
						ASSERT_VALID(pImageList);
						lvi.iImage = pImageList->Add(hCustomIcon);
					}
					else {
						// failed to load specified custom icon - use default
						CWin32Error xcpt(::GetLastError());
						xcpt.GetErrorMessage(szErrMsg, _countof(szErrMsg));
						AfxMessageBox(szErrMsg, MB_ICONWARNING | MB_OK);
						lvi.iImage = pMainDlg->m_iProjectIcon;
					}
				}
				else {
					// use default icon
					lvi.iImage = pMainDlg->m_iProjectIcon;
				}
				lvi.lParam = reinterpret_cast<LPARAM>(pData);
				VERIFY(InsertItem(&lvi) == lvi.iItem);
				SetItemText(lvi.iItem, I_DESCRIPTION, LPSTR_TEXTCALLBACK);
			}
		}
		// pump waiting messages (if any)
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	if (GetItemCount() > 0) {
		SortItems(I_NAME, SORT_ASCENDING);
		AutosizeColumns();
		SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, 0xFFFFFFFF);
	}

	// destroy the XML parser
	delete pParser;
}

void CProjectsList::ResetContent(void)
{
	while (GetItemCount() > 0) {
		PROJECT_DATA* pData = reinterpret_cast<PROJECT_DATA*>(GetItemData(0));
		ASSERT(pData != NULL);
		DeleteItem(0);
		delete pData;
	}
}

int CProjectsList::CompareItems(int iItemLhs, int iItemRhs)
{
	PROJECT_DATA* pDataLhs = reinterpret_cast<PROJECT_DATA*>(GetItemData(iItemLhs));
	ASSERT(pDataLhs != NULL);
	PROJECT_DATA* pDataRhs = reinterpret_cast<PROJECT_DATA*>(GetItemData(iItemRhs));
	ASSERT(pDataRhs != NULL);

	switch (m_iSortColumn)
	{
	case I_NAME:
		return (::lstrcmp(pDataLhs->szName, pDataRhs->szName) * m_nSortOrder);
	case I_DESCRIPTION:
		return (::lstrcmp(pDataLhs->szDescription, pDataRhs->szDescription) * m_nSortOrder);
	default:
		// shouldn't be reached
		return (0);
	}
}

void CProjectsList::OnGetDispInfo(NMHDR* pHdr, LRESULT* /*pnResult*/)
{
	LVITEM& lvi = reinterpret_cast<NMLVDISPINFO*>(pHdr)->item;
	if ((lvi.mask & LVIF_TEXT) != 0) {
		ASSERT(I_NAME <= lvi.iSubItem && lvi.iSubItem <= I_DESCRIPTION);
		PROJECT_DATA* pData = reinterpret_cast<PROJECT_DATA*>(GetItemData(lvi.iItem));
		ASSERT(pData != NULL);
		switch (lvi.iSubItem)
		{
		case I_NAME:
			::lstrcpyn(lvi.pszText, pData->szName, lvi.cchTextMax);
			break;
		case I_DESCRIPTION:
			::lstrcpyn(lvi.pszText, pData->szDescription, lvi.cchTextMax);
			break;
		}
	}
}

#if defined(_DEBUG)

void CProjectsList::AssertValid(void) const
{
	// first perform inherited validity check...
	CSortingListCtrl::AssertValid();
	// ...and then verify our own state as well
}

void CProjectsList::Dump(CDumpContext& dumpCtx) const
{
	try {
		// first invoke inherited dumper...
		CSortingListCtrl::Dump(dumpCtx);
		// ...and then dump own unique members
	}
	catch (CFileException* pXcpt) {
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif	// _DEBUG

// end of file
