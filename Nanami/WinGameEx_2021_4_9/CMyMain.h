#pragma once

//---------- GDI+ 사용을 위한 헤더 추가
#include <ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//---------- GDI+ 사용을 위한 헤더 추가

//----- Window의 시간값을 얻어오기 위한 헤더 추가
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")
//----- Window의 시간값을 얻어오기 위한 헤더 추가

#include <math.h>  //<-- sqrt() : 로트값 함수 등 수학함수를 사용하기 위하여...

class CMyMain
{
public:
	HWND m_hWnd = NULL;

private:
	ULONG_PTR gdiplusToken = NULL; //GDI+ 초기화를 위한 글로벌 변수
    
    //------------- BackDC 생성용 변수
	HDC     m_hBackDC = NULL;
	HBITMAP m_hBackBitmap = NULL;
	//------------- BackDC 생성용 변수

	//-----------델타 타임을 얻기 위한 변수
	float   m_DeltaTime;
	DWORD   m_LastTime = 0;
	DWORD   m_CurTime = 0;
	//-----------델타 타임을 얻기 위한 변수

	RECT      m_Rect;

public:
	void GameInit(HWND a_hWnd);
	void GameUpdate();
	void GameRender(HDC hdc);
	void GameEnd();
};

extern CMyMain g_CMyMain;  //변수의 선언