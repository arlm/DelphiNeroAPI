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
|* FILE: WavSrc.cpp
|*
|* PURPOSE: Implementation of the wave source class
******************************************************************************/


#include "stdafx.h"
#include "WavSrc.h"

// helper functions for file access
#include "FileHelper.h"

// IURLHolder implementation

bool CWavSrc::SetURL(const char* szURL, IStatus** ppStatus)
{
  RETURN_ERROR(AE_CallNotImplemented);
}

const char* CWavSrc::GetURL()
{
  return m_csURL;
}

EURLType CWavSrc::GetType()
{
  return URL_LocalFile;
}

// IProcess implementation

bool CWavSrc::Start(IStatus** ppStatus)
{
  if(NULL != ppStatus)
  {
    *ppStatus = NULL;
  }

  m_dwCurPos = 0;

  if(SetFilePointer(m_hFile, m_dwDataStart, 0, FILE_BEGIN) !=
                              m_dwDataStart)
  {
    RETURN_ERROR(GetLastError());
  }

  m_bStarted = true;

  return true;
}

bool CWavSrc::End(IStatus** ppStatus)
{
  if(NULL != ppStatus)
  {
    *ppStatus = NULL;
  }

  m_bStarted = false;

  return true;
}

bool CWavSrc::IsInProcess()
{
  return m_bStarted;
}

// IAudioItem implementation

bool CWavSrc::GetCreator(IAudioComponent** pCreator)
{
  if(!pCreator)
  {
    ASSERT(FALSE);
    return false;
  }

  *pCreator = m_pCreator;

  (*pCreator)->AddRef();

  return true;
}

EAuxFlags CWavSrc::GetAuxFlags()
{
  return SRC_FLAGS;
}

void CWavSrc::SetAuxFlags(EAuxFlags flags)
{
  // Nothing to do here
}

// IAudioSource implementation

SWavFormat CWavSrc::GetRawFormat()
{
  SWavFormat format;

  format.m_iSamplesPerSecond= m_format.wf.nSamplesPerSec;
  format.m_iBitsPerSample       = m_format.wBitsPerSample;
  format.m_iChannels            = m_format.wf.nChannels;

  return format;
}

// iBufSize must contain the size in bytes of the buffer pointed by pBuf.

bool CWavSrc::RawRead(BYTE* pBuf, int iBufSize, int* piRead,
            EAudioRawState& state,
            IStatus** ppStatus)
{
  if(!(pBuf && iBufSize && piRead))
  {
    RETURN_ERROR(AE_InvalidParameter);
  }

  if(NULL != ppStatus)
  {
    *ppStatus = NULL;
  }

  state = ERS_None;

  if(m_dwCurPos >= m_dwDataLen)
  {
    state = ERS_EndOfFile;

    RETURN_ERROR(AE_EOF);
  }

  DWORD dwRead = 0;

  DWORD dwRemaining = m_dwDataLen - m_dwCurPos;

  if(iBufSize > (int)dwRemaining)
  {
    iBufSize = dwRemaining;
    state = ERS_EndOfFile;
  }

  if (!(ReadFile(m_hFile, pBuf, iBufSize, (DWORD*)piRead, NULL) && *piRead))
  {

    // That means that the file is over or
    // something is wrong, in any case
    // stopping the process

    m_dwCurPos = m_dwDataLen;
  }
  else
  {
    m_dwCurPos += *piRead;
  }

  return true;
}

// Returns free-form text string about the item.

const char* CWavSrc::GetInfo()
{
  if(m_csInfo.IsEmpty())
  {
    m_csInfo.Format("PCM Wav file. Format: %d,  Channels: %d,"
              " Sample rate: %d, Bits per sample: %d",
              m_format.wf.wFormatTag,
              m_format.wf.nChannels,
              m_format.wf.nSamplesPerSec,
              m_format.wBitsPerSample);

    CString* pcsStrings[] =
    { &m_csArtist, &m_csTitle, &m_csCopyright, &m_csDate, &m_csComments };

    char* szarNames[5] =
    { "Artist", "Title", "Copyright", "Date", "Comments" };

    for(int i = 0; i < 5; i++)
    {
      CString* pcs = pcsStrings[i];

      if (pcs->IsEmpty())
        continue;

      m_csInfo += ",\r\n";

      CString csTemp;
      csTemp.Format("%s: %s", szarNames[i], (LPCTSTR)(*pcs));

      m_csInfo += csTemp;
    }
  }

  return m_csInfo;
}

// Returns the file duration in milliseconds.

ULONGLONG CWavSrc::GetDuration()
{
  return m_qwDuration;
}

// Returns RAW data length in bytes.

ULONGLONG CWavSrc::GetRawLen()
{
  return m_dwDataLen;
}

// ISeekable implementation

