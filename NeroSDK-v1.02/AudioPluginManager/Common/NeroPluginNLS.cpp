/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / AudioPluginManager
|*
|* FILE: NeroPluginNLS.h
|*
|* PURPOSE: Implementation of NLS support for Nero plugins
******************************************************************************/

#include "stdafx.h"
#include "NeroPluginNls.h"
//#include "resource.h"

#define ESPERANTO_TITLE	"[ENG]"
#define NLS_RES_TYPE	_T("NLSData")

#define MAX_STRING			10000
#define MAX_CLASS_NAME		500
#define MAX_MENU_ITEM_SIZE	500

struct LANGINFO
{
	LANGID		m_LangID;

	const char	*m_szAbbrev;
}
g_LangInfos[] =
{
	{ MAKELANGID(LANG_CHINESE,		SUBLANG_CHINESE_SIMPLIFIED),	"CHS" },
	{ MAKELANGID(LANG_CHINESE,		SUBLANG_CHINESE_TRADITIONAL),	"CHT" },
	{ MAKELANGID(LANG_DANISH,		SUBLANG_NEUTRAL),				"DAN" },
	{ MAKELANGID(LANG_GERMAN,		SUBLANG_NEUTRAL),				"DEU" },
	{ MAKELANGID(LANG_GREEK,		SUBLANG_NEUTRAL),				"ELL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_NEUTRAL),				"ESP" },
	{ MAKELANGID(LANG_FINNISH,		SUBLANG_NEUTRAL),				"FIN" },
	{ MAKELANGID(LANG_FRENCH,		SUBLANG_NEUTRAL),				"FRA" },
	{ MAKELANGID(LANG_HUNGARIAN,	SUBLANG_NEUTRAL),				"HUN" },
	{ MAKELANGID(LANG_ITALIAN,		SUBLANG_NEUTRAL),				"ITA" },
	{ MAKELANGID(LANG_JAPANESE,		SUBLANG_NEUTRAL),				"JPN" },
	{ MAKELANGID(LANG_KOREAN,		SUBLANG_NEUTRAL),				"KOR" },
	{ MAKELANGID(LANG_DUTCH,		SUBLANG_NEUTRAL),				"NDL" },
	{ MAKELANGID(LANG_NORWEGIAN,	SUBLANG_NORWEGIAN_BOKMAL),		"NOR" },
	{ MAKELANGID(LANG_POLISH,		SUBLANG_NEUTRAL),				"PLK" },
	{ MAKELANGID(LANG_PORTUGUESE,	SUBLANG_NEUTRAL),				"PTG" },
	{ MAKELANGID(LANG_ROMANIAN,		SUBLANG_NEUTRAL),				"ROM" },
	{ MAKELANGID(LANG_RUSSIAN,		SUBLANG_NEUTRAL),				"RUS" },
	{ MAKELANGID(LANG_SLOVENIAN,	SUBLANG_NEUTRAL),				"SLV" },
	{ MAKELANGID(LANG_SWEDISH,		SUBLANG_NEUTRAL),				"SVE" },
	{ MAKELANGID(LANG_UKRAINIAN,	SUBLANG_NEUTRAL),				"UKR" },

	{ MAKELANGID(LANG_ENGLISH,		SUBLANG_ENGLISH_US),			"ENG" },
	{ MAKELANGID(LANG_ENGLISH,		SUBLANG_DEFAULT),				"ENG" },
	{ MAKELANGID(LANG_ENGLISH,		SUBLANG_ENGLISH_US),			"ENU" },
	{ MAKELANGID(LANG_UKRAINIAN,	SUBLANG_DEFAULT),				"UKR" },
	{ MAKELANGID(LANG_JAPANESE,		SUBLANG_DEFAULT),				"JPN" },
	{ MAKELANGID(LANG_RUSSIAN,		SUBLANG_DEFAULT),				"RUS" },
	{ MAKELANGID(LANG_GERMAN,		SUBLANG_GERMAN),				"DEU" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_DEFAULT),				"ESP" },
	{ MAKELANGID(LANG_FRENCH,		SUBLANG_DEFAULT),				"FRA" },
	{ MAKELANGID(LANG_ITALIAN,		SUBLANG_DEFAULT),				"ITA" },
	{ MAKELANGID(LANG_PORTUGUESE,	SUBLANG_PORTUGUESE),			"PTG" },
	{ MAKELANGID(LANG_DANISH,		SUBLANG_DEFAULT),				"DAN" },
	{ MAKELANGID(LANG_DUTCH,		SUBLANG_DEFAULT),				"NLD" },
	{ MAKELANGID(LANG_CHINESE,		SUBLANG_CHINESE_TRADITIONAL),	"CHT" },
	{ MAKELANGID(LANG_CHINESE,		SUBLANG_CHINESE_SIMPLIFIED),	"CHS" },
	{ MAKELANGID(LANG_FINNISH,		SUBLANG_DEFAULT),				"FIN" },
	{ MAKELANGID(LANG_HUNGARIAN,	SUBLANG_DEFAULT),				"HUN" },
	{ MAKELANGID(LANG_POLISH,		SUBLANG_DEFAULT),				"PLK" },
	{ MAKELANGID(LANG_SWEDISH,		SUBLANG_DEFAULT),				"SVE" },
	{ MAKELANGID(LANG_NORWEGIAN,	SUBLANG_NORWEGIAN_BOKMAL),		"NOR" },
	{ MAKELANGID(LANG_CZECH,		SUBLANG_DEFAULT),				"CSY" },
	{ MAKELANGID(LANG_KOREAN,		SUBLANG_DEFAULT),				"KOR" },
	{ MAKELANGID(LANG_PORTUGUESE,	SUBLANG_PORTUGUESE_BRAZILIAN),	"PTB" },
	{ MAKELANGID(LANG_SLOVAK,		SUBLANG_DEFAULT),				"SKY" },
	{ MAKELANGID(LANG_SLOVENIAN,	SUBLANG_DEFAULT),				"SLV" },
	{ MAKELANGID(LANG_GREEK,		SUBLANG_DEFAULT),				"ELL" },
	{ MAKELANGID(LANG_TURKISH,		SUBLANG_DEFAULT),				"TRK" },
	{ MAKELANGID(LANG_THAI,			SUBLANG_DEFAULT),				"THA" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_CHILE),			"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH),				"ESP" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_MODERN),		"ESP" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_ARGENTINA),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_BOLIVIA),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_COLOMBIA),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_COSTA_RICA),	"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_DOMINICAN_REPUBLIC), "ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_ECUADOR),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_GUATEMALA),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_HONDURAS),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_MEXICAN),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_NICARAGUA),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_PANAMA),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_PARAGUAY),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_PERU),			"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_PUERTO_RICO),	"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_EL_SALVADOR),	"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_URUGUAY),		"ESL" },
	{ MAKELANGID(LANG_SPANISH,		SUBLANG_SPANISH_VENEZUELA),		"ESL" },
	{ MAKELANGID(LANG_CROATIAN,		SUBLANG_DEFAULT),				"HRV" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_SAUDI_ARABIA),	"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_ALGERIA),		"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_BAHRAIN),		"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_EGYPT),			"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_IRAQ),			"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_JORDAN),			"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_KUWAIT),			"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_LEBANON),		"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_LIBYA),			"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_MOROCCO),		"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_OMAN),			"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_QATAR),			"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_SYRIA),			"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_TUNISIA),		"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_UAE),			"ARA" },
	{ MAKELANGID(LANG_ARABIC,		SUBLANG_ARABIC_YEMEN),			"ARA" },
	{ MAKELANGID(LANG_HEBREW,		SUBLANG_DEFAULT),				"HEB" }
};

