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
#if !defined(AFX_BURNDLG_H__68259A4C_BF56_432B_9D2C_300A3C3A3F69__INCLUDED_)
#define AFX_BURNDLG_H__68259A4C_BF56_432B_9D2C_300A3C3A3F69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BurnDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBurnDlg dialog

class CBurnDlg
	: public CDialog
	, public IExternalChildWindow
{
public:
	NERO_SCSI_DEVICE_INFO * m_pDeviceInfo;
	BOOL m_bWizardMode;
	
protected:
	NERO_DEVICEHANDLE m_DeviceHandle;

// Construction
public:
	CBurnDlg(CWnd* pParent = NULL);   // standard constructor
	~CBurnDlg ();

	CComPtr<IModelessDialog> m_pModelessDialog;
	CWnd m_wndDialog;

	NERO_WRITE_IMAGE m_neroImage;

// Dialog Data
	//{{AFX_DATA(CBurnDlg)
	enum { IDD = IDD_BURN_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBurnDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// We have no cancel button so we added this manually.
	// 
	virtual void OnCancel();
	
	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBurnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnPostInitDialog (WPARAM wParam, LPARAM lParam);

	// IUnknown dummy implementation.
	// 
public:
	STDMETHOD (QueryInterface) (REFIID riid, void ** ppvObject)
	{
		if (ppvObject != NULL)
		{
			if(riid==IID_IRecorderComboboxCallbacks)
				*ppvObject = static_cast<IExternalChildWindow *> (this);

			return S_OK;
		}
		return E_NOINTERFACE;
	}
        
	ULONG STDMETHODCALLTYPE AddRef () { return 0; }
	ULONG STDMETHODCALLTYPE Release () { return 0; }

	// IExternalChildWindow
public:
	STDMETHOD (Create) (/*[in]*/ HWND hWndParent, /*[out, retval]*/ HWND * phWnd);
	STDMETHOD (get_MinSize) (/*[out, retval]*/ SIZE * pSize);
	STDMETHOD (get_MaxSize) (/*[out, retval]*/ SIZE * pSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BURNDLG_H__68259A4C_BF56_432B_9D2C_300A3C3A3F69__INCLUDED_)
