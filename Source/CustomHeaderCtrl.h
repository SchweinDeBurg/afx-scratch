// AfxScratch application.
// Copyright (c) 2004-2006 by Elijah Zarezky,
// All rights reserved.

// CustomHeaderCtrl.h - interface of the CCustomHeaderCtrl class

#if !defined(__CustomHeaderCtrl_h)
#define __CustomHeaderCtrl_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif	// _MSC_VER

class CCustomHeaderCtrl: public CHeaderCtrl
{
	DECLARE_DYNAMIC(CCustomHeaderCtrl)
	DECLARE_MESSAGE_MAP()

// message map functions
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint(void);
};

#endif	// __CustomHeaderCtrl_h

// end of file
