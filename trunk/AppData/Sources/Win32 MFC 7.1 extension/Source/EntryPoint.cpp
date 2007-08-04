// $PROJECT$ MFC extension DLL.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// EntryPoint.cpp - library entry point

// initially generated by $GENERATOR$ on $DATE$ at $TIME$
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

#include "stdafx.h"

#include <afxdllx.h>			// MFC extension DLL helpers

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// state of the extension DLL module
AFX_EXTENSION_MODULE g_afxModule = { FALSE, NULL };

// entry point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInst, DWORD fdwReason, void* /*pvReserved*/)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		TRACE0("$PROJECT$.dll Initializing!\n");
		// perform one-time initialization
		VERIFY(AfxInitExtensionModule(g_afxModule, hInst));
		// insert this DLL into the resource chain
		new CDynLinkLibrary(g_afxModule);
		// successfully attached
		return (TRUE);
	case DLL_PROCESS_DETACH:
		TRACE0("$PROJECT$.dll Terminating!\n");
		// perform per-process termination
		AfxTermExtensionModule(g_afxModule);
		// successfully detached
		return (TRUE);
	default:
		return (TRUE);
	}
}

// end of file
