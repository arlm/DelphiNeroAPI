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
|* PROGRAM: AddLogLineCallback.cpp
|*
|* PURPOSE: AddLogLine callback implementation
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// This is a Nero callback. The text may cointain several lines
// separated by newline characters: NL(LF) '\n' and is null character terminated.

void NERO_CALLBACK_ATTR CBurnContext::AddLogLine (void *pUserData, NERO_TEXT_TYPE type, const char *text)
{
	char * header;
	const char *start;

	// Evaluate the type of log entry that should be added
	// and assign the line header accordingly.
	// The line header will be attached to every output line.

	switch (type)
	{
		case NERO_TEXT_INFO:        // informative text
			header = "[i]";
			break;
		case NERO_TEXT_STOP:        // some operation stopped prematurely
			header = "[#]";
			break;
		case NERO_TEXT_EXCLAMATION: // important information 
			header = "[!]";
			break;
		case NERO_TEXT_QUESTION:    // a question which requires an answer
			header = "[?]";
			break;
		case NERO_TEXT_DRIVE:		// a message concerning a CD-ROM drive or recorder
			header = "[-]";
			break;
		default:
			header = "";
	}

	// Step through the message text, considering newline characters
	// and inserting a line break every 76 characters if the line is longer

	start = text;
	while (*start)
	{
		// search for newline NL(LF) and set a pointer to the 
		// next newline character. If no newline is found end becomes NULL.

		char *end = strchr (start, '\n');

		// Determine the length of the string part to be printed.
		// If a newline character was found the length is the difference between end and start
		// Otherwise there is no newline between the current position of start in the string
		// and the end of the string. So the length can be determined by a simple call to strlen.

		int len;
		if (NULL != end)
		{
			len = end - start;
		}
		else
		{
			len = strlen (start);
		}

		// We also make sure that no more than 76 characters are printed
		// no matter how long the current string part really is.

		if (len > 76)
		{
			len = 76;
		}

		// The formatted output:

		printf ("%-4.4s%-76.76s\n", header, start);

		// Shift the start pointer right by the amount of bytes just printed.

		start += len;

		// If newline characters were found start has to be set to the next character
		// If end contains NULL this means that either no newlines were found or
		// the end of the string has been reached.


		if (NULL != end)
		{
			++start;
		}
	}
}
