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
|* FILE: WavTgtFactory.cpp
|*
|* PURPOSE: Implementation of the wave target factory
******************************************************************************/


#include "stdafx.h"

#include "WavTgtFactory.h"

// {9E424B23-3D6A-48ca-A41D-B65927057499}
EXTERN_GUID(COMPID_TgtFactory , 0x9e424b23, 0x3d6a, 0x48ca, 0xa4, 0x1d, 0xb6, 0x59, 0x27, 0x5, 0x74, 0x99);

// Wave Target class
#include "WavTgt.h"

// Wave Settings dialog
#include "dlg_WavSettings.h"


extern IAudioPluginMgr* g_pPluginMgr;


void CWavTgtFactory::GetID(GUID *pGUID)
{
	ASSERT(pGUID);
	if(pGUID)
	   memcpy(pGUID, &COMPID_TgtFactory, sizeof(GUID));
}

const char* CWavTgtFactory::GetName()
{
  return "PCM Wav file";
}

EAudioComponentType CWavTgtFactory::GetType()
{
  return ACT_AudioURLTargetFactory;
}

bool CWavTgtFactory::Init(IAudioPluginMgr*  pMgr, IStatus** ppStatus)
{
  if(ppStatus)
  {
    *ppStatus = NULL;
  }

  if(g_pPluginMgr)
  {
    ASSERT(g_pPluginMgr == pMgr);
  }
  else
  {
    g_pPluginMgr = pMgr;
  }

  // success
  return true;
}


bool CWavTgtFactory::Done()
{
  return true;
}


// IURLAudioTargetFactory

bool CWavTgtFactory::CreateURLAudioTarget(IUnknown**        ppTgt,
                                          const SWavFormat& formatSrc,
                                          IStatus**         ppStatus)
{
  if(ppStatus)
  {
    *ppStatus = NULL;
  }

  *ppTgt = static_cast<IAggregatable*>
            (new CWavTgt(formatSrc, (IAudioComponent*)this));
  if(*ppTgt)
  {
    (*ppTgt)->AddRef();
  }

  return true;
}

bool CWavTgtFactory::EditSettings(IUnknown **ppTgt, int iCount)
{
  SWavFormat **ppDlgData = new SWavFormat*[iCount];

  if(!(ppTgt && iCount && ppDlgData))
  {
    ASSERT(FALSE);
    return false;
  }

  AFX_MANAGE_STATE(AfxGetStaticModuleState());

  for(int i = 0; i < iCount; i++)
  {
    CComQIPtr<IWavTgtSetDlgData> pDlgData = ppTgt[i];

    if(!pDlgData)
    {
      // This is an object of not a valid type because we cannot
      // retrieve our internal interface from it.
      ASSERT(FALSE);
      return false;
    }

    ppDlgData[i] = pDlgData->GetDlgData();
  }

  CWavSettingsDlg dlg(ppDlgData, iCount);

  int iDlgRet = dlg.DoModal();

  delete ppDlgData;

  return (iDlgRet == IDOK);
}

// Application should first call this function to determine if this
// factory can edit settings for items.
bool CWavTgtFactory::CanEditSettings()
{
  return true;
}

EURLType CWavTgtFactory::GetSupportedURLTypes()
{
  return URL_LocalFile;
}


// IExtEnum
int CWavTgtFactory::GetCount()
{ 
  return 2;
}

// The returned value can't be stored for later use.
// The application must copy it.
const char* CWavTgtFactory::GetExt(int iNum)
{
  if(0 == iNum)
  {
    return "wav";
  }
  else if(1 == iNum)
  {
    return "wave";
  }

  ASSERT(FALSE);

  return NULL;
}

long CWavTgtFactory::GetRefCount()
{
  return m_lRef;
}
