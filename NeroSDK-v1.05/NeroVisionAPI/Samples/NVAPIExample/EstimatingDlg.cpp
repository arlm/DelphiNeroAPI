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
|* PROGRAM: EstimatingDlg.cpp
|*
|* PURPOSE: A dialog box that holds controls that display progress of
|*          transcoding disk and time estimation.
******************************************************************************/

#include "stdafx.h"
#include "NVAPIExample.h"
#include "EstimatingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CEstimatingDlg::CEstimatingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEstimatingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEstimatingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEstimatingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEstimatingDlg)
	DDX_Control(pDX, IDC_PROGRESS, c_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEstimatingDlg, CDialog)
	//{{AFX_MSG_MAP(CEstimatingDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

