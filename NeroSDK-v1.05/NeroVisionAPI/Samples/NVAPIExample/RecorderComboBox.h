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
|* PROGRAM: RecorderComboBox.h
|*
|* PURPOSE: A combobox that holds all available recorders.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_RECORDER_COMBOBOX_H_
#define _NVAPIEXAMPLE_RECORDER_COMBOBOX_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "resource.h"       // main symbols


class CRecorderCombobox : public CComboBox
{
protected:
	NERO_SCSI_DEVICE_INFOS * m_pDeviceInfos;

public:
	CRecorderCombobox ();
	virtual ~CRecorderCombobox ();
		
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecorderCombobox)
	//}}AFX_VIRTUAL
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CRecorderCombobox)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

protected:
	void FillCombo (void);

public:
	const NERO_SCSI_DEVICE_INFO * GetCurrentRecorder (void) const;
	void Initialize (void);
};

#endif
