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
#include "BurnDlg.h"
#include "PropertyPageBurnSettings.h"
#include "PropertyPageImageInfo.h"
#include "TestNeroCBUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg dialog

CDlg::CDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDlg::~CDlg ()
{
}

void CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg)
	DDX_Control(pDX, IDC_BURN_WIZARD_MODE, c_WizardMode);
	DDX_Control(pDX, IDC_MEDIA_COMBO, m_MediaCombo);
	DDX_Control(pDX, IDC_MODAL_ERASE_DISC, c_ModalEraseDisc);
	DDX_Control(pDX, IDC_LANG_COMBO, m_Combo);
	DDX_Control(pDX, IDC_TEST_ERASE_DISC, c_TestEraseDisc);
	DDX_Control(pDX, IDC_TEST_DISC_INFO, c_TestDiscInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg, CDialog)
	//{{AFX_MSG_MAP(CDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST_ERASE_DISC, OnTestEraseDisc)
	ON_BN_CLICKED(IDC_TEST_DISC_INFO, OnTestDiscInfo)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TEST_BURN_SETTINGS, OnTestBurnSettings)
	ON_BN_CLICKED(IDC_TEST_BURN_SETTINGS_OLE, OnTestBurnSettingsOle)
	ON_BN_CLICKED(IDC_TEST_BURN_PROGRESS, OnTestBurnProgress)
	ON_BN_CLICKED(IDC_TEST_IMAGE_INFO, OnTestImageInfo)
	ON_BN_CLICKED(IDC_TEST_CHOOSE_RECORDER, OnTestChooseRecorder)
	ON_BN_CLICKED(IDC_TEST_CHOOSE_SESSION, OnTestChooseSession)
	ON_CBN_SELCHANGE(IDC_LANG_COMBO, OnSelchangeLangCombo)
	ON_BN_CLICKED(IDC_TEST_ERASE_DISC_MODELESS, OnTestEraseDiscModeless)
	ON_BN_CLICKED(IDC_TEST_WAIT_FOR_MEDIA, OnTestWaitForMedia)
	ON_CBN_SELCHANGE(IDC_MEDIA_COMBO, OnSelchangeMediaCombo)
	ON_CBN_SELCHANGE(IDC_RECORDER, OnSelchangeRecorder)
	ON_BN_CLICKED(IDC_TEST_IMAGE_INFO_OLE, OnTestImageInfoOle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg message handlers

BOOL CDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	BOOL bSuccess = FALSE;

	if (SUCCEEDED (m_pRecorderCombobox.CoCreateInstance (__uuidof (RecorderCombobox))))
	{
		CComQIPtr<IChildWindow> pChildWindow (m_pRecorderCombobox);

		CComBSTR bstr ("Custom append item");
		m_pRecorderCombobox->AppendCustomEntry (m_hIcon, bstr, (void *) 1);

		bstr = "Custom prepend item";
		m_pRecorderCombobox->PrependCustomEntry (m_hIcon, bstr, (void *) 1);
		
		if (pChildWindow)
		{
			pChildWindow.p->Subclass (GetDlgItem (IDC_RECORDER)->m_hWnd, &bSuccess);
		}

		// set this object as callback receiver
		m_pRecorderCombobox.p->put_Callbacks(this);
	}
	
	if (bSuccess && SUCCEEDED (m_pWriteSpeedCombobox.CoCreateInstance (__uuidof (SpeedCombobox))))
	{
		// set the default media type
		m_pWriteSpeedCombobox.p->put_MediaType(MEDIA_CD);
		m_pWriteSpeedCombobox->put_HideWhenEmpty (FALSE);
		
		CComQIPtr<IChildWindow> pChildWindow (m_pWriteSpeedCombobox);
		
		if (pChildWindow)
		{
			pChildWindow.p->Subclass (GetDlgItem (IDC_WRITESPEEDS)->m_hWnd, &bSuccess);
		}	
	}

	
	BOOL bEnable = bSuccess && ((CApp*)AfxGetApp)->m_bNeroAPIInitOk;
	c_TestDiscInfo.EnableWindow (bEnable);
	c_TestEraseDisc.EnableWindow (bEnable);

	c_ModalEraseDisc.SetCheck (1);
	c_WizardMode.SetCheck (1);

	m_MediaCombo.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDlg::OnTestEraseDisc() 
{
	NEROAPI_CDRW_ERASE_MODE mode = NEROAPI_ERASE_QUICK;
	
	// Declare a smart pointer to INERO_SCSI_DEVICE_INFO interface. Create
	// an instance of DiscInfoDlg class.
	// 
	CComPtr<INERO_SCSI_DEVICE_INFO> pNSDI;
	if (SUCCEEDED (pNSDI.CoCreateInstance (__uuidof (EraseSettingsDlg))))
	{
		CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
		ATLASSERT (pRecorderNSDI);

		LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
		pRecorderNSDI.p->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);

		pNSDI->put_NERO_SCSI_DEVICE_INFO ( pDeviceInfo );

		CComQIPtr<IEraseSettingsDlg> pEraseSettingsDlg (pNSDI);
		ATLASSERT (pEraseSettingsDlg.p != NULL);

		bool bModelessErase = c_ModalEraseDisc.GetCheck () == 0;
		pEraseSettingsDlg->put_ModelessErase (bModelessErase);
		
		if (bModelessErase)
		{
			pEraseSettingsDlg->put_Callbacks (this);
		}

		// Declare a smart pointer to IModalDialog interface and call its
		// DoModal method.
		// 
		CComPtr<IModalDialog> pModalDialog;
		int iRet = 0;
		if(SUCCEEDED(pNSDI.QueryInterface(&pModalDialog)))
			pModalDialog->DoModal (m_hWnd, &iRet);
		
		if (!bModelessErase)
		{
			// Display different information depending on the return value.
			// 
			switch (iRet)
			{
			case IDOK:
				{
					CString str, sDevice;
					NERO_SCSI_DEVICE_INFO * pDeviceInfo;
					
					// Get the last current selection in the recorder combobox.
					// 
					pNSDI->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);
					sDevice.Format ("Selected device was \"%s\".", (pDeviceInfo != NULL && pDeviceInfo->nsdiDeviceName[0] != '\0')? pDeviceInfo->nsdiDeviceName: "[no device selected]");
					
					str.Format ("%s\nUser selected OK and erase process completed successfully!", sDevice);
					AfxMessageBox (str);
				}
				break;
				
			case IDCANCEL:
				AfxMessageBox ("The dialog was canceled!");
				break;
				
			default:
				{
					CString str;
					str.Format ("There was an error displaying the dialog box!");
					AfxMessageBox (str);
				}
			}
		}
		else
		{
			CComQIPtr<IEraseSettingsDlg2> pEraseSettingsDlg2 (pNSDI);

			if(pEraseSettingsDlg2.p)
			{
				HWND hWndDlg;
				pEraseSettingsDlg2->get_ModelessDlgHWND(&hWndDlg);
				ATLASSERT(hWndDlg);
				/*
				if(hWndDlg)
					VERIFY(::CloseWindow(hWndDlg));
				*/
			}
		}
	}
}

