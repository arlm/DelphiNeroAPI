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
|* FILE: dlg_WavSettings.cpp
|*
|* PURPOSE: Implementation of the target item settings editor dialog.
******************************************************************************/


#include "stdafx.h"
#include "dlg_WavSettings.h"
#include "AudioPluginEnv.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern IAudioPluginMgr* g_pPluginMgr;

// This class doesn't have a default constructor, it must be initialized
// by this one, it receives an array of item handles, font and the language.
CWavSettingsDlg::CWavSettingsDlg(SWavFormat** parItems, int iItemNum)
: CDialog(CWavSettingsDlg::IDD, NULL),
  m_parItems    (parItems),
  m_iItemNumber (iItemNum),
  m_pTranslator (NULL)
{
  //{{AFX_DATA_INIT(CWavSettingsDlg)
  m_iChannels = -1;
  m_iSampleSize = -1;
  m_csFreq = _T("");
  //}}AFX_DATA_INIT
}

void CWavSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWavSettingsDlg)
  DDX_Control(pDX, IDCOMBO_FREQ, m_comboFreq);
  DDX_Control(pDX, IDCOMBO_SAMPLE_SIZE, m_comboSampleSize);
  DDX_Control(pDX, IDCOMBO_CHANNELS, m_comboChannels);
  DDX_CBIndex(pDX, IDCOMBO_CHANNELS, m_iChannels);
  DDX_CBIndex(pDX, IDCOMBO_SAMPLE_SIZE, m_iSampleSize);
  DDX_CBString(pDX, IDCOMBO_FREQ, m_csFreq);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWavSettingsDlg, CDialog)
  //{{AFX_MSG_MAP(CWavSettingsDlg)
  ON_WM_DESTROY()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Merges up the fields from received items and initializes controls.
BOOL CWavSettingsDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();

  if(!(m_parItems && m_iItemNumber))
  {
    ASSERT(FALSE);

    EndDialog(IDCANCEL);

    return TRUE;
  }

  SWavFormat mi;
  memset(&mi, 0xff, sizeof(SWavFormat));

  // Finding equal and different fields in
  // items received. Fields which are different
  // in mi will have value of MUL_VAL

  for(int iCurField = 0; iCurField < (sizeof(SWavFormat) / sizeof(DWORD));
    iCurField++)
  {
    DWORD dwCurValue = MUL_VAL;

    for(int iCurItem = 0; iCurItem < m_iItemNumber; iCurItem++)
    {
      DWORD* pItem = (DWORD*)m_parItems[iCurItem];

      if(pItem)
      {
        DWORD dwCurItemField = pItem[iCurField];

        if (dwCurValue == MUL_VAL)
          dwCurValue = dwCurItemField;
        else
        {
          if (dwCurValue != dwCurItemField)
            break;
        }
      }
      else
      {
        ASSERT(FALSE);
      }
    }

    // all the items have the same value
    if (iCurItem == m_iItemNumber)  
      ((DWORD*)&mi)[iCurField] = dwCurValue;
  }
                      
  // Initializing controls from mi
  // Filling the frequency combo

  int iarSampleRates[]  =
  {
    6000, 8000, 11025,  12000,  16000,  22050,
    32000,  32075,  36000,  44100,  48000
  };

  for(int i = 0; i < sizeof(iarSampleRates) / sizeof(int); i++)
  {
    int iValue = iarSampleRates[i];

    CString csTemp;
    csTemp.Format("%d", iValue);

    m_comboFreq.SetItemData(m_comboFreq.AddString(csTemp), iValue);
  }

  if(mi.m_iSamplesPerSecond != MUL_VAL)
    m_csFreq.Format("%d", mi.m_iSamplesPerSecond);

  int iarSampleSizes[] =
  {
    BITS_PER_BYTE,
    BITS_PER_WORD,
    BITS_PER_3BYTE,
    BITS_PER_DWORD
  };

  for(i = 0; i < sizeof(iarSampleSizes) / sizeof(int); i++)
  {
    m_comboSampleSize.SetItemData(i, iarSampleSizes[i]);

    if(mi.m_iBitsPerSample == iarSampleSizes[i])
      m_iSampleSize = i;
  }

  int iarChannelsNumber[] =
  {
    1,
    2
  };

  for(i = 0; i < sizeof(iarChannelsNumber) / sizeof(int); i++)
  {
    m_comboChannels.SetItemData(i, iarChannelsNumber[i]);

    if (mi.m_iChannels == iarChannelsNumber[i])
      m_iChannels = i;
  }

  UpdateData(FALSE);

  CComQIPtr<ILanguage> pLang = g_pPluginMgr;

  ASSERT(pLang);
  if(pLang)
  {
    m_pTranslator = CreateTranslator(IDR_PLUGIN_NLSDATA,
                      pLang->GetLanguage());
    m_pTranslator->TranslateWindow(m_hWnd);
  }

  return TRUE;
}

// Stores settings from controls in items and closes the dialog
void CWavSettingsDlg::OnOK() 
{
  UpdateData(TRUE);

  DWORD dwarDataFromScr[sizeof(SWavFormat) / sizeof(DWORD)] =
  {
    m_csFreq.IsEmpty()? MUL_VAL: atoi(m_csFreq),
    m_comboSampleSize.GetItemData(m_iSampleSize),
    m_comboChannels.GetItemData(m_iChannels)
  };

  for(int iCurItem = 0; iCurItem < m_iItemNumber; iCurItem++)
  {
    DWORD* pItem = (DWORD*)m_parItems[iCurItem];

    for(int iField = 0, iFieldNum = sizeof(SWavFormat) / sizeof(DWORD);
      iField < iFieldNum; iField++)
    {
      DWORD dwField = dwarDataFromScr[iField];

      if(dwField != MUL_VAL)
        pItem[iField] = dwField;
    }
  }

  CDialog::OnOK();
}

// Destroys the translator after the dialog has been closed
void CWavSettingsDlg::OnDestroy() 
{
  CDialog::OnDestroy();
  DestroyTranslator(m_pTranslator);
}
