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
|* FILE: WavTgt.cpp
|*
|* PURPOSE: Implementation of the wave target class
******************************************************************************/


#include "stdafx.h"
#include "WavTgt.h"

// helper functions for file access
#include "FileHelper.h"

#include "NeroPluginUtil.h"


// IAudioItem implementation

// return the object that created the wave target
bool CWavTgt::GetCreator(IAudioComponent** pCreator)
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

EAuxFlags CWavTgt::GetAuxFlags()
{
  return m_flags;
}

void CWavTgt::SetAuxFlags(EAuxFlags flags)
{
  m_flags = flags;
}

bool CWavTgt::SetURL(const char* szURL, IStatus** ppStatus)
{
  // only local URLs are allowed for this target
  if(false == IsURLLocal(szURL))
  {
    RETURN_ERROR(AE_BadPathName);
  }

  m_csURL = szURL;

  return true;
}

const char * CWavTgt::GetURL()
{
  return  m_csURL;
}

EURLType CWavTgt::GetType()
{
  return URL_LocalFile;
}

// IWavTgtSetDlgData implementation

SWavFormat * CWavTgt::GetDlgData()
{
  return &m_DlgData;
}

// IProcess implementation

bool CWavTgt::Start(IStatus **ppStatus)
{
  if(ppStatus)
  {
    *ppStatus = NULL;
  }

  m_hFile = CreateFile(m_csURL, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL, NULL);

  DWORD dwError = GetLastError();

  bool bRes = (m_hFile != INVALID_HANDLE_VALUE);

  if(false == bRes)
  {
    RETURN_ERROR(dwError);
  }

  int iSamplesPerSec = m_DlgData.m_iSamplesPerSecond;


  // Starting the target

  m_bEndProcess = FALSE;

  DWORD dwWritten   = 0;
  
  // Starting header

  char* szHeader    = "RIFF****WAVEfmt ";
  WriteFile(m_hFile, szHeader, strlen(szHeader), &dwWritten, NULL);

  // WAVE chunk size

  DWORD dw = 16;
  WriteFile(m_hFile, &dw, sizeof(DWORD), &dwWritten, NULL);

  // Sampling format

  PCMWAVEFORMAT format =
  {
    WAVE_FORMAT_PCM,
    m_DlgData.m_iChannels,
    iSamplesPerSec,
    (m_DlgData.m_iChannels * iSamplesPerSec *
            m_DlgData.m_iBitsPerSample) / BITS_PER_BYTE,
    (m_DlgData.m_iChannels * m_DlgData.m_iBitsPerSample) /
                                BITS_PER_BYTE,
    m_DlgData.m_iBitsPerSample
  };

  WriteFile(m_hFile, &format, sizeof(PCMWAVEFORMAT), &dwWritten, NULL);

  // Data chunk header

  char *szData = "data****";
  WriteFile(m_hFile, szData, strlen(szData), &dwWritten, NULL);

  m_dwWrittenRAWSize = 0;

  // The remaining information will be saved as soon as RAW data is received
  // and the artist, copyright and other additional information will be
  // save in EndTarget, after the whole RAW chunk is ready.

  return bRes;
}

