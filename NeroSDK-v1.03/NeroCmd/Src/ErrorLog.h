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
|* PROGRAM: ErrorLog.h
|*
|* PURPOSE: CErrorLog class declaration
******************************************************************************/


#ifndef _ERROR_LOG_H_
#define _ERROR_LOG_H_

class CErrorLog {
protected:
	FILE * m_fh;

public:
	CErrorLog ();
	~CErrorLog ();

	bool Open (LPCSTR psFilename);
	int printf (const char * format, ...);

};

#endif
