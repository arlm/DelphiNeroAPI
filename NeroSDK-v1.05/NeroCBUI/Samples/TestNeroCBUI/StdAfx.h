// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__72E81479_2016_46DE_B110_D658F34B35DB__INCLUDED_)
#define AFX_STDAFX_H__72E81479_2016_46DE_B110_D658F34B35DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <atlbase.h>

#include "NeroAPIGlue.h"

#pragma warning (disable:4192)
#include "NeroCBUI.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__72E81479_2016_46DE_B110_D658F34B35DB__INCLUDED_)