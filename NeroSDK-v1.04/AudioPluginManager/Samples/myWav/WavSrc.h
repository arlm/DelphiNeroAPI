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
|* FILE: WavTgt.h
|*
|* PURPOSE: Declaration file for the wave target class
******************************************************************************/

#ifndef _WAV_SRC_
# define _WAV_SRC_

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000


// CStatus and CAggregatable 
#include "AudioBase.h"

// wave format definitions
#include "WavFormat.h"

// source info dialog
#include "dlg_WavSrcInfo.h"


class CWavSrc : public  CAggregatable,
                public  IURLHolder,
                public  IProcess,
                public  IAudioItem,
                public  IAudioSource,
                public  IAudioRawReader,
                public  ISeekable,
                public  IAudioRawBlockInfo,
                public  ISrcInfoViewerEditor,
                public  IInfoReader,
                public  SWavCommon
{
// Construction/Destruction
public:

  CWavSrc(const char* szURL, IAudioComponent* pCreator, IStatus** ppStatus);
  virtual ~CWavSrc();

// Operations
public:

  AGGREGATABLE_INTERFACE_MAP_BEGIN
    INTERFACE_ENTRY(IURLHolder)
    INTERFACE_ENTRY(IAudioItem)
    INTERFACE_ENTRY(IProcess)
    INTERFACE_ENTRY(IAudioSource)
    INTERFACE_ENTRY(IAudioRawReader)
    INTERFACE_ENTRY(ISeekable)
    INTERFACE_ENTRY(IAudioRawBlockInfo)
    INTERFACE_ENTRY(ISrcInfoViewerEditor)
    INTERFACE_ENTRY(IInfoReader)
  AGGREGATABLE_INTERFACE_MAP_END

                                
  // IURLHolder
  virtual bool SetURL(const char* szURL, IStatus** ppStatus);
  virtual const char* GetURL();
  virtual EURLType GetType();
                                
  // IProcess
  virtual bool Start(IStatus** ppStatus);
  virtual bool End(IStatus** ppStatus);
  virtual bool IsInProcess();
                                
  // IAudioItem
  virtual bool GetCreator(IAudioComponent** pCreator);

  virtual EAuxFlags GetAuxFlags();

  virtual void SetAuxFlags(EAuxFlags flags);
                                
  // IAudioSource
  virtual SWavFormat GetRawFormat();

  // iBufSize must contain the size in bytes of the buffer pointed by pBuf.
  virtual bool RawRead( BYTE* pBuf, int iBufSize, int* piRead,
                        EAudioRawState &state,
                        IStatus** ppStatus);

  // Returns free-form text string about the item.
  virtual const char * GetInfo();

  // Returns the file duration in milliseconds.
  virtual ULONGLONG GetDuration();

  // Returns RAW data length in bytes.
  virtual ULONGLONG GetRawLen();
                                
  // ISeekable
  virtual bool Seek(ULONGLONG pos, IStatus** ppStatus);
  virtual ULONGLONG GetPos();
  virtual ULONGLONG GetBlockSize();
  virtual ULONGLONG GetDataLength();
                            
  // ISrcInfoViewerEditor
  virtual bool GetCallback(ISrcInfoCallback** ppCB);
  virtual void SetCallback(ISrcInfoCallback* pNewCallback);
  virtual bool DoModal(IStatus** ppStatus);
  virtual bool CloseModal(IStatus** ppStatus);
  virtual bool SaveDialogToObject(IStatus** ppStatus);
  virtual bool SaveObjectToFile(IStatus** ppStatus);
  virtual bool CanSaveObjectToFile();
                                
  // IInfoReader
  virtual const char* GetTitle();
  virtual const char* GetArtist();
  virtual const char* GetAlbum();
  virtual const char* GetYear();
  virtual const char* GetGenre();

  virtual HRESULT ReadMMIO();
                              
// others
public:
  virtual PCMWAVEFORMAT GetWavSrcFormat();
  virtual HANDLE GetFileHandle();
  bool    IsOK() { return m_bOK; };

// Data
protected:
  CComPtr<ISrcInfoCallback>   m_pCallback;
  CWavSrcInfoDlg*             m_pAdvInfoDlg;

  // the object
  HANDLE  m_hFile;

  bool    m_bRiffChunk;
  bool    m_bWavChunk;

  DWORD   m_dwDataStart;
          
  // size of RAW in bytes
  DWORD   m_dwDataLen;

  // current position in bytes
  DWORD   m_dwCurPos;

  PCMWAVEFORMAT   m_format;
  ULONGLONG       m_qwDuration;
  int             m_iBlockSize;

  CString         m_csURL;

  // free-form text info
  CString         m_csInfo;

  bool            m_bOK;
  bool            m_bStarted;

  CComPtr<IAudioComponent>  m_pCreator;
};


#endif //_WAV_SRC_