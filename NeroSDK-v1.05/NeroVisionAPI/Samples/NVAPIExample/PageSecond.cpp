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
|* PROGRAM: PageSecond.cpp
|*
|* PURPOSE: Implementation of the second page.
******************************************************************************/

#include "stdafx.h"
#include "NVAPIExample.h"
#include "PageSecond.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSecond dialog


CPageSecond::CPageSecond(CSheet * pParent)
	: CPage(CPageSecond::IDD, pParent)
	, m_bFirstActivate (true)
{
	//{{AFX_DATA_INIT(CPageSecond)
	//}}AFX_DATA_INIT
}


void CPageSecond::DoDataExchange(CDataExchange* pDX)
{
	CPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSecond)
	DDX_Control(pDX, IDC_CHILD_DIALOG_PLACEHOLDER, c_ChildDialogPlaceholder);
	DDX_Control(pDX, IDC_SPEED, c_Speed);
	DDX_Control(pDX, IDC_RECORDER, c_Recorder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSecond, CPage)
	//{{AFX_MSG_MAP(CPageSecond)
	ON_CBN_SELCHANGE(IDC_RECORDER, OnSelchangeRecorder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

bool CPageSecond::Create (void)
{
	return CDialog::Create (m_lpszTemplateName, m_pParentWnd) != FALSE;
}

bool CPageSecond::OnNext (void)
{
	// If "Next" button is clicked set the currently selected recorder and
	// speed to the common inter-page communication CPageData instance.
	// 
	CPageData * pPageData = GetPageData ();

	pPageData->m_pDeviceInfo = c_Recorder.GetCurrentRecorder ();
	pPageData->m_dwBurnSpeed = c_Speed.GetSelectedSpeed ();

	return false;
}

void CPageSecond::OnChangeState (bool bActivate, bool bForward)
{
	if (bActivate)
	{
		if (m_bFirstActivate)
		{
			m_bFirstActivate = false;

			// If the page is activated for the first time, fill in the
			// recorder combobox and update the speeds combobox accordingly.
			// 
			c_Recorder.Initialize ();
			UpdateSpeeds ();
		}
		
		if (bForward)
		{
			// If the page is activated in the forward direction, we should
			// prepare for transcoding time and disk size estimation.
			// 
			CWaitCursor wait;

			// Reset the estimation dialog's controls. Show the estimation
			// dialog and hide the estimation-done dialog.
			// 
			m_dlgEstimating.c_Progress.SetPos (0);
			m_dlgEstimating.ShowWindow (SW_SHOW);
			m_dlgEstimateDone.ShowWindow (SW_HIDE);
			m_dlgEstimateDone.m_sEstimatedSize.Empty ();
			m_dlgEstimateDone.m_sEstimatedTime.Empty ();
			UpdateWindow ();
			
			CPageData * pPageData = GetPageData ();

			// Load and set the error string in case the estimation fails.
			// 
			m_dlgEstimateDone.m_sEstimatedSize.LoadString (IDS_ERROR_GETTING_DISK_SIZE);
			m_dlgEstimateDone.m_sEstimatedTime.LoadString (IDS_ERROR_GETTING_TIME);

			// Now set the XML string to the NeroVisionAPI's Project
			// object.
			// 
			BOOL bSuccess = pPageData->m_pProject->SetXMLString ((LPSTR)(LPCSTR) GetPageData ()->m_sXML);
			if (!bSuccess)
			{
				// On error, get the error text and display it.
				// 
				IErrorPtr pError = pPageData->m_pProject->LastError;
				
				USES_CONVERSION;
				AfxMessageBox (W2CA (pError->ErrText));
			}
			else
			{
				// If XML setting succeeded, ask for disk size and
				// trancoding duration estimates.
				// 
				__int64 iSize = 0;
				bSuccess = pPageData->m_pProject->EstimateDiskSize (&iSize);
				if (bSuccess)
				{
					// On success, format the disk size and put it on the
					// dialog.
					// 
					CString sFormat;
					sFormat.LoadString (IDS_DISK_SIZE_FORMAT);
					m_dlgEstimateDone.m_sEstimatedSize.Format (sFormat, (int)(iSize/(1024*1024)));
				}

				// Now get the transcoding duration estimation. This might
				// take a while. We are passing an IProgressCallback interface
				// pointer which we are implementing. This will give us
				// an opportunity to move the progress bar and indicate
				// how long the process will take.
				// 
				double dSeconds = 0;
				bSuccess = pPageData->m_pProject->EstimateCreateNeroBurnContextTime (this, &dSeconds);
				if (bSuccess)
				{
					// On success, format the time and set it on the
					// dialog.
					// 
					CString sFormat;
					sFormat.LoadString (IDS_TIME_FORMAT);
					int iSeconds = (int) dSeconds;
					m_dlgEstimateDone.m_sEstimatedTime.Format (sFormat, iSeconds/60, iSeconds%60);
				}
			}

			// Transfer the data onto the dialog and switch the two dialogs.
			// 
			m_dlgEstimateDone.UpdateData (FALSE);
			m_dlgEstimateDone.ShowWindow (SW_SHOW);
			m_dlgEstimating.ShowWindow (SW_HIDE);
		}
	}
}


BOOL CPageSecond::OnInitDialog() 
{
	CPage::OnInitDialog();

	// Create the two child dialogs.
	// 
	VERIFY (m_dlgEstimateDone.Create (CEstimateDoneDlg::IDD, this));
	VERIFY (m_dlgEstimating.Create (CEstimatingDlg::IDD, this));

	// Place them in place of the placeholder.
	// 
	CRect rcPlaceholder;
	c_ChildDialogPlaceholder.GetWindowRect (&rcPlaceholder);
	ScreenToClient (&rcPlaceholder);
	m_dlgEstimateDone.MoveWindow (&rcPlaceholder);
	m_dlgEstimating.MoveWindow (&rcPlaceholder);

	// Set the range of the progess bar.
	// 
	m_dlgEstimating.c_Progress.SetRange (0, 100);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSecond::UpdateSpeeds (void)
{
	// Refresh the speeds combobox according to the recorder selected in
	// the recorder combobox.
	// 
	c_Speed.RefreshSpeeds (c_Recorder.GetCurrentRecorder ());
}

void CPageSecond::OnSelchangeRecorder() 
{
	// When recorder selection changes, update the speeds.
	// 
	UpdateSpeeds ();
}

STDMETHODIMP CPageSecond::raw_OnProgress (
							enum ProgressAction action,
							BSTR itemname,
							double currentRemain,
							double currentTotal,
							float currentFraction,
							double totalRemain,
							double totalTotal,
							float totalFraction)
{
	// Update the progress bar and pump the messages so that everything
	// remains responsive during transcoding duration estimation.
	// 
	int iPercent = (int) (currentFraction*100);
	m_dlgEstimating.c_Progress.SetPos (iPercent);
	m_dlgEstimating.c_Progress.UpdateWindow ();

	return S_OK;
}

STDMETHODIMP CPageSecond::raw_ShouldCancel (
										   VARIANT_BOOL * pbCancel)
{
	// The duration estimation cannot be canceled. It usually takes only
	// a few seconds. Everybody can wait this long ;-)
	// 
	*pbCancel = VARIANT_FALSE;
	
	return S_OK;
}
