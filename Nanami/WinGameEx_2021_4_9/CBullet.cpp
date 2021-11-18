#include "framework.h"
#include "CBullet.h"

//--Class 소속의 Static 변수들 초기화 (필수)
HBRUSH CBullet::m_B_brsh = NULL;
HPEN   CBullet::m_R_pen = NULL;

CBullet::CBullet()
{
	if (m_B_brsh == NULL)
		m_B_brsh = CreateSolidBrush(RGB(0, 100, 255));

	if (m_R_pen == NULL)
		m_R_pen = (HPEN)GetStockObject(NULL_PEN);

	m_BLActive  = false;					//액티브 비활성화로 시작
	m_LifeTime  = 4.0f;						//4초
	m_MoveSpeed = 800.0f;					//800픽셀 / 1초
	m_HalfColl  = 20.0f;					//충돌반경
}

CBullet::~CBullet()
{
	if (m_B_brsh != NULL)
	{
		DeleteObject(m_B_brsh);
		m_B_brsh = NULL;
	}

	if (m_R_pen != NULL)
	{
		DeleteObject(m_R_pen);
		m_R_pen = NULL;
	}
}

void CBullet::BulletUpdate(float a_DeltaTime, RECT& a_RT)
{
	m_LifeTime = m_LifeTime - a_DeltaTime;
	if (m_LifeTime < 0.0f)
	{
		m_BLActive = false;
	}

	m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_MoveSpeed));
	//총알 이동처리

	if(a_RT.right + 10.0f < m_CurPos.x)
		m_BLActive = false;
}

void CBullet::BulletRender(HDC a_hDC)
{
	Rectangle(a_hDC, (int)(m_CurPos.x - 12.0f), (int)(m_CurPos.y - 2.5f), 
					(int)(m_CurPos.x + 12.0f), (int)(m_CurPos.y + 2.5f));
}