void CDlg::OnTestDiscInfo() 
{
	// Declare a smart pointer to INERO_SCSI_DEVICE_INFO interface. Create
	// an instance of DiscInfoDlg class.
	// 
	CComPtr<INERO_SCSI_DEVICE_INFO> pNSDI;
	if (SUCCEEDED (pNSDI.CoCreateInstance (__uuidof (DiscInfoDlg))))
	{
		CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
		ATLASSERT (pRecorderNSDI);

		LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
		pRecorderNSDI.p->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);

		pNSDI->put_NERO_SCSI_DEVICE_INFO ( pDeviceInfo );

		// Declare a smart pointer to IModalDialog interface and call its
		// DoModal method.
		// 
		CComPtr<IModalDialog> pModalDialog;
		int iRet = 0;
		if(SUCCEEDED(pNSDI->QueryInterface(&pModalDialog)))
			pModalDialog->DoModal (m_hWnd,&iRet);

		// Display different information depending on the return value.
		// 
		switch (iRet)
		{
		case IDOK:
			{
				CString str, sDevice;
				NERO_SCSI_DEVICE_INFO * pDeviceInfo;

				// Get the last current selection in the recorder combobox.
				// 
				pNSDI->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);
				sDevice.Format ("%s", (pDeviceInfo != NULL && pDeviceInfo->nsdiDeviceName[0] != '\0')? pDeviceInfo->nsdiDeviceName: "[no device selected]");
				
				str.Format ("Everything was fine.\nThe user's last selection was \"%s\".", sDevice);
				AfxMessageBox (str);
			}
			break;
			
		case IDCANCEL:
			AfxMessageBox ("The dialog was canceled!");
			break;
			
		default:
			{
				CString str;
				str.Format ("There was an error displaying the dialog box!");
				AfxMessageBox (str);
			}
		}
	}
}

