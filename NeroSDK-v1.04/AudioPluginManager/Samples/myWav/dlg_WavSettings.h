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
|* FILE: dlg_WavSettings.h
|*
|* PURPOSE: Definition of target item settings editor dialog class.
******************************************************************************/

#if !defined(AFX_DLG_WAVSETTINGS_H__23F58034_73E7_4DEB_B9E5_0ECA1DE88FF3__INCLUDED_)
# define AFX_DLG_WAVSETTINGS_H__23F58034_73E7_4DEB_B9E5_0ECA1DE88FF3__INCLUDED_

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000


// main symbols
#include "resource.h"

// translator class definitions
#include "NeroPluginNLS.h"


struct SWavFormat;

// Target item settings editor dialog class.
class CWavSettingsDlg : public CDialog
{
// Construction
public:
  CWavSettingsDlg(SWavFormat** parItems, int iItemNum);

// Data
private:
  enum {MUL_VAL = 0xffffffff};

  SWavFormat**  m_parItems;
  int           m_iItemNumber;

  CTranslator*  m_pTranslator;

// Dialog Data
  //{{AFX_DATA(CWavSettingsDlg)
  enum { IDD = IDD_WAV_SETTINGS };
  CComboBox m_comboFreq;
  CComboBox m_comboSampleSize;
  CComboBox m_comboChannels;
  int   m_iChannels;
  int   m_iSampleSize;
  CString m_csFreq;
  //}}AFX_DATA

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CWavSettingsDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CWavSettingsDlg)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  afx_msg void OnDestroy();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_WAVSETTINGS_H__23F58034_73E7_4DEB_B9E5_0ECA1DE88FF3__INCLUDED_)
