/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NVAPIExample
|*
|* PROGRAM: PageThird.h
|*
|* PURPOSE: Implementation of the third page.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_PAGE_THIRD_H_
#define _NVAPIEXAMPLE_PAGE_THIRD_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Page.h"
#include "PageData.h"


class CPageThird 
	: public CPage
	, public IProgressCallback
	, CNVAPIExamplePage<CPageThird>
{
protected:
	bool m_bActiveState;

	ProgressAction m_LastAction;
	CString m_sLastItemname;
	bool m_bAbort;
	DWORD m_dwStartTickCount;

// Construction
public:
	CPageThird(CSheet * pParent);

// Dialog Data
	//{{AFX_DATA(CPageThird)
	enum { IDD = IDD_THIRD_PAGE };
	CStatic	c_TotalTime;
	CStatic	c_Percent;
	CProgressCtrl	c_Progress;
	CListCtrl	c_Messages;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageThird)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageThird)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnStartProcess (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNeroUserDialog (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNeroIdleCallback (WPARAM wParam, LPARAM lParam);

	NeroUserDlgInOut NeroUserDialog (NeroUserDlgInOut type, void *data);

	void RestoreButtons (void);
	void InsertMessage (LPCSTR psMessage);
	void InsertMessage (UINT uMessageID);
	void SetPercent (int iPercent);
		
	static BOOL NERO_CALLBACK_ATTR NeroAbortedCallback (void *pUserData);
	static void NERO_CALLBACK_ATTR NeroAddLogLineCallback (void *pUserData, NERO_TEXT_TYPE type, const char *text);
	static BOOL NERO_CALLBACK_ATTR NeroProgressCallback (void *pUserData, DWORD dwProgressInPercent);
	
	// CPage implementation
public:
	bool Create (void);	
	bool OnNext (void);
	void OnChangeState (bool bActivate, bool bForward);

	// IProgressCallback
public:
	STDMETHOD (QueryInterface) (/* [in] */ REFIID riid, /* [iid_is][out] */ void ** ppvObject)
	{
		if (riid == IID_IUnknown ||
			riid == __uuidof (IProgressCallback))
		{
			*ppvObject = this;
			return S_OK;
		}
		else
		{
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}
	}
	STDMETHOD_(ULONG, AddRef) (void)
	{
		return 0;
	}
	STDMETHOD_(ULONG, Release) (void)
	{
		return 0;
	}
    STDMETHOD (raw_OnProgress) (
        enum ProgressAction action,
        BSTR itemname,
        double currentRemain,
        double currentTotal,
        float currentFraction,
        double totalRemain,
        double totalTotal,
        float totalFraction);
    STDMETHOD (raw_ShouldCancel) (
        VARIANT_BOOL * pbCancel);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