void CDlg::OnDestroy() 
{
	CDialog::OnDestroy();	
	
	m_pRecorderCombobox = NULL;
	m_pWriteSpeedCombobox = NULL;
}

void CDlg::OnTestBurnSettings() 
{
	CComPtr<IBurnSettings> pBurnSettings;
	if (SUCCEEDED (pBurnSettings.CoCreateInstance (__uuidof (BurnSettings))))
	{
		pBurnSettings.p->put_BurnFlags (NBF_BUF_UNDERRUN_PROT|NBF_SPEED_IN_KBS|NBF_DAO|NBF_VERIFY);
	}

	CPropertyPageBurnSettings page;

	if (page.m_pMfcPropertyPage != NULL)
	{
		CComQIPtr<INERO_SCSI_DEVICE_INFO> pNSDI (page.m_pMfcPropertyPage);
		ATLASSERT (pNSDI);

		CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
		ATLASSERT (pRecorderNSDI);

		LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
		pRecorderNSDI.p->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);

		pNSDI.p->put_NERO_SCSI_DEVICE_INFO (pDeviceInfo);

		CComQIPtr<IBurnSettingsDlg> pBurnSettingsDlg (page.m_pMfcPropertyPage);
		pBurnSettingsDlg.p->put_MediaType (SelectedMediaType());
		pBurnSettingsDlg.p->put_BurnSettings (pBurnSettings);

		CPropertySheet sheet;
		
		sheet.AddPage (&page);
		if (IDOK == sheet.DoModal ())
		{
			DWORD dwBurnFlags = 0;
			DWORD dwSpeed = 0;
			
			// These values aren't displayed. They only serve for debugging
			// purposes.
			// 
			pBurnSettings.p->get_BurnFlags (&dwBurnFlags);
			pBurnSettings.p->get_Speed (&dwSpeed);
		}
	}
}

void CDlg::OnTestBurnSettingsOle() 
{
	// Create BurnSettings object.
	// 
	CComPtr<IBurnSettings> pBurnSettings;
	if (SUCCEEDED (pBurnSettings.CoCreateInstance (__uuidof (BurnSettings))))
	{
		pBurnSettings.p->put_BurnFlags (NBF_BUF_UNDERRUN_PROT|NBF_SPEED_IN_KBS|NBF_DAO|NBF_VERIFY);
	}

	// Create BurnSettingsParam object and fill it with data.
	// 
	CComPtr<IBurnSettingsDlg> pParam;
	if (SUCCEEDED (pParam.CoCreateInstance (__uuidof (BurnSettingsDlgParam))))
	{
		pParam->put_BurnSettings (pBurnSettings);
		pParam->put_MediaType (SelectedMediaType ());
		
		CComQIPtr<INERO_SCSI_DEVICE_INFO> pNSDIParam (pParam);
		ATLASSERT (pNSDIParam);
		
		CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
		ATLASSERT (pRecorderNSDI);
		
		LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
		pRecorderNSDI->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);
		
		pNSDIParam->put_NERO_SCSI_DEVICE_INFO (pDeviceInfo);
	}

	IUnknown * pUnk = pParam;
	OleCreatePropertyFrame (m_hWnd, 0, 0, L"Title", 1, &pUnk, 1, (LPCLSID) &__uuidof (BurnSettingsDlg), 0, NULL, NULL);
}

void CDlg::OnTestBurnProgress() 
{
	CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
	ATLASSERT (pRecorderNSDI);

	LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
	pRecorderNSDI.p->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);

#if 1 // test the burn progress dialog of NeroCBUI
	CBurnDlg dlg;

	dlg.m_pDeviceInfo = pDeviceInfo;
	dlg.m_bWizardMode = c_WizardMode.GetCheck () != 0;

	dlg.DoModal ();

