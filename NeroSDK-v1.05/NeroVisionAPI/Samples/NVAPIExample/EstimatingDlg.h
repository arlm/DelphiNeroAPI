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
|* PROGRAM: EstimatingDlg.h
|*
|* PURPOSE: A dialog box that holds controls that display progress of
|*          transcoding disk and time estimation.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_ESTIMATING_DLG_H_
#define _NVAPIEXAMPLE_ESTIMATING_DLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEstimatingDlg : public CDialog
{
// Construction
public:
	CEstimatingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEstimatingDlg)
	enum { IDD = IDD_ESTIMATING_TIME_AND_SIZE };
	CProgressCtrl	c_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEstimatingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEstimatingDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
