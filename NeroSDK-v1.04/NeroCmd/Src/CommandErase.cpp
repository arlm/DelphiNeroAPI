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

	printf ("Erasing disc. This will take %d seconds.\n", time);


	// Erase the CDRW. Mode is either NEROAPI_ERASE_ENTIRE or NEROAPI_ERASE_QUICK.
	// Quick mode is default. NeroEraseDisc returns 0 if successful.
	// 
	DWORD dwFlags = 0;

	dwFlags |= params.GetDisableEjectAfterErase ()? NEDF_DISABLE_EJECT: 0;
	dwFlags |= params.GetForceEjectAfterErase ()? NEDF_EJECT_AFTER_ERASE: 0;

	int ret = NeroEraseDisc (m_NeroDeviceHandle, params.GetEraseMode(), dwFlags, NULL);

	// Return the proper EXITCODE

	return (0 != ret)? EXITCODE_ERROR_ERASING_CDRW: EXITCODE_OK;
}