#else // test the UserDlgHandler of NeroCBUI (don't forget to adapt the path to the image)

	((CApp *)AfxGetApp ())->SetUserDlgParentHWND (m_hWnd);
	((CApp *)AfxGetApp ())->ResetUserDlgAbort();

	NERO_WRITE_IMAGE m_neroImage;
	memset(&m_neroImage,0,sizeof(NERO_WRITE_IMAGE));
	m_neroImage.nwiImageFileName[0] = '\0';
	m_neroImage.nwiLongImageFileName = "c:\\test.nrg";

	NERO_DEVICEHANDLE handle = NeroOpenDevice(pDeviceInfo);
	NERO_PROGRESS * progress = NeroCreateProgress ();

	if(handle)
	{
		int result = NeroBurn(handle,NERO_BURN_IMAGE_MEDIA, &m_neroImage, NBF_WRITE|NBF_DETECT_NON_EMPTY_CDRW|NBF_DAO,0, progress);
		char * p = NeroGetLastError ();
		if (p)
		{
			AfxMessageBox (p);
		}
		NeroFreeMem (p);
	}
	else
	{
		ASSERT(FALSE);
	}

	NeroFreeMem (progress);
#endif
}

void CDlg::OnTestImageInfo() 
{
	CPropertyPageImageInfo page;

	CComQIPtr<IImageInfoDlg> pImageInfoDlg (page.m_pMfcPropertyPage);
	ATLASSERT (pImageInfoDlg.p != NULL);
	if (pImageInfoDlg.p != NULL)
	{
		static char szFilter[] = "Nero Images (*.nrg)|*.nrg|ISO Images (*.iso)|*.iso|All Files (*.*)|*.*||";
		CFileDialog fd (TRUE,"nrg",NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilter, this);
		
		if (IDOK == fd.DoModal ())
		{
			CComBSTR bstrFilename (fd.GetPathName ());
			pImageInfoDlg->put_ImageFilename (bstrFilename);

			CPropertySheet sheet;
			sheet.AddPage (&page);
			if (IDOK == sheet.DoModal ())
			{
			}
		}
	}
}

void CDlg::OnTestChooseRecorder() 
{
	CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
	ATLASSERT (pRecorderNSDI);
	
	LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
	pRecorderNSDI.p->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);
	
	CComPtr<INERO_SCSI_DEVICE_INFO> pNSDI;
	if (SUCCEEDED (pNSDI.CoCreateInstance (__uuidof (ChooseRecorderDlg))))
	{
		// Set the initial selection blindly to zero-th device.
		// 
		pNSDI->put_NERO_SCSI_DEVICE_INFO (pDeviceInfo);
		
		// Declare a smart pointer to IModalDialog interface and call its
		// DoModal method.
		// 
		CComQIPtr<IModalDialog> pModalDialog (pNSDI);
		ATLASSERT (pModalDialog.p != NULL);
		int iRet = 0;
		pModalDialog->DoModal (m_hWnd, &iRet);
		
		// Display different information depending on the return value.
		// 
		switch (iRet)
		{
		case IDOK:
			{
				CString str, sDevice;
				NERO_SCSI_DEVICE_INFO * pDeviceInfo;
				
				// Get the last current selection in the recorder combobox.
				// 
				pNSDI->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);
				sDevice.Format ("%s", (pDeviceInfo != NULL && pDeviceInfo->nsdiDeviceName[0] != '\0')? pDeviceInfo->nsdiDeviceName: "[no device selected]");
				
				str.Format ("The user's selection was \"%s\".", sDevice);
				AfxMessageBox (str);
			}
			break;
			
		case IDCANCEL:
			AfxMessageBox ("The dialog was canceled!");
			break;
			
		default:
			{
				CString str;
				str.Format ("There was an error displaying the dialog box!");
				AfxMessageBox (str);
			}
		}
	}
}

void CDlg::OnTestChooseSession() 
{
	CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
	ATLASSERT (pRecorderNSDI);
	
	LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
	pRecorderNSDI.p->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);
	
	CComPtr<INERO_SCSI_DEVICE_INFO> pNSDI;
	if (SUCCEEDED (pNSDI.CoCreateInstance (__uuidof (ChooseSessionDlg))))
	{
		// Set the initial selection blindly to zero-th device.
		// 
		pNSDI->put_NERO_SCSI_DEVICE_INFO (pDeviceInfo);
		
		// Declare a smart pointer to IModalDialog interface and call its
		// DoModal method.
		// 
		CComQIPtr<IModalDialog> pModalDialog (pNSDI);
		ATLASSERT (pModalDialog.p != NULL);
		int iRet = 0;
		pModalDialog->DoModal (m_hWnd, &iRet);
		
		// Display different information depending on the return value.
		// 
		switch (iRet)
		{
		case IDOK:
			{
				CString str;
				CComQIPtr<IChooseSessionDlg> pChooseSessionDlg (pNSDI);
				ATLASSERT (pChooseSessionDlg.p != NULL);

				DWORD dwTrackNumber;
				pChooseSessionDlg->get_TrackNumber (&dwTrackNumber);

				str.Format ("The user selected track #%d.", dwTrackNumber);
				AfxMessageBox (str);
			}
			break;
			
		case IDCANCEL:
			AfxMessageBox ("The dialog was canceled!");
			break;
			
		default:
			{
				CString str;
				str.Format ("There was an error displaying the dialog box!");
				AfxMessageBox (str);
			}
		}
	}
}

