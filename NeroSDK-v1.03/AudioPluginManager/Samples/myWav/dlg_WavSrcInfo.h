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
|* FILE: dlg_WavSrcInfo.h
|*
|* PURPOSE: Declaration of the source info dialog.
******************************************************************************/


#if !defined(AFX_DLG_WAVSRCINFO_H__E95FB7B0_430A_45E6_8970_876A7EBC49A9__INCLUDED_)
# define AFX_DLG_WAVSRCINFO_H__E95FB7B0_430A_45E6_8970_876A7EBC49A9__INCLUDED_

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000



// main symbols
#include "resource.h"

// translator class definitions
#include "NeroPluginNLS.h"

// interface definitions
#include "AudioPluginEnv.h"



class CWavSrc;

class CWavSrcInfoDlg : public CDialog
{
// Construction
public:

  CWavSrcInfoDlg(CWavSrc* pSource);

// Operations
protected:

  void  SetModified(bool b);
  void  UpdateModified();

// Data
protected:

  CWavSrc*                          m_pSource;
  CComQIPtr<ISrcInfoViewerEditor>   m_pInfo;
  bool                              m_bModified;
  int                               m_iCustBtnCount;
  CPtrArray                         m_ptrarUserButtons;
  CTranslator*                      m_pTranslator;

// Dialog Data
  //{{AFX_DATA(CWavSrcInfoDlg)
  enum { IDD = IDD_INFO };
  CButton m_btnStub;
  CButton m_btnOK;
  CEdit m_editDataFormat;
  CString m_csPath;
  CString m_csFileSize;
  CString m_csDateTime;
  CString m_csArtist;
  CString m_csDataFormat;
  CString m_csTitle;
  //}}AFX_DATA

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CWavSrcInfoDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CWavSrcInfoDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnSelendokGenre();
  afx_msg void OnChangeField();
  afx_msg void OnDestroy();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_WAVSRCINFO_H__E95FB7B0_430A_45E6_8970_876A7EBC49A9__INCLUDED_)
