// AfxScratch application.
// Copyright (c) 2004-2006 by Elijah Zarezky,
// All rights reserved.

// MacrosList.cpp - implementation of the CMacrosList class

#include "stdafx.h"
#include "AuxTypes.h"
#include "CustomHeaderCtrl.h"
#include "MacrosList.h"
#include "Resource.h"
#include "ProjectsList.h"
#include "CustomGroupBox.h"
#include "ResizableLayout.h"
#include "MainDialog.h"

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
IMPLEMENT_DYNAMIC(CMacrosList, CSortingListCtrl)

// message map
BEGIN_MESSAGE_MAP(CMacrosList, CSortingListCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
END_MESSAGE_MAP()

CMacrosList::CMacrosList(void)
{
	m_mapSuggest.SetAt(_T("$AUTHOR$"), Suggest_AUTHOR);
	m_mapSuggest.SetAt(_T("$COMPANY$"), Suggest_COMPANY);
	m_mapSuggest.SetAt(_T("$VERMAJOR$"), Suggest_VERMAJOR);
	m_mapSuggest.SetAt(_T("$VERBUILD$"), Suggest_VERBUILD);
	m_mapSuggest.SetAt(_T("$UUID$"), Suggest_UUID);
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
	strHeading.LoadString(IDS_MACRO_TYPE);
	InsertColumn(I_TYPE, strHeading, LVCFMT_LEFT, cxColumn);
	strHeading.LoadString(IDS_MACRO_VALUE);
	InsertColumn(I_VALUE, strHeading, LVCFMT_LEFT, cxColumn);
}

void CMacrosList::AutosizeColumns(void)
{
	CRect rectClient;

	SetColumnWidth(I_NAME, LVSCW_AUTOSIZE);
	int cxName = GetColumnWidth(I_NAME);
	SetColumnWidth(I_TYPE, LVSCW_AUTOSIZE);
	int cxType = GetColumnWidth(I_TYPE);
	SetColumnWidth(I_VALUE, LVSCW_AUTOSIZE);
	int cxValue = GetColumnWidth(I_VALUE);
	GetClientRect(rectClient);
	int cxDescription = std::max(20, rectClient.Width() - cxName - cxType - cxValue);
	SetColumnWidth(I_DESCRIPTION, cxDescription);
}

void CMacrosList::InitContent(LPCTSTR pszConfigFile)
{
	LVITEM lvi;
	UINT idsType;

	ASSERT(AfxIsValidString(pszConfigFile));

	CMainDialog* pMainDlg = DYNAMIC_DOWNCAST(CMainDialog, GetParent());
	ASSERT_VALID(pMainDlg);

	memset(&lvi, 0, sizeof(lvi));
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.iImage = pMainDlg->m_iMacroIcon;

	// create the XML parser
	CPugXmlParser* pParser = new CPugXmlParser();

	if (pParser->ParseFile(pszConfigFile))
	{
		CPugXmlBranch branchRoot = pParser->GetRoot();
		ASSERT(!branchRoot.IsNull());
		CPugXmlBranch branchMacros = branchRoot.FindByPath(_T("./Project/Macros"));
		ASSERT(!branchMacros.IsNull());
		int nNumMacros = branchMacros.GetChildrenCount();
		for (int i = 0; i < nNumMacros; ++i)
		{
			CPugXmlBranch branchMacro = branchMacros.GetChildAt(i);
			ASSERT(!branchMacro.IsNull());
			MACRO_DATA* pData = new MACRO_DATA;
			memset(pData, 0, sizeof(*pData));
			::lstrcpy(pData->szName, branchMacro.GetAttribute(_T("Name")));
			::lstrcpy(pData->szDescription, branchMacro.GetAttribute(_T("Description")));
			CString strMacroType(branchMacro.GetAttribute(_T("Type")));
			if (strMacroType == _T("number"))
			{
				// numeric value
				pData->eTypeID = MACRO_DATA::NUMBER;
				idsType = IDS_TYPE_NUMBER;
			}
			else if (strMacroType == _T("uuid"))
			{
				// UUID value
				pData->eTypeID = MACRO_DATA::UUID;
				idsType = IDS_TYPE_UUID;
			}
			else {
				// assume string value
				pData->eTypeID = MACRO_DATA::STRING;
				idsType = IDS_TYPE_STRING;
			}
			::LoadString(AfxGetResourceHandle(), idsType, pData->szType, MACRO_DATA::MAX_TYPE);
			::lstrcpy(pData->szValue, branchMacro.GetAttribute(_T("Default")));
			if (!IsMacroValueExists(pData))
			{
				// default value wasn't specified or invalid - try to suggest
				SuggestMacroValue(pData);
			}
			lvi.lParam = reinterpret_cast<LPARAM>(pData);
			VERIFY(InsertItem(&lvi) == lvi.iItem);
			for (int j = I_DESCRIPTION; j < NUM_COLUMNS; ++j)
			{
				SetItemText(lvi.iItem, j, LPSTR_TEXTCALLBACK);
			}
		}
	}

	if (GetItemCount() > 0)
	{
		SortItems(I_NAME, SORT_ASCENDING);
		AutosizeColumns();
		SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, 0xFFFFFFFF);
	}

	// destroy the XML parser
	delete pParser;
}