void CDlg::OnSelchangeLangCombo() 
{
	int iSel=m_Combo.GetCurSel();

	if(iSel>=0)
	{
		int iLen = m_Combo.GetLBTextLen(iSel);
		CString csLang;
		m_Combo.GetLBText(iSel,csLang);

		CComPtr<IInitSettings> pInitSettings;

		// we can safely create a new instance of the InitSettings object,
		// since NeroCBUI will only allow one instance of this object and therefore
		// we will receive the already existing object
		if (SUCCEEDED (pInitSettings.CoCreateInstance (__uuidof (InitSettings))))
		{
			if(pInitSettings->put_LanguageCode((const signed char*)(const char*)csLang)!=S_OK)
			{
				AfxMessageBox("Setting the language failed!");
				m_Combo.SetCurSel(-1);
			}
		}
		else
		{
			AfxMessageBox("Failed to get an instance of the IInitSettings interface!");
		}
	}
}

void CDlg::OnTestEraseDiscModeless() 
{
	// Get the selected recorder from the combo and set it to the
	// object.
	// 
	CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
	ATLASSERT (pRecorderNSDI);
	
	LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
	pRecorderNSDI->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);
	
	// Create EraseDiscDlg object.
	// 
	CComPtr<IModelessDialog> pModelessEraseDiscDialog;
	if (SUCCEEDED (pModelessEraseDiscDialog.CoCreateInstance (__uuidof (EraseDiscDlg))))
	{
		CComQIPtr<IEraseDiscDlg3> pEraseDiscDlg (pModelessEraseDiscDialog);
		ATLASSERT (pEraseDiscDlg.p != NULL);
		
		// Let the dialog know the device. Don't use direct handle, it is
		// more convenient this way.
		// 
		CComQIPtr<INERO_SCSI_DEVICE_INFO> pNSDI (pModelessEraseDiscDialog);
		ATLASSERT (pNSDI.p != NULL);
		
		pNSDI->put_NERO_SCSI_DEVICE_INFO (pDeviceInfo);
		
		// This is a trick as well as a whole IEraseDiscCallbacks interface
		// implementation, but it will do.
		// 
		pEraseDiscDlg->put_Callbacks (this);
		
		// Create the dialog.
		// 
		HWND hWndDlg;
		pModelessEraseDiscDialog->Create (m_hWnd, NULL, &hWndDlg);
	}
}

STDMETHODIMP CDlg::OnEraseDone (IEraseDiscDlg * pEraseDiscDlg)
{
	// Erase process has been completed.
	// 
	CString str;
	CComBSTR bstr;
	USES_CONVERSION;
	int iResult = 0;
	
	// Get the results...
	// 
	pEraseDiscDlg->get_ErasingResultString (&bstr);
	pEraseDiscDlg->get_ErasingResult (&iResult);
	
	// Format and display the results...
	// 
	str.Format ("Reported result was: %d.\nReported message was: \"%s\".", iResult, W2CA (bstr));
	AfxMessageBox (str);
	
	return S_OK;
}


STDMETHODIMP CDlg::OnFilterRecorder(LPCNERO_SCSI_DEVICE_INFO pDeviceInfo, BOOL * pbAccept)
{
	ASSERT (pDeviceInfo != NULL);
	ASSERT (pbAccept != NULL);
	
	// Filter out the devices that are not capable of burning.
	// 
	if (pDeviceInfo->nsdiDevType == NEA_SCSI_DEVTYPE_CDROM || 
		pDeviceInfo->nsdiDevType == NEA_SCSI_DEVTYPE_UNKNOWN || 
		pDeviceInfo->nsdiDevType == NEA_SCSI_DEVTYPE_UNSUPPORTED_WORM ||
		(pDeviceInfo->nsdiCapabilities & NSDI_ALLOWED) == 0)
	{
		// We don't want CDROMs, unknown and unsupported drives
		*pbAccept = FALSE;
	}
	else
	{
		*pbAccept = TRUE;
	}
	
	return S_OK;
}

