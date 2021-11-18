#pragma once
#include "Vector2D.h"

class CBullet
{
public:
	bool	    m_BLActive;   //�Ѿ��� ��Ƽ�� ����

	float		m_LifeTime;   //�Ѿ��� ������ Ÿ��(�Ѿ��� ���ʵ��� ���ư��� �� �������� �ð�)
	Vector2D	m_CurPos;     //�Ѿ��� ���� ��ġ
	Vector2D	m_DirVec;     //�Ѿ��� ���ư��� ���⺤��
	float		m_MoveSpeed;  //�Ѿ��� �̵� �ӵ�

	float       m_HalfColl;   //�浹 �ݰ�

	static HBRUSH	m_B_brsh; //���귯��
	static HPEN	    m_R_pen;  //�β�(1), ������ ��
	HGDIOBJ			a_Old_brsh;

public:
	CBullet();
	~CBullet();

	void BulletUpdate(float a_DeltaTime, RECT& a_RT);
	void BulletRender(HDC a_hDC);
};

