// AfxScratch application.
// Copyright (c) 2004-2010 by Elijah Zarezky,
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

// AfxScratchApp.cpp - implementation of the CAfxScratchApp class

//////////////////////////////////////////////////////////////////////////////////////////////
// PCH includes

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// resource includes

#include "Resource.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// other includes

#include "AfxScratchApp.h"
#include "AuxTypes.h"
#include "CustomHeaderCtrl.h"
#include "ProjectsList.h"
#include "MacrosList.h"
#include "CustomGroupBox.h"
#include "ResizableLayout.h"
#include "MainDialog.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// misc defines

#define SZ_MUTEX_APP_INST_NAME _T("AfxScratch.Instance.655393D6-3C2F-43E5-AEC3-29FCDC0AA439")

//////////////////////////////////////////////////////////////////////////////////////////////
// debugging support

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif   // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////
// object model

IMPLEMENT_DYNAMIC(CAfxScratchApp, CWinApp)

//////////////////////////////////////////////////////////////////////////////////////////////
// message map

BEGIN_MESSAGE_MAP(CAfxScratchApp, CWinApp)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////
// construction/destruction

CAfxScratchApp::CAfxScratchApp(void):
m_hMutexAppInst(NULL)
{
#if defined(AFXSCRATCH_DETOURED)
	RegQueryCatchpit();

	Detoured();

	(PVOID&)m_pfnLoadLibrary = ::DetourFindFunction("kernel32.dll", STRINGIZE(LoadLibrary));
	(PVOID&)m_pfnLoadLibraryEx = ::DetourFindFunction("kernel32.dll", STRINGIZE(LoadLibraryEx));
	
	DetourTransactionBegin();
	DetourUpdateThread(::GetCurrentThread());
	DetourAttach(reinterpret_cast<PVOID*>(&m_pfnLoadLibrary), &CAfxScratchApp::LoadLibrary);
	DetourAttach(reinterpret_cast<PVOID*>(&m_pfnLoadLibraryEx), &CAfxScratchApp::LoadLibraryEx);
	DetourTransactionCommit();
#endif   // AFXSCRATCH_DETOURED
}

CAfxScratchApp::~CAfxScratchApp(void)
{
#if defined(AFXSCRATCH_DETOURED)
	DetourTransactionBegin();
	DetourUpdateThread(::GetCurrentThread());
	DetourDetach(reinterpret_cast<PVOID*>(&m_pfnLoadLibrary),  &CAfxScratchApp::LoadLibrary);
	DetourDetach(reinterpret_cast<PVOID*>(&m_pfnLoadLibraryEx),  &CAfxScratchApp::LoadLibraryEx);
	DetourTransactionCommit();
#endif   // AFXSCRATCH_DETOURED
}

//////////////////////////////////////////////////////////////////////////////////////////////
// operations

HICON CAfxScratchApp::LoadSmIcon(LPCTSTR pszResName)
{
	HINSTANCE hInstRes = AfxGetResourceHandle();
	int cxSmIcon = ::GetSystemMetrics(SM_CXSMICON);
	int cySmIcon = ::GetSystemMetrics(SM_CYSMICON);
	HANDLE hSmIcon = ::LoadImage(hInstRes, pszResName, IMAGE_ICON, cxSmIcon, cySmIcon, 0);
	return (static_cast<HICON>(hSmIcon));
}

HICON CAfxScratchApp::LoadSmIconFromFile(LPCTSTR pszFileName)
{
	int cxSmIcon = ::GetSystemMetrics(SM_CXSMICON);
	int cySmIcon = ::GetSystemMetrics(SM_CYSMICON);
	HANDLE hSmIcon = ::LoadImage(NULL, pszFileName, IMAGE_ICON, cxSmIcon, cySmIcon, LR_LOADFROMFILE);
	return (static_cast<HICON>(hSmIcon));
}

void CAfxScratchApp::GetVersionString(CString& strDest)
{
	TCHAR szExeName[_MAX_PATH];
	DWORD dwHandle;
	CString strValueName;
	void* pvVerString;
	UINT cchFileVer;

	::GetModuleFileName(AfxGetInstanceHandle(), szExeName, _MAX_PATH);
	DWORD cbSize = ::GetFileVersionInfoSize(szExeName, &dwHandle);
	BYTE* pbVerInfo = new BYTE[cbSize];
	::GetFileVersionInfo(szExeName, dwHandle, cbSize, pbVerInfo);
	strValueName.LoadString(IDS_FILE_VERSION);
	::VerQueryValue(pbVerInfo, strValueName.GetBuffer(0), &pvVerString, &cchFileVer);
	strValueName.ReleaseBuffer();
	strDest = reinterpret_cast<LPCTSTR>(pvVerString);
	delete[] pbVerInfo;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// overridables

BOOL CAfxScratchApp::InitInstance(void)
{
	SetRegistryKey(IDS_REGISTRY_KEY);

	m_hMutexAppInst = ::CreateMutex(NULL, TRUE, SZ_MUTEX_APP_INST_NAME);
	if (m_hMutexAppInst == NULL)
	{
		AfxMessageBox(IDS_APP_INIT_FAILED, MB_OK | MB_ICONSTOP);
		return (FALSE);
	}
	else if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		if (AfxMessageBox(IDS_OTHER_APP_INSTANCE, MB_YESNO | MB_ICONWARNING) == IDNO)
		{
			::CloseHandle(m_hMutexAppInst);
			return (FALSE);
		}
	}

	AfxOleInit();

	CMainDialog dlgMain;
	m_pMainWnd = &dlgMain;
	dlgMain.DoModal();

	AfxOleTerm(FALSE);

	::CloseHandle(m_hMutexAppInst);
	m_hMutexAppInst = NULL;

	return (FALSE);
}

