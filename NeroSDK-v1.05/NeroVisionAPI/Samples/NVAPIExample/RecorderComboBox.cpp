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
|* PROGRAM: RecorderComboBox.cpp
|*
|* PURPOSE: A combobox that holds all available recorders.
******************************************************************************/

#include "stdafx.h"
#include "RecorderCombobox.h"

CRecorderCombobox::CRecorderCombobox ()
{
	m_pDeviceInfos = NULL;
}

CRecorderCombobox::~CRecorderCombobox ()
{
	ASSERT (m_pDeviceInfos == NULL);
}

void CRecorderCombobox::FillCombo (void)
{
	// Clear the contents of the combobox.
	// 
	ResetContent ();

	ASSERT (m_pDeviceInfos == NULL);

	CWaitCursor wait;
	m_pDeviceInfos = NeroGetAvailableDrivesEx (MEDIA_CD, NULL);
	wait.Restore ();

	if (m_pDeviceInfos != NULL)
	{
		// Loop through the devices...
		// 
		for (DWORD i = 0; i < m_pDeviceInfos->nsdisNumDevInfos; i ++)
		{
			const NERO_SCSI_DEVICE_INFO & nsdiRecorder = m_pDeviceInfos->nsdisDevInfos[i];

			if (NEA_SCSI_DEVTYPE_WORM != nsdiRecorder.nsdiDevType)
			{
				continue;
			}

			CString sName;
			if (0 != (nsdiRecorder.nsdiCapabilities & NSDI_IMAGE_RECORDER))
			{
				sName.Format("%s",nsdiRecorder.nsdiDeviceName);
			}
			else
			{
				sName.Format ("%c: %s (ID:%d HA:%d)",
					(nsdiRecorder.nsdiDriveLetter != '\0')? toupper (nsdiRecorder.nsdiDriveLetter): '?',
					nsdiRecorder.nsdiDeviceName,
					nsdiRecorder.nsdiDeviceID,
					nsdiRecorder.nsdiHostAdapterNo);
			}
			
			int iIndex = InsertString (0, sName);
			if (iIndex < 0)
			{
				// Unlikely, but an error can occur. In this case, bail out of
				// the loop.
				// 
				break;
			}

			// Make a link with with the particular NERO_SCSI_DEVICE_INFO.
			// 
			SetItemDataPtr (iIndex, (void *) &nsdiRecorder);
		}

		SetCurSel (0);
	}
}

BEGIN_MESSAGE_MAP(CRecorderCombobox, CComboBox)
	//{{AFX_MSG_MAP(CRecorderCombobox)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CRecorderCombobox::OnDestroy() 
{
	// When the control is destroyed, free the device infos.
	// 
	if (m_pDeviceInfos != NULL)
	{
		NeroFreeMem (m_pDeviceInfos);
		m_pDeviceInfos = NULL;
	}
	
	CComboBox::OnDestroy();
}

// This method is used to get the currently selected recorder. The actual
// NERO_SCSI_DEVICE_INFO pointer is stored in item's data pointer.
// 
const NERO_SCSI_DEVICE_INFO * CRecorderCombobox::GetCurrentRecorder (void) const
{
	int iItem = GetCurSel ();
	
	if (iItem != -1)
	{
		return (const NERO_SCSI_DEVICE_INFO *) GetItemDataPtr (iItem);
	}
	else
	{
		return NULL;
	}
}

// Initialize needs to be called in order to fill the combobox initially.
// 
void CRecorderCombobox::Initialize (void)
{
	FillCombo ();
}
