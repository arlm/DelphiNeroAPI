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
|* PROGRAM: CommandVersion,cpp
|*
|* PURPOSE: Obtaining Version Information
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// Print out the version information.

void CBurnContext::CommandVersion (void)
{
	// first print the version of NeroCMD

	// get the full path to the NeroCMD executable
	char* lpszNeroCMDPath=new char[_MAX_PATH];
	DWORD dwTemp=GetModuleFileName(NULL,lpszNeroCMDPath,_MAX_PATH);

	DWORD dwHandle=0;
	DWORD dwVerInfoSize = 0;
	
	if(dwTemp)
	{
		dwVerInfoSize = GetFileVersionInfoSize(lpszNeroCMDPath, &dwHandle);
	}

   	if(dwVerInfoSize)
	{
     	BYTE *lpVerInfo = new BYTE[dwVerInfoSize];

		// Get version info from resource.
		if(GetFileVersionInfo(lpszNeroCMDPath, dwHandle, dwVerInfoSize, lpVerInfo))
		{
			// Get the address to the VS_FIXEDFILEINFO structure data.
			UINT uLen=0;
			VS_FIXEDFILEINFO *lpVS_FixedFileInfo=NULL;
			VerQueryValue(lpVerInfo, "\\", (VOID **) &lpVS_FixedFileInfo, &uLen);

			if(lpVS_FixedFileInfo)
			{
				printf("NeroCmd version %d.%d.%d.%d\n\n",
						 HIWORD(lpVS_FixedFileInfo->dwProductVersionMS),
						 LOWORD(lpVS_FixedFileInfo->dwProductVersionMS),
						 HIWORD(lpVS_FixedFileInfo->dwProductVersionLS),
						 LOWORD(lpVS_FixedFileInfo->dwProductVersionLS));
			}
		}

		delete [] lpVerInfo;
		lpVerInfo=NULL;
	};

	delete [] lpszNeroCMDPath;
	lpszNeroCMDPath=NULL;


	// NeroGetAPIVersionEx retrieves NeroAPI's version number as 4 WORD
	// components.
	// 
	WORD majhi, majlo, minhi, minlo;

	// The call should succeeed always but we must play it safe since
	// it is already declared as returning BOOL.
	// 
	if (NeroGetAPIVersionEx (&majhi, &majlo, &minhi, &minlo, NULL))
	{
		printf ("Nero API version %d.%d.%d.%d\n\n",
				majhi,
				majlo,
				minhi,
				minlo);
	}
	else
	{
		printf ("Could not retrieve version information from NeroAPI!\n");
	}
}

