// $PROJECT$ application.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// MainDialog.cpp - implementation of the CMainDialog class

// initially generated by $GENERATOR$ on $DATE$ at $TIME$
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

//////////////////////////////////////////////////////////////////////////////////////////////
// PCH includes

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// resource includes

#include "Resource.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// other includes

#include "MainDialog.h"
#include "$PROJECT$App.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// debugging support

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif   // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////
// object model

IMPLEMENT_DYNAMIC(CMainDialog, CDialog)

//////////////////////////////////////////////////////////////////////////////////////////////
// message map

BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////
// construction/destruction

CMainDialog::CMainDialog(CWnd* pParentWnd):
CDialog(IDD_MAIN, pParentWnd),
m_hIcon(NULL),
m_hSmIcon(NULL)
{
	C$PROJECT$App* pApp = DYNAMIC_DOWNCAST(C$PROJECT$App, AfxGetApp());
	ASSERT_VALID(pApp);

	// load dialog's icons
	m_hIcon = pApp->LoadIcon(IDI_APP_ICON);
	m_hSmIcon = pApp->LoadSmIcon(MAKEINTRESOURCE(IDI_APP_ICON));
}

CMainDialog::~CMainDialog(void)
{
	::DestroyIcon(m_hSmIcon);
	::DestroyIcon(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// overridables

BOOL CMainDialog::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	// set dialog's icons
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hSmIcon, FALSE);

	// initialized
	return (TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// diagnostic services

#if defined(_DEBUG)

void CMainDialog::AssertValid(void) const
{
	// first perform inherited validity check...
	CDialog::AssertValid();

	// ...and then verify our own state as well
}

void CMainDialog::Dump(CDumpContext& dumpCtx) const
{
	try
	{
		// first invoke inherited dumper...
		CDialog::Dump(dumpCtx);

		// ...and then dump own unique members
		dumpCtx << "m_hIcon = " << m_hIcon;
		dumpCtx << "\nm_hSmIcon = " << m_hSmIcon;
	}
	catch (CFileException* pXcpt)
	{
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif   // _DEBUG

// end of file