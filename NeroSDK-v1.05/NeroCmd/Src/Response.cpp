/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroCmd
|*
|* PROGRAM: Response.h
|*
|* PURPOSE: Interaction with the user via keyboard
******************************************************************************/

#include "stdafx.h"
#include "Response.h"

bool CResponse::m_bUseDefaultResponse = false;

CResponse::CResponse (const CResponsePairs * pResponsePairs, int iDefaultPairIndex) :
	m_pResponsePairs (pResponsePairs),
	m_iDefaultPairIndex (iDefaultPairIndex)
{
	_ASSERTE (m_pResponsePairs != NULL);
	
#ifdef _DEBUG
	// Check that the index is within bounds.
	// 
	for (int iCount = 0; m_pResponsePairs[iCount].m_psButtonText != NULL; iCount ++);
	_ASSERTE (iDefaultPairIndex < iCount);
#endif
}

// Static method to globally set if default (non-interactive) responses
// are used or not.
// 
void CResponse::SetUseDefaultResponse (bool bUseDefaultResponse)
{
	m_bUseDefaultResponse = bUseDefaultResponse;
}

// Overloaded operator for ease of use.
// 
CResponse::operator NeroUserDlgInOut () const
{
	return SelectResponse ();
}

// This is a helper function that displays a set of choices and allows
// the user to move from one choice to another by pressing the arrow
// keys.

NeroUserDlgInOut CResponse::SelectResponse (void) const
{
	// Set the initial response to be the default one.
	// 
	int iSelection = m_iDefaultPairIndex;

	while (1)
	{
		printf ("\r");
		for (int i = 0; m_pResponsePairs[i].m_psButtonText != NULL; i ++)
		{
			printf ((i == iSelection)? ">": " ");
			printf ("%s", m_pResponsePairs[i].m_psButtonText);
			printf ((i == iSelection)? "< ": "  ");
		}
		fflush (stdout);
		
		// If default response is desired, return immediately,
		// otherwise wait for the actual keypresses.
		// 
		if (m_bUseDefaultResponse)
		{
			printf ("\n");
			return m_pResponsePairs[iSelection].m_RetVal;
		}
		else
		{
			while (1)
			{
				unsigned char ch = getch ();
				if (ch == '\r')
				{
					printf ("\r                                                                                ");
					fflush (stdout);
					return m_pResponsePairs[iSelection].m_RetVal;
				}
				else if (ch == 0xe0)
				{
					ch = getch ();
					
					if (ch == 75)
					{
						if (iSelection > 0)
						{
							iSelection--;
							break;
						}
					}
					else if (ch == 77)
					{
						if (m_pResponsePairs[iSelection + 1].m_psButtonText != NULL)
						{
							iSelection ++;
							break;
						}
					}
				}
			}
		}
	}
}

const CResponsePairs
	CResponseYesNo::m_ResponsePairs[] = { "Yes", DLG_RETURN_TRUE, "No", DLG_RETURN_FALSE, NULL};

const CResponsePairs
	CResponseOkay::m_ResponsePairs[] = { "OK", DLG_RETURN_EXIT, NULL};




const CResponsePairs CResponseGeneric::m_ResponsePairs_ok[] =
	{ "OK", DLG_RETURN_OK, NULL};
const CResponsePairs CResponseGeneric::m_ResponsePairs_yesno[] =
	{ "Yes", DLG_RETURN_YES, "No", DLG_RETURN_NO, NULL};
const CResponsePairs CResponseGeneric::m_ResponsePairs_okcancel[] =
	{ "OK", DLG_RETURN_OK, "Cancel", DLG_RETURN_CANCEL, NULL};
const CResponsePairs CResponseGeneric::m_ResponsePairs_retrycancel[] =
	{ "Retry", DLG_RETURN_RETRY, "Cancel", DLG_RETURN_CANCEL, NULL};
const CResponsePairs CResponseGeneric::m_ResponsePairs_abortretryignore[] =
	{ "Abort", DLG_RETURN_ABORT, "Retry", DLG_RETURN_RETRY, "Ignore", DLG_RETURN_IGNORE, NULL};
const CResponsePairs CResponseGeneric::m_ResponsePairs_yesnocancel[] =
	{ "Yes", DLG_RETURN_YES, "No", DLG_RETURN_NO, "Cancel", DLG_RETURN_CANCEL, NULL};


CResponseGeneric::CResponseGeneric (NERODLG_MESSAGE_TYPE msgType, NeroUserDlgInOut defaultReturn)
	: CResponse (NULL, 0)
{
	switch (msgType)
	{
	case NDMT_OK:
		m_pResponsePairs = m_ResponsePairs_ok;
		m_iDefaultPairIndex = 0;
		
		_ASSERTE (defaultReturn == DLG_RETURN_OK);
		break;
	case NDMT_YESNO:
		m_pResponsePairs = m_ResponsePairs_yesno;
		m_iDefaultPairIndex = (defaultReturn == DLG_RETURN_YES)? 0: 1;

		_ASSERTE (defaultReturn == DLG_RETURN_YES ||
				defaultReturn == DLG_RETURN_NO);
		break;
	case NDMT_OKCANCEL:
		m_pResponsePairs = m_ResponsePairs_okcancel;
		m_iDefaultPairIndex = (defaultReturn == DLG_RETURN_OK)? 0: 1;

		_ASSERTE (defaultReturn == DLG_RETURN_OK ||
				defaultReturn == DLG_RETURN_CANCEL);
		break;
	case NDMT_RETRYCANCEL:
		m_pResponsePairs = m_ResponsePairs_retrycancel;
		m_iDefaultPairIndex = (defaultReturn == DLG_RETURN_RETRY)? 0: 1;

		_ASSERTE (defaultReturn == DLG_RETURN_RETRY ||
				defaultReturn == DLG_RETURN_CANCEL);
		break;
	case NDMT_ABORTRETRYIGNORE:
		m_pResponsePairs = m_ResponsePairs_abortretryignore;
		m_iDefaultPairIndex = (defaultReturn == DLG_RETURN_ABORT)? 0: ((defaultReturn == DLG_RETURN_RETRY)? 1: 2);

		_ASSERTE (defaultReturn == DLG_RETURN_ABORT ||
				defaultReturn == DLG_RETURN_RETRY ||
				defaultReturn == DLG_RETURN_IGNORE);
		break;
	case NDMT_YESNOCANCEL:
		m_pResponsePairs = m_ResponsePairs_yesnocancel;
		m_iDefaultPairIndex = (defaultReturn == DLG_RETURN_YES)? 0: ((defaultReturn == DLG_RETURN_NO)? 1: 2);

		_ASSERTE (defaultReturn == DLG_RETURN_YES ||
				defaultReturn == DLG_RETURN_NO ||
				defaultReturn == DLG_RETURN_CANCEL);
		break;
	}
}

bool CResponseGeneric::IsOk (void) const
{
	return m_pResponsePairs != NULL;
}

