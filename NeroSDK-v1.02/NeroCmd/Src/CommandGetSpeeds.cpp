/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroCmd
|*
|* PROGRAM: CommandGetSpeeds.cpp
|*
|* PURPOSE: List the available speeds for a drive
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function prints the available read and write speeds for a
// particular drive.
//
CExitCode CBurnContext::CommandGetSpeeds (const PARAMETERS & params)
{
	// First look for a particular drive according to the user specified
	// command line parameters.
	//
	int iDriveIndex = LookForADrive (params);

	// If value is negative, the drive was not found. Return an error.
	//
	if (iDriveIndex < 0)
	{
		return EXITCODE_ERROR_OPENNING_DRIVE;
	}

	NERO_SPEED_INFOS * pReadSpeeds;
	NERO_SPEED_INFOS * pWriteSpeeds;

	pReadSpeeds = NeroGetAvailableSpeeds (m_NeroDeviceHandle, ACCESSTYPE_READ, (NERO_MEDIA_TYPE) params.GetMediaType (), NULL);
	pWriteSpeeds = NeroGetAvailableSpeeds (m_NeroDeviceHandle, ACCESSTYPE_WRITE, (NERO_MEDIA_TYPE) params.GetMediaType (), NULL);

	printf ("%-20s: %s\n", "Drive name", m_NeroDeviceInfos->nsdisDevInfos[iDriveIndex].nsdiDeviceName);
	if (pReadSpeeds)
	{
		printf ("%-20s: ", "Read speeds");
		DecodeSpeeds (*pReadSpeeds);
		printf ("\n");

		NeroFreeMem (pReadSpeeds);
	}

	if (pWriteSpeeds)
	{
		printf ("%-20s: ", "Write speeds");
		DecodeSpeeds (*pWriteSpeeds);
		printf ("\n");

		NeroFreeMem (pWriteSpeeds);
	}
	
	return EXITCODE_OK;
}

