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
|* PROGRAM: NVAPIExample.cpp
|*
|* PURPOSE: CWinApp derived class.
******************************************************************************/

#include "stdafx.h"
#include "NVAPIExample.h"
#include "NVAPIExampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CNVAPIExampleApp, CWinApp)
	//{{AFX_MSG_MAP(CNVAPIExampleApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


CNVAPIExampleApp::CNVAPIExampleApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNVAPIExampleApp object

CNVAPIExampleApp theApp;


// This is a static member variable important for NeroAPI initialization.
// 
NERO_SETTINGS CNVAPIExampleApp::ns = 
{
	NULL,
	"Ahead",
	"Nero Burning ROM",
	"Nero.txt",
	{NeroIdleCallback, &theApp},
	{NeroUserDialog, &theApp},
	FALSE,
	0
};

BOOL CNVAPIExampleApp::InitInstance()
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

	HRESULT hr = CoInitialize (NULL);
	if (FAILED (hr))
	{
		return FALSE;
	}

	// Initialize NeroAPI...
	// 
	BOOL bSuccess = NeroAPIGlueConnect (NULL);
	if (!bSuccess)
	{
		AfxMessageBox (IDS_NEROAPI_GLUE_CONNECT_FAILED);
		return FALSE;
	}

	NEROAPI_INIT_ERROR err = NeroInit (&ns, NULL);
	if (err != NEROAPI_INIT_OK)
	{
		AfxMessageBox (IDS_NERO_INIT_FAILED);
		return FALSE;
	}

	CNVAPIExampleDlg dlg;
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

int CNVAPIExampleApp::ExitInstance() 
{
	// Clean up the NeroAPI...
	// 
	NeroDone ();
	NeroAPIGlueDone ();
	
	CoUninitialize ();
	
	return CWinApp::ExitInstance();
}

// This is a helper method used for pumping the messages in long operations
// that hijack the main app's thread.
// 
void CNVAPIExampleApp::PumpMessages (void) const
{
    MSG msg;
    while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
    {
        if (!AfxGetApp ()->PumpMessage ())
        {
            ::PostQuitMessage (0);
            break;
        }
    }
}

// NeroAPI's idle callback impementation.
// 
BOOL NERO_CALLBACK_ATTR CNVAPIExampleApp::NeroIdleCallback (void *pUserData)
{
	CNVAPIExampleApp * pThis = (CNVAPIExampleApp *) pUserData;

	// When NeroAPI is idle, let's pump messages to keep everything nicely
	// responsive.
	// 
	pThis->PumpMessages ();

	// Forward the idle callback request to the main app's window using a
	// user defined message.
	// 
	return (BOOL) pThis->GetMainWnd ()->SendMessage (UM_NERO_IDLE_CALLBACK);
}

// NeroAPI's user dialog callback impementation.
// 
NeroUserDlgInOut NERO_CALLBACK_ATTR CNVAPIExampleApp::NeroUserDialog (void *pUserData, NeroUserDlgInOut type, void *data)
{
	CNVAPIExampleApp * pThis = (CNVAPIExampleApp *) pUserData;

	// Forward the user dialog callback to the main app's windows using a
	// user defined message and return whatever the handler returns to us.
	// 
	return (NeroUserDlgInOut) pThis->GetMainWnd ()->SendMessage (UM_NERO_USER_DIALOG, (WPARAM) type, (LPARAM) data);
}

