/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / AudioPluginManager
|*
|* FILE: logfile.cpp
|*
|* PURPOSE: CLogFile implementation for debugging purposes
******************************************************************************/

#include "stdafx.h"
#include "LogFile.h"

#ifndef WIN64

void CLogFile::SetFileName(const char *szFilePath)
{
	m_csFilePath = szFilePath;
}

void CLogFile::operator<<(const char *szString)
{
	// We need to open the file, write something and close it immediately
	// because nobody know what will happen after this function.
	CStdioFile file;

	// Can we open the existing file?
	if(!file.Open(m_csFilePath, CFile::modeWrite) &&
			// We couldn't open it, can we create it?
			!file.Open(m_csFilePath, CFile::modeWrite|CFile::modeCreate))
		return;

	// We should move to the end of the file.
	file.Seek(0, CFile::end);

//	file.WriteString(">>>\n");

	file.WriteString(szString);
	file.WriteString("\n");

	file.Flush();

	file.Close();
}

#endif // WIN64
