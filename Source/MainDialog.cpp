// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// MainDialog.cpp - implementation of the CMainDialog class

#include "stdafx.h"
#include "AuxTypes.h"
#include "CustomListCtrl.h"
#include "ProjectsList.h"
#include "MacrosList.h"
#include "MainDialog.h"
#include "Resource.h"
#include "AfxScratchApp.h"
#include "AboutDialog.h"
#include "MacroValueDialog.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// object model
IMPLEMENT_DYNAMIC(CMainDialog, CDialog)

// message map
BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PROJECTS, OnItemChangedListProjects)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MACROS, OnDblClkListMacros)
	ON_BN_CLICKED(IDC_BUTTON_VALUE, OnButtonValue)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, OnButtonRestore)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
END_MESSAGE_MAP()

CMainDialog::CMainDialog(CWnd* pParentWnd):
CDialog(IDD_MAIN, pParentWnd),
m_hIcon(NULL),
m_hSmIcon(NULL),
m_iProjectIcon(-1),
m_iMacroIcon(-1)
{
	CString strRegKey;
	HICON hIcon;

	CAfxScratchApp* pApp = DYNAMIC_DOWNCAST(CAfxScratchApp, AfxGetApp());
	ASSERT_VALID(pApp);

	// obtain the application data folder
	m_strAppData = pApp->GetProfileString(_T("Settings"), _T("AppData"));
	if (m_strAppData.IsEmpty()) {
		// use default - within application data for all users
		::SHGetSpecialFolderPath(NULL, m_strAppData.GetBuffer(_MAX_PATH), CSIDL_COMMON_APPDATA, TRUE);
		m_strAppData.ReleaseBuffer();
		strRegKey.LoadString(IDS_REGISTRY_KEY);
		m_strAppData += _T('\\') + strRegKey;
		m_strAppData += _T('\\') + CString(AfxGetAppName());
		::SHCreateDirectoryEx(NULL, m_strAppData, NULL);
		pApp->WriteProfileString(_T("Settings"), _T("AppData"), m_strAppData);
	}

	// load dialog's icons
	m_hIcon = pApp->LoadIcon(IDI_APP_ICON);
	m_hSmIcon = pApp->LoadSmIcon(MAKEINTRESOURCE(IDI_APP_ICON));

	// obtain the generated projects location
	m_strLocation = pApp->GetProfileString(_T("Settings"), _T("Location"));
	if (m_strLocation.IsEmpty()) {
		// use default - common repository for documents
		::SHGetSpecialFolderPath(NULL, m_strLocation.GetBuffer(_MAX_PATH), CSIDL_PERSONAL, TRUE);
		m_strLocation.ReleaseBuffer();
		pApp->WriteProfileString(_T("Settings"), _T("Location"), m_strLocation);
	}

	// prepare default image list
	int cxSmIcon = ::GetSystemMetrics(SM_CXSMICON);
	int cySmIcon = ::GetSystemMetrics(SM_CYSMICON);
	m_imageList.Create(cxSmIcon, cySmIcon, ILC_COLOR16 | ILC_MASK, 8, 8);
	hIcon = pApp->LoadSmIcon(MAKEINTRESOURCE(IDI_PROJECT_ICON));
	m_iProjectIcon = m_imageList.Add(hIcon);
	::DestroyIcon(hIcon);
	hIcon = pApp->LoadSmIcon(MAKEINTRESOURCE(IDI_MACRO_ICON));
	m_iMacroIcon = m_imageList.Add(hIcon);
	::DestroyIcon(hIcon);
}

CMainDialog::~CMainDialog(void)
{
	m_imageList.DeleteImageList();
	::DestroyIcon(m_hSmIcon);
	::DestroyIcon(m_hIcon);
}