bool CWavSrc::Seek(ULONGLONG pos, IStatus** ppStatus)
{
  if(NULL == ppStatus)
  {
    *ppStatus = NULL;
  }

  DWORD dwLastPos = SetFilePointer(m_hFile, 0, 0, FILE_CURRENT);
  DWORD dwNewPos  = (DWORD)(m_dwDataStart + pos * m_iBlockSize);

  bool bRetCode = false;

  if(SetFilePointer(m_hFile, dwNewPos, 0, FILE_BEGIN) != dwNewPos)
  {
    SetFilePointer(m_hFile, dwLastPos, 0, FILE_BEGIN);
  }
  else
  {
    m_dwCurPos = (DWORD)(pos * m_iBlockSize);

    bRetCode = true;
  }

  if((false == bRetCode) && (NULL != ppStatus))
  {
    *ppStatus = new CStatus(AE_SeekFailed);
  }

  return bRetCode;
}

ULONGLONG CWavSrc::GetPos()
{
  return (m_dwCurPos / m_iBlockSize);
}

ULONGLONG CWavSrc::GetBlockSize()
{
  return m_iBlockSize;
}

ULONGLONG CWavSrc::GetDataLength()
{
  return (m_dwDataLen / m_iBlockSize);
}

// ISrcInfoViewerEditor implementation

bool CWavSrc::GetCallback(ISrcInfoCallback** ppCB)
{
  if(NULL == ppCB)
  {
    ASSERT(FALSE);
    return false;
  }

  *ppCB = m_pCallback;

  if(NULL != *ppCB)
  {
    (*ppCB)->AddRef();
  }

  return true;
}

void CWavSrc::SetCallback(ISrcInfoCallback* pNewCallback)
{
  m_pCallback = pNewCallback;
}

bool CWavSrc::DoModal(IStatus** ppStatus)
{
  CWavSrcInfoDlg dlg(this);
  m_pAdvInfoDlg = &dlg;
  dlg.DoModal();
  m_pAdvInfoDlg = NULL;

  return true;
}