// Creates the translator object and returns it's pointer.
CTranslator * CreateTranslator(WORD wResID, LANGID id)
{
	const char *szLang = "ENG";

	for(int i =0; i < (sizeof(g_LangInfos) / sizeof(LANGINFO)); i++)
	{
		if(id == g_LangInfos[i].m_LangID)
			szLang = g_LangInfos[i].m_szAbbrev;
	}

	CTranslator *pTranslator = new CTranslator(wResID, szLang);

	ASSERT(pTranslator);

	return pTranslator;
}

// Destroys the translator object.
void DestroyTranslator(CTranslator *pTranslator)
{
	if(pTranslator)
		delete pTranslator;
	else
	{
		ASSERT(FALSE);
	}
}

// Tries to find a translation for the expression stored in "szWord" and writes
// it to "*pcs". If the translation cannot be found, copies szWord to *pcs.
void CTranslator::GetWordTranslation(const char *szWord, CString *pcs)
{
	if(!(szWord && pcs))
	{
		ASSERT(FALSE);

		return;
	}

	CString csWord;

	for(const char *pc = szWord; *pc; pc++)
	{
		if(*pc != '&')
			csWord += *pc;
	}

	szWord = csWord;

	for(int i = 0, iLen = m_strarEng.GetSize(); i < iLen; i++)
	{
		if(m_strarEng[i] == szWord)
		{
			if(m_strarTgt.GetSize() > i)
			{
				CString csTemp = m_strarTgt[i];
				if(!csTemp.IsEmpty())
				{
					*pcs = csTemp;

					return;
				}
			}
		}
	}

	*pcs = szWord;
}

