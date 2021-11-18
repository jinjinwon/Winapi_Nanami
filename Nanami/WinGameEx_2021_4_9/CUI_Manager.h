#pragma once

//----- GDI+ Image 사용을 위한 헤더 추가
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image 사용을 위한 헤더 추가

class CUI_Manager
{
	TCHAR m_StrBuff[128];
	HFONT m_OldFont;
	HFONT m_Font_30Godic = NULL;

public:
	void UIMgr_Init();          //초기화 함수
	void UIMgr_Update(HWND a_hWnd, float a_DeltaTime); //게임의 연산 담당부분
	void UIMgr_Render(HDC a_hdc, int a_Point = 0);     //게임의 그리기 부분
	void UIMgr_Destroy();       //종료 처리 부분
};

extern CUI_Manager g_GUI_Mgr;
