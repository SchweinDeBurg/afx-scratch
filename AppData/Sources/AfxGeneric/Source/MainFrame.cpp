// $PROJECT$ application.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// MainFrame.cpp - implementation of the CMainFrame class
// initially generated by $GENERATOR$ on $DATE$ at $TIME$

#include "stdafx.h"
#include "MainFrame.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// object model
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

// message map
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
END_MESSAGE_MAP()

CMainFrame::CMainFrame(void)
{
}

CMainFrame::~CMainFrame(void)
{
}

#if defined(_DEBUG)

void CMainFrame::AssertValid(void) const
{
	// first perform inherited validity check...
	CFrameWnd::AssertValid();
	// ...and then verify our own state as well
}

void CMainFrame::Dump(CDumpContext& dumpCtx) const
{
	try {
		// first invoke inherited dumper...
		CFrameWnd::Dump(dumpCtx);
		// ...and then dump own unique members
	}
	catch (CFileException* pXcpt) {
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif	// _DEBUG

// end of file
