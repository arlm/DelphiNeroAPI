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

#include "stdafx.h"
#include "TestNeroCBUI.h"
#include "Dlg.h"
#include "NeroCBUIGlue.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CApp

BEGIN_MESSAGE_MAP(CApp, CWinApp)
	//{{AFX_MSG_MAP(CApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApp construction

CApp::CApp()
{
	m_bNeroAPIInitOk = false;
}
	
/////////////////////////////////////////////////////////////////////////////
// The one and only CApp object

CApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CApp initialization

BOOL CApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CoInitializeEx (NULL, COINIT_APARTMENTTHREADED);

	SetupNeroAPI ();

	CDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


int CApp::ExitInstance() 
{
	CleanupNeroAPI ();

	CoUninitialize ();
	
	return CWinApp::ExitInstance();
}

void CApp::SetupNeroAPI (void)
{
	NEROAPI_INIT_ERROR err;
	
	// Initialize the NeroAPI glue code.
	// 
	BOOL bSuccess = NeroAPIGlueConnect(NULL);
	if (bSuccess)
	{
		// Now, initialize the NeroAPI itself.
		// 
		m_NeroSettings.nstUserDialog.ncUserData=this;
		m_NeroSettings.nstIdle.ncUserData=this;
		err = NeroInit (&m_NeroSettings, NULL);
		
		// Now, create the InitSettings NeroCBUI object and pass it the
		// NeroAPI module handle.
		// 
		if (err == NEROAPI_INIT_OK && SUCCEEDED (m_pInitSettings.CoCreateInstance (__uuidof (InitSettings))))
		{
			// Release the object immediately so we can test successive
			// creation.
			// 
			m_pInitSettings = NULL;

			if (SUCCEEDED (m_pInitSettings.CoCreateInstance (__uuidof (InitSettings))))
			{
				m_pInitSettings->put_HMODULE (NeroAPIGlueGetModuleHandle ());
				m_pInitSettings->put_AppTitle ((const signed char*)"Test NeroCBUI");

				CComPtr<IInitSettings> pInitSettingsForTest;
				HRESULT hr = pInitSettingsForTest.CoCreateInstance (__uuidof (InitSettings));

				// The following are tests for proper operation of singleton
				// implementation. The second create must succeed and its
				// interface pointers must be litterally equal as they point
				// to the very same object.
				// 
				ATLASSERT (SUCCEEDED (hr));
				ATLASSERT (pInitSettingsForTest.p == m_pInitSettings.p);
			}

			CComPtr<IUnknown> pCompatibilityMgr;
			pCompatibilityMgr.Attach(NeroCBUIGlueGetCompatibilityMgr(NeroAPIGlueGetModuleHandle(),NULL));
			m_pInitSettings->put_CompatibilityMgr(pCompatibilityMgr);
			
			bSuccess = SUCCEEDED (m_pDlgHandler.CoCreateInstance (__uuidof (UserDlgHandler)));
			ATLASSERT (bSuccess);		
		}
	}
	

	m_bNeroAPIInitOk = (err == NEROAPI_INIT_OK) && bSuccess;
}

void CApp::SetUserDlgParentHWND (HWND hWnd)
{
	if (m_pDlgHandler.p != NULL)
	{
		m_pDlgHandler->put_ParentHWND (hWnd);
	}
}

void CApp::ResetUserDlgAbort()
{	 
	if (m_pDlgHandler.p != NULL)
	{
		m_pDlgHandler->put_Aborted (FALSE);
	}
}

void CApp::CleanupNeroAPI (void)
{
	m_pInitSettings = NULL;
	m_pDlgHandler = NULL;
	
	NeroDone ();
	NeroAPIGlueDone ();
}


NERO_SETTINGS CApp::m_NeroSettings = {
	NULL,
		"Ahead",
		"Nero - Burning Rom",
		"Nero.txt",
	{CApp::IdleCallback, 0},
	{CApp::UserDialog, 0},
	FALSE,
	0};
	
BOOL NERO_CALLBACK_ATTR CApp::IdleCallback (void *pUserData)
{
	MSG msg;
	
	while (::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if (!AfxGetThread()->PumpMessage())
		{
			::PostQuitMessage(0);
			break;
		}
	}
	
	// Do MFC's idle processing.
	// 
	LONG lIdle = 0;
	while (AfxGetThread ()->OnIdle (lIdle++))
		;

	BOOL bAborted = FALSE;
	CApp * pThis = (CApp *) pUserData;

	// here we check if the user pressed abort in one of the dialogs
	// of the NeroCBUI user dlg handler
	// don't forget to reset the abort flag in the user dlg handler
	// before starting a new burn process.
	if (pThis->m_pDlgHandler.p != NULL)
	{
		pThis->m_pDlgHandler->get_Aborted (&bAborted);
	}

	return bAborted;
}

NeroUserDlgInOut NERO_CALLBACK_ATTR CApp::UserDialog(void *pUserData, NeroUserDlgInOut type, void *data)
{	
	// We use the user dlg handler of NeroCBUI, so we don't have to take care
	// about this ourselves. If an application would need to so it could also
	// use the user dlg handler of NeroCBUI only for specific NeroUserDlgInOut types
	// and handle the rest by itself.
	// 
	// To enable the use of UserDlgHandler in TestNeroCBUI you have to change
	// OnTestBurnProgress in Dlg.cpp

	NeroUserDlgInOut result;

	ASSERT(pUserData);

	if(pUserData && SUCCEEDED(((CApp*)pUserData)->m_pDlgHandler->HandleUserDlg(type,data,&result)))
	{
		return result;
	}
	else
	{
		ATLASSERT(FALSE);
	}

	return DLG_RETURN_NOT_HANDLED;
}