BOOL CMainDialog::OnInitDialog(void)
{
	CString strAbout;
	CString strAppVer;
	CString strStatus;

	CDialog::OnInitDialog();

	// set dialog's icons
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hSmIcon, FALSE);

	// adjust system menu
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	ASSERT_VALID(pSysMenu);
	pSysMenu->AppendMenu(MF_BYPOSITION | MF_SEPARATOR);
	strAbout.LoadString(IDS_ABOUT);
	pSysMenu->AppendMenu(MF_BYPOSITION, IDM_SC_ABOUT, strAbout);

	// prepare projects list control
	m_listProjects.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listProjects.InsertColumns();
	m_listProjects.SetImageList(&m_imageList, LVSIL_SMALL);

	// prepare macros list control
	m_listMacros.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listMacros.InsertColumns();
	m_listMacros.SetImageList(&m_imageList, LVSIL_SMALL);

	// initialize projects list
	m_listProjects.InitContent(m_strAppData);

	// assign initial status text
	CAfxScratchApp* pApp = DYNAMIC_DOWNCAST(CAfxScratchApp, AfxGetApp());
	ASSERT_VALID(pApp);
	pApp->GetVersionString(strAppVer);
	strStatus.Format(IDS_TITLE_FORMAT, static_cast<LPCTSTR>(strAppVer));
	m_staticStatus.SetWindowText(strStatus);

	// initialized
	return (TRUE);
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_PROJECTS, m_listProjects);
	DDX_Control(pDX, IDC_LIST_MACROS, m_listMacros);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_strLocation);
	DDV_MaxChars(pDX, m_strLocation, _MAX_PATH);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_staticStatus);
}

void CMainDialog::OnOK(void)
{
	switch (GetFocus()->GetDlgCtrlID())
	{
	case IDC_LIST_PROJECTS:
		::MessageBeep(MB_ICONHAND);
		break;
	case IDC_LIST_MACROS:
		OnButtonValue();
		break;
	case IDC_EDIT_LOCATION:
		OnButtonBrowse();
		break;
	}
	// don't invoke inherited handler to avoid dialog closing
}

void CMainDialog::OnCancel(void)
{
	// don't invoke inherited handler to avoid dialog closing
}

void CMainDialog::OnClose(void)
{
	EndDialog(IDCANCEL);
}

void CMainDialog::OnDestroy(void)
{
	m_listMacros.ResetContent();
	m_listProjects.ResetContent();
	CDialog::OnDestroy();
}

HBRUSH CMainDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT uCtlColor)
{
	HBRUSH hbr;

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_EDIT_LOCATION:
		if (uCtlColor == CTLCOLOR_STATIC) {
			pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
			pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
			hbr = ::GetSysColorBrush(COLOR_WINDOW);
			break;
		}
	default:
		hbr = CDialog::OnCtlColor(pDC, pWnd, uCtlColor);
	}
	return (hbr);
}

void CMainDialog::OnSysCommand(UINT uID, LPARAM lParam)
{
	if ((uID & 0xFFF0) == IDM_SC_ABOUT) {
		CAboutDialog dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialog::OnSysCommand(uID, lParam);
	}
}

void CMainDialog::OnItemChangedListProjects(NMHDR* pHdr, LRESULT* /*pnResult*/)
{
	NMLISTVIEW* pNMLV = reinterpret_cast<NMLISTVIEW*>(pHdr);
	if ((pNMLV->uNewState & LVIS_SELECTED) != 0) {
		m_listMacros.ResetContent();
		// populate macros list
		PROJECT_DATA* pData = reinterpret_cast<PROJECT_DATA*>(m_listProjects.GetItemData(pNMLV->iItem));
		ASSERT(pData != NULL);
		m_listMacros.InitContent(pData->szConfigFile);
	}
}

void CMainDialog::OnDblClkListMacros(NMHDR* /*pHdr*/, LRESULT* /*pnResult*/)
{
	OnButtonValue();
}

void CMainDialog::OnButtonValue(void)
{
	POSITION pos = m_listMacros.GetFirstSelectedItemPosition();
	if (pos != NULL) {
		int iItem = m_listMacros.GetNextSelectedItem(pos);
		MACRO_DATA* pData = reinterpret_cast<MACRO_DATA*>(m_listMacros.GetItemData(iItem));
		ASSERT(pData != NULL);
		CMacroValueDialog dlgMacroValue(pData->szName);
		dlgMacroValue.m_strValue = pData->szValue;
		if (dlgMacroValue.DoModal() == IDOK) {
			::lstrcpy(pData->szValue, dlgMacroValue.m_strValue);
			m_listMacros.AutosizeColumns();
			m_listMacros.RedrawItems(iItem, iItem);
		}
		m_listMacros.SetFocus();
	}
	else {
		::MessageBeep(MB_ICONHAND);
	}
}

