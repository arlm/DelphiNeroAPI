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

#if !defined(AFX_PROPERTYPAGEBURNSETTINGS_H__4C9CA3D8_A9CB_4217_9B63_1D91DB80C3B4__INCLUDED_)
#define AFX_PROPERTYPAGEBURNSETTINGS_H__4C9CA3D8_A9CB_4217_9B63_1D91DB80C3B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyPageBurnSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBurnSettings dialog

class CPropertyPageBurnSettings : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropertyPageBurnSettings)

public:
	CComPtr<IMfcPropertyPage> m_pMfcPropertyPage;

// Construction
public:
	CPropertyPageBurnSettings();
	~CPropertyPageBurnSettings();

// Dialog Data
	//{{AFX_DATA(CPropertyPageBurnSettings)
//	enum { IDD = IDD_PROPERTY_PAGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageBurnSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageBurnSettings)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
	void AssertValid() const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEBURNSETTINGS_H__4C9CA3D8_A9CB_4217_9B63_1D91DB80C3B4__INCLUDED_)
