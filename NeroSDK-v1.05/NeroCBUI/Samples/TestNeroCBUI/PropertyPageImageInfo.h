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

#if !defined(AFX_PROPERTYPAGEIMAGEINFO_H__81CD706A_37E8_48B1_ABDC_36EEB9A6CA8E__INCLUDED_)
#define AFX_PROPERTYPAGEIMAGEINFO_H__81CD706A_37E8_48B1_ABDC_36EEB9A6CA8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyPageImageInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageImageInfo dialog

class CPropertyPageImageInfo : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropertyPageImageInfo)

public:
	CComPtr<IMfcPropertyPage> m_pMfcPropertyPage;

// Construction
public:
	CPropertyPageImageInfo();
	~CPropertyPageImageInfo();

// Dialog Data
	//{{AFX_DATA(CPropertyPageImageInfo)
//	enum { IDD = IDD_BURN_DLG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageImageInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageImageInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
		void AssertValid() const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEIMAGEINFO_H__81CD706A_37E8_48B1_ABDC_36EEB9A6CA8E__INCLUDED_)
