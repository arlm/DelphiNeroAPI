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
|* PROGRAM: SpeedComboBox.h
|*
|* PURPOSE: A combobox that holds all available speeds for a particular
|*          recorder.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_SPEED_COMBOBOX_H_
#define _NVAPIEXAMPLE_SPEED_COMBOBOX_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSpeedComboBox : public CComboBox
{
// Construction
public:
	CSpeedComboBox() {}
	virtual ~CSpeedComboBox() {}
	
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeedComboBox)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CSpeedComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	void RefreshSpeeds (const NERO_SCSI_DEVICE_INFO * pnsdi);
	DWORD GetSelectedSpeed (void) const;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
