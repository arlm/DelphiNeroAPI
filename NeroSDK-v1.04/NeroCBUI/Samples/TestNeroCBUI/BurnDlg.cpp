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
// NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! 
// 
// In order to make BurnDlg work in a MFC project one should:
// 
// 1) Create a new CDialog derived class (probably using the wizard). The
//    dialog template should be empty (no controls). Its size will mandate
//    the initial size of the BurnProgressDlg.
// 2) OnInitDialog should be used to create a NeroCBUI BurnProgressDlg
//    object and set its properties. This is the place to create the
//    actual window with IModelessDialog::Create method.
// 3) It is essential to trigger the WM_GETMINMAXINFO message if NULL was
//    passed as pRect to IModelessDialog::Create. If it is non-NULL,
//    WM_GETMINMAXINFO triggering is not necessary.
// 4) PreTranslateMessage should be overriden to allow the BurnProgressDlg
//    to handle its own dialog messages.
// 5) OnCancel should be handled (even though there are no controls) so that
//    dialog dismissal is handled properly.
// 6) OnSize should be handled to allow the sizing of the BurnProgressDlg.
// 7) Finally, the burn process should be started after the dialog is
//    initialized. It is best to post a user message from the OnInitDialog
//    so that OnInitDialog can return. When the message is processed, it
//    will initiate the burn process. Due to the MFC architecture, even
//    though we posted a message from OnInitDialog, the dialog will not yet
//    be shown at the time of user message processing so we MUST show and
//    update the window manually.
// 
// NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! 

#include "stdafx.h"
#include "TestNeroCBUI.h"
#include "BurnDlg.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Allow the #define below if you want to test the dialog without setting
// the minimum size.
// 
//#define DONT_FORCE_MIN_SIZE


#define UM_POST_INIT_DIALOG		(WM_APP + 1)

/////////////////////////////////////////////////////////////////////////////
// CBurnDlg dialog


CBurnDlg::CBurnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBurnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBurnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pDeviceInfo = NULL;
	m_bWizardMode = FALSE;
}

CBurnDlg::~CBurnDlg ()
{
	m_wndDialog.Detach ();

	// We must not release m_pDeviceInfo. It is not ours!!!
	// 
}

void CBurnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBurnDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBurnDlg, CDialog)
	//{{AFX_MSG_MAP(CBurnDlg)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_POST_INIT_DIALOG, OnPostInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBurnDlg message handlers

BOOL CBurnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (SUCCEEDED (m_pModelessDialog.CoCreateInstance (__uuidof (BurnProgressDlg))))
	{
		CComQIPtr<IBurnProgressDlg3> pBurnProgressDlg (m_pModelessDialog);
		CComBSTR bstr;

		// We add this as a custom control as we are implementing dummy
		// IUnknown and needed IExternalChildWindow interface.
		// 
		pBurnProgressDlg->AddCustomControl (BPCCP_BOTTOM_RIGHT_CORNER, this);

		bstr = "Test name";
		pBurnProgressDlg.p->put_CompilationName (bstr);
		bstr = "100 MB";
		pBurnProgressDlg.p->put_CompilationSize (bstr);
		bstr = "01:05:10";
		pBurnProgressDlg.p->put_CompilationTime (bstr);
		bstr = "ISO/Audio";
		pBurnProgressDlg.p->put_CompilationType (bstr);

		pBurnProgressDlg->put_WizardMode (m_bWizardMode);
		if(m_bWizardMode)
			pBurnProgressDlg.p->put_GUIFlags (BPGF_USED_BUFFER);

		CRect rect;
		GetClientRect (&rect);

		// Create the BurnProgressDlg with the same dimensions as its
		// parent dialog.
		// 
		HWND hWndDialog = NULL;
		m_pModelessDialog.p->Create (m_hWnd, &rect, &hWndDialog);
		if (hWndDialog != NULL)
		{
			m_wndDialog.Attach (hWndDialog);
			m_wndDialog.ShowWindow (SW_SHOW);
		}

		// Let the dialog be shown first, then start the burn process.
		// 
		PostMessage (UM_POST_INIT_DIALOG);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBurnDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	if (m_pModelessDialog)
	{
		m_pModelessDialog.p->Destroy ();
	}
}

void CBurnDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if (m_wndDialog.m_hWnd != NULL)
	{
		CRect rect (0, 0, cx, cy);
		m_wndDialog.MoveWindow (&rect);
	}
}

void CBurnDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
#ifndef DONT_FORCE_MIN_SIZE
	if (m_wndDialog.m_hWnd != NULL)
	{
		MINMAXINFO mmi;
		
		mmi = *lpMMI;
		m_wndDialog.SendMessage (WM_GETMINMAXINFO, 0, (LPARAM) &mmi);
		
		CRect rect (0, 0, mmi.ptMinTrackSize.x, mmi.ptMinTrackSize.y);
		AdjustWindowRectEx (&rect, GetStyle (), FALSE, GetExStyle ());
		
		lpMMI->ptMinTrackSize.x = rect.Width ();
		lpMMI->ptMinTrackSize.y = rect.Height ();
	}
	else
	{
		CDialog::OnGetMinMaxInfo(lpMMI);
	}
#else
	CDialog::OnGetMinMaxInfo(lpMMI);
#endif
}

BOOL CBurnDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (m_pModelessDialog)
	{
		if (m_pModelessDialog.p->TranslateAccelerator (pMsg) == S_OK)
		{
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CBurnDlg::OnPostInitDialog (WPARAM wParam, LPARAM lParam)
{
	CComQIPtr<IBurnProgressDlg> pBurnProgressDlg (m_pModelessDialog);
	if (pBurnProgressDlg)
	{
		ShowWindow (SW_SHOW);
		UpdateWindow ();

		static char szFilter[] = "Nero Images (*.nrg)|*.nrg|ISO Images (*.iso)|*.iso|All Files (*.*)|*.*||";
		CFileDialog fileDlg(TRUE,"nrg",NULL
			, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilter, this);
		if(fileDlg.DoModal() == IDOK)
		{
			m_neroImage.nwiImageFileName[0] = '\0';
			CString csFilename = fileDlg.GetPathName();
			m_neroImage.nwiLongImageFileName = (LPCSTR)csFilename;
		

			pBurnProgressDlg.p->Burn2 (m_pDeviceInfo, NERO_BURN_IMAGE_MEDIA, &m_neroImage, NBF_DETECT_NON_EMPTY_CDRW|NBF_WRITE, 0, NULL);
		}
		else
		{
			pBurnProgressDlg.p->AddLogLine(NERO_TEXT_STOP,L"Burning not started! (TestNeroCBUI)");
			pBurnProgressDlg.p->Cancel();
		}
	}
	
	return 0;
}

void CBurnDlg::OnCancel()
{
	CComQIPtr<IBurnProgressDlg> pBurnProgressDlg (m_pModelessDialog);
	BOOL bCanClose = FALSE;

	ATLASSERT (pBurnProgressDlg.p != NULL);

	if (pBurnProgressDlg.p)
	{
		// Ask the BurnProgressDlg if we are allowed to close the parent.
		// 
		pBurnProgressDlg.p->CanCloseParent (&bCanClose);
	}

	if (!bCanClose)
	{
		// If not allowed to close, cancel the burning process.
		// 
		if (pBurnProgressDlg.p)
		{
			pBurnProgressDlg.p->Cancel ();
		}
	}
	else
	{
		CDialog::OnCancel ();
	}
}

STDMETHODIMP CBurnDlg::Create (/*[in]*/ HWND hWndParent, /*[out, retval]*/ HWND * phWnd)
{
	*phWnd = CreateWindow ("BUTTON",
							"This is a test button!",
							WS_CHILD|WS_VISIBLE|BS_MULTILINE,
							0, 0, 10, 10,
							hWndParent,
							(HMENU) 9999,
							AfxGetResourceHandle (),
							NULL);

	return S_OK;
}

STDMETHODIMP CBurnDlg::get_MinSize (/*[out, retval]*/ SIZE * pSize)
{
	*pSize = CSize (50, 50);

	return S_OK;
}

STDMETHODIMP CBurnDlg::get_MaxSize (/*[out, retval]*/ SIZE * pSize)
{
	*pSize = CSize (150, INT_MAX);

	return S_OK;
}
