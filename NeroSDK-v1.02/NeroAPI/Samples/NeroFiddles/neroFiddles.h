/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* PROJECT: neroFiddles NeroAPI Example
|*
|* FILE: neroFiddles.h
|*
|* PURPOSE: Declaration file for the application.
******************************************************************************/

// neroFiddles.h : main header file for the NEROFIDDLES application
//

#if !defined(AFX_NEROFIDDLES_H__78BE85B7_87B6_11D4_8056_00105ABB05E6__INCLUDED_)
#define AFX_NEROFIDDLES_H__78BE85B7_87B6_11D4_8056_00105ABB05E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNeroFiddlesApp:
// See neroFiddles.cpp for the implementation of this class
//

class CNeroFiddlesApp : public CWinApp
{
public:
	CNeroFiddlesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNeroFiddlesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNeroFiddlesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEROFIDDLES_H__78BE85B7_87B6_11D4_8056_00105ABB05E6__INCLUDED_)
