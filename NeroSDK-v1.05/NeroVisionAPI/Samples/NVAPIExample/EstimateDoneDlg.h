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
|* PROGRAM: EstimateDoneDlg.h
|*
|* PURPOSE: A dialog box that holds controls showing data after
|*          transcoding disk and time estimation.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_ESTIMATE_DONE_DLG_H_
#define _NVAPIEXAMPLE_ESTIMATE_DONE_DLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEstimateDoneDlg : public CDialog
{
// Construction
public:
	CEstimateDoneDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEstimateDoneDlg)
	enum { IDD = IDD_TIME_AND_SIZE_ESTIMATE };
	CStatic	c_EstimatedSize;
	CStatic	c_EstimatedTime;
	CString	m_sEstimatedSize;
	CString	m_sEstimatedTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEstimateDoneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEstimateDoneDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
