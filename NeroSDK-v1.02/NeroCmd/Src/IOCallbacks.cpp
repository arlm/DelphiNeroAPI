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
|* PROGRAM: IOCallbacks.cpp
|*
|* PURPOSE: Callbacks that do not deal with files directly
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// These are IO callbacks necessary to perform operations with NeroAPI
// that don't deal with files directly.

// We use them when dealing with the PCM format

// WriteIOCallback will used when PCM data is being read from CD

DWORD NERO_CALLBACK_ATTR CBurnContext::WriteIOCallback (void *pUserData, BYTE *pBuffer, DWORD dwLen)
{
	// NeroAPI provides a file handle and a buffer of data, containing dwLen bytes

	return fwrite (pBuffer, 1, dwLen, (FILE *)pUserData);
}


BOOL NERO_CALLBACK_ATTR CBurnContext::EOFCallback (void *pUserData)
{
	return feof ((FILE *)pUserData);
}


BOOL NERO_CALLBACK_ATTR CBurnContext::ErrorCallback (void *pUserData)
{
	return ferror ((FILE *)pUserData);
}

// ReadIOCallback will be used when PCM is written to CD

DWORD NERO_CALLBACK_ATTR CBurnContext::ReadIOCallback (void *pUserData, BYTE *pBuffer, DWORD dwLen)
{
	// Read dwLen number of bytes from the file into pBuffer

	return fread (pBuffer, 1, dwLen, (FILE *)pUserData);
}
