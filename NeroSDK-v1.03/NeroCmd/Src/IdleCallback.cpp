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
|* PROGRAM: IdleCallback.cpp
|*
|* PURPOSE: Callback for idle processing
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"

// This is a NeroAPI callback responsible for idle processing. Since
// we have no idle processing, we simply return our aborted flag.

BOOL NERO_CALLBACK_ATTR CBurnContext::IdleCallback (void *pUserData)
{
	return s_bAborted;
}
