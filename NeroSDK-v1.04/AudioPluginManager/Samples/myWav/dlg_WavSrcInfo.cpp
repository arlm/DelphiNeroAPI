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
|* FILE: dlg_WavSrcInfos.cpp
|*
|* PURPOSE: Implementation of the source info dialog.
******************************************************************************/


#include "stdafx.h"
#include "dlg_WavSrcInfo.h"

#include "WavSrc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern IAudioPluginMgr* g_pPluginMgr;


// CWavSrcInfoDlg

CWavSrcInfoDlg::CWavSrcInfoDlg(CWavSrc* pSource)
: CDialog     (CWavSrcInfoDlg::IDD, NULL),
  m_pSource   (pSource),
  m_bModified   (0),
  m_iCustBtnCount (0)
{
  if(pSource)
  {
    m_pInfo = static_cast<IAggregatable*>(pSource);

    ASSERT(m_pInfo);
  }

  //{{AFX_DATA_INIT(CWavSrcInfoDlg)
  m_csPath = _T("");
  m_csFileSize = _T("");
  m_csDateTime = _T("");
  m_csArtist = _T("");
  m_csDataFormat = _T("");
  m_csTitle = _T("");
  //}}AFX_DATA_INIT
}

void CWavSrcInfoDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWavSrcInfoDlg)
  DDX_Control(pDX, IDBTN_STUB, m_btnStub);
  DDX_Control(pDX, IDOK, m_btnOK);
  DDX_Control(pDX, IDEDIT_DATA_FORMAT, m_editDataFormat);
  DDX_Text(pDX, IDEDIT_PATH, m_csPath);
  DDX_Text(pDX, IDEDIT_FILE_SIZE, m_csFileSize);
  DDX_Text(pDX, IDEDIT_DATETIME, m_csDateTime);
  DDX_Text(pDX, IDEDIT_ARTIST, m_csArtist);
  DDX_Text(pDX, IDEDIT_DATA_FORMAT, m_csDataFormat);
  DDX_Text(pDX, IDEDIT_TITLE, m_csTitle);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWavSrcInfoDlg, CDialog)
  //{{AFX_MSG_MAP(CWavSrcInfoDlg)
  ON_CBN_SELENDOK(IDCOMBO_GENRE, OnSelendokGenre)
  ON_EN_CHANGE(IDEDIT_ARTIST, OnChangeField)
  ON_EN_CHANGE(IDEDIT_DATETIME, OnChangeField)
  ON_EN_CHANGE(IDEDIT_TITLE, OnChangeField)
  ON_WM_DESTROY()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//#define EXTERNAL_GENRE
#include "GenreStrings.inc"



