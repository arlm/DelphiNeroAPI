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
|* PROGRAM: CommandInternal.cpp
|*
|* PURPOSE: Used only for internal testing!!!
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"

// This command is used strictly for internal testing.
// 
CExitCode CBurnContext::CommandInternal (const PARAMETERS & params)
{
	NERO_AUDIO_ITEM_HANDLE h = NeroAudioCreateTargetItem (8);
	NERO_CONFIG_RESULT r = NeroAudioGUIConfigureItem (&h, 1);
	NeroAudioCloseItem (h);

	return EXITCODE_OK;
}