int CAfxScratchApp::ExitInstance(void)
{
	return (__super::ExitInstance());
}

//////////////////////////////////////////////////////////////////////////////////////////////
// implementation helpers

#if defined(AFXSCRATCH_DETOURED)

CAfxScratchApp::PFN_LOAD_LIBRARY CAfxScratchApp::m_pfnLoadLibrary(NULL);
CAfxScratchApp::PFN_LOAD_LIBRARY_EX CAfxScratchApp::m_pfnLoadLibraryEx(NULL);

HMODULE WINAPI CAfxScratchApp::LoadLibrary(LPCTSTR pszFileName)
{
	TRACE(_T("*** CAfxScratchApp::LoadLibrary(%s)\n"), pszFileName);

	CAfxScratchApp* pApp = DYNAMIC_DOWNCAST(CAfxScratchApp, AfxGetApp());
	ASSERT(pApp != NULL);

	CString strFileNameLower(::PathFindFileName(pszFileName));
	strFileNameLower.MakeLower();

	DWORD fCatch = FALSE;
	if (pApp->m_mapCatchpit.Lookup(strFileNameLower, fCatch) && fCatch != 0)
	{
		::SetLastError(ERROR_FILE_NOT_FOUND);
		return (NULL);
	}
	else {
		return (m_pfnLoadLibrary(pszFileName));
	}
}

HMODULE WINAPI CAfxScratchApp::LoadLibraryEx(LPCTSTR pszFileName, HANDLE hFile, DWORD fdwFlags)
{
	TRACE(_T("*** CAfxScratchApp::LoadLibraryEx(%s, 0x%08X, 0x%08X)\n"), pszFileName, hFile, fdwFlags);

	CAfxScratchApp* pApp = DYNAMIC_DOWNCAST(CAfxScratchApp, AfxGetApp());
	ASSERT(pApp != NULL);

	CString strFileNameLower(::PathFindFileName(pszFileName));
	strFileNameLower.MakeLower();

	DWORD fCatch = FALSE;
	if (pApp->m_mapCatchpit.Lookup(strFileNameLower, fCatch) && fCatch != 0)
	{
		::SetLastError(ERROR_FILE_NOT_FOUND);
		return (NULL);
	}
	else {
		return (m_pfnLoadLibraryEx(pszFileName, hFile, fdwFlags));
	}
}

INT_PTR CAfxScratchApp::RegQueryCatchpit(void)
{
	CString strKeyName;
	CRegKey regKey;

	m_mapCatchpit.RemoveAll();

	// build the name of the registry key...
	::LoadString(::GetModuleHandle(NULL), IDS_REGISTRY_KEY, strKeyName.GetBuffer(_MAX_PATH), _MAX_PATH);
	strKeyName.ReleaseBuffer();
	strKeyName.Insert(0, _T("Software\\"));
	strKeyName += _T("\\AfxScratch\\Catchpit");

	// ...and then open this key
	regKey.Create(HKEY_CURRENT_USER, strKeyName);
	
	DWORD cNumValues = 0;
	if (::RegQueryInfoKey(regKey, 0, 0, 0, 0, 0, 0, &cNumValues, 0, 0, 0, 0) == ERROR_SUCCESS)
	{
		for (DWORD i = 0; i < cNumValues; ++i)
		{
			TCHAR szValueName[_MAX_PATH] = { 0 };
			DWORD cchNameLen = _countof(szValueName);
			DWORD fdwValueType = REG_NONE;
			if (::RegEnumValue(regKey, i, szValueName, &cchNameLen, 0, &fdwValueType, 0, 0) == ERROR_SUCCESS)
			{
				if (fdwValueType == REG_DWORD)
				{
					DWORD fCatch = FALSE;
					regKey.QueryDWORDValue(szValueName, fCatch);
					_tcslwr_s(szValueName, cchNameLen + 1);
					m_mapCatchpit.SetAt(szValueName, fCatch);
				}
			}
		}
	}

	return (m_mapCatchpit.GetCount());
}

#endif   // AFXSCRATCH_DETOURED

//////////////////////////////////////////////////////////////////////////////////////////////
// diagnostic services

#if defined(_DEBUG)

void CAfxScratchApp::AssertValid(void) const
{
	// first perform inherited validity check...
	CWinApp::AssertValid();

	// ...and then verify our own state as well
}

void CAfxScratchApp::Dump(CDumpContext& dumpCtx) const
{
	try
	{
		// first invoke inherited dumper...
		CWinApp::Dump(dumpCtx);

		// ...and then dump own unique members
	}
	catch (CFileException* pXcpt)
	{
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif   // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////
// the one and only application object

static CAfxScratchApp g_appAfxScratch;

// end of file