void CMacrosList::ResetContent(void)
{
	while (GetItemCount() > 0)
	{
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
	case I_TYPE:
		return (::lstrcmp(pDataLhs->szType, pDataRhs->szType) * m_nSortOrder);
	case I_VALUE:
		return (::lstrcmp(pDataLhs->szValue, pDataRhs->szValue) * m_nSortOrder);
	default:
		// shouldn't be reached
		return (0);
	}
}

BOOL CMacrosList::OnEraseBkgnd(CDC* /*pDC*/)
{
	return (TRUE);
}

void CMacrosList::OnPaint(void)
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

void CMacrosList::OnGetDispInfo(NMHDR* pHdr, LRESULT* /*pnResult*/)
{
	CString strType;

	LVITEM& lvi = reinterpret_cast<NMLVDISPINFO*>(pHdr)->item;
	if ((lvi.mask & LVIF_TEXT) != 0)
	{
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
		case I_TYPE:
			::lstrcpyn(lvi.pszText, pData->szType, lvi.cchTextMax);
			break;
		case I_VALUE:
			::lstrcpyn(lvi.pszText, pData->szValue, lvi.cchTextMax);
			break;
		}
	}
}

BOOL CMacrosList::IsMacroValueExists(MACRO_DATA* pData)
{
	TCHAR* pchrStop;
	unsigned char szTemp[MACRO_DATA::MAX_VALUE + 1];
	UUID uuid;

	// precondition
	ASSERT_POINTER(pData, MACRO_DATA);

	if (::lstrlen(pData->szValue) > 0)
	{
		// validate specified value
		switch (pData->eTypeID)
		{
		case MACRO_DATA::NUMBER:
			// numeric value
			_tcstol(pData->szValue, &pchrStop, 0);
			if (*pchrStop != 0)
			{
				*pchrStop = 0;
			}
			return (pData->szValue[0] != 0);
		case MACRO_DATA::UUID:
			// UUID value
			return (::UuidFromString(szTemp, &uuid) == RPC_S_OK);
		default:
			// assume string value
			ASSERT(pData->eTypeID == MACRO_DATA::STRING);
			return (TRUE);
		}
	}
	else {
		// passsed empty string
		return (FALSE);
	}
}

