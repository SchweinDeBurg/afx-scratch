// Ax$CONTROL$ ActiveX control.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// $CONTROL$Ctrl.h - interface of the C$CONTROL$Ctrl class
// initially generated by $GENERATOR$ on $DATE$ at $TIME$

#if !defined(__$CONTROL$Ctrl_h)
#define __$CONTROL$Ctrl_h

class C$CONTROL$Ctrl: public COleControl
{
	DECLARE_DYNCREATE(C$CONTROL$Ctrl)
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_EVENT_MAP()
	// class factory and CLSID
	DECLARE_OLECREATE_EX(C$CONTROL$Ctrl)
	// type name and misc status
	DECLARE_OLECTLTYPE(C$CONTROL$Ctrl)
	// type library information
	DECLARE_OLETYPELIB(C$CONTROL$Ctrl)
	// property pages
	DECLARE_PROPPAGEIDS(C$CONTROL$Ctrl)

// construction/destruction
public:
	C$CONTROL$Ctrl(void);
	virtual ~C$CONTROL$Ctrl(void);

// overridables
public:
	virtual void OnDraw(CDC* pDC, const CRect& rectBounds, const CRect& rectInvalid);
	virtual void OnResetState(void);
	virtual void DoPropExchange(CPropExchange* pPX);
};

#endif	// __$CONTROL$Ctrl_h

// end of file
