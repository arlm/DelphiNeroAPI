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
|* PROGRAM: AbortedCallback.cpp
|*
|* PURPOSE: AbortedCallback implementation
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"

// This is one of the Nero callbacks. It is responsible for aborting the
// pending process. We simply return the flag that we maintain.
// This abort flag is set in CtrlHandler when the user presses Ctrl+C

BOOL NERO_CALLBACK_ATTR CBurnContext::AbortedCallback (void *pUserData)
{
	return s_bAborted;
}