void CMacrosList::SuggestMacroValue(MACRO_DATA* pData)
{
	// precondition
	ASSERT_POINTER(pData, MACRO_DATA);

	PMF_SUGGEST pmfSuggest = NULL;
	if (pData->eTypeID == MACRO_DATA::UUID)
	{
		// very special case
		m_mapSuggest.Lookup(_T("$UUID$"), pmfSuggest);
		ASSERT(pmfSuggest != NULL);
		(this->*pmfSuggest)(pData->szValue);
	}
	else if (m_mapSuggest.Lookup(pData->szName, pmfSuggest))
	{
		// common case
		ASSERT(pmfSuggest != NULL);
		(this->*pmfSuggest)(pData->szValue);
	}
	else if (pData->eTypeID == MACRO_DATA::NUMBER)
	{
		// no suggestion found for the numeric value - use simple zero
		::lstrcpy(pData->szValue, _T("0"));
	}
}

void CMacrosList::Suggest_AUTHOR(LPTSTR pszDest)
{
	TCHAR szUserName[UNLEN + 1];

	// precondition
	ASSERT(AfxIsValidString(pszDest));

	DWORD cchNameLength = UNLEN + 1;
	if (::GetUserName(szUserName, &cchNameLength))
	{
		::lstrcpy(pszDest, szUserName);
	}
}

void CMacrosList::Suggest_COMPANY(LPTSTR pszDest)
{
	CString strKeyName;
	CRegKey regKey;

	// precondition
	ASSERT(AfxIsValidString(pszDest, 256));

	static TCHAR szFormat[] = _T("SOFTWARE\\Microsoft\\%s\\CurrentVersion");
	strKeyName.Format(szFormat, (::GetVersion() & 0x80000000) ? _T("Windows") : _T("Windows NT"));
	if (regKey.Open(HKEY_LOCAL_MACHINE, strKeyName) == ERROR_SUCCESS)
	{
#if (_MFC_VER < 0x0700)
		DWORD cbSize = 256 * sizeof(TCHAR);
		regKey.QueryValue(pszDest, _T("RegisteredOrganization"), &cbSize);
#else
		ULONG cchMaxLen = 256;
		regKey.QueryStringValue(_T("RegisteredOrganization"), pszDest, &cchMaxLen);
#endif	// _MFC_VER
		regKey.Close();
	}
}

void CMacrosList::Suggest_VERMAJOR(LPTSTR pszDest)
{
	// precondition
	ASSERT(AfxIsValidString(pszDest));

	::lstrcpy(pszDest, _T("1"));
}

void CMacrosList::Suggest_VERBUILD(LPTSTR pszDest)
{
	// precondition
	ASSERT(AfxIsValidString(pszDest));

	CTime timeNow = CTime::GetCurrentTime();
	union
	{
		struct
		{
			unsigned day : 5;
			unsigned month : 4;
			unsigned year : 5;
		} date_t;
		unsigned number;
	}
	build =
	{{
		timeNow.GetDay(),
		timeNow.GetMonth(),
		timeNow.GetYear() - 2000
	}};
	_ultot(build.number, pszDest, 10);
}

void CMacrosList::Suggest_UUID(LPTSTR pszDest)
{
	UUID uuid;
	unsigned char* pszTemp;

	::CoCreateGuid(&uuid);
	::UuidToString(&uuid, &pszTemp);
	::lstrcpy(pszDest, _A2T(reinterpret_cast<char*>(pszTemp)));
	::CharUpper(pszDest);
	::RpcStringFree(&pszTemp);
}

#if defined(_DEBUG)

void CMacrosList::AssertValid(void) const
{
	// first perform inherited validity check...
	CSortingListCtrl::AssertValid();

	// ...and then verify our own state as well
}

void CMacrosList::Dump(CDumpContext& dumpCtx) const
{
	try
	{
		// first invoke inherited dumper...
		CSortingListCtrl::Dump(dumpCtx);

		// ...and then dump own unique members
		dumpCtx << "m_mapSuggest = " << m_mapSuggest;
	}
	catch (CFileException* pXcpt)
	{
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif	// _DEBUG

// end of file