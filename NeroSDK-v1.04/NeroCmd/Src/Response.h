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

// This simple structure holds a pair of response text and
// the corresponding return value that should be returned
// if that particular text was selected.

struct CResponsePairs {
	LPCSTR m_psButtonText;
	NeroUserDlgInOut m_RetVal;
};

// The following class is a base class for all responses.
// 
class CResponse
{
protected:
	const CResponsePairs * m_pResponsePairs;
	int m_iDefaultPairIndex;
	static bool m_bUseDefaultResponse;

public:
	CResponse (const CResponsePairs * pResponsePairs, int iDefaultPairIndex);

	NeroUserDlgInOut SelectResponse (void) const;
	operator NeroUserDlgInOut () const;

	static void SetUseDefaultResponse (bool bUseDefaultResponse);
};

class CResponseYesNo : public CResponse
{
protected:
	static const CResponsePairs m_ResponsePairs[];
public:
	CResponseYesNo () : CResponse (m_ResponsePairs, 1) {}
};

class CResponseYesNoDefaultIsYes : public CResponseYesNo
{
public:
	CResponseYesNoDefaultIsYes () {m_iDefaultPairIndex = 0;}
};

class CResponseOkay : public CResponse
{
protected:
	static const CResponsePairs m_ResponsePairs[];
public:
	CResponseOkay () : CResponse (m_ResponsePairs, 0) {}
};