bool CWavSrc::CloseModal(IStatus** ppStatus)
{
  if(!(m_pAdvInfoDlg && IsWindow(m_pAdvInfoDlg->m_hWnd)))
  {
    return false;
  }

  m_pAdvInfoDlg->EndDialog(IDCANCEL);

  if (0 != IsWindow(m_pAdvInfoDlg->m_hWnd))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool CWavSrc::SaveDialogToObject(IStatus** ppStatus)
{
  return false;
}

bool CWavSrc::SaveObjectToFile(IStatus** ppStatus)
{
  return false;
}

bool CWavSrc::CanSaveObjectToFile()
{
  return false;
}

// IInfoReader implementation

const char* CWavSrc::GetTitle()
{
  return m_csTitle;
}

const char* CWavSrc::GetArtist()
{
  return m_csArtist;
}

const char* CWavSrc::GetAlbum()
{
  return NULL;
}

const char* CWavSrc::GetYear()
{
  return NULL;
}

const char* CWavSrc::GetGenre()
{
  return NULL;
}


CWavSrc::CWavSrc(const char* szURL, IAudioComponent* pCreator,
          IStatus** ppStatus) 

          : CAggregatable (0),
            m_pCreator    (pCreator),
            m_hFile       (INVALID_HANDLE_VALUE),
            m_bRiffChunk  (FALSE),
            m_bWavChunk   (FALSE),
            m_dwDataStart (0),
            m_dwDataLen   (0),
            m_dwCurPos    (0),
            m_iBlockSize  (0),
            m_bOK         (false),
            m_bStarted    (false)
{
  try
  {
    m_csURL = szURL;

    // CreateFile - create or open an object: Consoles, Communications resources 
    //                           Directories (open only), Files etc.
    //
    //  LPCTSTR lpFileName -  file name
    // DWORD dwDesiredAccess - access mode
    // DWORD dwShareMode - share mode
    // LPSECURITY_ATTRIBUTES lpSecurityAttributes - [in] Pointer to a SECURITY_ATTRIBUTES
    //                                              structure that determines whether the returned
    //                                              handle can be inherited by child processes.
    //                                              If lpSecurityAttributes is NULL, the handle cannot
    //                                              be inherited. 
    // DWORD dwCreationDisposition - how to create
    // DWORD dwFlagsAndAttributes - file attributes
    // HANDLE hTemplateFile - handle to template file

    m_hFile = CreateFile(szURL, GENERIC_READ, FILE_SHARE_READ,
              NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

    if(INVALID_HANDLE_VALUE == m_hFile )
    {
      if(NULL != ppStatus)
      {
        *ppStatus = new CStatus(GetLastError());
      }

      throw false;
    }


    // Trying to recognize the file

    DWORD dwRead    = 0,
    dwFileSize  = 0;

    try
    {
      ReadMMIO();
    }
    catch(BOOL )
    {
      // If we're here - something is wrong in this file
      // Sometimes files can contain some wrong information at the end,
      // but if the rest is OK we can accept such files.
    }

    // make sure that we are dealing with a valid file format

    if(false == ((INVALID_HANDLE_VALUE != m_hFile)  &&
                 (true == m_bRiffChunk) &&
                 (true == m_bWavChunk) &&
                 (0 != m_dwDataStart) &&
                 (0 != m_dwDataLen)))
    {
      if(NULL != ppStatus)
      {
        *ppStatus = new CStatus(AE_BadFormat);
      }

      throw false;
    }

    // make sure that we are dealing with a valid wave format

    if(false == (((8 == m_format.wBitsPerSample) ||
                  (16 == m_format.wBitsPerSample)) &&

                 ((1 == m_format.wf.nChannels) ||
                  (2 == m_format.wf.nChannels)) &&
  
                 ((m_format.wf.nSamplesPerSec) >= 1000 &&
                  (m_format.wf.nSamplesPerSec <= 100000))))
    {
      if(NULL != ppStatus)
      {
        *ppStatus = new CStatus(AE_BadFormat);
      }

      throw false;
    }
    
    // Calculating the file duration

    m_iBlockSize = (m_format.wBitsPerSample / BITS_PER_BYTE) *
                        m_format.wf.nChannels;

    m_qwDuration = (ULONGLONG)m_dwDataLen * (ULONGLONG)1000 /
                  m_format.wf.nAvgBytesPerSec;
  }
  catch(bool )
  {
    // Error occured

    return;
  }

  m_bOK = true;
}

CWavSrc::~CWavSrc()
{
  if(m_hFile != INVALID_HANDLE_VALUE)
  {
    CloseHandle(m_hFile);
  }
}

HANDLE CWavSrc::GetFileHandle()
{
  return m_hFile;
}

PCMWAVEFORMAT CWavSrc::GetWavSrcFormat()
{
  return m_format;
}

HRESULT CWavSrc::ReadMMIO()
{
  // Convert the CString URL to LPTSTR

  LPTSTR lpsz = new TCHAR[m_csURL.GetLength()+1];
  _tcscpy(lpsz, m_csURL);


  // MM I/O handle for the WAVE
  HMMIO         hmmio; 

  // Open the file with the appropriate multimedia function

  hmmio = mmioOpen(lpsz, NULL, MMIO_ALLOCBUF | MMIO_READ );

  // Free the temporay pointer

  delete lpsz;

  // Make sure that the file could be opened
  
  if( NULL != hmmio )
  {
    // Use in opening a WAVE file
    MMCKINFO      ckRiff;   

    // Use for subchunks
    MMCKINFO      ck;      

    // Search for the first chunk
    if( ( 0 != mmioDescend( hmmio, &ckRiff, NULL, 0 ) ) )
    {
      return E_FAIL;
    }

    // Make sure this is a valid wave file
    
    if( (ckRiff.ckid != FOURCC_RIFF) || (ckRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
    {
      return E_FAIL; 
    }

    // If we got here, we can be sure that there is a riff chunk, and the type is WAVE
    
    m_bRiffChunk = true;
    m_bWavChunk = true;

    // Search the input file for for the 'fmt ' chunk.

    ck.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if( 0 != mmioDescend( hmmio, &ck, &ckRiff, MMIO_FINDCHUNK))
    {
      return E_FAIL;
    }

    // Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
    // if there are extra parameters at the end, we'll ignore them

    if( ck.cksize < (LONG) sizeof(PCMWAVEFORMAT))
    {
     return E_FAIL;
    }

    // Read the 'fmt ' chunk into m_format

    if( mmioRead( hmmio, (HPSTR) &m_format, sizeof(PCMWAVEFORMAT)) != sizeof(PCMWAVEFORMAT))
    {
      return E_FAIL;
    }

    if( m_format.wf.wFormatTag == WAVE_FORMAT_PCM )
    {
      // Seek to the data

      if( -1 == mmioSeek( hmmio, ckRiff.dwDataOffset + sizeof(FOURCC), SEEK_SET))
      {
          return E_FAIL;
      }

      // Search the input file for the 'data' chunk.

      ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
      if( 0 != mmioDescend( hmmio, &ck, &ckRiff, MMIO_FINDCHUNK))
      {
        return E_FAIL;
      }

      // store offset and size of the data

      m_dwDataStart = ck.dwDataOffset;
      m_dwDataLen = ck.cksize;
    }
    else
    {
      // Wrong format 

      return E_FAIL;
    }

    // Close the file

    mmioClose( hmmio, 0 );

    return S_OK;
  }
  else
  {
    // File could not be openend
    return E_FAIL;
  }
}
