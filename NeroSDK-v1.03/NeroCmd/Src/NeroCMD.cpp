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
|* PROGRAM: NeroCMD.cpp
|*
|* PURPOSE: Main file of the application
******************************************************************************/



#include "stdafx.h"
#include "getopt.h"
#include "BurnContext.h"


// The one and only main() function

int main(int argc, char* argv[])
{
	PARAMETERS params;
	EXITCODE code;
	CBurnContext s_BurnContext(&params);

	// Get the parameters from the command line.

	if (!getopt (params, --argc, ++argv))
	{
		return s_BurnContext.Exit (EXITCODE_BAD_USAGE);
	}

	// Open the log file. If the log file name was not specified
	// no file will be be openned.

	s_BurnContext.OpenLogFile (params.GetErrorLogName());

	// Load the NEROAPI.DLL.

	code = s_BurnContext.NeroLoad ();
	if (code != EXITCODE_OK)
	{
		return s_BurnContext.Exit (code);
	}

	if (COMMAND_VERSION == params.GetCommand())
	{
		// Display version information.

		s_BurnContext.CommandVersion ();
		code = EXITCODE_OK;
	}
	else
	{
		// Initialize NeroAPI.

		code = s_BurnContext.InitNeroAPI ();
		if (code == EXITCODE_OK)
		{
			if (params.GetCommand () == COMMAND_IMAGE_INFO)
			{
				code = s_BurnContext.CommandImageInfo (params);
			}
			else
			{
				// Get available drives.

				code = s_BurnContext.GetAvailableDrives (params);
				if (code == EXITCODE_OK)
				{
					switch (params.GetCommand())
					{
					case COMMAND_LISTDRIVES:
						// Just give a nice listing of all available drives.

						code = s_BurnContext.CommandListDrives (params);
						break;

					case COMMAND_LISTFORMATS:
						code = s_BurnContext.CommandListFormats (params);
						break;

					case COMMAND_INTERNAL:
						// This command in strictly for INTERNAL use!!!
						// 
						code = s_BurnContext.CommandInternal (params);
						break;

					default:
						// Open the selected device. We didn't need this unitl now.

						code = s_BurnContext.OpenDevice (params);
						if (code == EXITCODE_OK)
						{
							switch (params.GetCommand())
							{
								case COMMAND_ERASE:
									code = s_BurnContext.CommandErase (params);
									break;

								case COMMAND_WRITE:
									code = s_BurnContext.CommandWrite (params);
									break;

								case COMMAND_CDINFO:
									code = s_BurnContext.CommandCDInfo (params);
									break;

								case COMMAND_READ:
									code = s_BurnContext.CommandRead (params);
									break;

								case COMMAND_EJECT:
								case COMMAND_LOAD:
									code = s_BurnContext.CommandEject (params);
									break;

								case COMMAND_DRIVE_INFO:
									code = s_BurnContext.CommandDriveInfo (params);
									break;

								case COMMAND_GET_SPEEDS:
									code = s_BurnContext.CommandGetSpeeds (params);
									break;

								case COMMAND_INTERNAL:
									// This command is strictly for INTERNAL (testing) use!!!
									//
									code = s_BurnContext.CommandInternal (params);
									break;

								default:

									// This should never happen!

									_ASSERTE (FALSE);
									code = EXITCODE_INTERNAL_ERROR;
							}
						}
					}
				}
			}
		}
	}

	// Print the user interaction error, if any.
	// 
	s_BurnContext.PrintUserInteractionMessage ();

	// Write Nero error log.

	s_BurnContext.WriteNeroErrorLog (params);

	// Print the exit code to the error log.
	// This is good for checking success of batch mode runs.

	s_BurnContext.PrintLogLine(CExitCode (code).GetTextualExitCode());

	return s_BurnContext.Exit (code);
}
