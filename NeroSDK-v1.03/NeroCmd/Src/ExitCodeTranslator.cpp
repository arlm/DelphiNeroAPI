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
|* PROGRAM: ExitCodeTranslator.cpp
|*
|* PURPOSE: Translation of NeroAPI errors to EXITCODEs
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function does simple translation from NeroAPI's burn error
// into our own EXITCODE.

CExitCode CBurnContext::TranslateNeroToExitCode (NEROAPI_BURN_ERROR err)
{
	switch (err)
	{
		case NEROAPI_BURN_OK:
			return EXITCODE_OK;

		case NEROAPI_BURN_UNKNOWN_CD_FORMAT:
			return EXITCODE_UNKNOWN_CD_FORMAT;

		case NEROAPI_BURN_INVALID_DRIVE:
			return EXITCODE_INVALID_DRIVE;

		case NEROAPI_BURN_FAILED:
			return EXITCODE_BURN_FAILED;

		case NEROAPI_BURN_FUNCTION_NOT_ALLOWED:
			return EXITCODE_FUNCTION_NOT_ALLOWED;

		case NEROAPI_BURN_DRIVE_NOT_ALLOWED:
			return EXITCODE_DRIVE_NOT_ALLOWED;

		case NEROAPI_BURN_USER_ABORT:
			return EXITCODE_USER_ABORTED;

		case NEROAPI_BURN_BAD_MESSAGE_FILE:
			return EXITCODE_BAD_MESSAGE_FILE;

		default:
			return EXITCODE_INTERNAL_ERROR;
	}
}
