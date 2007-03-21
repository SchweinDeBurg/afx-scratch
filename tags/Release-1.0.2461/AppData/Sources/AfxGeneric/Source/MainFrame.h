// $PROJECT$ application.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// MainFrame.h - interface of the CMainFrame class

// initially generated by $GENERATOR$ on $DATE$ at $TIME$
// visit http://home.peterstar.ru/zarezky/projects/afx_scratch.html for more info

#if !defined(__MainFrame_h)
#define __MainFrame_h

class CMainFrame: public CFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	CMainFrame(void);
	virtual ~CMainFrame(void);

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif	// __MainFrame_h

// end of file
