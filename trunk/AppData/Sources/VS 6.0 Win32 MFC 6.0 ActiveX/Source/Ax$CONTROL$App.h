// Ax$CONTROL$ ActiveX control.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// Ax$CONTROL$App.h - interface of the CAx$CONTROL$App class

// initially generated by $GENERATOR$ on $DATE$ at $TIME$
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

#if !defined(__Ax$CONTROL$App_h)
#define __Ax$CONTROL$App_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif   // _MSC_VER

class CAx$CONTROL$App: public COleControlModule
{
	DECLARE_DYNAMIC(CAx$CONTROL$App)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	CAx$CONTROL$App(void);
	virtual ~CAx$CONTROL$App(void);

// initialization/termination
public:
	virtual BOOL InitInstance(void);
	virtual int ExitInstance(void);
};

#endif   // __Ax$CONTROL$App_h

// end of file