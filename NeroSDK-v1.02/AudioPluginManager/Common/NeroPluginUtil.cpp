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
|* FILE: NeroPluginUtil.cpp
|*
|* PURPOSE: Implementation of auxiliary helper functions for Nero plugins
******************************************************************************/

#include "stdafx.h"
#include "NeroPluginUtil.h"
#include "afxinet.h"		// URL parsing

bool reg_SetPluginParam(const char *szVendor, const char *szProduct,
						const char *szPlugin, const char *szGroup,
						const char *szParam, DWORD dwValue)
{
	if(!(szVendor && szProduct && szPlugin && szParam))
	{
		ASSERT(FALSE);

		return false;
	}

	HKEY hKey = NULL;

	if(!szGroup)
		szGroup = "";

	try
	{
		CString csSubKey;
		csSubKey.Format("Software\\%s\\%s\\%s\\%s",
						szVendor, szProduct, szPlugin, szGroup);

		if(RegOpenKey(HKEY_CURRENT_USER, csSubKey, &hKey) != ERROR_SUCCESS &&
			RegCreateKey(HKEY_CURRENT_USER, csSubKey, &hKey) != ERROR_SUCCESS)
				throw false;

		if(RegSetValueEx(hKey, szParam, NULL, REG_DWORD,
							(BYTE*)&dwValue, sizeof(DWORD)) != ERROR_SUCCESS)
			throw false;

		throw true;
	}
	catch(bool b)
	{
		if(hKey)
			RegCloseKey(hKey);

		return b;
	}
}

bool reg_GetPluginParam(const char *szVendor, const char *szProduct,
						const char *szPlugin, const char *szGroup,
						const char *szParam, DWORD &dwValue)
{
	if(!(szVendor && szProduct && szPlugin && szParam))
	{
		ASSERT(FALSE);

		return false;
	}

	HKEY hKey = NULL;

	if(!szGroup)
		szGroup = "";

	try
	{
		CString csSubKey;
		csSubKey.Format("Software\\%s\\%s\\%s\\%s",
						szVendor, szProduct, szPlugin, szGroup);

		if(RegOpenKey(HKEY_CURRENT_USER, csSubKey, &hKey) != ERROR_SUCCESS)
			throw false;

		DWORD	dwType	= 0,
				dwSize	= sizeof(DWORD);

		if(RegQueryValueEx(hKey, szParam, NULL, &dwType,
							(BYTE*)&dwValue, &dwSize) != ERROR_SUCCESS)
			throw false;

		throw true;
	}
	catch(bool b)
	{
		if(hKey)
			RegCloseKey(hKey);

		return b;
	}
}

bool reg_SetPluginParam(const char *szVendor, const char *szProduct,
						const char *szPlugin, const char *szGroup,
						const char *szParam, const char *szValue)
{
	if(!(szVendor && szProduct && szPlugin && szParam))
	{
		ASSERT(FALSE);

		return false;
	}

	HKEY hKey = NULL;

	if(!szGroup)
		szGroup = "";

	try
	{
		CString csSubKey;
		csSubKey.Format("Software\\%s\\%s\\%s\\%s",
						szVendor, szProduct, szPlugin, szGroup);

		if(RegOpenKey(HKEY_CURRENT_USER, csSubKey, &hKey) != ERROR_SUCCESS &&
			RegCreateKey(HKEY_CURRENT_USER, csSubKey, &hKey) != ERROR_SUCCESS)
				throw false;

		if(RegSetValueEx(hKey, szParam, NULL, REG_SZ,
							(BYTE*)szValue,
							strlen(szValue) + 1) != ERROR_SUCCESS)
			throw false;

		throw true;
	}
	catch(bool b)
	{
		if(hKey)
			RegCloseKey(hKey);

		return b;
	}
}

CString reg_GetPluginParam(const char *szVendor, const char *szProduct,
							const char *szPlugin, const char *szGroup,
							const char *szParam)
{
	CString csValue;

	if(!(szVendor && szProduct && szPlugin && szParam))
	{
		ASSERT(FALSE);

		return csValue;
	}

	HKEY hKey = NULL;

	if(!szGroup)
		szGroup = "";

	try
	{
		CString csSubKey;
		csSubKey.Format("Software\\%s\\%s\\%s\\%s",
						szVendor, szProduct, szPlugin, szGroup);

		if(RegOpenKey(HKEY_CURRENT_USER, csSubKey, &hKey) != ERROR_SUCCESS)
			throw false;

		char szBuf[1000];

		DWORD	dwType	= 0,
				dwSize	= sizeof(szBuf);

		if(!(RegQueryValueEx(hKey, szParam, NULL, &dwType,
							(BYTE*)szBuf, &dwSize) == ERROR_SUCCESS &&
				dwType == REG_SZ))
			throw false;

		csValue = szBuf;

		throw true;
	}
	catch(bool )
	{
		if(hKey)
			RegCloseKey(hKey);
	}

	return csValue;
}

// Returns true if the URL points to a local file.
bool IsURLLocal(const char *szURL)
{
	DWORD			dwServiceType = 0;
	INTERNET_PORT	port;

	CString			csServer,
					csObject;

	return (AfxParseURL(szURL, dwServiceType, csServer, csObject, port) &&
			(dwServiceType == AFX_INET_SERVICE_FILE));
}

bool file_DoesExist(const char *szFile)
{
	HANDLE hExist = CreateFile(szFile,
								0,
								FILE_SHARE_DELETE|FILE_SHARE_READ|
									FILE_SHARE_WRITE,
								NULL,
								OPEN_EXISTING,
								0,
								NULL);

	bool bExist = (hExist != INVALID_HANDLE_VALUE);

	if(bExist)
		CloseHandle(hExist);

	return bExist;
}

bool file_GetTime(const char *szFile, CTime &time)
{
	HANDLE hFile = CreateFile(szFile,
								0,
								FILE_SHARE_DELETE|FILE_SHARE_READ|
									FILE_SHARE_WRITE,
								NULL,
								OPEN_EXISTING,
								0,
								NULL);

	if(hFile == INVALID_HANDLE_VALUE)
		return false;

	FILETIME	ftCreation,
				ftLastAccess,
				ftLastTime;

	BOOL bRet = GetFileTime(hFile, &ftCreation, &ftLastAccess, &ftLastTime);

	time = ftLastAccess;

	CloseHandle(hFile);

	return (bRet? true: false);
}

DWORD file_GetSize(const char *szFile)
{
	HANDLE hFile = CreateFile(szFile,
								0,
								FILE_SHARE_DELETE|FILE_SHARE_READ|
									FILE_SHARE_WRITE,
								NULL,
								OPEN_EXISTING,
								0,
								NULL);

	if(hFile == INVALID_HANDLE_VALUE)
		return 0;

	DWORD dwSize = GetFileSize(hFile, NULL);

	CloseHandle(hFile);

	return dwSize;
}
