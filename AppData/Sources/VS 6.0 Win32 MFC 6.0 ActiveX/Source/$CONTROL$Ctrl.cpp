// Ax$CONTROL$ ActiveX control.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// $CONTROL$Ctrl.cpp - implementation of the C$CONTROL$Ctrl class

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

#include "Identifiers.h"
#include "$CONTROL$Ctrl.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// debugging support

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif   // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////
// private globals

static const DWORD g_fdwOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

//////////////////////////////////////////////////////////////////////////////////////////////
// object model

IMPLEMENT_DYNCREATE(C$CONTROL$Ctrl, COleControl)

//////////////////////////////////////////////////////////////////////////////////////////////
// message map

BEGIN_MESSAGE_MAP(C$CONTROL$Ctrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, COleControl::OnProperties)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////
// dispatch map

BEGIN_DISPATCH_MAP(C$CONTROL$Ctrl, COleControl)
	// custom properties
	// custom methods
	// stock properties
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FORECOLOR()
	// stock methods
END_DISPATCH_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////
// event map

BEGIN_EVENT_MAP(C$CONTROL$Ctrl, COleControl)
END_EVENT_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////
// class factory and CLSID

IMPLEMENT_OLECREATE_EX(C$CONTROL$Ctrl, "$VENDOR$.$CONTROL$.$VERMAJOR$")

BOOL C$CONTROL$Ctrl::C$CONTROL$CtrlFactory::UpdateRegistry(BOOL fRegister)
{
	BOOL fSuccess;

	if (fRegister)
	{
		fSuccess = AfxOleRegisterControlClass(AfxGetInstanceHandle(), m_clsid, m_lpszProgID,
			IDS_CONTROL_TYPENAME, IDB_PALETTE_BUTTON, afxRegApartmentThreading, g_fdwOleMisc,
			LIBID_Ax$CONTROL$, g_wVerMajor, g_wVerMinor);
	}
	else {
		fSuccess = AfxOleUnregisterClass(m_clsid, m_lpszProgID);
	}
	return (fSuccess);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// type name and misc status

IMPLEMENT_OLECTLTYPE(C$CONTROL$Ctrl, IDS_CONTROL_TYPENAME, g_fdwOleMisc)

//////////////////////////////////////////////////////////////////////////////////////////////
// type library information

IMPLEMENT_OLETYPELIB(C$CONTROL$Ctrl, LIBID_Ax$CONTROL$, g_wVerMajor, g_wVerMinor)

//////////////////////////////////////////////////////////////////////////////////////////////
// property pages

BEGIN_PROPPAGEIDS(C$CONTROL$Ctrl, 1)
	PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(C$CONTROL$Ctrl)

//////////////////////////////////////////////////////////////////////////////////////////////
// construction/destruction

C$CONTROL$Ctrl::C$CONTROL$Ctrl(void):
COleControl()
{
	InitializeIIDs(&IID_I$CONTROL$Disp, &IID_I$CONTROL$Events);
}

C$CONTROL$Ctrl::~C$CONTROL$Ctrl(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
// overridables

void C$CONTROL$Ctrl::OnDraw(CDC* pDC, const CRect& rectBounds, const CRect& /*rectInvalid*/)
{
	COLORREF crBackColor = TranslateColor(GetBackColor());
	COLORREF crForeColor = TranslateColor(GetForeColor());
	CBrush brushBack(crBackColor);
	pDC->FillRect(rectBounds, &brushBack);
	pDC->SetBkColor(crBackColor);
	pDC->SetTextColor(crForeColor);
}

void C$CONTROL$Ctrl::OnResetState(void)
{
	COleControl::OnResetState();
}

void C$CONTROL$Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(g_wVerMajor, g_wVerMinor));
	COleControl::DoPropExchange(pPX);
}

// end of file
