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
|* PROGRAM: CommandEject.cpp
|*
|* PURPOSE: Eject and load implementation
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function executes the eject and load commands.

CExitCode CBurnContext::CommandEject (const PARAMETERS & params)
{
	int ret;

	// NeroEjectLoadCD returns 0 if successful or an error code if not.
	// "false" in parameter "eject" loads a CD, "true" ejects.

	if (COMMAND_EJECT == params.GetCommand())
	{
		ret = NeroEjectLoadCD (m_NeroDeviceHandle, true);
	}
	else // Should be COMMAND_LOAD.
	{
		ret = NeroEjectLoadCD (m_NeroDeviceHandle, false);
	}

	// Return the proper EXITCODE

	return (0 != ret)? EXITCODE_EJECT_FAILED: EXITCODE_OK;
}
