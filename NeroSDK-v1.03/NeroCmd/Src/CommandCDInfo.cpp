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
|* PROGRAM: CommandCDInfo.cpp
|*
|* PURPOSE: Retrieve CD information
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function performs execution of a CD info command.

CExitCode CBurnContext::CommandCDInfo (const PARAMETERS & params)
{
	// Retrieve a pointer to a NERO_CD_INFO structure for the specified device.
	// NULL will be returned if an error occurred. 
	// The allocated memory for the structure has to be freed by using  NeroFreeMem().
	// This will be performed by the destructor of CBurnContext.

	m_NeroCDInfo = NeroGetCDInfo (m_NeroDeviceHandle, NGCDI_READ_CD_TEXT|NGCDI_READ_ISRC);
	if (NULL == m_NeroCDInfo)
	{
		return EXITCODE_ERROR_GETTING_CD_INFO;
	}

	return DisplayCDInfo ();
}

CExitCode CBurnContext::DisplayCDInfo (void)
{
	// Ask the NeroAPI to give the description of the media type and
	// print if the string exists.
	// 
	char * psMedia = NeroGetTypeNameOfMedia (m_NeroCDInfo->ncdiMediaType, NULL);
	if (psMedia != NULL && psMedia[0] != '\0')
	{
		printf ("%s", psMedia);
		NeroFreeMem (psMedia);
	}
	else
	{
		printf ("<no media>");
	}

	// Print other CD information.

	printf (", %s, %d blocks free\n"
			"Artist %s, Title %s\n",
			m_NeroCDInfo->ncdiIsWriteable ? "writeable" : "not writable",
			m_NeroCDInfo->ncdiFreeCapacityInBlocks,
			m_NeroCDInfo->ncdiArtist[0] ? m_NeroCDInfo->ncdiArtist : "unknown",
			m_NeroCDInfo->ncdiTitle[0] ? m_NeroCDInfo->ncdiTitle : "unknown");

	if (m_NeroCDInfo->ncdiAvailableEraseModes != 0)
	{
		printf ("erase modes: ");
		if (NCDI_IS_ERASE_MODE_AVAILABLE ((*m_NeroCDInfo), NEROAPI_ERASE_ENTIRE))
		{
			printf ("entire ");
		}
		if (NCDI_IS_ERASE_MODE_AVAILABLE ((*m_NeroCDInfo), NEROAPI_ERASE_QUICK))
		{
			printf ("quick ");
		}
		printf ("\n");
	}


	// Print out information regarding each and every track..

	for (int i = 0; i < (int)(m_NeroCDInfo->ncdiNumTracks); i++)
	{
		NERO_TRACK_INFO * pTrackInfo = &m_NeroCDInfo->ncdiTrackInfos[i];

		printf ("%02d. %6s %6d - %6d = %6d blocks, session %d, ISRC: %s",
				pTrackInfo->ntiTrackNumber,
				pTrackInfo->ntiTrackType == NTT_AUDIO ? "audio" : pTrackInfo->ntiTrackType == NTT_DATA ? "data" : "unknown",
				pTrackInfo->ntiTrackStartBlk,
				pTrackInfo->ntiTrackStartBlk + pTrackInfo->ntiTrackLengthInBlks - 1,
				pTrackInfo->ntiTrackLengthInBlks,
				pTrackInfo->ntiSessionNumber,
				pTrackInfo->ntiISRC);

		if (pTrackInfo->ntiArtist[0] || pTrackInfo->ntiTitle[0])
		{
			printf (" (%s %s)\n", pTrackInfo->ntiArtist, pTrackInfo->ntiTitle);
		}
		else
		{
			printf ("\n");
		}
	}

	return EXITCODE_OK;
}
