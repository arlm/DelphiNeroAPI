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
|* FILE: WavTgtFactory.h
|*
|* PURPOSE: Declaration file for the wave target factory class.
******************************************************************************/

#ifndef _WAV_TGT_FACTORY_
# define _WAV_TGT_FACTORY_

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000


// CStatus and CAggregatable 
#include "AudioBase.h"


class CWavTgtFactory :  public  IIdentifiable,
                        public  CAggregatable,
                        public  IAudioComponent,
                        IURLAudioTargetFactory,
                        IExtEnum
{
// Construction/Destruction
public:
  CWavTgtFactory()
  : CAggregatable (AGGFLAG_NODELETE)
  {}

  virtual ~CWavTgtFactory() {};

// Operations
public:
  virtual long GetRefCount();

  AGGREGATABLE_INTERFACE_MAP_BEGIN
    INTERFACE_ENTRY(IIdentifiable)
    INTERFACE_ENTRY(IAudioComponent)
    INTERFACE_ENTRY(IURLAudioTargetFactory)
    INTERFACE_ENTRY(IExtEnum)
  AGGREGATABLE_INTERFACE_MAP_END

  // IIdentifiable
  void GetID(GUID *pGUID);

  // IAudioComponent
  virtual const char* GetName();
  virtual EAudioComponentType GetType();
  virtual bool Init(IAudioPluginMgr* pMgr, IStatus** ppStatus);
  virtual bool Done();

  // IURLAudioTargetFactory
  virtual bool CreateURLAudioTarget(IUnknown** ppTgt,
                                    const SWavFormat& formatSrc,
                                    IStatus** ppStatus);

  virtual bool EditSettings(IUnknown** ppTgt, int iCount);

  // Application should first call this function to determine if this
  // factory can edit settings for items.
  virtual bool CanEditSettings();
  virtual EURLType GetSupportedURLTypes();
  
  // IExtEnum
  int GetCount();

  // The returned value can't be stored for later use.
  // The application must copy it.
  const char* GetExt(int iNum);
};


#endif _WAV_TGT_FACTORY