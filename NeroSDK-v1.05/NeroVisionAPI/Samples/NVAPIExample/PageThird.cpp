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
|* PROGRAM: PageThird.cpp
|*
|* PURPOSE: Implementation of the third page.
******************************************************************************/

#include "stdafx.h"
#include "NVAPIExample.h"
#include "PageThird.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define UM_START_PROCESS		(WM_APP + 1)

#define TIMER_INTERVAL			500 /* ms */
#define TIMER_ID				100

CPageThird::CPageThird(CSheet * pParent)
	: CPage(CPageThird::IDD, pParent)
	, m_bActiveState (false)
	, m_bAbort (false)
{
	//{{AFX_DATA_INIT(CPageThird)
	//}}AFX_DATA_INIT
}


void CPageThird::DoDataExchange(CDataExchange* pDX)
{
	CPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageThird)
	DDX_Control(pDX, IDC_TOTAL_TIME, c_TotalTime);
	DDX_Control(pDX, IDC_PROGRESS_PERCENT, c_Percent);
	DDX_Control(pDX, IDC_PROGRESS, c_Progress);
	DDX_Control(pDX, IDC_MESSAGES, c_Messages);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageThird, CPage)
	//{{AFX_MSG_MAP(CPageThird)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_START_PROCESS, OnStartProcess)
	ON_MESSAGE(UM_NERO_USER_DIALOG, OnNeroUserDialog)
	ON_MESSAGE(UM_NERO_IDLE_CALLBACK, OnNeroIdleCallback)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageThird message handlers

bool CPageThird::Create (void)
{
	return CDialog::Create (m_lpszTemplateName, m_pParentWnd) != FALSE;
}


bool CPageThird::OnNext (void)
{
	// If we are in an active state, the button is used for abortion. So,
	// abort and eat the button click.
	// 
	if (m_bActiveState)
	{
		m_bAbort = true;
		return true;
	}
	else
	{
		return false;
	}
}

void CPageThird::OnChangeState (bool bActivate, bool bForward)
{
	// If the page is activated in the forward direction...
	// 
	if (bActivate && bForward)
	{
		// Change into active state and remember the initial tick count
		// so we can time this transcoding and burning.
		// 
		m_bActiveState = true;
		m_dwStartTickCount = GetTickCount ();

		// Start the timer that will update the elapsed time.
		// 
		SetTimer (TIMER_ID, TIMER_INTERVAL, NULL);
		
		// Change Next button to Abort and disable the other one.
		// 
		CString sAbort;
		sAbort.LoadString (IDS_BUTTON_ABORT);
		GetParent ()->GetDlgItem (IDOK)->SetWindowText (sAbort);
		GetParent ()->GetDlgItem (IDCANCEL)->EnableWindow (false);

		// Reset the position of the progress bar and remove all items from
		// the message list ctrl.
		// 
		c_Progress.SetPos (0);
		c_Percent.SetWindowText ("");
		c_TotalTime.SetWindowText ("");
		c_Messages.DeleteAllItems ();

		// Reset all relevant variables.
		// 
		m_LastAction = (ProgressAction) -1;
		m_sLastItemname.Empty ();
		m_bAbort = false;

		InsertMessage (IDS_STARTING_TRANSCODING);

		// Post a message to ourseleves so that everything is painted
		// before we begin.
		// 
		PostMessage (UM_START_PROCESS);
	}
}

