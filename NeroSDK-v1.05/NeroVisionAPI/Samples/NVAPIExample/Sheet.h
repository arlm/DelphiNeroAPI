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
|* PROGRAM: Sheet.h
|*
|* PURPOSE: Implementation of the common sheet abstract class.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_SHEET_H_
#define _NVAPIEXAMPLE_SHEET_H_

class CSheet : public CDialog
{
public:
	CSheet(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL)
		: CDialog (lpszTemplateName, pParentWnd)
	{
	}
	CSheet(UINT nIDTemplate, CWnd* pParentWnd = NULL)
		: CDialog (nIDTemplate, pParentWnd)
	{
	}
	
	virtual DWORD GetCommonPageData (void) PURE;
};

#endif
