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
|* PROGRAM: PageData.h
|*
|* PURPOSE: Implementation of the class that holds common data to be
|*          communicated among pages.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_PAGE_DATA_H_
#define _NVAPIEXAMPLE_PAGE_DATA_H_

#include "Sheet.h"


class CPageData
{
public:
	CString m_sXML;
	const NERO_SCSI_DEVICE_INFO * m_pDeviceInfo;
	DWORD m_dwBurnSpeed;
	IProjectPtr m_pProject;

public:
	CPageData ()
		: m_pDeviceInfo (NULL)
		, m_dwBurnSpeed (0)
	{
		try
		{
			// Create an instance of NeroVisionAPI's Project object.
			// 
			EVAL_HR (m_pProject.CreateInstance (__uuidof (Project)));
		}
		catch (...)
		{
		}
	}
};

// The following template class adds a function for getting the CPageData
// pointer to each class that derives from it.
// 
template<class T>
class CNVAPIExamplePage
{
protected:
	CPageData * GetPageData (void)
	{
		T * pT = (T *) this;
		CSheet * pParentSheet = (CSheet *) pT->GetParent ();
		return (CPageData *) pParentSheet->GetCommonPageData ();
	}
};

#endif
