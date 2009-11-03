// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// MacroValueDialog.h - interface of the CMacroValueDialog class

#if !defined(__MacroValueDialog_h)
#define __MacroValueDialog_h

class CMacroValueDialog: public CDialog
{
	DECLARE_DYNAMIC(CMacroValueDialog)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	CMacroValueDialog(LPCTSTR pszName, CWnd* pParentWnd = NULL);
	virtual ~CMacroValueDialog(void);

// overridables
public:
	virtual BOOL OnInitDialog(void);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

// attributes
public:
	CString m_strName;
	CString m_strValue;

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif	// __MacroValueDialog_h

// end of file