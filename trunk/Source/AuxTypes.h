// AfxScratch application.
// Copyright (c) 2004-2011 by Elijah Zarezky,
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
#endif   // _MSC_VER

//////////////////////////////////////////////////////////////////////////////////////////////
// projects list item data

struct PROJECT_DATA
{
	enum
	{
		// field lengths
		MAX_DEVENV = 16,
		MAX_FRAMEWORK = 32,
		MAX_NAME = 32,
		MAX_SRCROOT = _MAX_DIR,
		MAX_DESCRIPTION = 256
	};
	TCHAR szConfigFile[_MAX_PATH];
	TCHAR szDevEnv[MAX_DEVENV];
	TCHAR szFramework[MAX_FRAMEWORK];
	TCHAR szName[MAX_NAME];
	TCHAR szSrcRoot[MAX_SRCROOT];
	TCHAR szDescription[MAX_DESCRIPTION];
};

//////////////////////////////////////////////////////////////////////////////////////////////
// macros list item data

struct MACRO_DATA
{
	enum
	{
		// field lengths
		MAX_NAME = 16,
		MAX_DESCRIPTION = 256,
		MAX_TYPE = 8,
		MAX_VALUE = 64
	};
	TCHAR szName[MAX_NAME];
	TCHAR szDescription[MAX_DESCRIPTION];
	enum TYPE
	{
		// type of macro
		STRING,
		NUMBER,
		UUID
	} eTypeID;
	TCHAR szType[MAX_TYPE];
	TCHAR szValue[MAX_VALUE];
	BOOL fOptional;
};

#endif   // __AuxTypes_h

// end of file
