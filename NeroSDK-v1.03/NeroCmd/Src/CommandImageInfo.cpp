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
|* PROGRAM: CommandImageInfo.cpp
|*
|* PURPOSE: Retrieve image information
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function performs execution of a image info command.

CExitCode CBurnContext::CommandImageInfo (const PARAMETERS & params)
{
	// Retrieve a pointer to a NERO_CD_INFO structure for the supplied
	// image filename.
	// NULL will be returned if error occurrs. 
	// The allocated memory for the structure has to be freed by using  NeroFreeMem().
	// This will be performed by the destructor of CBurnContext.

	m_NeroCDInfo = NeroGetDiscImageInfo (params.GetImageInfoFileName (), NULL);
	if (NULL == m_NeroCDInfo)
	{
		return EXITCODE_ERROR_GETTING_CD_INFO;
	}

	return DisplayCDInfo ();
}
