// AfxScratch application.
// Copyright (c) 2004-2007 by Elijah Zarezky,
// All rights reserved.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// AuxTypes.h - auxiliary data types

#if !defined(__AuxTypes_h)
#define __AuxTypes_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif	// _MSC_VER

// projects list item data
struct PROJECT_DATA
{
	enum
	{
		// field lengths
		MAX_NAME = 31,
		MAX_DESCRIPTION = 255
	};
	TCHAR szConfigFile[_MAX_PATH];
	TCHAR szName[MAX_NAME + 1];
	TCHAR szDescription[MAX_DESCRIPTION + 1];
};

// macros list item data
struct MACRO_DATA
{
	enum
	{
		// field lengths
		MAX_NAME = 15,
		MAX_DESCRIPTION = 255,
		MAX_TYPE = 7,
		MAX_VALUE = 63
	};
	TCHAR szName[MAX_NAME + 1];
	TCHAR szDescription[MAX_DESCRIPTION + 1];
	enum TYPE
	{
		// type of macro
		STRING,
		NUMBER,
		UUID
	} eTypeID;
	TCHAR szType[MAX_TYPE + 1];
	TCHAR szValue[MAX_VALUE + 1];
	BOOL fOptional;
};

#endif	// __AuxTypes_h

// end of file
