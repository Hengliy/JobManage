// Job.h : main header file for the JOB application
//

#if !defined(AFX_JOB_H__56A22EF4_FF24_4381_9ECB_12EC5BD8BAAC__INCLUDED_)
#define AFX_JOB_H__56A22EF4_FF24_4381_9ECB_12EC5BD8BAAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJobApp:
// See Job.cpp for the implementation of this class
//

class CJobApp : public CWinApp
{
public:
	CJobApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJobApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJobApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JOB_H__56A22EF4_FF24_4381_9ECB_12EC5BD8BAAC__INCLUDED_)
