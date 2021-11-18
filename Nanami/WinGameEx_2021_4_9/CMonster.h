#pragma once

#include "Vector2D.h"

//----- GDI+ Image ����� ���� ��� �߰�
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image ����� ���� ��� �߰�

class CHero;  //���漱��
enum  CT_Type;

class CMonster
{
	Image* m_SocketImg = nullptr;	//�ִ� ����ó�� ����� ������

	int		m_ImgSizeX;			//�̹����� ���� ������
	int		m_ImgSizeY;			//�̹����� ���� ������
	int		m_HalfWidth = 15;	//�⺻ �̹����� ���� �ݻ�����
	int		m_HalfHeight = 15;	//�⺻ �̹����� ���� �ݻ�����

public:
	bool	     m_isActive = false;	    //��Ƽ�� ���� ����
	CT_Type		 m_CharicType;		//ĳ���� ������ "����"����? "������"����?
	static		 HBRUSH	m_R_brsh;   //����귯�� 
	float        m_MaxHP = 200.0f;  //�ִ� ü��ġ
	float        m_CurHP = 200.0f;  //���� ü��

	////--- ���� ��ǥ ���� ������....
	Vector2D     m_CurPos;			//���� ��ǥ   //#include "Vector2D.h"
	float        m_Speed = 150.0f;	//�̵� �ӵ�
	Vector2D     m_DirVec;			//�̵� ����
	float        m_HalfColl = 20;   //������ �浹 �ݰ�
	////--- ���� ��ǥ ���� ������....

public:
	CMonster();
	~CMonster();

public:
	void Init_Unit();
	void Update_Unit(float a_DeltaTime, CHero* a_Hero);
	void Render_Unit(HDC a_hDC);
	void Destroy_Unit();

	void Spawn(float a_XX, float a_YY, Image* a_RefImg = nullptr);
	void LoadUnitSize();

	void TakeDamage(float a_Value = 10.0f);
};

