/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NVAPIExample
|*
|* PROGRAM: NVAPIExample.h
|*
|* PURPOSE: CWinApp derived class.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_H_
#define _NVAPIEXAMPLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CNVAPIExampleApp : public CWinApp
{
protected:
	static NERO_SETTINGS ns;
public:
	CNVAPIExampleApp();

	void PumpMessages (void) const;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNVAPIExampleApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNVAPIExampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	static NeroUserDlgInOut NERO_CALLBACK_ATTR NeroUserDialog (void *pUserData, NeroUserDlgInOut type, void *data);
	static BOOL NERO_CALLBACK_ATTR NeroIdleCallback (void *pUserData);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
