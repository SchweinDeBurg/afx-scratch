// AfxScratch application.
// Copyright (c) 2004-2006 by Elijah Zarezky,
// All rights reserved.

// stdafx.cpp - source file that includes just the standard includes

#include "stdafx.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif	// _DEBUG

// import libraries
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "version.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "rpcrt4.lib")

// linker options
#if (_MSC_VER < 1300)
#pragma comment(linker, "/ignore:4089")		// all references to DLL discarded by /opt:ref
#pragma comment(linker, "/opt:ref")
#endif	// _MSC_VER

// end of file
