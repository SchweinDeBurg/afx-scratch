// AfxScratch application.
// Copyright (c) 2004-2008 by Elijah Zarezky,
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

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif   // __AfxScratchApp_h

// end of file
