/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroAPI
|*
|* PROGRAM: NeroAPIGlue.h
|*
|* PURPOSE: Functions for connecting to NeroAPI
******************************************************************************/


#ifndef __NEROAPIGLUE__
#define __NEROAPIGLUE__

#ifdef  __cplusplus
extern "C" {
#endif

/*
// All functions in NeroAPI.h are implemented here, too:
*/

#include "NeroAPI.h"

#define USING_NEROSDK

/*
// This function has to be called first.
*/

BOOL NADLL_ATTR NeroAPIGlueConnect (void *reserved);

/*
// This one cleans up after using the glue code.
*/
void NADLL_ATTR NeroAPIGlueDone (void);


#ifdef  __cplusplus
}
#endif


#endif /* __NEROAPIGLUE__ */

