/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* PROJECT: Nero Plugin Manager Example
|*
|* FILE: myWav.h
|*
|* PURPOSE: CWavApp declaration.
******************************************************************************/

#if !defined(AFX_MYWAV_H__E5459AD3_C7F4_11D6_BA0E_00A0D2171523__INCLUDED_)
#define AFX_MYWAV_H__E5459AD3_C7F4_11D6_BA0E_00A0D2171523__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

// Application class. Stores and retrieves last parameters of settings editor
// dialog in registry.
class CWavApp : public CWinApp
{
public:
	CWavApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavApp)
	public:
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CWavApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWAV_H__E5459AD3_C7F4_11D6_BA0E_00A0D2171523__INCLUDED_)
