#include "stdafx.h"
#include "Sheet.h"

CSheet::CSheet(LPCTSTR lpszTemplateName, CWnd* pParentWnd /*= NULL*/)
	: CDialog (lpszTemplateName, pParentWnd)
{
}

CSheet::CSheet(UINT nIDTemplate, CWnd* pParentWnd /*= NULL*/)
	: CDialog (nIDTemplate, pParentWnd)
{
}
