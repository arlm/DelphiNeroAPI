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
|* PROGRAM: SpeedComboBox.cpp
|*
|* PURPOSE: A combobox that holds all available speeds for a particular
|*          recorder.
******************************************************************************/

#include "stdafx.h"
#include "NVAPIExample.h"
#include "SpeedComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CSpeedComboBox, CComboBox)
	//{{AFX_MSG_MAP(CSpeedComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// This method is used to refresh the speeds of this combobox using the
// recorder passed as parameter.
// 
void CSpeedComboBox::RefreshSpeeds (const NERO_SCSI_DEVICE_INFO * pnsdi)
{
	// First clear the combobox.
	// 
	ResetContent ();

	if (pnsdi != NULL)
	{
		// Open the device...
		// 
		NERO_DEVICEHANDLE hDevice = NeroOpenDevice (pnsdi);

		if (hDevice != NULL)
		{
			// Get the speeds...
			// 
			NERO_SPEED_INFOS * pSpeeds = NeroGetAvailableSpeeds (hDevice,
																ACCESSTYPE_WRITE,
																MEDIA_CD,
																NULL);
			if (pSpeeds != NULL)
			{
				CString sSpeed;

				// Loop through all available speeds and add them to
				// the combobox.
				// 
				for (DWORD i = 0; i < pSpeeds->nsiNumSupportedSpeeds; i ++)
				{
					sSpeed.Format ("%d", pSpeeds->nsiSupportedSpeeds[i]);
					int iIndex = AddString (sSpeed);
					if (iIndex != CB_ERR)
					{
						// Set the item data to be the speed itself in X.
						// 
						SetItemData (iIndex, pSpeeds->nsiSupportedSpeeds[i]);
					}
				}

				NeroFreeMem (pSpeeds);
			}

			NeroCloseDevice (hDevice);
		}
	}

	// Always add the "Maximum" speed with a value of 0.
	// 

	int iIndex = AddString ("Maximum");
	if (iIndex != CB_ERR)
	{
		SetItemData (iIndex, 0);
	}

	SetCurSel (iIndex);
}

// Get the currently selected speed.
// 
DWORD CSpeedComboBox::GetSelectedSpeed (void) const
{
	int iCurSel = GetCurSel ();
	
	return (iCurSel == -1)? 0: GetItemData (iCurSel);
}
