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
|* FILE: WavEnum.cpp
|*
|* PURPOSE: Implementation of the factory enumerator class
******************************************************************************/


#include "stdafx.h"
#include "WavEnum.h"

// wave target factory 
#include "WavTgtFactory.h"

// wave source factory
#include "WavSrcFactory.h"

// globals, defined in the main module
extern IAudioPluginMgr* g_pPluginMgr;
extern CWavTgtFactory   g_TgtFactory;
extern CWavSrcFactory   g_SrcFactory;

// {D8E76911-E1D2-4560-8E28-F953D6E1BC56}
EXTERN_GUID(COMPID_WavEnum, 0xd8e76911, 0xe1d2, 0x4560, 0x8e, 0x28, 0xf9, 0x53, 0xd6, 0xe1, 0xbc, 0x56);

// QueryInterface returns either IUnknown, IAudioComponent or IComponentEnum
STDMETHODIMP CWavEnum::QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppObj)
{
  // ppObj must not be NULL
  if(NULL == ppObj)
  {
    ASSERT(FALSE);
    
    return E_INVALIDARG;
  }

  *ppObj = NULL;

  if(IsEqualIID(riid, IID_IUnknown))
    *ppObj = static_cast<IUnknown*>(static_cast<IAudioComponent*>(this));
  else
  if(IsEqualIID(riid, IID_IIdentifiable))
    *ppObj = static_cast<IIdentifiable*>(this);
  else
  if(IsEqualIID(riid, IID_IAudioComponent))
    *ppObj = static_cast<IAudioComponent*>(this);
  else
  if(IsEqualIID(riid, IID_IComponentEnum))
    *ppObj = static_cast<IComponentEnum*>(this);

  if(*ppObj)
    AddRef();

  if (NULL != *ppObj)
  {
    return S_OK;
  }
  else
  {
    return E_NOINTERFACE;
  }
}

// Increase the reference counter and return the number of references
STDMETHODIMP_(ULONG) CWavEnum::AddRef()
{
  InterlockedIncrement(&m_lRef);

  return m_lRef;
}

// Decrease the reference counter and return the number of references
STDMETHODIMP_(ULONG) CWavEnum::Release()
{
  InterlockedDecrement(&m_lRef);

  return m_lRef;
}

void CWavEnum::GetID(GUID *pGUID)
{
   ASSERT(pGUID);
   if(pGUID) 
      memcpy(pGUID, &COMPID_WavEnum, sizeof(GUID));
}

// IAudioComponent
const char* CWavEnum::GetName()
{
  return "wav enum";
}

EAudioComponentType CWavEnum::GetType()
{
  return ACT_ComponentEnumerator;
}

bool CWavEnum::Init(IAudioPluginMgr* pMgr, IStatus** ppStatus)
{
  if(ppStatus)
  {
    *ppStatus = NULL;
  }

  // set the global pointer to the Audio Plugin Manager
  g_pPluginMgr = pMgr;

  return true;
}

bool CWavEnum::Done()
{
  return true;
}

// IComponentEnum

// Return the number of supported components
int CWavEnum::GetCount()
{
  // PCM reader, ADPCM reader and PCM writer
  return 3;
}

// return a pointer to a factory object
bool CWavEnum::GetComponent(int iNum, IAudioComponent** ppComp)
{
  *ppComp = NULL;

  if(iNum == 0)
  {
    *ppComp = &g_SrcFactory;
  }
  else if(iNum == 1)
  {
    *ppComp = &g_TgtFactory;
  }
  else if(iNum == 2)
  {
    // not implemented
    //  *ppComp = &g_ADPCMSrcFactory;
  }

  if(*ppComp)
  {
    (*ppComp)->AddRef();
  }

  if (NULL != *ppComp)
  {
    return true;
  }
  else
  {
    return false;
  }
}

long CWavEnum::GetRefCount()
{
  return m_lRef;
}
