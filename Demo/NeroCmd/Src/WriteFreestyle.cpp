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
|* PROGRAM: WriteFreestyle.cpp
|*
|* PURPOSE: Freestyle format CD burning
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function is responsible for burning a freestyle cd.

CExitCode CBurnContext::WriteFreestyle (const PARAMETERS & params)
{
	int iSize;
	NERO_WRITE_FREESTYLE_CD * pWriteCD;
	EXITCODE code;
	NERO_ISO_ITEM* pItem = NULL;

	// Calculate the size required for NERO_WRITE_FREESTYLE_CD plus the given number of tracks

	iSize = sizeof (NERO_WRITE_FREESTYLE_CD) + (params.GetNumberOfTracks() - 1) * sizeof (NERO_FREESTYLE_TRACK);

	// Allocate the required memory and assign it to the NERO_WRITE_FREESTYLE_CD pointer

	pWriteCD = (NERO_WRITE_FREESTYLE_CD *) new char[iSize];

	// Make sure the system could allocate enough memory

	if (NULL == pWriteCD)
	{
		return EXITCODE_OUT_OF_MEMORY;
	}

	// Fill the allocated memory with null bytes

	memset (pWriteCD, 0, iSize);

	// Fill in the basic information

	pWriteCD->nwfcdStructureSize = sizeof (NERO_FREESTYLE_CD);
	pWriteCD->nwfcdNumTracks = params.GetNumberOfTracks();
	pWriteCD->nwfcdArtist = params.GetArtist();
	pWriteCD->nwfcdTitle = params.GetTitle();
	pWriteCD->nwfcdCDExtra = params.GetUseCDExtra();

	try
	{
		// Get the ISO track from the information in the parameters.

		code = GetIsoTrack (params, &pWriteCD->nwfcdIsoTrack, &pItem);
		if (code != EXITCODE_OK)
		{
			throw code;
		}

		// Fill in the CD stamp information as it only became available after
		// GetIsoTrack().

		pWriteCD->nwfcdpCDStamp = m_pCDStamp;

		for (int i = 0; i < params.GetNumberOfTracks(); i ++)
		{

			// Helper variables to promote readability

			NERO_DATA_EXCHANGE* ndeShort = &(pWriteCD->nwfcdTracks [i].nftSourceDataExchg);
			int iNameSize = sizeof (ndeShort->ndeData.ndeFileName);
			char* pFileName = (char*)&(pWriteCD->nwfcdTracks [i].nftSourceDataExchg.ndeData.ndeFileName);
			LPCSTR sFileName = params.GetTrackFileName(i);

			// Fill in type information, file name and mode

			ndeShort->ndeType = NERO_ET_FILE_RAW;
			strncpy (pFileName, sFileName, iNameSize);
			pFileName[iNameSize - 1] = 0;
			pWriteCD->nwfcdTracks[i].nftTracktype = params.GetTrackMode(i);
		}
		
		pWriteCD->nwfcdMediaType = (NERO_MEDIA_TYPE) params.GetMediaType ();

		NEROAPI_BURN_ERROR err;

		// Perform the actual burn process

		err = NeroBurn (m_NeroDeviceHandle,
						NERO_FREESTYLE_CD,
						pWriteCD,
						GetBurnFlags (params),
						params.GetSpeedToNeroBurn (),
						&s_NeroProgress);

		code = TranslateNeroToExitCode (err);
	}
	catch (EXITCODE e)
	{
		code = e;
	}

	// Free allocated memory

	NeroFreeIsoTrack (pWriteCD->nwfcdIsoTrack);
	DeleteIsoItemTree (pItem);
	delete [] (char *)pWriteCD;

	return code;
}
