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
#include "stdafx.h"
#include "testnerocbui.h"
#include "PropertyPageImageInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageImageInfo property page

IMPLEMENT_DYNCREATE(CPropertyPageImageInfo, CPropertyPage)

CPropertyPageImageInfo::CPropertyPageImageInfo() : CPropertyPage((UINT)1/*CPropertyPageImageInfo::IDD*/)
{
	//{{AFX_DATA_INIT(CPropertyPageImageInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	if (SUCCEEDED (m_pMfcPropertyPage.CoCreateInstance (__uuidof (ImageInfoDlg))))
	{
		AFX_OLDPROPSHEETPAGE * pPSP;
		m_pMfcPropertyPage.p->get_AFX_OLDPROPSHEETPAGE (&pPSP);
		
		m_psp = *pPSP;
	}
}

CPropertyPageImageInfo::~CPropertyPageImageInfo()
{
}

void CPropertyPageImageInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageImageInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

#ifdef _DEBUG
void CPropertyPageImageInfo::AssertValid() const
{
	CDialog::AssertValid();
	ASSERT(m_psp.dwSize == sizeof(m_psp));
	ASSERT(m_psp.dwFlags & PSP_USECALLBACK);
}
#endif


BEGIN_MESSAGE_MAP(CPropertyPageImageInfo, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageImageInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageImageInfo message handlers
