#pragma once

#include "Vector2D.h"

class CBackGround
{
	Vector2D  m_CurPos = { 0.0f, 0.0f };				//ĳ������ ��ġ ��ǥ ����
	Vector2D  m_SclDir = { -1.0f, 0.0f };

public:
	//------------- �⺻ GDI ������� ��� �̹��� �ε��� ����
	HDC     m_hBackImgDC = NULL;	//�̹��� ����� DC
	HBITMAP m_hBackImgBMP = NULL;	//�̹��� �ε��� �ӽ� BMP
	int     m_BackImgWidth = 0;		//�̹��� ���� ������
	int     m_BackImgHeight = 0;    //�̹��� ���� ������
	//------------- �⺻ GDI ������� ��� �̹��� �ε��� ����

public:
	void BG_Init(HWND a_hWnd);				//�ʱ�ȭ �Լ�
	void BG_Update(float a_DeltaTime, RECT& a_RT);				//������ ���� ���κ�
	void BG_Render(HDC a_hdc, RECT& a_RT);	//������ �׸��� �κ�
	void BG_Destroy();						//���� ó�� �κ�
};

extern CBackGround g_BGround;