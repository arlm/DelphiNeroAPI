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
|* FILE: WavTgt.h
|*
|* PURPOSE: Declaration file for the wave target class
******************************************************************************/

#ifndef _WAV_TGT_
# define _WAV_TGT_

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000

// CStatus and CAggregatable 
#include "AudioBase.h"

// wave format definitions
#include "WavFormat.h"


// Internal interfaces

// {48960729-B5C6-48fb-B6A9-AF3E428F9E2B}
EXTERN_GUID(IID_IWavTgtSetDlgData, 
			0x48960729, 0xb5c6, 0x48fb,
			0xb6, 0xa9, 0xaf, 0x3e, 0x42, 0x8f, 0x9e, 0x2b);

struct __declspec(uuid("48960729-B5C6-48fb-B6A9-AF3E428F9E2B"))
                              IWavTgtSetDlgData;

interface IWavTgtSetDlgData : public IUnknown
{
  virtual SWavFormat* GetDlgData()  = 0;
};


// CWavTgt - the wave target class

class CWavTgt : public CAggregatable,
                public IURLHolder,
                public IAudioItem,
                public IProcess,
                public IAudioRawWriter,
                public IWavTgtSetDlgData,
                public IInfoWriter,
                public SWavCommon
{
// Construction/Destruction
public:
  CWavTgt(const SWavFormat &formatSrc, IAudioComponent *pCreator)
  : CAggregatable   (0),
    m_dwWrittenRAWSize  (0),
    m_hFile       (INVALID_HANDLE_VALUE),
    m_flags       (EAuxFlags(0)),
    m_pCreator      (pCreator),
    m_DlgData     (formatSrc),
    m_bEndProcess   (false)
  {};

  virtual ~CWavTgt() {};

// Operations
public:

  AGGREGATABLE_INTERFACE_MAP_BEGIN
    INTERFACE_ENTRY(IAudioItem)
    INTERFACE_ENTRY(IURLHolder)
    INTERFACE_ENTRY(IProcess)
    INTERFACE_ENTRY(IAudioRawWriter)
    INTERFACE_ENTRY(IWavTgtSetDlgData)
    INTERFACE_ENTRY(IInfoWriter)
  AGGREGATABLE_INTERFACE_MAP_END

  // IAudioItem

  virtual bool GetCreator(IAudioComponent** pCreator);

  // Bitmask of auxiliary flags
  virtual EAuxFlags GetAuxFlags();
  virtual void SetAuxFlags(EAuxFlags flags);

  // IURLHolder
  virtual bool SetURL(const char* szURL, IStatus** ppStatus);
  virtual const char* GetURL();
  virtual EURLType GetType();

  // IWavTgtSetDlgData
  SWavFormat* GetDlgData();

  // IProcess
  virtual bool Start(IStatus** ppStatus);
  virtual bool End(IStatus** ppStatus);
  virtual bool IsInProcess();

  // IAudioTarget
  virtual bool RawWrite(BYTE* pData, int iNumberOfBytesToWrite,
              EAudioRawState& state,
              IStatus** ppStatus);

  virtual SWavFormat GetRawFormat();

  // IInfoWriter
  virtual void SetTitle(const char* szTitle);
  virtual void SetArtist(const char* szArtist);
  virtual void SetAlbum(const char* szAlbum);
  virtual void SetYear(const char* szYear);
  virtual void SetGenre(const char* szGenre);

// Data
protected:
  CString                   m_csURL;
  int                       m_dwWrittenRAWSize;
  HANDLE                    m_hFile;
  EAuxFlags                 m_flags;
  CComPtr<IAudioComponent>  m_pCreator;
  SWavFormat                m_DlgData;
  bool                      m_bEndProcess;
};

#endif // _WAV_TGT