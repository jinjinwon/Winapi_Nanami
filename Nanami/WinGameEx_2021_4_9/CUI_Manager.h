#pragma once

//----- GDI+ Image ����� ���� ��� �߰�
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image ����� ���� ��� �߰�

class CUI_Manager
{
	TCHAR m_StrBuff[128];
	HFONT m_OldFont;
	HFONT m_Font_30Godic = NULL;

public:
	void UIMgr_Init();          //�ʱ�ȭ �Լ�
	void UIMgr_Update(HWND a_hWnd, float a_DeltaTime); //������ ���� ���κ�
	void UIMgr_Render(HDC a_hdc, int a_Point = 0);     //������ �׸��� �κ�
	void UIMgr_Destroy();       //���� ó�� �κ�
};

extern CUI_Manager g_GUI_Mgr;
