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
|* FILE: NeroPluginUtil.h
|*
|* PURPOSE: Definitions of auxiliary helper functions for Nero plugins
******************************************************************************/

#ifndef _NERO_PLUGIN_UTIL_
#define _NERO_PLUGIN_UTIL_

//////////////////////////////////////////////////////////// Registry helpers //

// If szGroup is not null, additional subgroup is assumed, this parameter can
// be NULL for no additional groups indication.
bool	reg_SetPluginParam(const char *szVendor, const char *szProduct,
							const char *szPlugin, const char *szGroup,
							const char *szParam, DWORD dwValue);

bool	reg_GetPluginParam(const char *szVendor, const char *szProduct,
							const char *szPlugin, const char *szGroup,
							const char *szParam, DWORD &dwValue);

bool	reg_SetPluginParam(const char *szVendor, const char *szProduct,
							const char *szPlugin, const char *szGroup,
							const char *szParam, const char *szValue);

CString	reg_GetPluginParam(const char *szVendor, const char *szProduct,
							const char *szPlugin, const char *szGroup,
							const char *szParam);

//////////////////////////////////////////////////////////////// File helpers //

bool	file_DoesExist(const char *szFile);
DWORD	file_GetSize(const char *szFile);

// Returns the time of last access to the file, which is, actually, the time
// of last reading/writing to the file.
bool	file_GetTime(const char *szFile, CTime &time);

////////////////////////////////////////////////////////////////////// Others //

#include "AudioErrors.h"

// Returns true if the URL points to a local file.
bool	IsURLLocal(const char *szURL);

EAudioError MapSysErrorToAudio(DWORD dwErr);

#endif // _NERO_PLUGIN_UTIL_