void CMainDialog::OnButtonSave(void)
{
	POSITION pos = m_listProjects.GetFirstSelectedItemPosition();
	if (pos != NULL) {
		int iItem = m_listProjects.GetNextSelectedItem(pos);
		PROJECT_DATA* pPrjData = reinterpret_cast<PROJECT_DATA*>(m_listProjects.GetItemData(iItem));
		ASSERT(pPrjData != NULL);
		CPugXmlParser* pParser = new CPugXmlParser();
		if (pParser->ParseFile(pPrjData->szConfigFile)) {
			CPugXmlBranch branchRoot = pParser->GetRoot();
			ASSERT(!branchRoot.IsNull());
			CPugXmlBranch branchMacros = branchRoot.FindByPath(_T("./Project/Macros"));
			ASSERT(!branchMacros.IsNull());
			int nNumMacros = m_listMacros.GetItemCount();
			for (int i = 0; i < nNumMacros; ++i) {
				MACRO_DATA* pMacData = reinterpret_cast<MACRO_DATA*>(m_listMacros.GetItemData(i));
				ASSERT(pMacData != NULL);
				CPugXmlBranch branchMacro = branchMacros.FindFirstElemAttr(_T("Macro"), _T("Name"),
					pMacData->szName);
				ASSERT(!branchMacro.IsNull());
				if (::lstrlen(pMacData->szValue) > 0) {
					// change or add default macro value
					if (!branchMacro.SetAttributeValue(_T("Default"), pMacData->szValue)) {
						branchMacro.AddAttribute(_T("Default"), pMacData->szValue);
					}
				}
				else {
					// remove default macro value
					branchMacro.DeleteAttributeAt(_T("Default"));
				}
			}
			// serialize modified XML tree to the stream
			try {
				std::ofstream ofsXML(_T2A(pPrjData->szConfigFile), std::ios::trunc);
				branchRoot.Serialize(ofsXML);
			}
			catch (const std::exception& xcpt) {
				AfxMessageBox(_A2T(xcpt.what()), MB_ICONSTOP | MB_OK);
			}
		}
		delete pParser;
	}
}

void CMainDialog::OnButtonRestore(void)
{
	POSITION pos = m_listProjects.GetFirstSelectedItemPosition();
	if (pos != NULL) {
		m_listMacros.ResetContent();
		int iItem = m_listProjects.GetNextSelectedItem(pos);
		PROJECT_DATA* pData = reinterpret_cast<PROJECT_DATA*>(m_listProjects.GetItemData(iItem));
		ASSERT(pData != NULL);
		m_listMacros.InitContent(pData->szConfigFile);
	}
}

void CMainDialog::OnButtonBrowse(void)
{
	CString strPrompt;

	strPrompt.LoadString(IDS_LOCATION_PROMPT);
	CFolderDialog dlgFolder(strPrompt, m_strLocation, this);
	if (dlgFolder.DoModal() == IDOK) {
		m_strLocation = dlgFolder.GetFolderPath();
		SetDlgItemText(IDC_EDIT_LOCATION, m_strLocation);
		CAfxScratchApp* pApp = DYNAMIC_DOWNCAST(CAfxScratchApp, AfxGetApp());
		ASSERT_VALID(pApp);
		pApp->WriteProfileString(_T("Settings"), _T("Location"), m_strLocation);
	}
}

void CMainDialog::OnButtonGenerate(void)
{
	POSITION pos = m_listProjects.GetFirstSelectedItemPosition();
	if (pos != NULL) {
		// retrieve and validate dialog data
		if (UpdateData()) {
			int iItem = m_listProjects.GetNextSelectedItem(pos);
			GenerateProject(reinterpret_cast<PROJECT_DATA*>(m_listProjects.GetItemData(iItem)));
		}
	}
	else {
		::MessageBeep(MB_ICONHAND);
	}
}

void CMainDialog::OnButtonExit(void)
{
	EndDialog(IDCANCEL);
}

