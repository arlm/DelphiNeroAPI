/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroCBUI
|*
|* PROGRAM: TestNeroCBUI
|*
|* PURPOSE: Sample application for the use of NeroCBUI
******************************************************************************/
#if !defined(AFX_DLG_H__69443FF9_C64C_45A7_B2D0_E414174232DC__INCLUDED_)
#define AFX_DLG_H__69443FF9_C64C_45A7_B2D0_E414174232DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlg dialog

class CDlg :
	public CDialog,
	public IEraseDiscCallbacks,
	public IRecorderComboboxCallbacks
{
// Construction
public:
	CDlg(CWnd* pParent = NULL);	// standard constructor
	~CDlg ();

// Dialog Data
	//{{AFX_DATA(CDlg)
	enum { IDD = IDD_TESTNEROCBUI_DIALOG };
	CButton	c_WizardMode;
	CComboBox	m_MediaCombo;
	CButton	c_ModalEraseDisc;
	CComboBox	m_Combo;
	CButton	c_TestEraseDisc;
	CButton	c_TestDiscInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTestEraseDisc();
	afx_msg void OnTestDiscInfo();
	afx_msg void OnDestroy();
	afx_msg void OnTestBurnSettings();
	afx_msg void OnTestBurnSettingsOle();
	afx_msg void OnTestBurnProgress();
	afx_msg void OnTestImageInfo();
	afx_msg void OnTestChooseRecorder();
	afx_msg void OnTestChooseSession();
	afx_msg void OnSelchangeLangCombo();
	afx_msg void OnTestEraseDiscModeless();
	afx_msg void OnTestWaitForMedia();
	afx_msg void OnSelchangeMediaCombo();
	afx_msg void OnSelchangeRecorder();
	afx_msg void OnTestImageInfoOle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CComPtr<IRecorderCombobox2> m_pRecorderCombobox;
	CComPtr<ISpeedCombobox> m_pWriteSpeedCombobox;

	// IUnknown dummy implementation
protected:
	NERO_MEDIA_TYPE SelectedMediaType();
	STDMETHOD (QueryInterface) (REFIID riid, void ** ppvObject)
	{
		if (ppvObject != NULL)
		{
			if(riid==IID_IRecorderComboboxCallbacks)
				*ppvObject = static_cast<IRecorderComboboxCallbacks *> (this);
			else if(riid==IID_IEraseDiscCallbacks)
				*ppvObject = static_cast<IEraseDiscCallbacks *> (this);

			return S_OK;
		}
		return E_NOINTERFACE;
	}
        
	ULONG STDMETHODCALLTYPE AddRef ()
	{
		return 0;
	}
	
	ULONG STDMETHODCALLTYPE Release ()
	{
		return 0;
	}

	// 
	// IEraseDiscCallbacks implementation
	// 
	
	STDMETHOD (OnEraseDone) (IEraseDiscDlg * pEraseDiscDlg);		

	//
	// IRecorderComboboxCallbacks implementation
	// 
	STDMETHOD (OnFilterRecorder) (LPCNERO_SCSI_DEVICE_INFO pDeviceInfo, BOOL * pbAccept);
	STDMETHOD (OnFilterEnd) ();
	STDMETHOD (OnContentRefreshed) ();
	STDMETHOD (OnCurSelInUseStatusChange) (BOOL bInUse);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__69443FF9_C64C_45A7_B2D0_E414174232DC__INCLUDED_)
