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
|* PROGRAM: SpeedComboBox.cpp
|*
|* PURPOSE: stdafx.h : include file for standard system include files,
|*          or project specific include files that are used frequently, but
|*          are changed infrequently
******************************************************************************/

#if !defined(AFX_STDAFX_H__CE924482_1714_4DFA_84FE_E204CC6D7EB2__INCLUDED_)
#define AFX_STDAFX_H__CE924482_1714_4DFA_84FE_E204CC6D7EB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlconv.h>

#import "msxml3.dll"
#include <msxml2.h>
using namespace MSXML2;

#define EVAL_HR(_hr) { HRESULT hr = _hr; if FAILED(hr) throw hr; }

#import "C:\Program Files\Ahead\NeroVision\NeroVisionAPI.dll"
using namespace NeroVisionAPI;

#include "NeroAPIGlue.h"

// Disable "'identifier' : identifier was truncated to 'number' characters in the debug information"
// type of warnings.
// 
#pragma warning(disable:4786)

// Special user defined messages used to forward nero user dialog and
// idle callbacks to the interested recipients.
// 
#define UM_NERO_USER_DIALOG		(WM_APP + 111)
#define UM_NERO_IDLE_CALLBACK	(WM_APP + 112)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CE924482_1714_4DFA_84FE_E204CC6D7EB2__INCLUDED_)
