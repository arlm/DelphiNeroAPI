/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroAPI
|*
|* PROGRAM: NeroCBUIGlue.h
|*
|* PURPOSE: Methods for connecting to NeroCBUI
******************************************************************************/
#ifndef __NEROCBUIGLUE__
#define __NEROCBUIGLUE__

#include <unknwn.h>

#ifdef  __cplusplus
extern "C" {
#endif

/*
 *	get an instance of the NeroAPI compatibility manager to be passed
 *  to NeroCBUI with IInitSettings::put_CompatibilityMgr
 */ 
IUnknown* __cdecl NeroCBUIGlueGetCompatibilityMgr(HMODULE hNeroAPI, void *reserved);

#ifdef  __cplusplus
}
#endif


#endif /* __NEROAPIGLUE__ */

