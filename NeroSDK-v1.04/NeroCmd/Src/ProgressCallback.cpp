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
|* PROGRAM: ProgressCallback.cpp
|*
|* PURPOSE: Callback for displaying progress on current operation
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This is a Nero callback responsible for showing progress of the
// current operation. Here we print the numerical percent and a
// simple progress meter.

BOOL NERO_CALLBACK_ATTR CBurnContext::ProgressCallback (void *pUserData, DWORD dwProgressInPercent)
{
	// print the numerical value

	printf ("%03d%% ", dwProgressInPercent);

	// print the progress meter

	int w = (74*dwProgressInPercent)/100;
	for (int i = w; i > 0; i --)
	{
		printf ("#");
	}
	for (i = 74 - w; i > 0; i --)
	{
		printf (".");
	}

	// carriage return

	printf ("\r");

	fflush (stdout);

	// We simply return the aborted flag

	return s_bAborted;
}

