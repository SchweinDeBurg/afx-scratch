// AfxScratch application.
// Copyright (c) 2004-2005 by Elijah Zarezky,
// All rights reserved.

// AfxScratchApp.h - interface of the CAfxScratchApp class

#if !defined(__AfxScratchApp_h)
#define __AfxScratchApp_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif	// _MSC_VER

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

#endif	// __AfxScratchApp_h

// end of file
