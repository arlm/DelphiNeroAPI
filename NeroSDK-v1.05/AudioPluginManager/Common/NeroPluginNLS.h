/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / AudioPluginManager
|*
|* FILE: NeroPluginNLS.h
|*
|* PURPOSE: Translator class definition for NLS support for Nero plugins
******************************************************************************/

#ifndef _NERO_PLUGIN_NLS_
#define _NERO_PLUGIN_NLS_

/////////////////////////////////////////////////////////// CStranslateAction //

#include "afxtempl.h"

enum EWindowType
{
	ETT_Wrong,
	ETT_Combo,
	ETT_ListBox,
	ETT_Other
};

class CTranslateAction
{
// Construction/Destruction
public:
	CTranslateAction(HWND hWnd, const char *szPrevText);
	~CTranslateAction();

// Operations
public:
	void		Undo();

	void		AddSubItemAction(int iNum, const char *szPrevText);

protected:

// Data
protected:
	HWND							m_hWnd;
	CString							m_csPrevText;

	EWindowType						m_type;

	struct SUBACTION
	{
	// Construction/Destruction
		SUBACTION()
		:	m_iItem			(-1)
		{}

		SUBACTION(int iItemNum, const char *szPrevText)
		:	m_iItem			(iItemNum),
			m_csPrevText	(szPrevText)
		{}

	// Data
		int			m_iItem;
		CString		m_csPrevText;
	};

	CArray<SUBACTION, SUBACTION&>	m_SubActions;

	bool							m_bUndone;
};

///////////////////////////////////////////////////////////////// CTranslator //

// Translator class. Translates windows and separate expressions.
class CTranslator
{
// Construction/Destruction
public:
	CTranslator(WORD wResID, const char *szLang);
	~CTranslator();

// Operations
public:
	void			TranslateWindow(HWND hMainWnd);
	void			TranslateMenu(HMENU hMenu);
	void			UndoTranslation();

	void			GetWordTranslation(const char *szWord, CString *pcs);

// Data
protected:
	CString			m_csLang;

	CStringArray	m_strarEng,
					m_strarTgt;

	// Maps window handles to CTranslateAction pointers.
	CMapPtrToPtr	m_History;
};

CTranslator *	CreateTranslator(WORD wResID, LANGID id);
void			DestroyTranslator(CTranslator *pTranslator);

#endif _NERO_PLUGIN_NLS_
