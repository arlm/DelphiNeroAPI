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
|* PROGRAM: PageFirst.h
|*
|* PURPOSE: Implementation of the first page.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_PAGE_FIRST_H_
#define _NVAPIEXAMPLE_PAGE_FIRST_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Page.h"
#include "PageData.h"

/////////////////////////////////////////////////////////////////////////////
// CPageFirst dialog

class CPageFirst
	: public CPage
	, CNVAPIExamplePage<CPageFirst>
{
protected:
	// The tree items on the first level can be of the CONTENTTYPE type.
	// 
	enum CONTENTTYPE
	{
		VIDEOTITLE = 0,
		SLIDESHOW
	};

	// The tree items on the second level of a SLIDESHOW can be of the
	// TRANSITION type. INVALID means an image path. NONE means no
	// transition.
	// 
	enum TRANSITION
	{
		INVALID = -1,
		NONE = 0,
		WIPEUP,
		WIPEDOWN,
		WIPELEFT,
		WIPERIGHT,
		MOVEIN,
		MOVEOUT
	};

	// These two ints hold the sequence numbers for newly inserted video
	// and slideshow items. They are used for automatic unique naming of
	// new items.
	// 
	int m_iVideoItemSequence;
	int m_iSlideshowItemSequence;

// Construction
public:
	CPageFirst(CSheet * pParentSheet);
	
// Dialog Data
	//{{AFX_DATA(CPageFirst)
	enum { IDD = IDD_FIRST_PAGE };
	CButton	c_Save;
	CButton	c_Remove;
	CComboBox	c_ProjectType;
	CButton	c_Load;
	CButton	c_InsertVideo;
	CButton	c_InsertSlide;
	CButton	c_InsertImage;
	CComboBox	c_TransitionType;
	CTreeCtrl	c_Content;
	int		m_iProjectType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageFirst)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageFirst)
	virtual BOOL OnInitDialog();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void OnInsertVideo();
	afx_msg void OnRemove();
	afx_msg void OnInsertSlide();
	afx_msg void OnSelchangedContent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTransitionType();
	afx_msg void OnInsertImage();
	afx_msg void OnBeginlabeleditContent(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnQuitWithDelay (WPARAM wParam, LPARAM lParam);

	void ChangeTransition (HTREEITEM hItem, const TRANSITION transition);
	void UpdateControls (void);
	IXMLDOMDocumentPtr BuildXML (void);
	void ParseXMLDocument (const IXMLDOMDocumentPtr pDocument);

	void ParseNeroVisionProject (const IXMLDOMElementPtr pProject);
	void ParseSubproject (const IXMLDOMElementPtr pSubProject);
	void ParseContent (const IXMLDOMElementPtr pContent);
	void ParseVideotitle (const IXMLDOMElementPtr pVideotitle);
	void ParseSlideshow (const IXMLDOMElementPtr pSlideshow);

	void InsertVideo (LPCSTR psVideoItemName, LPCSTR psPath);
	HTREEITEM InsertSlideshow (LPCSTR psSlideshowName);
	void InsertTransition (HTREEITEM hSlideItem, CPageFirst::TRANSITION transition = TRANSITION::NONE);
	void InsertImage (HTREEITEM hSlideItem, LPCSTR psImagePath);

	_bstr_t PrettyFormatXML (/*[in]*/ BSTR bstrInputXML);
		
	// CPage implementation
public:
	bool Create (void);	
	bool OnNext (void);
	void OnChangeState (bool bActivate, bool bForward);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
