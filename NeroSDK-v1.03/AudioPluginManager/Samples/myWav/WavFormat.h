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
|* FILE: WavFormat.h
|*
|* PURPOSE: Wave format definitions and structs.
******************************************************************************/


#ifndef _WAV_FORMATD_
# define _WAV_FORMATD_

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000


// Headers

// length of the name part
const int WAV_CHUNK_NAME_LEN = 4;

// the number of supported subchunks of the LIST chunk
const int LIST_CHUNK_ITEMS = 5; 

// source flags
const EAuxFlags SRC_FLAGS = ((EAuxFlags) (EAF_LightOpen|
                                          EAF_Readable|
                                          EAF_CanRecOnAudioCD|EAF_CanRecOnDataCD|
                                          EAF_CanCopy|
                                          EAF_CanDLToMp3PlayerOrPortabDvc|
                                          EAF_CanConvert));

// SWavCommon

// A base structure for both source and target item classes.
// Incapsulates the additional information.
struct SWavCommon
{
// Data

// the order of placement of this fields MUST not
// be changed or MUST be arranged with the second
// switch of Recurse Wave function

  CString   m_csArtist;
  CString   m_csComments;
  CString   m_csCopyright;
  CString   m_csDate;
  CString   m_csTitle;
};

#endif // _WAV_FORMATD_