LRESULT CPageThird::OnStartProcess (WPARAM wParam, LPARAM lParam)
{
	// Now start transcoding. The method won't return until it finishes
	// but we have a progress callback to monitor the process.
	// 
	try
	{
		INeroBurnContextPtr pBurnContext;
		CPageData * pPageData = GetPageData ();

		VARIANT_BOOL bSuccess = pPageData->m_pProject->CreateNeroBurnContext (NeroAPIGlueGetModuleHandle (),
																			this,
																			&pBurnContext);
		if (!bSuccess)
		{
			// Transcoding was unsuccessful...
			// 
			if (m_bAbort)
			{
				// If unsuccessful and aborted, simply display the aborted
				// message.
				// 
				CString sAborted;
				sAborted.LoadString (IDS_ERROR_ABORTED);
				InsertMessage (sAborted);

				AfxMessageBox (IDS_ERROR_ABORTED);
			}
			else
			{
				// If there was an error, insert another message line into the
				// message listctrl and display an error message box!
				// 
				IErrorPtr pError = pPageData->m_pProject->LastError;
				
				USES_CONVERSION;
				CString sError;
				CString sFormat;
				sFormat.LoadString (IDS_TRANSCODING_ERROR_FORMAT);
				sError.Format (sFormat, pError->ErrCode, W2CA (pError->XMLID), W2CA (pError->ErrText));
				InsertMessage (sError);

				AfxMessageBox (IDS_ERROR_TRANSCODING);
			}
		}
		else
		{
			// Ok, now do the burning...
			// 
			InsertMessage (IDS_STARTING_BURNING);

			bool bBurnError = true;

			// Open the device...
			// 
			NERO_DEVICEHANDLE hDevice = NeroOpenDevice (pPageData->m_pDeviceInfo);
			if (hDevice != NULL)
			{
				NERO_PROGRESS * pNeroProgress;

				// Create NERO_PROGRESS structure using API.
				// 
				pNeroProgress = NeroCreateProgress ();
				if (pNeroProgress != NULL)
				{
					// Fill-in the NERO_PROGRESS structure wiht our own
					// callbacks.
					// 
					pNeroProgress->npAbortedCallback = NeroAbortedCallback;
					pNeroProgress->npAddLogLineCallback = NeroAddLogLineCallback;
					pNeroProgress->npProgressCallback = NeroProgressCallback;
					pNeroProgress->npUserData = this;

					// Now, finally start burning using the NERO_CD_FORMAT
					// and NERO_WRITE_CD as returned from NeroVisionAPI.
					// The burn speed and recorder were previously selected
					// by the user.
					// 
					NEROAPI_BURN_ERROR err;
					err = NeroBurn (hDevice,
									(NERO_CD_FORMAT) pBurnContext->NERO_CD_FORMAT,
									pBurnContext->NERO_WRITE_CD,
									NBF_WRITE|NBF_DAO,
									pPageData->m_dwBurnSpeed,
									pNeroProgress);

					bBurnError = err != NEROAPI_BURN_OK;

					NeroFreeMem (pNeroProgress);
				}

				NeroCloseDevice (hDevice);
			}

			// Display an appropriate message depending on the status of
			// the burn operation.
			// 
			AfxMessageBox (bBurnError? IDS_BURN_FAILED: IDS_BURN_OK);
		}
	}
	catch (...)
	{
		AfxMessageBox (IDS_UNEXPECTED_NVAPI_ERROR);
	}

	// When everything is finally done, restore the buttons to original
	// state.
	// 
	RestoreButtons ();
	
	return 0;
}

// This is a helper message to insert a message into the log using a
// message string ID.
// 
void CPageThird::InsertMessage (UINT uMessageID)
{
	CString sMessage;
	sMessage.LoadString (uMessageID);
	InsertMessage (sMessage);
}

// This is a helper message to insert a message into the log using a
// direct string pointer.
// 
void CPageThird::InsertMessage (LPCSTR psMessage)
{
	int iIndex = c_Messages.InsertItem (c_Messages.GetItemCount (), psMessage, 0);
	c_Messages.EnsureVisible (iIndex, false);
	c_Messages.UpdateWindow ();
}

