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
|* PROGRAM: WriteNeroErrorLog.cpp
|*
|* PURPOSE: Write the error log to a file
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This function simply writes the standard nero error log out
// to a file.

void CBurnContext::WriteNeroErrorLog (const PARAMETERS & params)
{
	// If --no_error_log was set, GetWriteErrorLog will return false.

	if (params.GetWriteErrorLog())
	{
		char filename[255];

		// If the --nero_log_timestamp command line parameter
		// was provided we will add year,month,day,hour,minute and
		// seconds information to the file name prefix.

		if (params.GetNeroLogTimestamp())
		{
			char tmpbuf[128];
			struct tm *today;
			time_t ltime;
			time( &ltime );
			today = localtime( &ltime );

			// Use strftime to build a customized time string
			strftime( tmpbuf, 128, "%Y%m%d%H%M%S%", today );
			strcpy(filename, "neroerr");
			strcat(filename, tmpbuf);
			strcat(filename, ".txt");
		}
		else
		{
			// standard name otherwise

			strcpy(filename, "neroerr.txt");
		}

		FILE * fh = fopen (filename, "w");
		if (NULL != fh)
		{
			char * psLog = NeroGetErrorLog ();
			if (NULL != psLog)
			{
				fputs (psLog, fh);
			}

			fclose (fh);
			NeroFreeMem (psLog);
		}
	}
}
