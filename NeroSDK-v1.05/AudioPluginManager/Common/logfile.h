/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / AudioPluginManager
|*
|* FILE: logfile.h
|*
|* PURPOSE: Definition of logfile for debugging purposes
******************************************************************************/

#ifndef _LOG_FILE_
#	define _LOG_FILE_

#ifndef WIN64

class CLogFile
{
// Construction/Destruction
public:

// Operations
public:
	void	SetFileName(const char *szFilePath);
	void	operator<<(const char *szString);

protected:

// Data
protected:
	CString	m_csFilePath;
};

#endif // WIN64

#endif // _LOG_FILE_
