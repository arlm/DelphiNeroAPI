/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* PROJECT: Nero Plugin Manager Example
|*
|* FILE: myWav.cpp
|*
|* PURPOSE: Global variables and implementation of the published DLL functions.
******************************************************************************/


#include "stdafx.h"
#include "myWav.h"

// component enumerator
#include "WavEnum.h"

// wave target factory 
#include "WavTgtFactory.h"

// wave source factory
#include "WavSrcFactory.h"

#ifdef _DEBUG
# define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CWavApp, CWinApp)
	//{{AFX_MSG_MAP(CWavApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CWavApp::CWavApp() {}

CWavApp theApp;


// Global data

// reference to the Audio Plugin Manager
// this pointer will be provided during initialization by the 
// Audio Plugin Manager itself.
IAudioPluginMgr* g_pPluginMgr = NULL;


// instances of the component enumerator and the factories
// will be kept alive until the DLL is unloaded
CWavEnum g_enum;  
CWavTgtFactory g_TgtFactory;
CWavSrcFactory g_SrcFactory;


// The Audio Plugin Manager will call this function during initialization
bool NERO_PLUGIN_GetPrimaryAudioObject(IAudioComponent** pAC)
{
  // the pointer must be different from NULL
  ASSERT(pAC);

  if(NULL == pAC)
  {
    return false;
  }

  // our primary audio object is the component enumerator
  *pAC = &g_enum;

  if(NULL != *pAC)
  {
    (*pAC)->AddRef();
  }

  return true;
}

// This function will be called when the Nero application is closed
bool NERO_PLUGIN_ReadyToFinish()
{
  return  (g_TgtFactory.GetRefCount() <= 1) && (g_SrcFactory.GetRefCount() <= 1) &&
        (g_enum.GetRefCount() <= 1);
}
