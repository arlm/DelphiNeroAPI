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
|* PROGRAM: PageSecond.h
|*
|* PURPOSE: Implementation of the second page.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_PAGE_SECOND_H_
#define _NVAPIEXAMPLE_PAGE_SECOND_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Page.h"
#include "RecorderCombobox.h"
#include "SpeedComboBox.h"
#include "PageData.h"
#include "EstimatingDlg.h"
#include "EstimateDoneDlg.h"


class CPageSecond
	: public CPage
	, public IProgressCallback
	, CNVAPIExamplePage<CPageSecond>
{
protected:
	bool m_bFirstActivate;

	CEstimatingDlg m_dlgEstimating;
	CEstimateDoneDlg m_dlgEstimateDone;

// Construction
public:
	CPageSecond(CSheet * pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageSecond)
	enum { IDD = IDD_SECOND_PAGE };
	CStatic	c_ChildDialogPlaceholder;
	CSpeedComboBox	c_Speed;
	CRecorderCombobox	c_Recorder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageSecond)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageSecond)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeRecorder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void UpdateSpeeds (void);		

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
