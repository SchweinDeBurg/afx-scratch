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

// AfxScratchApp.h - interface of the CAfxScratchApp class

#if !defined(__AfxScratchApp_h)
#define __AfxScratchApp_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif   // _MSC_VER

class CAfxScratchApp: public CWinApp
{
	DECLARE_DYNAMIC(CAfxScratchApp)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	CAfxScratchApp(void);
	virtual ~CAfxScratchApp(void);

// operations
public:
	HICON LoadSmIcon(LPCTSTR pszResName);
	HICON LoadSmIconFromFile(LPCTSTR pszFileName);
	void GetVersionString(CString& strDest);

// overridables
public:
	virtual BOOL InitInstance(void);
	virtual int ExitInstance(void);

// attributes
public:
	HANDLE m_hMutexAppInst;

// implementation helpers
private:
#if defined(AFXSCRATCH_DETOURED)
	// LoadLibrary[A/W] catcher
	typedef HMODULE(WINAPI* PFN_LOAD_LIBRARY)(LPCTSTR);
	static PFN_LOAD_LIBRARY m_pfnLoadLibrary;
	static HMODULE WINAPI LoadLibrary(LPCTSTR pszFileName);
	// LoadLibraryEx[A/W] catcher
	typedef HMODULE(WINAPI* PFN_LOAD_LIBRARY_EX)(LPCTSTR, HANDLE, DWORD);
	static PFN_LOAD_LIBRARY_EX m_pfnLoadLibraryEx;
	static HMODULE WINAPI LoadLibraryEx(LPCTSTR pszFileName, HANDLE hFile, DWORD fdwFlags);
	// catched DLLs
	CMap<CString, LPCTSTR, DWORD, DWORD> m_mapCatchpit;
	INT_PTR RegQueryCatchpit(void);
	bool IsCatchpitEmpty(void) const;
#endif   // AFXSCRATCH_DETOURED

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

//////////////////////////////////////////////////////////////////////////////////////////////
// inlines

inline bool CAfxScratchApp::IsCatchpitEmpty(void) const
{
	return (m_mapCatchpit.GetCount() == 0);
}

#endif   // __AfxScratchApp_h

// end of file
