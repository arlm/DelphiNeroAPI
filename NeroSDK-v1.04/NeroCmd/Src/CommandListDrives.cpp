/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroCmd
|*
|* PROGRAM: CommandListDrives.cpp
|*
|* PURPOSE: List available drives and their characteristics
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function performs listing of all available drives with their
// main characteristics. m_NeroDeviceInfos has been filled by a call
// GetAvailableDrives during NeroAPI initialization in main().

CExitCode CBurnContext::CommandListDrives (const PARAMETERS & params)
{
	printf (
			"Drv: Adapter                      Underrun Protection Technology  # type     ID\n"
			"-------------------------------------------------------------------------------\n");

	for (int i = 0; i < (int)(m_NeroDeviceInfos->nsdisNumDevInfos); i ++)
	{
		// Use a helper variable for better code readability

		NERO_SCSI_DEVICE_INFO tempNSDI = m_NeroDeviceInfos->nsdisDevInfos[i];

		// Check whether the drive has a Windows drive letter,
		// use '?' if it is not available.

		char cDriveLetter;
		if (0 != tempNSDI.nsdiDriveLetter)
		{
			cDriveLetter = tempNSDI.nsdiDriveLetter;
		}
		else
		{
			cDriveLetter = '?';
		}
		
		LPCSTR psUnderrunProtName;

		// Check for buffer underrun protection.
		// 
		if (tempNSDI.nsdiCapabilities & NSDI_BUF_UNDERRUN_PROT)
		{
			// If it exists, use the name provided by NeroAPI or a generic
			// string otherwise.
			// 
			psUnderrunProtName = (tempNSDI.nsdiBufUnderrunProtName[0] != '\0')? tempNSDI.nsdiBufUnderrunProtName: "<supported>";
		}
		else
		{
			// There is on underrun protection.
			// 
			psUnderrunProtName = "<none>";
		}
		
		// Print one line for every device

		printf ("%c %-31s %-31s %2d %-7s %2d\n",
			cDriveLetter,
			tempNSDI.nsdiDeviceName,
			psUnderrunProtName,
			tempNSDI.nsdiHostAdapterNo,
			tempNSDI.nsdiHostAdapterName,
			tempNSDI.nsdiDeviceID);
	}
	printf ("\n");

	return EXITCODE_OK;
}

