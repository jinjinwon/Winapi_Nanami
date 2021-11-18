#pragma once

#include "Vector2D.h"

class CBackGround
{
	Vector2D  m_CurPos = { 0.0f, 0.0f };				//캐릭터의 위치 좌표 변수
	Vector2D  m_SclDir = { -1.0f, 0.0f };

public:
	//------------- 기본 GDI 방식으로 배경 이미지 로딩용 변수
	HDC     m_hBackImgDC = NULL;	//이미지 저장용 DC
	HBITMAP m_hBackImgBMP = NULL;	//이미지 로딩용 임시 BMP
	int     m_BackImgWidth = 0;		//이미지 가로 사이즈
	int     m_BackImgHeight = 0;    //이미지 세로 사이즈
	//------------- 기본 GDI 방식으로 배경 이미지 로딩용 변수

public:
	void BG_Init(HWND a_hWnd);				//초기화 함수
	void BG_Update(float a_DeltaTime, RECT& a_RT);				//게임의 연산 담당부분
	void BG_Render(HDC a_hdc, RECT& a_RT);	//게임의 그리기 부분
	void BG_Destroy();						//종료 처리 부분
};

extern CBackGround g_BGround;