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
|* PROGRAM: CNVAPIExampleDlg.cpp
|*
|* PURPOSE: Implementation of the main property sheet like dialog.
******************************************************************************/

#include "stdafx.h"
#include "NVAPIExample.h"
#include "NVAPIExampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is a standard about box.
// 
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// Disable the warning about "this" usage member variable initialization
// in the constructor.
// 
#pragma warning(disable:4355)

CNVAPIExampleDlg::CNVAPIExampleDlg(CWnd* pParent /*=NULL*/)
	: CSheet(CNVAPIExampleDlg::IDD, pParent)
	, m_iCurrentPage (-1)
	, m_pageFirst (this)
	, m_pageSecond (this)
	, m_pageThird (this)
	, m_iPageCount (sizeof (m_pPages)/sizeof (m_pPages[0]))
{
	//{{AFX_DATA_INIT(CNVAPIExampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAIN);

	// Initialize the pages array.
	// 
	m_pPages[0] = &m_pageFirst;
	m_pPages[1] = &m_pageSecond;
	m_pPages[2] = &m_pageThird;
}

void CNVAPIExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CSheet::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNVAPIExampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNVAPIExampleDlg, CSheet)
	//{{AFX_MSG_MAP(CNVAPIExampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_NERO_USER_DIALOG, OnNeroUserDialog)
	ON_MESSAGE(UM_NERO_IDLE_CALLBACK, OnNeroIdleCallback)
END_MESSAGE_MAP()



BOOL CNVAPIExampleDlg::OnInitDialog()
{
	CSheet::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Get the rectangle of the child page dialog placeholder.
	// 
	CRect rcPlaceholder;
	GetDlgItem (IDC_PAGE_PLACEHOLDER)->GetWindowRect (&rcPlaceholder);
	ScreenToClient (&rcPlaceholder);

	// Create and reposition all child pages using the placeholder
	// rectangle.
	// 
	for (int i = 0; i < m_iPageCount; i ++)
	{
		VERIFY (m_pPages[i]->Create ());
		m_pPages[i]->MoveWindow (&rcPlaceholder);
	}

	// Once everything is created, switch to the zero-th page.
	// 
	SwitchPage (0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNVAPIExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CSheet::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNVAPIExampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CSheet::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNVAPIExampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNVAPIExampleDlg::OnAbout() 
{
	CAboutDlg dlg;

	dlg.DoModal ();
}

// OK button is actually a Next button.
// 
void CNVAPIExampleDlg::OnOK() 
{
	// First ask the page if it wants to handle the click and only act
	// if not.
	// 
	if (!m_pPages[m_iCurrentPage]->OnNext ())
	{
		// Go to the next page unless we are at the end.
		// 
		if (m_iCurrentPage < m_iPageCount - 1)
		{
			SwitchPage (m_iCurrentPage + 1);
		}
		else
		{
			// If at the end, exit. The user clicked 'Finish'.
			// 
			CSheet::OnOK();
		}
	}
}

// Cancel button is actually a Back button.
// 
void CNVAPIExampleDlg::OnCancel() 
{
	// First ask the page if it wants to handle the click and only act
	// if not.
	// 
	if (!m_pPages[m_iCurrentPage]->OnBack ())
	{
		// Go to the previous page unless we are at the beginning.
		// 
		if (0 < m_iCurrentPage)
		{
			SwitchPage (m_iCurrentPage - 1);
		}
	}
}

// A method used for page switching.
// 
void CNVAPIExampleDlg::SwitchPage (int iNewPage)
{
	// Get the pointers to CPage for ease of use.
	// 
	CPage * pOldPage = m_iCurrentPage >= 0? m_pPages[m_iCurrentPage]: NULL;
	CPage * pNewPage = m_pPages[iNewPage];

	// Load the string for 'Back', set it to the button and enable it
	// as appropriate.
	// 
	CString str;
	str.LoadString (IDS_BUTTON_BACK);
	GetDlgItem (IDCANCEL)->SetWindowText (str);
	GetDlgItem (IDCANCEL)->EnableWindow (iNewPage > 0);
	
	// Load the string for 'Finish' or 'Next' as appropriate and always
	// enable the button (this is to make sure if any of the pages left it
	// disabled.
	// 
	str.LoadString (iNewPage == m_iPageCount-1? IDS_BUTTON_FINISH: IDS_BUTTON_NEXT);
	GetDlgItem (IDOK)->SetWindowText (str);
	GetDlgItem (IDOK)->EnableWindow (TRUE);
	
	bool bForward = m_iCurrentPage < iNewPage;

	// Now, show the new page, then hide the old one.
	// 
	pNewPage->ShowWindow (SW_SHOW);
	if (pOldPage != NULL)
	{
		pOldPage->OnChangeState (false, bForward);
		pOldPage->ShowWindow (SW_HIDE);
	}
	pNewPage->UpdateWindow ();
	pNewPage->OnChangeState (true, bForward);
	
	m_iCurrentPage = iNewPage;
}

void CNVAPIExampleDlg::OnClose() 
{
	// If X was clicked, just end the dialog.
	// 
	EndDialog (IDCANCEL);
}

DWORD CNVAPIExampleDlg::GetCommonPageData (void)
{
	return (DWORD) &m_pageData;
}

// This is a message handler for our user message UM_NERO_USER_DIALOG. We
// have no interest in handling it. Instead, we forward it to the current
// page.
// 
LRESULT CNVAPIExampleDlg::OnNeroUserDialog (WPARAM wParam, LPARAM lParam)
{
	return m_pPages[m_iCurrentPage]->SendMessage (UM_NERO_USER_DIALOG, wParam, lParam);
}

// This is a message handler for our user message UM_NERO_IDLE_CALLBACK. We
// have no interest in handling it. Instead, we forward it to the current
// page.
// 
LRESULT CNVAPIExampleDlg::OnNeroIdleCallback (WPARAM wParam, LPARAM lParam)
{
	return m_pPages[m_iCurrentPage]->SendMessage (UM_NERO_IDLE_CALLBACK);
}

