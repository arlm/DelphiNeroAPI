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
|* PROGRAM: WriteIsoAudio.cpp
|*
|* PURPOSE: Burning ISO/Audio CDs
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function is responsible for burning ISO CDs and DVDs,
// as well as Audio and mixed mode CDs

CExitCode CBurnContext::WriteIsoAudio (const PARAMETERS & params)
{
	int iSize;
	NERO_WRITE_CD * pWriteCD = NULL;
	EXITCODE code;
	NERO_ISO_ITEM * pItem = NULL;

	// Calculate the size required for NERO_WRITE_CD plus the given number of tracks

	iSize = sizeof (NERO_WRITE_CD) + (params.GetNumberOfTracks() - 1) * sizeof (NERO_AUDIO_TRACK);

	// Allocate the required memory and assign it to the NERO_WRITE_CD pointer

	pWriteCD = (NERO_WRITE_CD *) new char[iSize];

	// Make sure the system could allocate enough memory

	if (NULL == pWriteCD)
	{
		return EXITCODE_OUT_OF_MEMORY;
	}

	// Fill the allocated memory with null bytes

	memset (pWriteCD, 0, iSize);

	// Fill in the basic information

	pWriteCD->nwcdNumTracks = params.GetNumberOfTracks();
	pWriteCD->nwcdArtist = params.GetArtist();
	pWriteCD->nwcdTitle = params.GetTitle();
	pWriteCD->nwcdCDExtra = params.GetUseCDExtra();

	pWriteCD->nwcdMediaType = (NERO_MEDIA_TYPE) params.GetMediaType ();

	// Set DVD as media type if the user requested so
	// DVD is only allowed with ISO; will not work with Audio
	// or mixed mode.

	if (params.GetUseDVD())
	{
		pWriteCD->nwcdMediaType = (NERO_MEDIA_TYPE) (pWriteCD->nwcdMediaType | MEDIA_DVD_ANY);
	}

	try
	{
		// Get the ISO track from the information in the parameters.

		code = GetIsoTrack (params, &pWriteCD->nwcdIsoTrack, &pItem);
		if (code != EXITCODE_OK)
		{
			throw code;
		}

		// Fill in the CD stamp information as it only became available after
		// GetIsoTrack.

		pWriteCD->nwcdpCDStamp = m_pCDStamp;

		for (int i = 0; i < params.GetNumberOfTracks(); i ++)
		{
			// Write continously; first track requires minimal pause of 150, though.

			if (0 == i)
			{
				pWriteCD->nwcdTracks[i].natPauseInBlksBeforeThisTrack = 150;
			}
			else
			{
				pWriteCD->nwcdTracks[i].natPauseInBlksBeforeThisTrack = 0;
			}

			// Find the file name extension

			LPCSTR psExt = strrchr (params.GetTrackFileName(i), '.');
			LPCSTR psFilename = params.GetTrackFileName(i);
			
			// Helper variables to promote readability

			NERO_DATA_EXCHANGE & ndeShort = pWriteCD->nwcdTracks[i].natSourceDataExchg;

			// WAV, MP3, WMA and PCM are allowed types
			// stricmp performs a lowercase comparison and returns 0 if the strings are identical.
			// We fill in type information and file name.

			if ((NULL != psExt) && (0 == stricmp (psExt, ".wav")))
			{
				ndeShort.ndeType = NERO_ET_FILE;
				ndeShort.ndeData.ndeLongFileName.reserved = NULL;
				ndeShort.ndeData.ndeLongFileName.ptr = psFilename;
			}
			else if ((NULL != psExt) && (0 == stricmp (psExt, ".mp3")))
			{
				ndeShort.ndeType = NERO_ET_FILE_MP3;
				ndeShort.ndeData.ndeLongFileName.reserved = NULL;
				ndeShort.ndeData.ndeLongFileName.ptr = psFilename;
			}
			else if ((NULL != psExt) && (0 == stricmp (psExt, ".wma")))
			{
				ndeShort.ndeType = NERO_ET_FILE_WMA;
				ndeShort.ndeData.ndeLongFileName.reserved = NULL;
				ndeShort.ndeData.ndeLongFileName.ptr = psFilename;
			}
			else if ((NULL != psExt) && (0 == stricmp (psExt, ".pcm")))
			{
				// PCM format will be handled by callbacks

				ndeShort.ndeType = NERO_ET_IO_CALLBACK;
				ndeShort.ndeData.ndeIO.nioIOCallback = ReadIOCallback;
				ndeShort.ndeData.ndeIO.nioEOFCallback = EOFCallback;
				ndeShort.ndeData.ndeIO.nioErrorCallback = ErrorCallback;

				struct _stat buf;

				if (0 != _stat (psFilename, &buf))
				{
					m_ErrorLog.printf ("Cannot determine length of file %s\n", psFilename);

					throw EXITCODE_ERROR_DETERMINING_LENGTH_OF_FILE;
				}

				// Calculate the length in blocks. Block size for Audio compilations is 2352 bytes.

				pWriteCD->nwcdTracks [i].natLengthInBlocks = buf.st_size / 2352;

				// Open the file for reading in binary mode

				ndeShort.ndeData.ndeIO.nioUserData = fopen (psFilename, "rb");
				if (NULL == ndeShort.ndeData.ndeIO.nioUserData)
				{
					m_ErrorLog.printf ("Cannot open source file %s\n", psFilename);
					
					throw EXITCODE_ERROR_OPENNING_FILE;
				}
			}
			else
			{
				m_ErrorLog.printf ("Unknown file type '%s'\n", psFilename);
				
				throw EXITCODE_UNKNOWN_FILE_TYPE;
			}
		}
		
		NEROAPI_BURN_ERROR err;
		CBurnContextProgress m_NeroProgress;
		
		// Perform the actual burn process

		err = NeroBurn (m_NeroDeviceHandle,
						NERO_ISO_AUDIO_MEDIA,
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

	// Close the files that have been opened for
	// handling of PCM format if any.

	for (int i = 0; i < params.GetNumberOfTracks(); i ++)
	{
		if (pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeType == NERO_ET_IO_CALLBACK &&
			pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeIO.nioUserData)
		{
			fclose ((FILE *)pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeIO.nioUserData);
		}
	}

	// Free allocated memory

	if(pWriteCD && pWriteCD->nwcdIsoTrack)
	{
		NeroFreeIsoTrack (pWriteCD->nwcdIsoTrack);
		pWriteCD->nwcdIsoTrack = NULL;
	}
	if(pItem)
	{
		DeleteIsoItemTree (pItem);
		pItem = NULL;
	}
	if(pWriteCD)
	{
		delete [] (char *)pWriteCD;
		pWriteCD = NULL;
	}

	return code;
}
