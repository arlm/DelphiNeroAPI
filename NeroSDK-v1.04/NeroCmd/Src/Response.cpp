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

