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
|* PROGRAM: CommandDriveInfo.cpp
|*
|* PURPOSE: List the characteristics of a particular drive
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function prints the significant characteristics of a particular
// drive. m_NeroDeviceInfos has been filled by a call
// GetAvailableDrives during NeroAPI initialization in main().

CExitCode CBurnContext::CommandDriveInfo (const PARAMETERS & params)
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

	// Use a helper variable for better code readability

	NERO_SCSI_DEVICE_INFO * pNSDI = &m_NeroDeviceInfos->nsdisDevInfos[iDriveIndex];

	// Determine the Windows drive letter for this device or use the
	// question mark if drive letter is not available.
	// 
	char cDriveLetter = (0 != pNSDI->nsdiDriveLetter)? toupper (pNSDI->nsdiDriveLetter): '?';

	// Print out all the relevant information for this drive.
	// 
	printf ("%-20s: %c\n", "Drive letter", cDriveLetter);
	printf ("%-20s: %s\n", "Device name", pNSDI->nsdiDeviceName);
	printf ("%-20s: %d\n", "Device id", pNSDI->nsdiDeviceID);
	printf ("%-20s: %s\n", "Host adapter name", pNSDI->nsdiHostAdapterName);
	printf ("%-20s: %d\n", "Host adapter number", pNSDI->nsdiHostAdapterNo);

	printf ("%-20s: ", "Underrun protection");

	// Check for buffer underrun protection.
	// 
	if (pNSDI->nsdiCapabilities & NSDI_BUF_UNDERRUN_PROT)
	{
		// If it exists, use the name provided by NeroAPI or a generic
		// string otherwise.
		// 
		printf ("%s\n", (pNSDI->nsdiBufUnderrunProtName[0] != '\0')? pNSDI->nsdiBufUnderrunProtName: "<suported>");
	}
	else
	{
		// There is on underrun protection.
		// 
		printf ("%s\n", "<none>");
	}
	
	printf ("%-20s: %08x\n", "Drive buffer size", pNSDI->nsdiDriveBufferSize);

	printf ("%-20s: ", "Mandatory BUP speed");
	if (pNSDI->nsdiMandatoryBUPSpeed == 0)
	{
		// If there is no mandatory BUP speed for this drive, print <none>
		// instead of zero.
		// 
		printf ("<none>\n");
	}
	else
	{
		printf ("%d\n", pNSDI->nsdiMandatoryBUPSpeed);
	}

	printf ("%-20s: ", "Device type");
	DecodeDeviceType (pNSDI);
	printf ("\n");

	char * psMedia = NeroGetTypeNameOfMedia (pNSDI->nsdiMediaSupport, NULL);
	if (psMedia)
	{
		printf ("%-20s: %s\n", "Media support", (psMedia[0] != '\0')? psMedia: "<none>");
		NeroFreeMem (psMedia);
	}

	printf ("%-20s: ", "Capabilities");
	DecodeCapabilities (pNSDI);
	printf ("\n");

	printf ("%-20s: ", "Read speeds");
	DecodeSpeeds (pNSDI->nsdiReadSpeeds);
	printf ("\n");

	printf ("%-20s: ", "Write speeds");
	DecodeSpeeds (pNSDI->nsdiWriteSpeeds);
	printf ("\n");
	
	return EXITCODE_OK;
}

// This function prints the contents of the NERO_SPEED_INFOS structure.
//
void CBurnContext::DecodeSpeeds (const NERO_SPEED_INFOS & nsi)
{
	for (int i = 0; i < nsi.nsiNumSupportedSpeeds; i ++)
	{
		if (i > 0)
		{
			printf (", ");
		}

		if (nsi.nsiBaseSpeedKBs != 0)
		{
			printf ("%d", nsi.nsiSupportedSpeedsKBs[i]/nsi.nsiBaseSpeedKBs);
		}
		else
		{
			printf ("%d", nsi.nsiSupportedSpeedsKBs[i]);
		}
	}

	printf ("\n%-20s: %d", "Base speed in KB/s", nsi.nsiBaseSpeedKBs);
}

// This function prints the device type.
//
void CBurnContext::DecodeDeviceType (const NERO_SCSI_DEVICE_INFO * pNSDI) const
{
	switch (pNSDI->nsdiDevType)
	{
	case NEA_SCSI_DEVTYPE_WORM:
		printf ("WORM");
		break;
		
	case NEA_SCSI_DEVTYPE_CDROM:
		printf ("CD-ROM");
		break;
		
	case NEA_SCSI_DEVTYPE_UNSUPPORTED_WORM:
		printf ("Unsupported WORM");
		break;

	case NEA_SCSI_DEVTYPE_UNKNOWN:
	default:
		printf ("Unknown");
	}
}

// This function prints tha available drive capabilities.
// 
void CBurnContext::DecodeCapabilities (const NERO_SCSI_DEVICE_INFO * pNSDI) const
{
	bool bFirst = true;

	if ((pNSDI->nsdiCapabilities & NSDI_ALLOWED) != 0)
	{
		printf ("allowed ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_DAO) != 0)
	{
		printf ("dao ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_READ_CD_TEXT) != 0)
	{
		printf ("read_cd_text ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_VARIABLE_PAUSES_IN_TAO) != 0)
	{
		printf ("variable_pauses_in_tao ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_DAO_WRITE_CD_TEXT) != 0)
	{
		printf ("dao_write_cd_text ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_IMAGE_RECORDER) != 0)
	{
		printf ("image_recorder ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_UNDETECTED) != 0)
	{	
		printf ("undetected ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_IDE_BUS) != 0)
	{
		printf ("ide_bus");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_SCSI_BUS) != 0)
	{
		printf ("scsi_bus ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_BUF_UNDERRUN_PROT) != 0)
	{
		printf ("underrun_prot ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_ALLOW_CHANGE_BOOKTYPE) != 0)
	{
		printf ("allow_change_booktype ");
	}

	if ((pNSDI->nsdiCapabilities & NSDI_DVDPLUSVR_SUPPORTED) != 0)
	{
		printf ("dvd+vr ");
	}
}
