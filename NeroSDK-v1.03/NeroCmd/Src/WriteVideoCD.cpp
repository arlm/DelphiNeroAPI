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
|* PROGRAM: WriteVideoCD.cpp
|*
|* PURPOSE: Burn Video CDs
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function performs burning Video or Super Video CDs.

CExitCode CBurnContext::WriteVideoCD (const PARAMETERS & params)
{
	int iSize;
	NERO_WRITE_VIDEO_CD * pWriteCD;
	EXITCODE code;
	NERO_ISO_ITEM * pItem = NULL;

	// Calculate the size required for NERO_WRITE_CD plus the given number of tracks

	iSize = sizeof (NERO_WRITE_VIDEO_CD) + (params.GetNumberOfTracks() - 1) * sizeof (NERO_VIDEO_ITEM);

	// Allocate the required memory and assign it to the NERO_WRITE_CD pointer

	pWriteCD = (NERO_WRITE_VIDEO_CD *) new char[iSize];
	if (!pWriteCD)
	{
		return EXITCODE_OUT_OF_MEMORY;
	}

	// Fill the allocated memory with null bytes

	memset (pWriteCD, 0, iSize);

	// Fill in the basic information

	pWriteCD->nwvcdSVCD = (BURNTYPE_SVIDEOCD == params.GetBurnType())? true: false;
	pWriteCD->nwvcdNumItems = params.GetNumberOfTracks();

	pWriteCD->nwvcdLongTempPath = params.GetTempPath ();

	try
	{
		// Get the ISO track from the information in the parameters.

		code = GetIsoTrack (params, &pWriteCD->nwvcdIsoTrack, &pItem);
		if (code != EXITCODE_OK)
		{
			throw code;
		}

		for (int i = 0; i < params.GetNumberOfTracks(); i ++)
		{
			// Helper variables to promote readability

			LPCSTR psFilename = params.GetTrackFileName(i);
			NERO_VIDEO_ITEM * item = &pWriteCD->nwvcdItems[i];

			item->nviLongSourceFileName = psFilename;

			// MPEG and JPEG are allowed types
			// stricmp performs a lowercase comparison and returns 0 if the strings are identical.
			// We fill in type information and file name.

			LPCSTR psExt = strrchr (psFilename, '.');

			if (psExt && (!stricmp (psExt, ".mpg") || !stricmp (psExt, ".mpeg")))
			{
				item->nviItemType = NERO_MPEG_ITEM;

				// no pause after mpeg items

				item->nviPauseAfterItem=0;
			}
			else if (psExt && (!stricmp (psExt, ".avi")))
			{
				item->nviItemType = NERO_NONENCODED_VIDEO_ITEM;
				
				// no pause after avi items

				item->nviPauseAfterItem=0;
			}
			else if (psExt && (!stricmp (psExt, ".jpg") || !stricmp (psExt, ".jpeg")))
			{
				item->nviItemType = NERO_JPEG_ITEM;
				
				// infinite pause after jpeg items
				
				item->nviPauseAfterItem=-1;
			}
			else
			{
				m_ErrorLog.printf ("Unknown file type '%s'\n", params.GetTrackFileName(i));
				
				throw EXITCODE_UNKNOWN_FILE_TYPE;
			}
		}
		
		NEROAPI_BURN_ERROR err;
		CBurnContextProgress m_NeroProgress;
		
		// Perform the actual burn process

		err = NeroBurn (m_NeroDeviceHandle,
						NERO_VIDEO_CD,
						pWriteCD,
						GetBurnFlags (params),
						params.GetSpeedToNeroBurn (),
						m_NeroProgress);

		code = TranslateNeroToExitCode (err);
	}
	catch (EXITCODE e)
	{
		code = e;
	}

	// Free allocated memory

	NeroFreeIsoTrack (pWriteCD->nwvcdIsoTrack);
	DeleteIsoItemTree (pItem);
	delete [] (char *)pWriteCD;

	return code;
}

