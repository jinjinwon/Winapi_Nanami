#pragma once

//---------- GDI+ ����� ���� ��� �߰�
#include <ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//---------- GDI+ ����� ���� ��� �߰�

//----- Window�� �ð����� ������ ���� ��� �߰�
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")
//----- Window�� �ð����� ������ ���� ��� �߰�

#include <math.h>  //<-- sqrt() : ��Ʈ�� �Լ� �� �����Լ��� ����ϱ� ���Ͽ�...

class CMyMain
{
public:
	HWND m_hWnd = NULL;

private:
	ULONG_PTR gdiplusToken = NULL; //GDI+ �ʱ�ȭ�� ���� �۷ι� ����
    
    //------------- BackDC ������ ����
	HDC     m_hBackDC = NULL;
	HBITMAP m_hBackBitmap = NULL;
	//------------- BackDC ������ ����

	//-----------��Ÿ Ÿ���� ��� ���� ����
	float   m_DeltaTime;
	DWORD   m_LastTime = 0;
	DWORD   m_CurTime = 0;
	//-----------��Ÿ Ÿ���� ��� ���� ����

	RECT      m_Rect;

public:
	void GameInit(HWND a_hWnd);
	void GameUpdate();
	void GameRender(HDC hdc);
	void GameEnd();
};

extern CMyMain g_CMyMain;  //������ ����