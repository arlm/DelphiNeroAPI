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
|* PROGRAM: ErrorLog.cpp
|*
|* PURPOSE: CErrorLog class implementation
******************************************************************************/


#include "stdafx.h"
#include "ErrorLog.h"


// Constructor

CErrorLog::CErrorLog ()
{
	// Set the file handle to NULL.
	// 
	m_fh = NULL;
}


// Destructor

CErrorLog::~CErrorLog ()
{
	// Make sure the file is closed and the handle is released.
	// 
	if (m_fh)
	{
		fclose (m_fh);
	}
}

// Open logfile

bool CErrorLog::Open (LPCSTR psFilename)
{
	// If the filename is supplied, try and open it.
	// 
	if (NULL != psFilename)
	{
		m_fh = fopen (psFilename, "wt");
	}

	return m_fh != NULL;
}

// Add one line to the logfile

int CErrorLog::printf (const char * format, ...)
{
	va_list args;
	
	va_start (args, format);

	if (NULL != m_fh)
	{
		vfprintf (m_fh, format, args);
	}

	int ret = vprintf (format, args);

	va_end (args);

	return ret;
}