void CMainDialog::SetStatusTextPath(LPCTSTR pszFormat, LPCTSTR pszPath)
{
	CRect rectStatus;
	CString strText;

	ASSERT(AfxIsValidString(pszFormat));
	ASSERT(AfxIsValidString(pszPath));

	CClientDC dcStatus(&m_staticStatus);
	CFont* pFont = m_staticStatus.GetFont();
	CFont* pPrevFont = dcStatus.SelectObject(pFont);
	m_staticStatus.GetClientRect(rectStatus);
	CSize sizeFormat = dcStatus.GetTextExtent(pszFormat, ::lstrlen(pszFormat));
	int cxPath = rectStatus.Width() - sizeFormat.cx;
	CString strTruncPath(pszPath);
	::PathCompactPath(dcStatus.GetSafeHdc(), strTruncPath.GetBuffer(_MAX_PATH), cxPath);
	strTruncPath.ReleaseBuffer();
	dcStatus.SelectObject(pPrevFont);
	strText.Format(pszFormat, strTruncPath);
	m_staticStatus.SetWindowText(strText);
}

void CMainDialog::CreateMacrosDict(void)
{
	CString strAppVer;
	CString strGenerator;
	SYSTEMTIME stNow;
	TCHAR szTemp[32];

	m_mapMacrosDict.RemoveAll();

	int nNumMacros = m_listMacros.GetItemCount();
	for (int i = 0; i < nNumMacros; ++i) {
		MACRO_DATA* pData = reinterpret_cast<MACRO_DATA*>(m_listMacros.GetItemData(i));
		m_mapMacrosDict.SetAt(pData->szName, pData->szValue);
	}

	CAfxScratchApp* pApp = DYNAMIC_DOWNCAST(CAfxScratchApp, AfxGetApp());
	ASSERT_VALID(pApp);
	pApp->GetVersionString(strAppVer);
	strGenerator.Format(_T("%s %s"), AfxGetAppName(), static_cast<LPCTSTR>(strAppVer));
	m_mapMacrosDict.SetAt(_T("$GENERATOR$"), strGenerator);

	::GetLocalTime(&stNow);
	m_mapMacrosDict.SetAt(_T("$DAY$"), _itot(stNow.wDay, szTemp, 10));
	m_mapMacrosDict.SetAt(_T("$MONTH$"), _itot(stNow.wMonth, szTemp, 10));
	m_mapMacrosDict.SetAt(_T("$YEAR$"), _itot(stNow.wYear, szTemp, 10));
	m_mapMacrosDict.SetAt(_T("$HOUR$"), _itot(stNow.wHour, szTemp, 10));
	m_mapMacrosDict.SetAt(_T("$MINUTE$"), _itot(stNow.wMinute, szTemp, 10));
	m_mapMacrosDict.SetAt(_T("$SECOND$"), _itot(stNow.wSecond, szTemp, 10));
	::GetDateFormat(0, 0, &stNow, _T("dd.MM.yyyy"), szTemp, 32);
	m_mapMacrosDict.SetAt(_T("$DATE$"), szTemp);
	::GetTimeFormat(0, 0, &stNow, _T("HH:mm:ss"), szTemp, 32);
	m_mapMacrosDict.SetAt(_T("$TIME$"), szTemp);
}

void CMainDialog::SubstituteMacros(CString& strText)
{
	CString strName;
	CString strValue;

	if (!strText.IsEmpty()) {
		POSITION pos = m_mapMacrosDict.GetStartPosition();
		while (pos != NULL) {
			m_mapMacrosDict.GetNextAssoc(pos, strName, strValue);
			strText.Replace(strName, strValue);
		}
	}
}

