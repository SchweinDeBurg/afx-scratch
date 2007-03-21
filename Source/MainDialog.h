// AfxScratch application.
// Copyright (c) 2004-2006 by Elijah Zarezky,
// All rights reserved.

// MainDialog.h - interface of the CMainDialog class

#if !defined(__MainDialog_h)
#define __MainDialog_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif	// _MSC_VER

class CMainDialog: public ETSLayoutDialog, public CResizableLayout
{
	DECLARE_DYNAMIC(CMainDialog)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	CMainDialog(CWnd* pParentWnd = NULL);
	virtual ~CMainDialog(void);

// overridables
public:
	virtual BOOL OnInitDialog(void);
	virtual CWnd* GetResizableWnd(void) const;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK(void);
	virtual void OnCancel(void);

// message map functions
protected:
	afx_msg void OnClose(void);
	afx_msg void OnDestroy(void);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT uCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysCommand(UINT uID, LPARAM lParam);
	afx_msg void OnItemChangedListProjects(NMHDR* pHdr, LRESULT* pnResult);
	afx_msg void OnDblClkListMacros(NMHDR* pHdr, LRESULT* pnResult);
	afx_msg void OnButtonValue(void);
	afx_msg void OnButtonSave(void);
	afx_msg void OnButtonRestore(void);
	afx_msg void OnButtonBrowse(void);
	afx_msg void OnButtonGenerate(void);
	afx_msg void OnButtonExit(void);

// attributes
public:
	CString m_strAppData;
	HICON m_hIcon;
	HICON m_hSmIcon;
	CCustomGroupBox m_groupProjects;
	CProjectsList m_listProjects;
	CCustomGroupBox m_groupMacros;
	CMacrosList m_listMacros;
	CCustomGroupBox m_groupLocation;
	CString m_strLocation;
	CStatic m_staticStatus;
	CImageList m_imageList;
	int m_iProjectIcon, m_iMacroIcon;
	CMap<CString, LPCTSTR, CString, LPCTSTR> m_mapMacrosDict;

// implementation helpers
private:
	void SetStatusTextPath(LPCTSTR pszFormat, LPCTSTR pszPath);
	void CreateMacrosDict(void);
	void SubstituteMacros(CString& strText);
	void GenerateFile(LPCTSTR pszDest, LPCTSTR pszSrc, CPugXmlBranch& branchFile);
	void GenerateProject(PROJECT_DATA* pData);

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif	// __MainDialog_h

// end of file
