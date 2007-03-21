// AfxScratch application.
// Copyright (c) 2004 by Elijah Zarezky,
// All rights reserved.

// AuxTypes.h - auxiliary data types

#if !defined(__AuxTypes_h)
#define __AuxTypes_h

// projects list item data
struct PROJECT_DATA {
	enum {
		// field lengths
		MAX_NAME = 31,
		MAX_DESCRIPTION = 255
	};
	TCHAR szConfigFile[_MAX_PATH];
	TCHAR szName[MAX_NAME + 1];
	TCHAR szDescription[MAX_DESCRIPTION + 1];
};

// macros list item data
struct MACRO_DATA {
	enum {
		// field lengths
		MAX_NAME = 15,
		MAX_DESCRIPTION = 255,
		MAX_TYPE = 7,
		MAX_VALUE = 63
	};
	TCHAR szName[MAX_NAME + 1];
	TCHAR szDescription[MAX_DESCRIPTION + 1];
	enum TYPE {
		// type of macro
		STRING,
		NUMBER,
		UUID
	} eTypeID;
	TCHAR szType[MAX_TYPE + 1];
	TCHAR szValue[MAX_VALUE + 1];
};

#endif	// __AuxTypes_h

// end of file
