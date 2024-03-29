// $PROJECT$ application.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// EntryPoint.cpp - application entry point

// initially generated by $GENERATOR$ on $DATE$ at $TIME$
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

//////////////////////////////////////////////////////////////////////////////////////////////
// PCH includes

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// debugging support

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif   // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////
// the one and only application object

static CWinApp g_app$PROJECT$;

//////////////////////////////////////////////////////////////////////////////////////////////
// entry point

int _tmain(int /*argc*/, TCHAR* /*argv*/[], TCHAR* /*envp*/[])
{
	// try to initialize MFC
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), SW_HIDE))
	{
		return (-1);
	}

	// terminate MFC
#if defined(_DEBUG)
	AfxLockTempMaps();
	AfxUnlockTempMaps(-1);
#endif	// _DEBUG
	AfxWinTerm();

	// return to Windoze
	return (0);
}

// end of file