void CMainDialog::GenerateFile(LPCTSTR pszDest, LPCTSTR pszSrc, CPugXmlBranch& branchFile)
{
	CString strFormat;
	CString strLine;

	ASSERT(AfxIsValidString(pszDest));
	ASSERT(AfxIsValidString(pszSrc));

	CString strDestName(branchFile.GetAttribute(_T("Name")));
	strDestName.Insert(0, pszDest);
	SubstituteMacros(strDestName);

	CString strSrcName(branchFile.GetAttribute(_T("Name")));
	strSrcName.Insert(0, pszSrc);

	strFormat.LoadString(IDS_WRITING_FORMAT);
	SetStatusTextPath(strFormat, strDestName);

	::SHCreateDirectoryEx(NULL, strDestName.Left(strDestName.ReverseFind(_T('\\'))), NULL);
	if (CString(branchFile.GetAttribute(_T("Type"))) == _T("text")) {
		// text file - perform macro substitution
		try {
			CStdioFile fileDest(strDestName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
			CStdioFile fileSrc(strSrcName, CFile::modeRead | CFile::typeText);
			while (fileSrc.ReadString(strLine)) {
				SubstituteMacros(strLine);
				fileDest.WriteString(strLine + _T('\n'));
			}
		}
		catch (CFileException* pXcpt) {
			pXcpt->ReportError();
			pXcpt->Delete();
			RestoreWaitCursor();
		}
	}
	else {
		// assume binary file - simple copy
		::CopyFile(strSrcName, strDestName, FALSE);
	}
}

void CMainDialog::GenerateProject(PROJECT_DATA* pData)
{
	CString strFormat;
	CString strProjectName;

	ASSERT(pData != NULL);

	strFormat.LoadString(IDS_PARSING_FORMAT);
	SetStatusTextPath(strFormat, pData->szConfigFile);
	BeginWaitCursor();

	// create the XML parser
	CPugXmlParser* pParser = new CPugXmlParser();

	if (pParser->ParseFile(pData->szConfigFile)) {
		// prepare the macros "dictionary"
		CreateMacrosDict();
		if (!m_mapMacrosDict.Lookup(_T("$PROJECT$"), strProjectName) || strProjectName.IsEmpty()) {
			strProjectName = pData->szName;
			m_mapMacrosDict.SetAt(_T("$PROJECT$"), strProjectName);
		}
		// create the project folder
		CString strProjectFolder = m_strLocation + _T('\\') + strProjectName;
		strFormat.LoadString(IDS_CREATING_FORMAT);
		SetStatusTextPath(strFormat, strProjectFolder);
		::SHCreateDirectoryEx(NULL, strProjectFolder, NULL);
		// obtain the source folder
		CString strSrcFolder = m_strAppData + _T("\\Sources\\") + CString(pData->szName);
		// parse source files
		CPugXmlBranch branchRoot = pParser->GetRoot();
		ASSERT(!branchRoot.IsNull());
		CPugXmlBranch branchFiles = branchRoot.FindByPath(_T("./Project/Files"));
		ASSERT(!branchFiles.IsNull());
		int nNumFiles = branchFiles.GetChildrenCount();
		for (int i = 0; i < nNumFiles; ++i) {
			CPugXmlBranch branchFile = branchFiles.GetChildAt(i);
			ASSERT(!branchFile.IsNull());
			GenerateFile(strProjectFolder, strSrcFolder, branchFile);
		}
		// finished
		strFormat.LoadString(IDS_GENERATED_FORMAT);
		SetStatusTextPath(strFormat, strProjectFolder);
	}

	EndWaitCursor();

	// destroy the XML parser
	delete pParser;
}

#if defined(_DEBUG)

void CMainDialog::AssertValid(void) const
{
	// first perform inherited validity check...
	CDialog::AssertValid();
	// ...and then verify our own state as well
	ASSERT_VALID(&m_listProjects);
	ASSERT_VALID(&m_listMacros);
	ASSERT_VALID(&m_imageList);
}

void CMainDialog::Dump(CDumpContext& dumpCtx) const
{
	try {
		// first invoke inherited dumper...
		CDialog::Dump(dumpCtx);
		// ...and then dump own unique members
		dumpCtx << "m_strAppData = " << m_strAppData;
		dumpCtx << "\nm_hIcon = " << m_hIcon;
		dumpCtx << "\nm_hSmIcon = " << m_hSmIcon;
		dumpCtx << "\nm_listProjects = " << m_listProjects;
		dumpCtx << "\nm_listMacros = " << m_listMacros;
		dumpCtx << "\nm_strLocation = " << m_strLocation;
		dumpCtx << "\nm_imageList = " << m_imageList;
		dumpCtx << "\nm_iProjectIcon = " << m_iProjectIcon;
		dumpCtx << "\nm_iMacroIcon = " << m_iMacroIcon;
	}
	catch (CFileException* pXcpt) {
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif	// _DEBUG

// end of file
