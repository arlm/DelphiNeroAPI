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
|* PROGRAM: CommandListFormats.cpp
|*
|* PURPOSE: Lists supported audio formats.
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


CExitCode CBurnContext::CommandListFormats (const PARAMETERS & params)
{
	NERO_AUDIO_FORMAT_INFO nafi;

	// Zero-out the structure.
	// 
	memset (&nafi, 0, sizeof (nafi));

	// Loop until API function returns FALSE. Supported formats start at 0.
	// Print some basic information about each format.
	//
	for (int iCount = 0; NeroAudioGetFormatInfo (iCount, &nafi); iCount ++)
	{
		if (iCount == 0)
		{
			// Print a header only before the first item.
			// 
			printf ("Num Description (extension), target, config\n");
			printf ("-------------------------------------------\n");
		}

		printf ("%3d. %s (%s)", iCount, nafi.nafiDescription, nafi.nafiExtList);
		if (nafi.nafiTgt)	printf (", is_target");
		if (nafi.nafiConfigurable)	printf (", is_configurable");
		printf ("\n");
	}

	if (iCount == 0)
	{
		printf ("There are no formats!\n");
	}

	return EXITCODE_OK;
}
