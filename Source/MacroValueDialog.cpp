// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// MacroValueDialog.cpp - implementation of the CMacroValueDialog class

#include "stdafx.h"
#include "MacroValueDialog.h"
#include "Resource.h"
#include "AuxTypes.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// object model
IMPLEMENT_DYNAMIC(CMacroValueDialog, CDialog)

// message map
BEGIN_MESSAGE_MAP(CMacroValueDialog, CDialog)
END_MESSAGE_MAP()

CMacroValueDialog::CMacroValueDialog(LPCTSTR pszName, CWnd* pParentWnd):
CDialog(IDD_MACRO_VALUE, pParentWnd),
m_strName(pszName)
{
}

CMacroValueDialog::~CMacroValueDialog(void)
{
}

BOOL CMacroValueDialog::OnInitDialog(void)
{
	CString strFormat;
	CString strCaption;

	CDialog::OnInitDialog();

	GetWindowText(strFormat);
	strCaption.Format(strFormat, static_cast<LPCTSTR>(m_strName));
	SetWindowText(strCaption);

	return (TRUE);
}

void CMacroValueDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_VALUE, m_strValue);
	DDV_MaxChars(pDX, m_strValue, MACRO_DATA::MAX_VALUE);
}

#if defined(_DEBUG)

void CMacroValueDialog::AssertValid(void) const
{
	// first perform inherited validity check...
	CDialog::AssertValid();
	// ...and then verify our own state as well
}

void CMacroValueDialog::Dump(CDumpContext& dumpCtx) const
{
	try {
		// first invoke inherited dumper...
		CDialog::Dump(dumpCtx);
		// ...and then dump own unique members
		dumpCtx << "m_strName = " << m_strName;
		dumpCtx << "\nm_strValue = " << m_strValue;
	}
	catch (CFileException* pXcpt) {
		pXcpt->ReportError();
		pXcpt->Delete();
	}
}

#endif	// _DEBUG

// end of file
