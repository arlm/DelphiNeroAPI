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
|* PROGRAM: SetPhaseCallback.cpp
|*
|* PURPOSE: Callback for reporting phase changes
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This is a Nero callback that prints the change of phase.

void NERO_CALLBACK_ATTR CBurnContext::SetPhaseCallback (void *pUserData, const char *text)
{
	printf ("    %-76s\n", text);
}
