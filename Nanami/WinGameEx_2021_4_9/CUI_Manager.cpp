#include "framework.h"
#include "CUI_Manager.h"

void CUI_Manager::UIMgr_Init()
{
	m_Font_30Godic = CreateFont(30, 0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
}

void CUI_Manager::UIMgr_Update(HWND a_hWnd, float a_DeltaTime)
{
}

void CUI_Manager::UIMgr_Render(HDC a_hdc, int a_Point)
{
	m_OldFont = (HFONT)SelectObject(a_hdc, m_Font_30Godic);

	SetTextAlign(a_hdc, TA_LEFT);
	SetBkMode(a_hdc, TRANSPARENT);

	_stprintf_s(m_StrBuff, L"Point : %d", a_Point);
	TextOut(a_hdc, 15, 10, m_StrBuff, (int)_tcslen(m_StrBuff));

	SetBkMode(a_hdc, OPAQUE);        //텍스트 배경 원래대로...
	SetTextAlign(a_hdc, TA_LEFT);    // 원래대로...
	SelectObject(a_hdc, m_OldFont);  // 원래대로...
}

void CUI_Manager::UIMgr_Destroy()
{
	if (m_Font_30Godic != NULL)
	{
		DeleteObject(m_Font_30Godic);
		m_Font_30Godic = NULL;
	}
}

CUI_Manager g_GUI_Mgr;