BOOL CPageThird::OnInitDialog() 
{
	CPage::OnInitDialog();
	
	// Insert a single column into the listctrl and make sure that the
	// width is set to maximum minus the size of the vertical scrollbar.
	// 
	CRect rcMessages;
	c_Messages.GetClientRect (&rcMessages);
	
	CString sColumnCaption;
	sColumnCaption.LoadString (IDS_MESSAGES_COLUMN);
	
	c_Messages.InsertColumn (0,
		sColumnCaption,
		LVCFMT_LEFT,
		rcMessages.Width () - ::GetSystemMetrics (SM_CXVSCROLL));
	
	c_Messages.SetExtendedStyle (LVS_EX_FULLROWSELECT);

	c_Progress.SetRange (0, 100);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

STDMETHODIMP CPageThird::raw_OnProgress (
							enum ProgressAction action,
							BSTR itemname,
							double currentRemain,
							double currentTotal,
							float currentFraction,
							double totalRemain,
							double totalTotal,
							float totalFraction)
{
	USES_CONVERSION;
	CString sNewItemname = W2CA (itemname);

	// If either the action or the item name changed, let's insert another
	// message line.
	// 
	if (action != m_LastAction ||
		sNewItemname != m_sLastItemname)
	{
		m_LastAction = action;
		m_sLastItemname = sNewItemname;

		// These phases are supported by NeroVisionAPI. Their stings are
		// in the string table.
		// 
		static UINT uActionIDs[] = {
			IDS_ACTION_ESTIMATING,
			IDS_ACTION_PREPARING,
			IDS_ACTION_TRANSCODING,
			IDS_ACTION_GENERATING,
			IDS_ACTION_ANALYZING,
		};

		// Make sure the action is within known bounds.
		// 
		if (action < Estimating || action > Analyzing)
		{
			action = Estimating;
		}
		
		// Format and insert the message line.
		// 
		CString sAction;
		CString sMessage;
		sAction.LoadString (uActionIDs[action]);
		sMessage.Format ("%s %s", sAction, sNewItemname);
		
		InsertMessage (sMessage);
	}

	// Update the progress bar and pump the messages so that everything
	// remains responsive.
	// 
	SetPercent ((int) (totalFraction*100));

	((CNVAPIExampleApp *)AfxGetApp ())->PumpMessages ();
	
	return S_OK;
}

// This is a helper method to set both the progress bar and a textual
// progress percent.
// 
void CPageThird::SetPercent (int iPercent)
{
	CString sPercent;
	sPercent.Format ("%d%%", iPercent);
	c_Percent.SetWindowText (sPercent);
	c_Progress.SetPos (iPercent);
}

STDMETHODIMP CPageThird::raw_ShouldCancel (
										   VARIANT_BOOL * pbCancel)
{
	// Cancel the transcoding operation as needed and pump the messages.
	// 
	*pbCancel = m_bAbort? VARIANT_TRUE: VARIANT_FALSE;
	
	((CNVAPIExampleApp *)AfxGetApp ())->PumpMessages ();
	
	return S_OK;
}

void CPageThird::RestoreButtons (void)
{
	// If we are in an active state it means that we are either
	// transcoding or burning. Either way, we should abort the process.
	// 
	m_bActiveState = false;
	
	KillTimer (TIMER_ID);

	CString sBack;
	sBack.LoadString (IDS_BUTTON_BACK);
	GetParent ()->GetDlgItem (IDCANCEL)->EnableWindow (true);
	GetParent ()->GetDlgItem (IDCANCEL)->SetWindowText (sBack);
	
	CString sFinish;
	sFinish.LoadString (IDS_BUTTON_FINISH);
	GetParent ()->GetDlgItem (IDOK)->SetWindowText (sFinish);
}

// The aborted callback only returns our aborted flag.
// 
BOOL NERO_CALLBACK_ATTR CPageThird::NeroAbortedCallback (void *pUserData)
{
	CPageThird * pThis = (CPageThird *) pUserData;

	return pThis->m_bAbort;
}

// Add log line callback inserts a new message into the log.
// 
void NERO_CALLBACK_ATTR CPageThird::NeroAddLogLineCallback (void *pUserData, NERO_TEXT_TYPE type, const char *text)
{
	CPageThird * pThis = (CPageThird *) pUserData;

	pThis->InsertMessage (text);
}

// Progress callback advances the progress bar.
// 
BOOL NERO_CALLBACK_ATTR CPageThird::NeroProgressCallback (void *pUserData, DWORD dwProgressInPercent)
{
	CPageThird * pThis = (CPageThird *) pUserData;

	pThis->SetPercent (dwProgressInPercent);

	return pThis->m_bAbort;
}

// This handler is for our user message UM_NERO_USER_DIALOG which is sent
// to us by our parent and in turn by the application which owns the real
// user dialog and idle handlers.
// 
LRESULT CPageThird::OnNeroUserDialog (WPARAM wParam, LPARAM lParam)
{
	return (LRESULT) NeroUserDialog ((NeroUserDlgInOut) wParam, (void *) lParam);
}

NeroUserDlgInOut CPageThird::NeroUserDialog (NeroUserDlgInOut type, void *data)
{
	// We handle here only a few of the user dialog messages.
	// 
	switch (type)
	{
		case DLG_WAITCD:
			{
				// When the cd is requested, display the localized version
				// of the message in the list ctrl log.
				// 
				LPSTR psText = NeroGetLocalizedWaitCDTexts ((NERO_WAITCD_TYPE) (int)data);
				if (psText != NULL)
				{
					InsertMessage (psText);
					NeroFreeMem (psText);
				}
			}

			return DLG_RETURN_EXIT;
			
		case DLG_WAITCD_REMINDER:
			// Just insert the reminder message in the log.
			// 
			InsertMessage (IDS_WAITCD_REMAINDER);
			
			return DLG_RETURN_EXIT;

		case DLG_WAITCD_DONE:
			// When waiting on a cd is done, insert a message.
			// 
			InsertMessage (IDS_WAITCD_DONE);

			return DLG_RETURN_EXIT;
			
		case DLG_FILESEL_IMAGE:
			{
				CString sFilter;
				sFilter.LoadString (IDS_NERO_IMAGE_FILES_FILTER);
				CFileDialog fd (FALSE,
					"txt",
					NULL,
					OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
					sFilter,
					this);
				
				if (IDOK == fd.DoModal ())
				{
					if (fd.GetPathName ().GetLength () < MAX_PATH)
					{
						strcpy ((char *) data, fd.GetPathName ());
						return DLG_RETURN_CONTINUE;
					}
				}
			}
			return DLG_RETURN_EXIT;
			
		case DLG_WAITCD_MEDIA_INFO:
			{
				// Insert the info about the media present and requested.
				// 
				const NERO_DLG_WAITCD_MEDIA_INFO * pMediaInfo = (const NERO_DLG_WAITCD_MEDIA_INFO *) data;
				ATLASSERT (pMediaInfo != NULL);

				CString sFormat;
				CString sMessage;
				sFormat.LoadString (IDS_FORMAT_WAITCD_MEDIA_INFO);
				sMessage.Format (sFormat, pMediaInfo->ndwmiLastDetectedMediaName,
											pMediaInfo->ndwmiRequestedMediaName);
				InsertMessage (sMessage);
				
				// The return value is ignored.
				// 
				return DLG_RETURN_EXIT;
			}
			
		default:
			return DLG_RETURN_NOT_HANDLED;
	}
}

// We know about NeroAPI's idle callback by handling a user message
// UM_NERO_IDLE_CALLBACK. All we are required to do is return our aborted
// flag.
// 
LRESULT CPageThird::OnNeroIdleCallback (WPARAM wParam, LPARAM lParam)
{
	return (LRESULT) m_bAbort;
}

void CPageThird::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == TIMER_ID)
	{
		// When our timer fires, let's update the elapsed time.
		// 
		DWORD dwDelta = (GetTickCount () - m_dwStartTickCount + 500)/1000;
		DWORD dwHours = dwDelta/3600;
		DWORD dwMinutes = (dwDelta%3600)/60;
		DWORD dwSeconds = dwDelta%60;
		
		CString sTime;
		sTime.Format ("%02d:%02d:%02d", dwHours, dwMinutes, dwSeconds);
		
		c_TotalTime.SetWindowText (sTime);
	}

	CPage::OnTimer(nIDEvent);
}