STDMETHODIMP CDlg::OnFilterEnd()
{
	return S_OK;
}

STDMETHODIMP CDlg::OnContentRefreshed()
{
	// here we check, if the selected recorder changed and set the selected recorder
	// in the write speed combo box
	CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
	ATLASSERT (pRecorderNSDI);
	
	LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
	pRecorderNSDI->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);

	CComQIPtr<INERO_SCSI_DEVICE_INFO> pSpeedNSDI (m_pWriteSpeedCombobox);
	ATLASSERT (pSpeedNSDI);

	pSpeedNSDI->put_NERO_SCSI_DEVICE_INFO (pDeviceInfo);

	return S_OK;
}
	
STDMETHODIMP CDlg::OnCurSelInUseStatusChange(BOOL bInUse)
{
	// normally one would deactivate the burn button if bInUse
	// is TRUE and activate it otherwise
	return S_OK;
}

void CDlg::OnTestWaitForMedia() 
{
	// Get the selected recorder from the combo.
	// 
	CComQIPtr<INERO_SCSI_DEVICE_INFO> pRecorderNSDI (m_pRecorderCombobox);
	ATLASSERT (pRecorderNSDI);
	
	LPNERO_SCSI_DEVICE_INFO pDeviceInfo = NULL;
	pRecorderNSDI->get_NERO_SCSI_DEVICE_INFO (&pDeviceInfo);

	if (pDeviceInfo != NULL)
	{
		NERO_DEVICEHANDLE deviceHandle = NeroOpenDevice (pDeviceInfo);

		if (deviceHandle != NULL)
		{
			CComPtr<IWaitForMediaDlg> pWaitForMedia;
			if (SUCCEEDED (pWaitForMedia.CoCreateInstance (__uuidof (WaitForMediaDlg))))
			{
				BOOL bAbort = FALSE;

				pWaitForMedia->WaitForMedia (m_hWnd, deviceHandle, SelectedMediaType(), NBF_WRITE, NULL, &bAbort);

				CString str;
				str.Format ("The outcome of the operation was %sto abort!", bAbort? "": "NOT ");
				AfxMessageBox (str);
			}

			NeroCloseDevice (deviceHandle);
		}
	}
}

void CDlg::OnSelchangeMediaCombo() 
{
	m_pWriteSpeedCombobox.p->put_MediaType(SelectedMediaType());
}

NERO_MEDIA_TYPE CDlg::SelectedMediaType()
{
	NERO_MEDIA_TYPE mediatype=MEDIA_CD; // default value

	int iSel=m_MediaCombo.GetCurSel();

	if(iSel>=0)
	{
		CString csMedia;
		m_MediaCombo.GetLBText(iSel,csMedia);
		
		if(csMedia=="CD")
		{
			mediatype=MEDIA_CD;
		}
		else if(csMedia=="DVD")
		{
			mediatype=MEDIA_DVD_ANY;
		}
		else if(csMedia=="HDB")
		{
			mediatype=MEDIA_HDB;
		}
		else
		{
			ASSERT(false);
		}
	}
	
	return mediatype;
}

void CDlg::OnSelchangeRecorder() 
{
	OnContentRefreshed ();
}

void CDlg::OnTestImageInfoOle() 
{
	static char szFilter[] = "Nero Images (*.nrg)|*.nrg|ISO Images (*.iso)|*.iso|All Files (*.*)|*.*||";
	CFileDialog fd (TRUE,"nrg",NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilter, this);
	
	if (IDOK == fd.DoModal ())
	{
		CComPtr<IImageInfoDlg> pParam;

		if (SUCCEEDED (pParam.CoCreateInstance (__uuidof (ImageInfoDlgParam))))
		{
			CComBSTR bstrFilename (fd.GetPathName ());
			pParam->put_ImageFilename (bstrFilename);

			IUnknown * pUnk = pParam;
			OleCreatePropertyFrame (m_hWnd, 0, 0, L"Title", 1, &pUnk, 1, (LPCLSID) &__uuidof (ImageInfoDlg), 0, NULL, NULL);
		}
	}
}
