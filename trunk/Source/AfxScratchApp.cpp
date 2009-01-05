// AfxScratch application.
// Copyright (c) 2004-2009 by Elijah Zarezky,
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
}

CAfxScratchApp::~CAfxScratchApp(void)
{
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
