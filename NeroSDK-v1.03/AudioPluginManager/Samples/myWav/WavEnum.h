/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* PROJECT: Nero Plugin Manager Example
|*
|* FILE: WavEnum.h
|*
|* PURPOSE: Declaration file for the factory enumerator class.
******************************************************************************/

#ifndef _WAV_ENUM_
# define _WAV_ENUM_

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000


// CStatus and CAggregatable 
#include "AudioBase.h"


class CWavEnum : public IIdentifiable, public IAudioComponent, public IComponentEnum
{
// Construction/Destruction
public:
  CWavEnum() : m_lRef(0) {};
  virtual ~CWavEnum() {}

// Operations
public:
  virtual long GetRefCount();

  // IUnknown
  STDMETHODIMP QueryInterface(REFIID riid, void __RPC_FAR* __RPC_FAR* ppObj);
  STDMETHODIMP_(ULONG) AddRef();
  STDMETHODIMP_(ULONG) Release();

  // IIdentifiable
  virtual void GetID(GUID *pGUID);

  // IAudioComponent
  virtual const char* GetName();
  virtual EAudioComponentType GetType();
  virtual bool Init(IAudioPluginMgr* pMgr, IStatus** ppStatus);
  virtual bool Done();

  // IComponentEnum
  virtual int GetCount();
  virtual bool GetComponent(int iNum, IAudioComponent** ppComp);

// Data
protected:
  long    m_lRef;
};


#endif // _WAV_ENUM_