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
|* PROGRAM: CommandRead.cpp
|*
|* PURPOSE: Perform DAE (digital audio extraction)
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function performs DAE (digital audio extraction).

CExitCode CBurnContext::CommandRead (const PARAMETERS & params)
{
	// Make sure that NeroGetCDInfo has not been called before to prevent multiple 
	// allocation of memory for NERO_CD_INFO.

	_ASSERTE (m_NeroCDInfo == NULL);

	// First, get the CD info.
	// NeroGetCDInfo retrieves a pointer to a NERO_CD_INFO structure for the specified device.
	// The allocated memory for the structure has to be freed by using  NeroFreeMem().
	// NULL will be returned if an error occurred.

	m_NeroCDInfo = NeroGetCDInfo (m_NeroDeviceHandle, NGCDI_READ_CD_TEXT);
	if (NULL == m_NeroCDInfo)
	{
		return EXITCODE_ERROR_GETTING_CD_INFO;
	}

	// Loop through the user supplied list of tracks.

	for (int i = 0; i < params.GetNumberOfTracks(); i++)
	{
		NERO_TRACK_INFO* pTrackInfo = NULL;
		NERO_CALLBACK callback;
		NERO_DATA_EXCHANGE exchange;

		// Find the track among the existing tracks on the CD.

		for (unsigned int j = 0; j < m_NeroCDInfo->ncdiNumTracks; j ++)
		{
			if (m_NeroCDInfo->ncdiTrackInfos[j].ntiTrackNumber == params.GetTrackNumber(i))
			{
				pTrackInfo = &m_NeroCDInfo->ncdiTrackInfos[j];
				break;
			}
		}

		// If the track could not be found pTrackInfo still contains NULL

		if (NULL == pTrackInfo)
		{
			// If the track was not found, report an error.

			m_ErrorLog.printf ("Track %d for file '%s' was not found on CD\n", params.GetTrackNumber(i), params.GetTrackFileName(i));

			return EXITCODE_TRACK_NOT_FOUND;
		}
		
		// Track found, now extract the audio data.

		callback.ncCallbackFunction = ProgressCallback;
		callback.ncUserData = &s_NeroSettings;

		// Find the file extension the user supplied for the file 
		// that will contain the extracted data.
		// Supported extensions are WAV and PCM.

		// Try to find the file extension by looking for '.' from the right

		char* psExt = strrchr (params.GetTrackFileName(i), '.');

		// stricmp performs a lowercase comparison and returns 0 if the strings are identical.

		if ((NULL != psExt) && (0 == stricmp (psExt, ".wav")))
		{
			// WAV files require NERO_ET_FILE as data exchange type

			exchange.ndeType = NERO_ET_FILE;

			// Use the long version of the filename instead of the
			// deprecated short one.
			// 
			exchange.ndeData.ndeLongFileName.reserved = 0;
			exchange.ndeData.ndeLongFileName.ptr = params.GetTrackFileName(i);
		}
		else if ((NULL != psExt) && (0 == stricmp (psExt, ".pcm")))
		{
			// PCM files require NEOR_ET_IO_CALLBACK to exchange data directly

			exchange.ndeType = NERO_ET_IO_CALLBACK;

			// Set the required callbacks

			exchange.ndeData.ndeIO.nioIOCallback = WriteIOCallback;
			exchange.ndeData.ndeIO.nioEOFCallback = EOFCallback;
			exchange.ndeData.ndeIO.nioErrorCallback = ErrorCallback;
			
			// fopen with mode "wb" opens an empty file for writing in binary (untranslated) mode. If the given file exists, its contents are destroyed. 
			// Translations involving carriage-return and linefeed characters are suppressed. 
			
			exchange.ndeData.ndeIO.nioUserData = fopen (params.GetTrackFileName(i), "wb");

			// Make sure that the file could be openend

			if (0 == exchange.ndeData.ndeIO.nioUserData)
			{
				m_ErrorLog.printf ("Cannot open target file %s\n", params.GetTrackFileName(i));

				return EXITCODE_ERROR_OPENNING_FILE;
			}
		}
		else
		{
			// We did not recognize the file extension.

			m_ErrorLog.printf ("Unknown file type for writing of %s\n", params.GetTrackFileName(i));

			return EXITCODE_UNKNOWN_FILE_TYPE;
		}

		// Print track number and file name

		printf ("%02d. '%s':\n", params.GetTrackNumber(i), params.GetTrackFileName(i));

		// Do the actual audio extraction.
		// Aborting will not be reported by NeroGetLastError().
		// Incomplete target files are not deleted.
		// 0 is returned if the operation was successful.

		int res = NeroDAE (m_NeroDeviceHandle,
							pTrackInfo->ntiTrackStartBlk,
							pTrackInfo->ntiTrackLengthInBlks,
							&exchange,
							params.GetReadSpeed (),
							&callback);

		// If we extracted PCM the data file needs to be closed

		if (exchange.ndeType == NERO_ET_IO_CALLBACK)
		{
			// Close the file handle if we opened it.

			if (0 != exchange.ndeData.ndeIO.nioUserData)
			{
				fclose ((FILE *) exchange.ndeData.ndeIO.nioUserData);
			}
		}

		// If NeroDAE did not return 0 the operation failed.

		if (0 != res)
		{
			return EXITCODE_DAE_FAILED;
		}

		printf ("\n");
	}

	return EXITCODE_OK;
}
