// $PROJECT$ static library.
// Copyright (c) $YEAR$ by $AUTHOR$,
// All rights reserved.

// stdafx.cpp - source file that includes just the standard includes

// initially generated by $GENERATOR$ on $DATE$ at $TIME$
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

#include "stdafx.h"

// linker options

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment(linker, "/nodefaultlib:libcd.lib")
#else
#pragma comment(linker, "/nodefaultlib:libc.lib")
#endif	// _DEBUG || DEBUG

// required libraries

#if defined(_CPPRTTI) && (_WIN32_WCE < 0x500)
#pragma comment(lib, "ccrtrtti.lib")
#endif	// _CPPRTTI && _WIN32_WCE

// end of file