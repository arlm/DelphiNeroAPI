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
|* FILE: WavSrcFactory.cpp
|*
|* PURPOSE: Implementation of the wave source factory
******************************************************************************/


#include "stdafx.h"

#include "WavSrcFactory.h"

#include "WavSrc.h"


EXTERN_GUID(COMPID_SrcFactory, 0x459215ca, 0x50f5, 0x42cc, 0xbf, 0x51, 0x84, 0x38, 0x11, 0x9d, 0xee, 0x6c);

extern IAudioPluginMgr* g_pPluginMgr;


void CWavSrcFactory::GetID(GUID *pGUID)
{
	ASSERT(pGUID);
	if(pGUID)
	memcpy(pGUID, &COMPID_SrcFactory, sizeof(GUID));
}

const char* CWavSrcFactory::GetName()
{
  return "PCM Wav file";
}

EAudioComponentType CWavSrcFactory::GetType()
{
  return ACT_AudioURLSourceFactory;
}

bool CWavSrcFactory::Init(IAudioPluginMgr* pMgr, IStatus** ppStatus)
{
  if(NULL != ppStatus)
  {
    *ppStatus = NULL;
  }

  if(NULL != g_pPluginMgr)
  {
    ASSERT(g_pPluginMgr == pMgr);
  }
  else
  {
    g_pPluginMgr = pMgr;
  }

  // success
  return true;
}

bool CWavSrcFactory::Done()
{
  return true;
}

EAuxFlags CWavSrcFactory::GetAuxFlags()
{
  return SRC_FLAGS;
}

EURLType CWavSrcFactory::GetSupportedURLTypes()
{
  return URL_LocalFile;
}

// IExtEnum implementation
int CWavSrcFactory::GetCount()
{ 
  return 2;
}

// The returned value can't be stored for later use.
// The application must copy it.
const char* CWavSrcFactory::GetExt(int iNum)
{
  if(0 == iNum)
  {
    return "wav";
  }
  else if(1 == iNum)
  {
    return "wave";
  }

  ASSERT(FALSE);

  return NULL;
}

bool CWavSrcFactory::Open(const char* szURL,
                          IUnknown**  ppSrc,
                          EAuxFlags flagsInclude,
                          EAuxFlags flagsExclude,
                          IStatus** ppStatus)
{
  if(ppStatus)
  {
    *ppStatus = NULL;
  }

  CWavSrc* pSrc = new CWavSrc(szURL, (IAudioComponent*)this, ppStatus);

  bool bOK = pSrc->IsOK();

  if(bOK)
  {
    *ppSrc = static_cast<IAggregatable*>(pSrc);

    (*ppSrc)->AddRef();
  }
  else
  {
    delete pSrc;

    *ppSrc = NULL;
  }

  return bOK;
}

long CWavSrcFactory::GetRefCount()
{
  return m_lRef;
}

const char *CWavSrcFactory::GetVendorName()
{
  return "Example Vendor";
}

bool CWavSrcFactory::CanDisplayAboutBox()
{
  return true;
}

void CWavSrcFactory::DisplayAboutBox()
{
  AfxMessageBox("Ahead Software Example PCM WAV plugin.");
}