BOOL CWavSrcInfoDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();

  // Obtainig the language information from the plugin manager in order to
  // translate this window.
  CComQIPtr<ILanguage> pLang = g_pPluginMgr;

  ASSERT(pLang);
  if(pLang)
  {
    m_pTranslator = CreateTranslator(IDR_PLUGIN_NLSDATA, pLang->GetLanguage());
    m_pTranslator->TranslateWindow(m_hWnd);
  }

  if(!(m_pSource && m_pInfo))
  {
    ASSERT(FALSE);

    EndDialog(IDCANCEL);

    return TRUE;
  }
  // file path
  CComQIPtr<IURLHolder> pURLHolder = m_pSource;

  if(pURLHolder)
  {
    m_csPath = pURLHolder->GetURL();
  }
 
  // file size
  DWORD dwSize = GetFileSize(m_pSource->GetFileHandle(), NULL);

  m_csFileSize.Format("%u", dwSize);

  for(int i = m_csFileSize.GetLength() - 3; i > 0; i -= 3)
  {
    m_csFileSize.Insert(i, ".");
  }
                            
  // date / time
  CFile file;
  file.GetFilePath();

  FILETIME ft;
  GetFileTime(m_pSource->GetFileHandle(), NULL, NULL, &ft);

  CTime time(ft);
  m_csDateTime = time.Format("%d.%m.%Y  %H:%M");

  // additional info values
  const char* szValue = NULL;

  CComQIPtr<IInfoReader> pInfoReader = m_pInfo;

  if(pInfoReader)
  {
    szValue = pInfoReader->GetArtist();
    if(szValue)
    {
      m_csArtist = szValue;
    }

    szValue = pInfoReader->GetTitle();
    if(szValue)
    {
      m_csTitle = szValue;
    }
  }
  
  // data format
  // 80 is the rough position of the second column
  m_editDataFormat.SetTabStops(80);

  m_csDataFormat.Format("Format:\tPCM\r\n"
              "Samplerate:\t%d\r\nChannels:\t%d\r\n"
              "BitPerSample:\t%d",
              m_pSource->GetWavSrcFormat().wf.nSamplesPerSec,
              m_pSource->GetWavSrcFormat().wf.nChannels,
              m_pSource->GetWavSrcFormat().wBitsPerSample);

  // application buttons
  CComPtr<ISrcInfoCallback> pCB;
  
  if(m_pInfo->GetCallback(&pCB) && pCB)
  {
    CRect rOK,
        rSave,
        rThisClient;

    GetClientRect(&rThisClient);

    m_btnOK.GetWindowRect(&rOK);
    m_btnStub.GetWindowRect(&rSave);
    ScreenToClient(&rOK);
    ScreenToClient(&rSave);

    int iDiff = rSave.top - rOK.top;

    m_iCustBtnCount = pCB->GetCustomControlCount();

    int iLastButtonBottom = 0;

    for(int i = 0; i < m_iCustBtnCount; i++)
    {
      CComPtr<IControl> pControl;
      if(!pCB->GetControl(i, &pControl) ||
          strcmpi(pControl->GetClassName(), "BUTTON"))
        continue;

      int iHInc = iDiff * i;

      CRect rNew(rOK.left, rSave.top + iHInc,
            rOK.right, rSave.bottom + iHInc);

      iLastButtonBottom = rNew.bottom;

      CButton* pBtn = new CButton;
      pBtn->Create(pControl->GetTitle(),
              GetWindowLong(m_btnStub.m_hWnd, GWL_STYLE),
              rNew, this, IDBTN_CUSTOM_FIRST +
              pControl->GetID());

      pBtn->SetFont(m_btnOK.GetFont());

      pBtn->ShowWindow(SW_SHOW);

      m_ptrarUserButtons.Add(pBtn);
    }

    // Resizind the dialog in order our new buttons to fit in it.
    iLastButtonBottom += (iDiff - rOK.Height());

    if(iLastButtonBottom > rThisClient.Height())
    {
      CRect r(0, 0, rThisClient.Width(), iLastButtonBottom);

      AdjustWindowRect(&r, GetWindowLong(m_hWnd, GWL_STYLE), FALSE);

      SetWindowPos(NULL, 0, 0, r.Width(), r.Height(),
              SWP_NOZORDER|SWP_NOMOVE);
    }
  }

  // update and validate
  UpdateData(FALSE);

  UpdateModified();
  
  return TRUE;
}

void CWavSrcInfoDlg::SetModified(bool b)
{
  bool bModifiedChanged = (b == m_bModified);

  m_bModified = b;

  UpdateModified();

  CComPtr<ISrcInfoCallback> pCB;
  
  if(m_pSource->GetCallback(&pCB) && pCB)
  {
    pCB->OnModified(b);
  }
}

void CWavSrcInfoDlg::UpdateModified()
{
//  m_btnSaveToID3Tag.EnableWindow(m_bModified);
}

void CWavSrcInfoDlg::OnChangeField() 
{
  SetModified(true);
}

void CWavSrcInfoDlg::OnSelendokGenre() 
{
  SetModified(true);
}

BOOL CWavSrcInfoDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
  int iID = LOWORD(wParam) - IDBTN_CUSTOM_FIRST;

  if(iID >= 0 && iID < m_iCustBtnCount)
  {
    CComPtr<ISrcInfoCallback> pCB;
    if(m_pSource->GetCallback(&pCB) && pCB)
    {
      pCB->OnCustomButton(iID);
    }
    else
    {
      // this must be not NULL, otherwise where from did
      // we get our custom buttons?
      ASSERT(pCB);
    }
    return TRUE;
  }
  
  return CDialog::OnCommand(wParam, lParam);
}

// Destroys the translator after the dialog has been closed
void CWavSrcInfoDlg::OnDestroy() 
{
  CDialog::OnDestroy();
  
  for(int i = 0; i < m_ptrarUserButtons.GetSize(); i++)
  {
    delete ((CButton*)m_ptrarUserButtons[i]);
  }
  
  DestroyTranslator(m_pTranslator);
}
