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
|* FILE: FileHelper.cpp
|*
|* PURPOSE: Implementation of helper functions for file access
******************************************************************************/

#include "stdafx.h"

#include "FileHelper.h"

#ifdef _DEBUG
# define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Returns the current position in the file.

DWORD GetFilePointer(HANDLE hFile)
{
  ASSERT(hFile != INVALID_HANDLE_VALUE);

  return SetFilePointer(hFile, 0, 0, FILE_CURRENT);
}


// Reads a DWORD from a file, if it's not possible throws an exception. This
// allows to scan the file with multiple read without checking after every read.

void ReadDWORD(void* pObject, HANDLE hFile)
{
  if(!(pObject && hFile))
  {
    ASSERT(FALSE);

    throw FALSE;
  }

  DWORD dwRead = 0;

  if (!(ReadFile(hFile, pObject, sizeof(DWORD), &dwRead, NULL) &&
    dwRead == sizeof(DWORD)))
  {
    throw FALSE;
  }
}


// Reads a WORD from a file, if it's not possible throws an exception. This
// allows to scan the file with multiple read without checking after every read.

void ReadWORD(void* pObject, HANDLE hFile)
{
  if(!(pObject && hFile))
  {
    ASSERT(FALSE);

    throw FALSE;
  }

  DWORD dwRead = 0;

  if (!(ReadFile(hFile, pObject, sizeof(WORD), &dwRead, NULL) &&
    dwRead == sizeof(WORD)))
  {
    throw FALSE;
  }
}


// Reads a DWORD from the file and aligns it to a 2-byte border since the chunk
// length must be aligned to word size.

DWORD ReadChunkLen(HANDLE hFile)
{
  ASSERT(hFile);

  DWORD dwLen = 0;

  ReadDWORD(&dwLen, hFile);

  if (dwLen % 2)
  {
    dwLen++;
  }

  return dwLen;
}


// Writes a byte in the file.

void WriteZeroByte(HANDLE hFile)
{
  if(hFile)
  {
    BYTE  bt      = 0;
    DWORD dwWritten = 0;

    WriteFile(hFile, &bt, 1, &dwWritten, NULL);
  }
  else
  {
    ASSERT(FALSE);
  }
}