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
|* PROGRAM: CommandWrite.cpp
|*
|* PURPOSE: General Write Function
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function distinguishes between different burn types and
// acts accordingly.

CExitCode CBurnContext::CommandWrite (const PARAMETERS & params)
{
	EXITCODE code;

	switch (params.GetBurnType())
	{
	case BURNTYPE_IMAGE:

		// WriteImage burns Nero Image files (.nrg)

		code = WriteImage (params);
		break;

	case BURNTYPE_ISOAUDIO:
		
		// WriteIsoAudio handles ISO CDs and DVDs, as well as Audio and mixed mode CDs

		code = WriteIsoAudio (params);
		break;

	case BURNTYPE_SVIDEOCD:
	case BURNTYPE_VIDEOCD:

		// Both Video CD and Super Video CD are written by WriteVideoCD

		code = WriteVideoCD (params);
		break;

	case BURNTYPE_FREESTYLE:

		// Write Freestyle compilation

		code = WriteFreestyle (params);
		break;

	default:

		// No valid burn type

		code = EXITCODE_INTERNAL_ERROR;
	}

	return code;
}

