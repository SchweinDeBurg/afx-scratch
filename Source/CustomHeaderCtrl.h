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

// CustomHeaderCtrl.h - interface of the CCustomHeaderCtrl class

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif   // _MSC_VER

#if !defined(__CustomHeaderCtrl_h)
#define __CustomHeaderCtrl_h

//////////////////////////////////////////////////////////////////////////////////////////////
// CCustomHeaderCtrl

class CCustomHeaderCtrl: public CHeaderCtrl
{
	DECLARE_DYNAMIC(CCustomHeaderCtrl)
	DECLARE_MESSAGE_MAP()

// message map functions
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint(void);
};

#endif   // __CustomHeaderCtrl_h

// end of file
