// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// MacrosList.h - interface of the CMacrosList class

#if !defined(__MacrosList_h)
#define __MacrosList_h

class CMacrosList: public CCustomListCtrl
{
	DECLARE_DYNAMIC(CMacrosList)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	CMacrosList(void);
	virtual ~CMacrosList(void);

// operations
public:
	void InsertColumns(void);
	void AutosizeColumns(void);
	void InitContent(LPCTSTR pszConfigFile);
	void ResetContent(void);

// overridables
protected:
	virtual int CompareItems(int iItemLhs, int iItemRhs);

// message map functions
protected:
	afx_msg void OnGetDispInfo(NMHDR* pHdr, LRESULT* pnResult);

// attributes
public:
	enum {
		// column indices
		I_NAME,
		I_DESCRIPTION,
		I_VALUE,
		NUM_COLUMNS		// should be the LAST enumerator!
	};

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif	// __MacrosList_h

// end of file
