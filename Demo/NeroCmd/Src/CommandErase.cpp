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
|* PROGRAM: CommandErase.cpp
|*
|* PURPOSE: Implements erasure of CDRWs
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function erases a CDRW either entirely or in quick mode.

CExitCode CBurnContext::CommandErase (const PARAMETERS & params)
{
	// Get the estimated time for the erase operation

	int time = NeroGetCDRWErasingTime (m_NeroDeviceHandle, params.GetEraseMode());

	// Abort on error

	switch (time)
	{
		case -1:
			return EXITCODE_NO_CD_INSERTED;

		case -2:
			return EXITCODE_NO_SUPPORT_FOR_CDRW;

		default:
			break;
	}

	printf ("Erasing CDRW. This will take %d seconds.\n", time);


	// Erase the CDRW. Mode is either NEROAPI_ERASE_ENTIRE or NEROAPI_ERASE_QUICK.
	// Quick mode is default. NeroEraseCDRW returns 0 if successful
	
	int ret = NeroEraseCDRW (m_NeroDeviceHandle, params.GetEraseMode());

	// Return the proper EXITCODE

	return (0 != ret)? EXITCODE_ERROR_ERASING_CDRW: EXITCODE_OK;
}
