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
|* PROGRAM: WriteImage.cpp
|*
|* PURPOSE: ISO image burning
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function is responsible for burning an ISO image.

CExitCode CBurnContext::WriteImage (const PARAMETERS & params)
{
	// Make sure that an image file name has been provided by the user

	_ASSERTE (NULL != params.GetImageFileName());

	NERO_WRITE_IMAGE writeCD;

	// Fill in the image file name

	strncpy (writeCD.nwiImageFileName, params.GetImageFileName(), sizeof (writeCD.nwiImageFileName));
	writeCD.nwiImageFileName[sizeof (writeCD.nwiImageFileName)-1] = 0;
	
	NEROAPI_BURN_ERROR err;

	// Burn the image

	err = NeroBurn (m_NeroDeviceHandle,
					NERO_BURN_IMAGE_MEDIA,
					&writeCD,
					GetBurnFlags (params),
					params.GetSpeedToNeroBurn (),
					&s_NeroProgress);

	return TranslateNeroToExitCode (err);
}

