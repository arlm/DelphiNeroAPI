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
|* PROGRAM: getopt.h
|*
|* PURPOSE: COMMAND and BURNTYPE enumerations
|*          PARAMETERS and CSimpleStringArray class declarations
******************************************************************************/


#ifndef _GETOPT_H_
#define _GETOPT_H_

#include "parameters.h"

// Decoding the argument list.

bool getopt (PARAMETERS & params, int argc, char ** argv);

#endif
