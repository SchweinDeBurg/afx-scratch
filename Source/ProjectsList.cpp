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

// ProjectsList.cpp - implementation of the CProjectsList class

//////////////////////////////////////////////////////////////////////////////////////////////
// PCH includes

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// resource includes

#include "Resource.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// other includes

#include "ProjectsList.h"

#include "MainDialog.h"
#include "AfxScratchApp.h"

#if (_MFC_VER < 0x0700)
#include <../src/afximpl.h>
#else
#include <../src/mfc/afximpl.h>
#endif   // _MFC_VER

//////////////////////////////////////////////////////////////////////////////////////////////
// unwanted ICL warnings

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

//////////////////////////////////////////////////////////////////////////////////////////////
// debugging support

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////
// object model

IMPLEMENT_DYNAMIC(CProjectsList, CSortingListCtrl)

//////////////////////////////////////////////////////////////////////////////////////////////
// message map

BEGIN_MESSAGE_MAP(CProjectsList, CSortingListCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////
// construction/destruction

CProjectsList::CProjectsList(void)
{
}

CProjectsList::~CProjectsList(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
// operations

void CProjectsList::InsertColumns(void)
{
	CRect rectClient;

	GetClientRect(rectClient);
	int cxVScroll = ::GetSystemMetrics(SM_CXVSCROLL);
	int cxColumn = ((rectClient.Width() - cxVScroll) / NUM_COLUMNS);

	CString strDevEnv(MAKEINTRESOURCE(IDS_PROJECT_DEVENV));
	InsertColumn(I_DEVENV, strDevEnv, LVCFMT_LEFT, cxColumn);
	CString strFramework(MAKEINTRESOURCE(IDS_PROJECT_FRAMEWORK));
	InsertColumn(I_FRAMEWORK, strFramework, LVCFMT_LEFT, cxColumn);
	CString strName(MAKEINTRESOURCE(IDS_PROJECT_NAME));
	InsertColumn(I_NAME, strName, LVCFMT_LEFT, cxColumn);
	CString strDescription(MAKEINTRESOURCE(IDS_PROJECT_DESCRIPTION));
	InsertColumn(I_DESCRIPTION, strDescription, LVCFMT_LEFT, cxColumn);
}

void CProjectsList::AutosizeColumns(void)
{
	CRect rectClient;

	int cxColumns = 0;
	for (int i = I_DEVENV; i <= I_NAME; ++i)
	{
		SetColumnWidth(i, LVSCW_AUTOSIZE);
		cxColumns += GetColumnWidth(i);
	}

	GetClientRect(rectClient);
	int cxDescription = std::max(20, rectClient.Width() - cxColumns);
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
	while (!fStop)
	{
		fStop = !finder.FindNextFile();
		if (!finder.IsDots() && !finder.IsDirectory())
		{
			CString strFilePath = finder.GetFilePath();
#if defined(UNICODE) || defined(_UNICODE)
			CTextFileRead fileConfig(strFilePath);
			CString strXML;
			fileConfig.Read(strXML);
			ATL::CAutoVectorPtr<TCHAR> ptrBuffer(new TCHAR[strXML.GetLength() + 1]);
			_tcscpy(ptrBuffer, strXML);
			if (pParser->Parse(ptrBuffer))
#else
			if (pParser->ParseFile(strFilePath))
#endif	// UNICODE
			{
				PROJECT_DATA* pData = new PROJECT_DATA;
				memset(pData, 0, sizeof(*pData));
				_tcscpy(pData->szConfigFile, strFilePath);
				CPugXmlBranch branchRoot = pParser->GetRoot();
				ASSERT(!branchRoot.IsNull());
				CPugXmlBranch branchProject = branchRoot.FindByPath(_T("./Project"));
				ASSERT(!branchProject.IsNull());
				_tcscpy(pData->szDevEnv, branchProject.GetAttribute(_T("DevEnv")));
				_tcscpy(pData->szFramework, branchProject.GetAttribute(_T("Framework")));
				_tcscpy(pData->szName, branchProject.GetAttribute(_T("Name")));
				_tcscpy(pData->szDescription, branchProject.GetAttribute(_T("Description")));
				CString strIcon(branchProject.GetAttribute(_T("Icon")));
				if (!strIcon.IsEmpty())
				{
					CAfxScratchApp* pApp = DYNAMIC_DOWNCAST(CAfxScratchApp, AfxGetApp());
					ASSERT_VALID(pApp);
					CString strIconPath = CString(pszAppData) + _T("\\Config\\") + strIcon;
					HICON hCustomIcon = pApp->LoadSmIconFromFile(strIconPath);
					if (hCustomIcon != NULL)
					{
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
				_tcscpy(pData->szSrcRoot, branchProject.GetAttribute(_T("SrcRoot")));
				lvi.lParam = reinterpret_cast<LPARAM>(pData);
				VERIFY(InsertItem(&lvi) == lvi.iItem);
				SetItemText(lvi.iItem, I_DESCRIPTION, LPSTR_TEXTCALLBACK);
			}
		}

		// pump waiting messages (if any)
		while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
#if (_MFC_VER < 0x0700)
			AfxGetThread()->PumpMessage();
#else
			AfxPumpMessage();
#endif   // _MFC_VER
		}
	}

	if (GetItemCount() > 0)
	{
		SortItems(I_DEVENV, SORT_ASCENDING);
		AutosizeColumns();
		SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, 0xFFFFFFFF);
	}

	// destroy the XML parser
	delete pParser;
}

void CProjectsList::ResetContent(void)
{
	while (GetItemCount() > 0)
	{
		PROJECT_DATA* pData = reinterpret_cast<PROJECT_DATA*>(GetItemData(0));
		ASSERT(pData != NULL);
		DeleteItem(0);
		delete pData;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
// overridables

int CProjectsList::CompareItems(int iItemLhs, int iItemRhs)
{
	PROJECT_DATA* pDataLhs = reinterpret_cast<PROJECT_DATA*>(GetItemData(iItemLhs));
	ASSERT(pDataLhs != NULL);
	PROJECT_DATA* pDataRhs = reinterpret_cast<PROJECT_DATA*>(GetItemData(iItemRhs));
	ASSERT(pDataRhs != NULL);

	switch (m_iSortColumn)
	{
	case I_DEVENV:
		return (_tcscmp(pDataLhs->szDevEnv, pDataRhs->szDevEnv) * m_nSortOrder);
	case I_FRAMEWORK:
		return (_tcscmp(pDataLhs->szFramework, pDataRhs->szFramework) * m_nSortOrder);
	case I_NAME:
		return (_tcscmp(pDataLhs->szName, pDataRhs->szName) * m_nSortOrder);
	case I_DESCRIPTION:
		return (_tcscmp(pDataLhs->szDescription, pDataRhs->szDescription) * m_nSortOrder);
	default:
		// shouldn't be reached
		return (0);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
// message map functions

BOOL CProjectsList::OnEraseBkgnd(CDC* /*pDC*/)
{
	return (TRUE);
}

void CProjectsList::OnPaint(void)
{
	CPaintDC dcPaint(this);
	CMemDC dcMem(&dcPaint);
	enum { fuOptions = PRF_NONCLIENT | PRF_CLIENT };
	SendMessage(WM_PRINTCLIENT, reinterpret_cast<WPARAM>(dcMem.GetSafeHdc()), fuOptions);
	if (::IsWindow(m_headerCustom.GetSafeHwnd()))
	{
		m_headerCustom.SendMessage(WM_PRINTCLIENT, reinterpret_cast<WPARAM>(dcMem.GetSafeHdc()), fuOptions);
	}
}

void CProjectsList::OnGetDispInfo(NMHDR* pHdr, LRESULT* /*pnResult*/)
{
	LVITEM& lvi = reinterpret_cast<NMLVDISPINFO*>(pHdr)->item;
	if ((lvi.mask & LVIF_TEXT) != 0)
	{
		ASSERT(I_DEVENV <= lvi.iSubItem && lvi.iSubItem <= I_DESCRIPTION);
		PROJECT_DATA* pData = reinterpret_cast<PROJECT_DATA*>(GetItemData(lvi.iItem));
		ASSERT(pData != NULL);
		switch (lvi.iSubItem)
		{
		case I_DEVENV:
			_tcsncpy(lvi.pszText, pData->szDevEnv, lvi.cchTextMax);
			break;
		case I_FRAMEWORK:
			_tcsncpy(lvi.pszText, pData->szFramework, lvi.cchTextMax);
			break;
		case I_NAME:
			_tcsncpy(lvi.pszText, pData->szName, lvi.cchTextMax);
			break;
		case I_DESCRIPTION:
			_tcsncpy(lvi.pszText, pData->szDescription, lvi.cchTextMax);
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
// diagnostic services

#if defined(_DEBUG)

void CProjectsList::AssertValid(void) const
{
	// first perform inherited validity check...
	CSortingListCtrl::AssertValid();

	// ...and then verify our own state as well
}

void CProjectsList::Dump(CDumpContext& dumpCtx) const
{
	try
	{
		// first invoke inherited dumper...
		CSortingListCtrl::Dump(dumpCtx);

		// ...and then dump own unique members
	}
	catch (CFileException* pXcpt)
	{
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif   // _DEBUG

// end of file
