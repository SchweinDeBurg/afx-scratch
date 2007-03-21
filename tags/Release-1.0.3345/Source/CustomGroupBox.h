// AfxScratch application.
// Copyright (c) 2004-2006 by Elijah Zarezky,
// All rights reserved.

// CustomGroupBox.h - interface of the CCustomGroupBox class

#if !defined(__CustomGroupBox_h)
#define __CustomGroupBox_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif	// _MSC_VER

class CCustomGroupBox: public CButton
{
	DECLARE_DYNAMIC(CCustomGroupBox)
	DECLARE_MESSAGE_MAP()

// message map functions
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint(void);
};

#endif	// __CustomGroupBox_h

// end of file
