/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* PROJECT: neroFiddles NeroAPI Example
|*
|* FILE: neroFiddlesDlg.h
|*
|* PURPOSE: Declaration file for the user interaction dialog.
******************************************************************************/


#if !defined(AFX_NEROFIDDLESDLG_H__78BE85B9_87B6_11D4_8056_00105ABB05E6__INCLUDED_)
#define AFX_NEROFIDDLESDLG_H__78BE85B9_87B6_11D4_8056_00105ABB05E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNeroFiddlesDlg dialog

class CNeroFiddlesDlg : public CDialog
{
// Construction
public:
	static void NERO_CALLBACK_ATTR SetPhaseCallback (void* pUserData, const char* text);
	static void NERO_CALLBACK_ATTR AddLogLine(void* pUserData, NERO_TEXT_TYPE type, const char* text);
	static BOOL NERO_CALLBACK_ATTR AbortedCallback (void* pUserData);
	static BOOL NERO_CALLBACK_ATTR ProgressCallback (void* pUserData, DWORD dwProgressInPercent);
	static NeroUserDlgInOut NERO_CALLBACK_ATTR UserDialog(void* pUserData, NeroUserDlgInOut type, void* data);
	static BOOL NERO_CALLBACK_ATTR IdleCallback (void* pUserData);
	CNeroFiddlesDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNeroFiddlesDlg)
	enum { IDD = IDD_NEROFIDDLES_DIALOG };
	CButton	mOK;
	CButton	mCancel;
	CButton	mbtnAbort;
	CProgressCtrl	mpgsProgress;
	CEdit	medtMessages;
	CEdit	medtFileName;
	CComboBox	mcbxDevices;
	CButton	mbtnBurn;
	CButton	mbtnBrowse;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNeroFiddlesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNeroFiddlesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnBurn();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAbort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char mpcImage [256];
	bool mbAborted;
	void NeroAPIFree();
	NERO_SETTINGS nsSettings;
	void AppendString(CString str);
	void NeroAPIInit();
    char pcLanguageFile [128];
    char pcSoftware [128];
    char pcVendor [128];
	char pcNeroFilesPath [128];
	char pcDriveName [128];
	FILE* pFile;
	NERO_ISO_ITEM mniiFile;
	NERO_WRITE_CD writeCD;
	NERO_PROGRESS npProgress;
	NERO_SCSI_DEVICE_INFOS* pndiDeviceInfos;
	NERO_DEVICEHANDLE ndhDeviceHandle;
	CString mstrPathName;
	CString mstrFileName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEROFIDDLESDLG_H__78BE85B9_87B6_11D4_8056_00105ABB05E6__INCLUDED_)
