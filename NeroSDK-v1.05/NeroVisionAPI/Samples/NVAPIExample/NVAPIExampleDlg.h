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
|* PROGRAM: NVAPIExampleDlg.h
|*
|* PURPOSE: Implementation of the main property sheet like dialog.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_DLG_H_
#define _NVAPIEXAMPLE_DLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PageFirst.h"
#include "PageSecond.h"
#include "PageThird.h"
#include "PageData.h"
#include "Sheet.h"


class CNVAPIExampleDlg : public CSheet
{
protected:
	// First, second and third page.
	// 
	CPageFirst m_pageFirst;
	CPageSecond m_pageSecond;
	CPageThird m_pageThird;

	CPage * m_pPages[3];
	int m_iCurrentPage;
	const int m_iPageCount;

	// Common data communicator for all three pages.
	// 
	CPageData m_pageData;

// Construction
public:
	CNVAPIExampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNVAPIExampleDlg)
	enum { IDD = IDD_NVAPIEXAMPLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNVAPIExampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNVAPIExampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnNeroUserDialog (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNeroIdleCallback (WPARAM wParam, LPARAM lParam);
		
protected:
	void SwitchPage (int iNewPage);

	// CSheet
public:
	virtual DWORD GetCommonPageData (void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
