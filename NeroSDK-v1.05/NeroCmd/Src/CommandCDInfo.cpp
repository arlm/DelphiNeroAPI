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
		printf ("Erase modes:");
		if (NCDI_IS_ERASE_MODE_AVAILABLE ((*m_NeroCDInfo), NEROAPI_ERASE_ENTIRE))
		{
			printf (" Entire");
		}
		if (NCDI_IS_ERASE_MODE_AVAILABLE ((*m_NeroCDInfo), NEROAPI_ERASE_QUICK))
		{
			printf (" Quick");
		}
		printf ("\n");
	}

	if (m_NeroCDInfo->ncdiMediumFlags != 0)
	{
		printf ("Medium flags:");
		
		if (0 != (m_NeroCDInfo->ncdiMediumFlags & NCDIMF_VIRTUALMULTISESSION))
		{
			printf (" VMS");
		}
		if (0 != (m_NeroCDInfo->ncdiMediumFlags & NCDIMF_HDB_SUPPORTED))
		{
			printf (" HDB");
		}
		
		printf ("\n");
	}

	printf ("Layer 0 max blocks: %d\n", m_NeroCDInfo->ncdiLayer0MaxBlocks);
	printf ("Total capacity: %d\n", m_NeroCDInfo->ncdiTotalCapacity);
	
	printf ("\n");

	// Print out information regarding each and every track..

	for (DWORD i = 0; i < m_NeroCDInfo->ncdiNumTracks; i++)
	{
		if (i == 0)
		{
			printf ("  %3s %-6s %-10s %-10s %-10s %-5s %s\n",
				"###",
				"Type",
				"Start",
				"Stop",
				"Length",
				"Sess#",
				"ISRC");
			printf ("  ---+------+----------+----------+----------+-----+----\n");
		}

		NERO_TRACK_INFO * pTrackInfo = &m_NeroCDInfo->ncdiTrackInfos[i];

		printf ("  %02d. %-6s 0x%08x 0x%08x 0x%08x %5d %-15.15s\n",
				pTrackInfo->ntiTrackNumber,
				pTrackInfo->ntiTrackType == NTT_AUDIO ? "audio" : pTrackInfo->ntiTrackType == NTT_DATA ? "data" : "unknown",
				pTrackInfo->ntiTrackStartBlk,
				pTrackInfo->ntiTrackStartBlk + pTrackInfo->ntiTrackLengthInBlks - 1,
				pTrackInfo->ntiTrackLengthInBlks,
				pTrackInfo->ntiSessionNumber,
				pTrackInfo->ntiISRC);
		
		if (pTrackInfo->ntiArtist[0] != '\0')
		{
			printf ("      Artist: \"%s\"\n", pTrackInfo->ntiArtist);
		}
		if (pTrackInfo->ntiTitle[0] != '\0')
		{
			printf ("      Title: \"%s\"\n", pTrackInfo->ntiTitle);
		}
	}
	
	// If virtual multisession is supported...
	// 
	if (0 != (m_NeroCDInfo->ncdiMediumFlags & NCDIMF_VIRTUALMULTISESSION))
	{
		NERO_VMS_INFO * pVMSInfo = NeroGetVMSInfo (m_NeroDeviceHandle, 0);
		
		if (pVMSInfo != NULL)
		{
			printf ("\nVirtual multisession info:\n");
			printf ("Next writable address: 0x%08x\n", pVMSInfo->nvmsiNextWritableAddress);
			
			printf ("\n");

			for (DWORD i = 0; i < pVMSInfo->nvmsiNumSessions; i++)
			{
				if (i == 0)
				{
					printf ("  %3s %-20s %-10s %s\n",
						"###",
						"Session name",
						"Next addr",
						"Creation time");
					printf ("  ---+--------------------+----------+-------------\n");
				}

				const NERO_VMSSESSION & VMSSession = pVMSInfo->nvmsiSessionInfo[i];
				
				printf ("  %02d. %-20.20s 0x%08x %s",
					i + 1,
					VMSSession.nvmssSessionName,
					VMSSession.nvmssNextWritableAddress,
					asctime (&VMSSession.nvmssCreationTime));
			}

			NeroFreeMem (pVMSInfo);
		}
	}

	return EXITCODE_OK;
}
