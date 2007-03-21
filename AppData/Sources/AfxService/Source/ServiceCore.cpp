// $PROJECT$ NT service.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// ServiceCore.cpp - core service routines
// initially generated by $GENERATOR$ on $DATE$ at $TIME$

#include "stdafx.h"
#include "ExecLogging.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// private globals
static CWinThread* g_pWorkerThread = NULL;
static LONG g_fStop = FALSE;

// worker thread procedure
static UINT WorkerProc(void* /*pParam*/)
{
	WriteLogFileEntry(LL_MINIMAL, _T("Started worker thread."));

	// enter worker loop
	while (!g_fStop) {
	}

	// final clean-up
	::InterlockedExchange(&g_fStop, FALSE);

	// successfully finished
	WriteLogFileEntry(LL_MINIMAL, _T("Finished worker thread."));
	AfxEndThread(0);
	return (0);
}

// control handler function of a service
void WINAPI ServiceHandler(DWORD fdwControl)
{
	SERVICE_STATUS ss;

	ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	switch (fdwControl)
	{
	case SERVICE_CONTROL_SHUTDOWN:
		WriteLogFileEntry(LL_MINIMAL, _T("Detected operating system shutdown."));
		// fall through
	case SERVICE_CONTROL_STOP:
		WriteLogFileEntry(LL_MINIMAL, _T("Requested to stop %s service."), g_szServiceName);
		::InterlockedExchange(&g_fStop, TRUE);
		::WaitForSingleObject(*g_pWorkerThread, INFINITE);
		g_pWorkerThread = NULL;
		ss.dwCurrentState = SERVICE_STOPPED;
		g_dwServiceState = ss.dwCurrentState;
		break;
	default:
		ss.dwCurrentState = g_dwServiceState;
		break;
	}
	ss.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	ss.dwWin32ExitCode = NO_ERROR;
	ss.dwServiceSpecificExitCode = 0;	// will be ignored
	ss.dwCheckPoint = 0;
	ss.dwWaitHint = 0;
	::SetServiceStatus(g_hServiceStatus, &ss);
	if (g_dwServiceState == SERVICE_STOPPED) {
		WriteLogFileEntry(LL_MINIMAL, _T("Stopped %s service."), g_szServiceName);
	}
}

// service entry-point function
void WINAPI ServiceMain(DWORD /*dwArgc*/, LPTSTR /*apszArgv*/[])
{
	SERVICE_STATUS ss;

	g_hServiceStatus = ::RegisterServiceCtrlHandler(g_szServiceName, ServiceHandler);
	ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ss.dwCurrentState = SERVICE_RUNNING;
	ss.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	ss.dwWin32ExitCode = NO_ERROR;
	ss.dwServiceSpecificExitCode = 0;	// will be ignored
	ss.dwCheckPoint = 0;
	ss.dwWaitHint = 0;
	::SetServiceStatus(g_hServiceStatus, &ss);
	g_dwServiceState = ss.dwCurrentState;
	WriteLogFileEntry(LL_MINIMAL, _T("Runned %s service."), g_szServiceName);
	g_pWorkerThread = AfxBeginThread(WorkerProc, NULL);
}

// end of file
