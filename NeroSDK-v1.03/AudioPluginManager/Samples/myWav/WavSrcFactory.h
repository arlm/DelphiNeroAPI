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
|* FILE: WavSrcFactory.h
|*
|* PURPOSE: Declaration file for the wave sourc factory class.
******************************************************************************/

#ifndef _WAV_SRC_FACTORY_
# define _WAV_SRC_FACTORY_

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000


// CStatus and CAggregatable 
#include "AudioBase.h"


class CWavSrcFactory :  public IIdentifiable, 
                        public CAggregatable,
                        public IAudioComponent,
                        public IURLAudioSourceFactory,
                        public IExtEnum,
						public IVendorInfo
{
// Construction/Destruction
public:
  CWavSrcFactory()
  : CAggregatable (AGGFLAG_NODELETE)
  {}

  virtual ~CWavSrcFactory() {};

// Operations
public:
  virtual long GetRefCount();

  AGGREGATABLE_INTERFACE_MAP_BEGIN
    INTERFACE_ENTRY(IIdentifiable)
    INTERFACE_ENTRY(IAudioComponent)
    INTERFACE_ENTRY(IURLAudioSourceFactory)
    INTERFACE_ENTRY(IExtEnum)
	INTERFACE_ENTRY(IVendorInfo)
  AGGREGATABLE_INTERFACE_MAP_END

  // IIdentifiable
  void GetID(GUID *pGUID);

  // IAudioComponent
  virtual const char* GetName();
  virtual EAudioComponentType GetType();
  virtual bool Init(IAudioPluginMgr* pMgr, IStatus** ppStatus);
  virtual bool Done();
  virtual bool
  Open( const char*   szURL,
        IUnknown**    ppSrc,
        EAuxFlags     flagsInclude,
        EAuxFlags     flagsExclude,
        IStatus**     ppStatus);

  virtual EAuxFlags GetAuxFlags();

  virtual EURLType GetSupportedURLTypes();
  
  // IExtEnum
  int GetCount();

  // The returned value can't be stored for later use.
  // The application must copy it.
  const char* GetExt(int iNum);
  
  // IVendorInfo
  const char * GetVendorName();
  bool CanDisplayAboutBox();
  void DisplayAboutBox();
};


#endif // _WAV_SRC_FACTORY_