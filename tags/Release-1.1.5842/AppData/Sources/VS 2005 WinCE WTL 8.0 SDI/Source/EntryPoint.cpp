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
// resource includes

#include "Resource.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// other includes

#include "MainFrame.h"

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInst*/, LPTSTR pszCmdLine, int nShowCmd)
{
	// check for previous instance
	HRESULT hr = CMainFrame::ActivatePreviousInstance(hInstance, pszCmdLine);
	if (FAILED(hr) || hr == S_FALSE)
	{
		return (hr);
	}

	// initialize application
	_Module.Init(NULL, hInstance);
	WTL::CMessageLoop msgLoop;
	_Module.AddMessageLoop(&msgLoop);

	// try to create main window
	CMainFrame mainFrame;
	if (!::IsWindow(mainFrame.CreateEx()))
	{
		ATLTRACE2(WTL::atlTraceUI, 0, _T("Main window creation failed!\n"));
		return (-1);
	}

	// show main window and enter message pump
	mainFrame.ShowWindow(nShowCmd);
	int nResult = msgLoop.Run();

	// terminate application
	_Module.RemoveMessageLoop();
	_Module.Term();

	// return to Windoze
	return (nResult);
}

// end of file
