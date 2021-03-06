#pragma once
#include "Vector2D.h"

class CBullet
{
public:
	bool	    m_BLActive;   //총알의 액티브 상태

	float		m_LifeTime;   //총알의 라이프 타임(총알을 몇초동안 날아가게 할 것인지의 시간)
	Vector2D	m_CurPos;     //총알의 현재 위치
	Vector2D	m_DirVec;     //총알의 날아가는 방향벡터
	float		m_MoveSpeed;  //총알의 이동 속도

	float       m_HalfColl;   //충돌 반경

	static HBRUSH	m_B_brsh; //블루브러쉬
	static HPEN	    m_R_pen;  //두께(1), 빨간색 펜
	HGDIOBJ			a_Old_brsh;

public:
	CBullet();
	~CBullet();

	void BulletUpdate(float a_DeltaTime, RECT& a_RT);
	void BulletRender(HDC a_hDC);
};

