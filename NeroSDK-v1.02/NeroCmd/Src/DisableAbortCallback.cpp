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
|* PROGRAM: DisableAbortCallback.cpp
|*
|* PURPOSE: Handling of the DisableAbort callback
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This is one of the NeroAPI callbacks. It prints out the info
// to remind user whether the current operation is abortable.

void NERO_CALLBACK_ATTR CBurnContext::DisableAbortCallback (void *pUserData, BOOL enableAbort)
{
	// Just print out one or the other string.
	// 
	puts ((!enableAbort)? "[i] The current process cannot be interrupted": "[i] The process can be interrupted again");
}
