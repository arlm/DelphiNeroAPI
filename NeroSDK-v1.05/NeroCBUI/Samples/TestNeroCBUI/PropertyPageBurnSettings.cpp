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
// NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! 
// 
// In order to make BurnSettingsDlg work in a MFC project (or any other
// object that supports IMfcPropertyPage interface), one should:
// 
// 1) Create a new CPropertyPage derived class (probably using the wizard)
//    using any available dialog resource (IDD_xxx)
// 2) Once created, remove IDD reference from the H file and replace IDD
//    reference in the constructor (CPP file) with e.h. (UINT)1. It can
//    be any nonzero value. It is not used and if zero, assertion occurs.
// 3) CoCreateInstance a BurnSettingsDlg object asking for its
//    IMfcPropertyPage interface.
// 4) Call get_AFX_OLDPROPSHEETPAGE method to obtain the AFX_OLDPROPSHEETPAGE
//    structure.
// 5) Assign it to m_psp.
// 6) Add AssertValid method to the wizard generated code so just like
//    here to override CPropertyPage's implementation. This is to get rid
//    of some asserts.
// 7) You're done. Use the newly created CPropertyPage derivative as you
//    normaly would. Just don't try to add on any more functionality as
//    it simply won't work. The DialogProc is replaced with NeroCBUI's own
//    and so the message handling does not occur here.
// 
// NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! NOTES ! 


#include "stdafx.h"
#include "testnerocbui.h"
#include "PropertyPageBurnSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBurnSettings property page

IMPLEMENT_DYNCREATE(CPropertyPageBurnSettings, CPropertyPage)

CPropertyPageBurnSettings::CPropertyPageBurnSettings() : CPropertyPage((UINT)1/*CPropertyPageBurnSettings::IDD*/)
{
	//{{AFX_DATA_INIT(CPropertyPageBurnSettings)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	if (SUCCEEDED (m_pMfcPropertyPage.CoCreateInstance (__uuidof (BurnSettingsDlg))))
	{
		AFX_OLDPROPSHEETPAGE * pPSP;
		m_pMfcPropertyPage.p->get_AFX_OLDPROPSHEETPAGE (&pPSP);
		
		m_psp = *pPSP;
	}
}

CPropertyPageBurnSettings::~CPropertyPageBurnSettings()
{
}

void CPropertyPageBurnSettings::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageBurnSettings)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

#ifdef _DEBUG
void CPropertyPageBurnSettings::AssertValid() const
{
	CDialog::AssertValid();
	ASSERT(m_psp.dwSize == sizeof(m_psp));
	ASSERT(m_psp.dwFlags & PSP_USECALLBACK);
}
#endif

BEGIN_MESSAGE_MAP(CPropertyPageBurnSettings, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageBurnSettings)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBurnSettings message handlers
