#include "stdafx.h"
#include "Page.h"
#include "Sheet.h"

CPage::CPage(LPCTSTR lpszTemplateName, CSheet * pParentSheet)
	: CDialog (lpszTemplateName, pParentSheet)
	, m_pParentSheet (pParentSheet)
{
}

CPage::CPage(UINT nIDTemplate, CSheet * pParentSheet)
	: CDialog (nIDTemplate, pParentSheet)
	, m_pParentSheet (pParentSheet)
{
}