bool CWavTgt::End(IStatus** ppStatus)
{
  ASSERT(m_hFile != INVALID_HANDLE_VALUE);

  if(ppStatus)
  {
    *ppStatus = NULL;
  }

  // align to the word size the RAW chunk
  if(m_dwWrittenRAWSize % 2)  
  {
    WriteZeroByte(m_hFile);
  }

  // List chunk
  DWORD dwListChunkSizePos  = 0,
      dwWritten     = 0;

  CString *pcsCurField    = &m_csArtist;

  BOOL  bHeaderIsWritten  = FALSE;

  DWORD dwListChunkSize   = 0;

  char *szarListSubTitles[] =
  {
    "IART",   // Artist
    "ICMT",   // Comments
    "ICOP",   // Copyright
    "ICRD",   // Creation date
    "INAM"    // Name (the title)
  };

  for(int i = 0; i < LIST_CHUNK_ITEMS; i++, pcsCurField++)
  {
    if(!pcsCurField->IsEmpty())
    {
      // the size of list item chunk size

      dwListChunkSize += 8; 

      if (!bHeaderIsWritten)
      {
        // the INFO word

        dwListChunkSize += WAV_CHUNK_NAME_LEN;  

        dwListChunkSizePos =
              GetFilePointer(m_hFile) + WAV_CHUNK_NAME_LEN;

        char *szListHeader = "LIST****INFO";
        WriteFile(m_hFile, szListHeader, strlen(szListHeader),
              &dwWritten, NULL);
        
        bHeaderIsWritten = TRUE;
      }

      // Subchunk title

      WriteFile(m_hFile, szarListSubTitles[i], WAV_CHUNK_NAME_LEN,
            &dwWritten, NULL);

      DWORD dwDataLen = pcsCurField->GetLength() + 1;

      dwListChunkSize += dwDataLen;

      // The size of this subchunk

      WriteFile(m_hFile, &dwDataLen, sizeof(DWORD),
            &dwWritten, NULL);

      // The subchunk content

      WriteFile(m_hFile, (LPCTSTR)(*pcsCurField), dwDataLen,
            &dwWritten, NULL);

      // align the chunk's size to the word size
      if(dwDataLen % 2) 
      {
        WriteZeroByte(m_hFile);
        dwListChunkSize++;
      }
    }
  }

  // Fill the size field of the LIST chunk

  if(bHeaderIsWritten)
  {
    SetFilePointer(m_hFile, dwListChunkSizePos, 0, FILE_BEGIN);

    WriteFile(m_hFile, &dwListChunkSize, sizeof(DWORD),
          &dwWritten, NULL);

    // align the list chunk's size to the word size

    if(dwListChunkSize % 2) 
      WriteZeroByte(m_hFile);
  }

  // Filling the RIFF chunk's size

  DWORD dwFileSize = GetFileSize(m_hFile, NULL);

  if (dwFileSize % 2)
  { 
    // Going to the end of the file to align
    // the file's size to size of word

    SetFilePointer(m_hFile, 0, 0, FILE_END);
    WriteZeroByte(m_hFile);

    dwFileSize++;
  }

  SetFilePointer(m_hFile, WAV_CHUNK_NAME_LEN, 0, FILE_BEGIN);

  // The RIFF header size

  dwFileSize -= 8;  

  WriteFile(m_hFile, &dwFileSize, sizeof(DWORD), &dwWritten, NULL);

  // Writing the "data" chunk's size

  SetFilePointer(m_hFile, 40, 0, FILE_BEGIN);

  WriteFile(m_hFile, &m_dwWrittenRAWSize, sizeof(DWORD), &dwWritten,
        NULL);

  CloseHandle(m_hFile);
  m_hFile = INVALID_HANDLE_VALUE;

  return true;
}

bool CWavTgt::IsInProcess()
{
  return (m_hFile != INVALID_HANDLE_VALUE);
}

// IAudioTarget implementation

bool CWavTgt::RawWrite(BYTE *pData, int iNumberOfBytesToWrite,
            EAudioRawState &state,
            IStatus **ppStatus)
{
  if(false == (pData && iNumberOfBytesToWrite))
  {
    RETURN_ERROR(AE_InvalidParameter);
  }

  ASSERT(m_hFile != INVALID_HANDLE_VALUE);

  if(ppStatus)
  {
    *ppStatus = NULL;
  }

  DWORD dwWritten = 0;

  // WriteFile returns zero for failure
  int iRes = WriteFile(m_hFile, pData, iNumberOfBytesToWrite, &dwWritten, NULL);

  if(0 == iRes)
  {
    DWORD dwError = GetLastError();
    RETURN_ERROR(dwError);
  }

  m_dwWrittenRAWSize += iNumberOfBytesToWrite;

  return true;
}

SWavFormat CWavTgt::GetRawFormat()
{
  return m_DlgData;
}

// IInfoWriter implementation

void CWavTgt::SetTitle(const char *szTitle)
{
  m_csTitle = szTitle;
}

void CWavTgt::SetArtist(const char *szArtist)
{
  m_csArtist = szArtist;
}

void CWavTgt::SetAlbum(const char *szAlbum)
{
  // not implemented
}

void CWavTgt::SetYear(const char *szYear)
{
  // not implemented
}

void CWavTgt::SetGenre(const char *szGenre)
{
  // not implemented
}
