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
|* PROGRAM: Page.h
|*
|* PURPOSE: Implementation of the common page abstract class.
******************************************************************************/

#ifndef _NVAPIEXAMPLE_PAGE_H_
#define _NVAPIEXAMPLE_PAGE_H_

#include "Sheet.h"

class CPage : public CDialog
{
public:
	CPage(LPCTSTR lpszTemplateName, CSheet * pParentSheet)
		: CDialog (lpszTemplateName, pParentSheet)
	{
	}
	CPage(UINT nIDTemplate, CSheet * pParentSheet)
		: CDialog (nIDTemplate, pParentSheet)
	{
	}
	
	virtual bool Create (void) PURE;
	virtual bool OnNext (void) {return false;}
	virtual bool OnBack (void) {return false;}
	virtual void OnChangeState (bool bActivate, bool bForward) PURE;
};

#endif
