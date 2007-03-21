// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
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

// static libraries
#if defined(__STL_CONFIG_H)
#if defined(_DEBUG)
#pragma comment(linker, "/nodefaultlib:msvcprtd.lib")
#pragma comment(lib, "libciod.lib")
#else
#pragma comment(linker, "/nodefaultlib:msvcprt.lib")
#pragma comment(lib, "libcio.lib")
#endif	// _DEBUG
#endif	// __STL_CONFIG_H

// linker options
#pragma comment(linker, "/ignore:4089")		// all references to DLL discarded by /opt:ref

// end of file
