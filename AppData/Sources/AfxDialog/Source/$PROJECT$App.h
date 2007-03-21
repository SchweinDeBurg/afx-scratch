// $PROJECT$ application.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// $PROJECT$App.h - interface of the C$PROJECT$App class
// initially generated by $GENERATOR$ on $DATE$ at $TIME$

#if !defined(__$PROJECT$App_h)
#define __$PROJECT$App_h

class C$PROJECT$App: public CWinApp
{
	DECLARE_DYNAMIC(C$PROJECT$App)
	DECLARE_MESSAGE_MAP()

// construction/destruction
public:
	C$PROJECT$App(void);
	virtual ~C$PROJECT$App(void);

// operations
public:
	HICON LoadSmIcon(LPCTSTR pszResName);

// overridables
public:
	virtual BOOL InitInstance(void);

// diagnostic services
#if defined(_DEBUG)
public:
	virtual void AssertValid(void) const;
	virtual void Dump(CDumpContext& dumpCtx) const;
#endif
};

#endif	// __$PROJECT$App_h

// end of file
