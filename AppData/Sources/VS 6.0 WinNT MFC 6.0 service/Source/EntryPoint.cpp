// $PROJECT$ NT service.
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

#include "ExecLogging.h"

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

int _tmain(int argc, TCHAR* argv[], TCHAR* /*envp*/[])
{
	BOOL fMemTrack;

	// try to initialize MFC
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), SW_HIDE))
	{
		return (-1);
	}

#if defined(_DEBUG)
	// install a client-defined reporting function
	_CrtSetReportHook(LogFile_WriteDbgRpt);
#endif   // _DEBUG

#if defined(_DEBUG)
	CMemoryState memStart, memStop, memDiff;
	// get the initial snapshot of memory
	memStart.Checkpoint();
#endif   // _DEBUG

	// adjust profile name
	fMemTrack = AfxEnableMemoryTracking(FALSE);
	free(const_cast<LPTSTR>(g_app$PROJECT$.m_pszProfileName));
	g_app$PROJECT$.m_pszProfileName = _tcsdup(argv[0]);
	AfxEnableMemoryTracking(fMemTrack);
	::PathRenameExtension(const_cast<LPTSTR>(g_app$PROJECT$.m_pszProfileName), _T(".ini"));

	// start logging
	CString strLogName(argv[0]);
	::PathRenameExtension(strLogName.GetBuffer(0), _T(".log"));
	strLogName.ReleaseBuffer();
	LogFile_Create(strLogName);
	LogFile_WriteEntry(LL_MINIMAL, IDS_EXE_STARTED, argv[0]);

	// parse command-line arguments
	if (argc > 1)
	{
		SC_HANDLE schManager = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (::lstrcmpi(argv[1], _T("/Register")) == 0)
		{
			// insert service into the SCM database
			SC_HANDLE schService = ::CreateService(schManager, g_szServiceName, g_szServiceName,
				SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START,
				SERVICE_ERROR_NORMAL, argv[0], NULL, NULL, NULL, NULL, NULL);
			::CloseServiceHandle(schService);
			LogFile_WriteEntry(LL_MINIMAL, IDS_SERVICE_REGISTERED, g_szServiceName);
		}
		else if (::lstrcmpi(argv[1], _T("/UnRegister")) == 0)
		{
			// remove service from the SCM database
			SC_HANDLE schService = ::OpenService(schManager, g_szServiceName, SERVICE_ALL_ACCESS);
			::DeleteService(schService);
			::CloseServiceHandle(schService);
			LogFile_WriteEntry(LL_MINIMAL, IDS_SERVICE_UNREGISTERED, g_szServiceName);
		}
		else {
			// unrecognized command-line argument
			LogFile_WriteEntry(LL_MINIMAL, IDS_CMDLINE_BAD_ARGUMENT, argv[1]);
		}
		::CloseServiceHandle(schManager);
	}
	else {
		// just start the service
		static SERVICE_TABLE_ENTRY aste[] =
		{
			{ g_szServiceName, ServiceMain },
			{ NULL, NULL }   // end of table - required
		};
		LogFile_WriteEntry(LL_MINIMAL, IDS_SCM_CONNECT);
		::StartServiceCtrlDispatcher(aste);
		LogFile_WriteEntry(LL_MINIMAL, IDS_SCM_DISCONNECTED);
	}

#if defined(_DEBUG)
	// get the final memory state...
	memStop.Checkpoint();
	// ...and then check the leaks
	if (memDiff.Difference(memStart, memStop))
	{
		_CrtMemDumpStatistics(&memDiff.m_memState);
		_CrtDumpMemoryLeaks();
	}
#endif   // _DEBUG
	LogFile_WriteEntry(LL_MINIMAL, IDS_EXE_FINISHED, argv[0]);

	// terminate MFC
#if defined(_DEBUG)
	AfxLockTempMaps();
	AfxUnlockTempMaps(-1);
#endif   // _DEBUG
	AfxWinTerm();

	// return to Windoze
	return (0);
}

// end of file
