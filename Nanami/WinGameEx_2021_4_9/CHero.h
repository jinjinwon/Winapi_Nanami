#pragma once

#include "Vector2D.h"

//----- GDI+ Image ����� ���� ��� �߰�
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image ����� ���� ��� �߰�

class CHero
{
	Image* m_SocketImg;			//�̹��� ����
	Image* m_ImgData;			//�̹��� �ε��� ������ ����

	float  m_Speed = 300.0f;	//�̵� �ӵ� ����

	float  m_AttackSpeed = 0.2f;    //���ݼӵ�
	float  m_BLCycle = 0.0f;		//���� �ֱ� ���� ����

	int    m_ImgSizeX;			//�̹����� ���� ������
	int    m_ImgSizeY;			//�̹����� ���� ������
	int    m_HalfWidth = 15;	//�⺻ �̹����� ���� �ݻ�����
	int    m_HalfHeight = 15;	//�⺻ �̹����� ���� �ݻ�����

public:
	//----- ���� ĳ������ �Ӹ��� Hp �ٿ� �ʿ��� ����
	int      m_CurHP = 150;
	int      m_MaxHp = 150;
	static   HBRUSH	 m_R_brsh;
	//----- ���� ĳ������ �Ӹ��� Hp �ٿ� �ʿ��� ����

	Vector2D  m_CurPos;				//ĳ������ ��ġ ��ǥ ����

	////---------- ������ ���� ����
	//double		m_LerpDur = 400.0;  //m_LerpDuration ���� �ð� 0.5��
	//Vector2D	m_SvDir = { 0.0f, 0.0f };

	//bool        m_IsAccel_X = false;
	//double		m_PER_X = 0.0f;
	//DWORD		m_TimeGap_X = 0;		//�ð� ����
	//int			m_DcsGap_X = 0;         //DecreaseGap ���� ���� ����, ���̳ʽ����� ���� �� �ִ�.
	//DWORD		m_AccStTime_X = 0;		//acceleration
	//DWORD		m_CurTime_X = 0;

	//bool        m_IsAccel_Y = false;
	//double		m_PER_Y = 0.0f;
	//DWORD		m_TimeGap_Y = 0;		//�ð� ����
	//int			m_DcsGap_Y = 0;         //DecreaseGap ���� ���� ����, ���̳ʽ����� ���� �� �ִ�.
	//DWORD		m_AccStTime_Y = 0;		//acceleration
	//DWORD		m_CurTime_Y = 0;
	////---------- ������ ���� ����

	float     m_HalfColl = 20.0f;   //���ΰ��� �浹 �ݰ�

	//------ �ɷ�ġ
	static   int	m_PointCount;		//���� 
	//------ �ɷ�ġ

public:
	void Init_Unit(HWND a_hWnd);
	void Update_Unit(float a_DeltaTime, RECT& a_RT, DWORD a_CurTime = 0);
	void Render_Unit(HDC a_hDC);
	void Destroy_Unit();

	void TakeDamage(float a_Damage = 10.0f);

private:
	void LoadUnitSize();
	void HeroLimitMove(RECT& a_RT);
};

extern CHero g_Hero;