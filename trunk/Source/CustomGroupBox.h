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

// CustomGroupBox.h - interface of the CCustomGroupBox class

#if !defined(__CustomGroupBox_h)
#define __CustomGroupBox_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif   // _MSC_VER

class CCustomGroupBox: public CButton
{
	DECLARE_DYNAMIC(CCustomGroupBox)
	DECLARE_MESSAGE_MAP()

// message map functions
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint(void);
};

#endif   // __CustomGroupBox_h

// end of file
