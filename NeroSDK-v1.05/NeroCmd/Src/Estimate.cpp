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
|* PROGRAM: Estimate.cpp
|*
|* PURPOSE: Estimate ISO track size
******************************************************************************/

#include "stdafx.h"
#include "BurnContext.h"

CExitCode CBurnContext::CommandEstimate (const PARAMETERS & params)
{
	EXITCODE code = EXITCODE_OK;
	NERO_ISO_ITEM * pItem = NULL;
	NERO_FILESYSTEMTRACK_OPTIONS fso;
	CNeroIsoTrack * pIsoTrack = NULL;

	memset (&fso, 0, sizeof (fso));
	fso.netsStructureSize = sizeof (fso);
	fso.netsMediaType = (NERO_MEDIA_TYPE) params.GetMediaType ();
	fso.netsDeviceHandle = m_NeroDeviceHandle;
	fso.netsFlags = GetBurnFlags (params);

	if (params.GetUseDVD())
	{
		fso.netsMediaType = (NERO_MEDIA_TYPE) (fso.netsMediaType | MEDIA_DVD_ANY);
	}

	try
	{
		// Get the ISO track from the information in the parameters.

		code = GetIsoTrack (params, &pIsoTrack, &pItem);
		if (code != EXITCODE_OK)
		{
			throw code;
		}

		// Fill in the CD stamp information as it only became available after
		// GetIsoTrack.

		fso.netspCDStamp = m_pCDStamp;

		DWORD dwEstimateFlags = 0;

		if (!params.GetEstimateNoFSOverhead ())
		{
			dwEstimateFlags |= NETS_FILESYSTEM_OVERHEAD;
		}

		if (!params.GetEstimateNoData ())
		{
			dwEstimateFlags |= NETS_DATA;
		}

		if (!params.GetEstimateNoExactSize ())
		{
			dwEstimateFlags |= NETS_EXACT_SIZE;
		}
		
		unsigned int uEstimatedSize = NeroEstimateTrackSize (pIsoTrack,
															dwEstimateFlags,
															&fso);

		if (uEstimatedSize == -1)
		{
			code = EXITCODE_ERROR_DOING_ESTIMATION;
		}
		else
		{
			code = EXITCODE_OK;

			printf ("Estimated track size: %u blocks\n", uEstimatedSize);
		}
	}
	catch (EXITCODE e)
	{
		code = e;
	}
	
	// Free allocated memory
	
	if (pIsoTrack != NULL)
	{
		NeroFreeIsoTrack (pIsoTrack);
	}

	if (pItem != NULL)
	{
		DeleteIsoItemTree (pItem);
	}
	
	return code;
}