// Recursively translates all the child windows of hMainWnd window i.e. their
// window texts and contents of list and combo boxes.
void CTranslator::TranslateWindow(HWND hMainWnd)
{
														// The window itself
	char szText[1000];
	::GetWindowText(hMainWnd, szText, 1000);

	CString csTranslation;

	GetWordTranslation(szText, &csTranslation);
	SetWindowText(hMainWnd, csTranslation);

	CTranslateAction *pAction = NULL;

	if(m_History.Lookup((void*)hMainWnd, (void*&)pAction))
	{
		// This means that the window is translated for the second time.
		ASSERT(FALSE);
	}
	else
		// Everything is OK, the window is not translated yet.
	{
		pAction = new CTranslateAction(hMainWnd, szText);

		m_History.SetAt((void*)hMainWnd, pAction);
	}

	ASSERT(pAction);
										 				// Container controls
	::GetClassName(hMainWnd, szText, 1000);

	// We cannot translate sorted combo boxes
	if(!strcmpi(szText, "COMBOBOX") &&
		!(::GetWindowLong(hMainWnd, GWL_STYLE) & CBS_SORT))
	{
		CComboBox *pCombo = (CComboBox*)CWnd::FromHandle(hMainWnd);

		int iCurSel = pCombo->GetCurSel();

		for(int i = 0, iLen = pCombo->GetCount(); i < iLen; i++)
		{
			CString csPrevText;
			pCombo->GetLBText(i, csPrevText);

			GetWordTranslation(csPrevText, &csTranslation);

			DWORD dw = pCombo->GetItemData(i);
			pCombo->DeleteString(i);

			pCombo->InsertString(i, csTranslation);
			pCombo->SetItemData(i, dw);

			if (iCurSel == i)
				pCombo->SetCurSel(iCurSel);

			pAction->AddSubItemAction(i, csPrevText);
		}
	}

	// We cannot translate sorted list boxes
	if(!strcmpi(szText, "LISTBOX") &&
		!(::GetWindowLong(hMainWnd, GWL_STYLE) & LBS_SORT))
	{
		CListBox *pLB = (CListBox*)CWnd::FromHandle(hMainWnd);

		int iCurSel = pLB->GetCurSel();

		for(int i = 0, iLen = pLB->GetCount(); i < iLen; i++)
		{
			CString csPrevText;
			pLB->GetText(i, csPrevText);

			GetWordTranslation(csPrevText, &csTranslation);

			DWORD dw = pLB->GetItemData(i);
			pLB->DeleteString(i);

			pLB->InsertString(i, csTranslation);
			pLB->SetItemData(i, dw);

			pAction->AddSubItemAction(i, csPrevText);
		}

		pLB->SetCurSel(iCurSel);
	}
														// And child windows

	for(HWND hWnd = ::GetWindow(hMainWnd, GW_CHILD|GW_HWNDFIRST); hWnd;
		hWnd = ::GetWindow(hWnd, GW_HWNDNEXT))
	{
		TranslateWindow(hWnd);
	}
}

void CTranslator::TranslateMenu(HMENU hMenu)
{
	for(int i = 0, iCount = GetMenuItemCount(hMenu); i < iCount; i++)
	{
		char szItem[MAX_MENU_ITEM_SIZE];

		if(GetMenuString(	hMenu,
							i,
							szItem,
							sizeof(szItem),
							MF_BYPOSITION))
		{

			CString csTranslation;
			GetWordTranslation(szItem, &csTranslation);

			ModifyMenu(hMenu, i, MF_BYPOSITION|MF_STRING, GetMenuItemID(hMenu, i),
						csTranslation);
		}

		HMENU hSubMenu = GetSubMenu(hMenu, i);
		if(hSubMenu)
			TranslateMenu(hSubMenu);
	}
}

