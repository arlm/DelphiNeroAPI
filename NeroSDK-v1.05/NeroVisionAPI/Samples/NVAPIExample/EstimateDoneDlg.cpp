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
|* PROGRAM: EstimateDoneDlg.cpp
|*
|* PURPOSE: A dialog box that holds controls showing data after
|*          transcoding disk and time estimation.
******************************************************************************/

#include "stdafx.h"
#include "NVAPIExample.h"
#include "EstimateDoneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CEstimateDoneDlg::CEstimateDoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEstimateDoneDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEstimateDoneDlg)
	m_sEstimatedSize = _T("");
	m_sEstimatedTime = _T("");
	//}}AFX_DATA_INIT
}


void CEstimateDoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEstimateDoneDlg)
	DDX_Control(pDX, IDC_ESTIMATED_SIZE, c_EstimatedSize);
	DDX_Control(pDX, IDC_ESTIMATED_TIME, c_EstimatedTime);
	DDX_Text(pDX, IDC_ESTIMATED_SIZE, m_sEstimatedSize);
	DDX_Text(pDX, IDC_ESTIMATED_TIME, m_sEstimatedTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEstimateDoneDlg, CDialog)
	//{{AFX_MSG_MAP(CEstimateDoneDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

