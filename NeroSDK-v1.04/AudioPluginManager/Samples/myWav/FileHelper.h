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
|* FILE: FileHelper.h
|*
|* PURPOSE: Declaration of helper functions for file access
******************************************************************************/

#ifndef _FILE_HELPER_
# define _FILE_HELPER_

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000


// Returns the current position in the file.
DWORD GetFilePointer(HANDLE hFile);


// Reads a DWORD from a file, if it's not possible throws an exception. This
// allows to scan the file with multiple read without checking after every read.
void  ReadDWORD(void* pObject, HANDLE hFile);


// Reads a WORD from a file, if it's not possible throws an exception. This
// allows to scan the file with multiple read without checking after every read.
void  ReadWORD(void* pObject, HANDLE hFile);


// Reads a DWORD from the file and aligns it to a 2-byte border since the chunk
// length must be aligned to word size.
DWORD ReadChunkLen(HANDLE hFile);


// Writes a byte in the file.
void  WriteZeroByte(HANDLE hFile);


#endif // _FILE_HELPER_