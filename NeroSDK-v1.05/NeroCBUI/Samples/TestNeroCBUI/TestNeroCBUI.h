/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroCBUI
|*
|* PROGRAM: TestNeroCBUI
|*
|* PURPOSE: Sample application for the use of NeroCBUI
******************************************************************************/
#if !defined(AFX_TESTNEROCBUI_H__62BFE6D1_C68D_4C95_819C_CF24F5519C3D__INCLUDED_)
#define AFX_TESTNEROCBUI_H__62BFE6D1_C68D_4C95_819C_CF24F5519C3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CApp:
// See TestNeroCBUI.cpp for the implementation of this class
//

class CApp : public CWinApp
{
public:
	CApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetUserDlgParentHWND (HWND hWnd);
	void ResetUserDlgAbort();
	
protected:
	void SetupNeroAPI (void);
	void CleanupNeroAPI (void);
	static NERO_SETTINGS m_NeroSettings;
	static NeroUserDlgInOut NERO_CALLBACK_ATTR UserDialog(void *pUserData, NeroUserDlgInOut type, void *data);
	static BOOL NERO_CALLBACK_ATTR CApp::IdleCallback (void *pUserData);
		
	CComPtr<IInitSettings3> m_pInitSettings;
	CComPtr<IUserDlgHandler> m_pDlgHandler;

public:
	bool m_bNeroAPIInitOk;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTNEROCBUI_H__62BFE6D1_C68D_4C95_819C_CF24F5519C3D__INCLUDED_)