// This class doesn't have a default constructor. It must be created by this one
// to initialize it. wResID is the ID of resource containing the translation
// text.
CTranslator::CTranslator(WORD wResID, const char *szLang)
:	m_csLang	(szLang)
{
	HINSTANCE	hInst		= AfxGetInstanceHandle();

	HRSRC		hRes		= NULL;
	HGLOBAL		hResData	= NULL;

	try
	{
		CString csRes;
		csRes.Format("#%d", wResID);

		hRes		= FindResource(hInst, csRes, NLS_RES_TYPE);
		if(!hRes)
			throw 0;

		DWORD dwResSize = SizeofResource(hInst, hRes);

		hResData	= LoadResource(hInst, hRes);
		if(!hResData)
			throw 0;

		char *pcRes = (char*)LockResource(hResData);

									// Start the parsing of the resource data

		enum { Out, English, National} status = Out;

		DWORD dwCurPos = 0;

		CString csCurWord;

		BOOL	bEnglishDone	= FALSE,
				bNationalDone	= FALSE;

		for(char *pcTemp = pcRes; dwCurPos < dwResSize; dwCurPos++, pcTemp++)
		{
			if(*pcTemp != '\r' && *pcTemp != '\n' && *pcTemp != '\t')
			{
				char cNext = pcTemp[1];

				if(*pcTemp == '\\' && (cNext == 'n' || cNext == 'r' || cNext == 't'))
				{
					csCurWord += (cNext == 'n')? '\n': ((cNext == 'r')? '\r': '\t');

					dwCurPos++;
					pcTemp++;
				}
				else
					csCurWord += *pcTemp;
			}
			else
			{
				if(!csCurWord.IsEmpty())
				{
					if(status == Out)
					{
						if(!bEnglishDone)
						{
							if(!csCurWord.CompareNoCase(ESPERANTO_TITLE))
							{
								status = English;
							}
						}

						if(!bNationalDone && status == Out)
						{
							CString csTemp;
							csTemp.Format("[%s]", szLang);

							if(!csCurWord.CompareNoCase(csTemp))
								status = National;
						}
					}
					else
					{
						if (isdigit(csCurWord[0]))
						{
							int		iNumber = 0;
							CString	csString;

							for(const char *pc = csCurWord; *pc; pc++)
							{
								if (*pc == ' ')
									break;
							}

							iNumber = atoi(csCurWord);
							csString = (char*)(pc + 1);

							if(status == English)
							{
								m_strarEng.SetAtGrow(iNumber, csString);
							}
							else	// National
							{
								m_strarTgt.SetAtGrow(iNumber, csString);
							}
						}
						else
						{
							status = Out;
							pcTemp--;

							continue;
						}
					}

					csCurWord.Empty();
				}
			}
		}
	}
	catch(...)
	{
	}
}

CTranslator::~CTranslator()
{
	for(POSITION pos = m_History.GetStartPosition(); pos; )
	{
		CTranslateAction	*pAction	= NULL;
		HWND				hWnd		= NULL;

		m_History.GetNextAssoc(pos, (void*&)hWnd, (void*&)pAction);

		ASSERT(pAction);
		
		if(pAction)
			delete pAction;
	}
}

void CTranslator::UndoTranslation()
{
	for(POSITION pos = m_History.GetStartPosition(); pos; )
	{
		CTranslateAction	*pAction	= NULL;
		HWND				hWnd		= NULL;

		m_History.GetNextAssoc(pos, (void*&)hWnd, (void*&)pAction);

		ASSERT(pAction);
		
		if(pAction)
			pAction->Undo();
	}
}

//////////////////////////////////////////////////////////// CTranslateAction //

CTranslateAction::CTranslateAction(HWND hWnd, const char *szPrevText)
:	m_csPrevText	(szPrevText),
	m_hWnd			(hWnd),
	m_type			(ETT_Other),
	m_bUndone		(false)
{
	char szClassName[MAX_CLASS_NAME];

	if(!::IsWindow(hWnd) ||
		!::GetClassName(hWnd, szClassName, MAX_CLASS_NAME))
	{
		// We cannot obtain the window class name or the window doesn't exist.
		m_type = ETT_Wrong;

		return;
	}

	if(!strcmpi(szClassName, "COMBOBOX"))
		m_type = ETT_Combo;

	if(!strcmpi(szClassName, "LISTBOX"))
		m_type = ETT_ListBox;
}

CTranslateAction::~CTranslateAction()
{
}

void CTranslateAction::Undo()
{
	if(m_bUndone)
	{
		ASSERT(FALSE);

		return;
	}

	::SetWindowText(m_hWnd, m_csPrevText);

	for(int i = 0, iCount = m_SubActions.GetSize(); i < iCount; i++)
	{
		SUBACTION &sa = m_SubActions[i];

		switch(m_type)
		{
			case ETT_Combo:
			{
				CComboBox *pCB = (CComboBox*)CWnd::FromHandle(m_hWnd);

				DWORD dwItemData = pCB->GetItemData(sa.m_iItem);
				pCB->DeleteString(i);
				pCB->InsertString(sa.m_iItem, sa.m_csPrevText);
				pCB->SetItemData(sa.m_iItem, dwItemData);

				break;
			}

			case ETT_ListBox:
			{
				CListBox *pLB = (CListBox*)CWnd::FromHandle(m_hWnd);

				DWORD dwItemData = pLB->GetItemData(sa.m_iItem);
				pLB->DeleteString(i);
				pLB->InsertString(sa.m_iItem, sa.m_csPrevText);
				pLB->SetItemData(sa.m_iItem, dwItemData);

				break;
			}

			case ETT_Other:
			default:
			{
				break;
			}
		}
	}

	m_bUndone = true;
}

void CTranslateAction::AddSubItemAction(int iNum, const char *szPrevText)
{
	m_SubActions.Add(SUBACTION(iNum, szPrevText));
}
