#include "framework.h"
#include "CBullet.h"

//--Class �Ҽ��� Static ������ �ʱ�ȭ (�ʼ�)
HBRUSH CBullet::m_B_brsh = NULL;
HPEN   CBullet::m_R_pen = NULL;

CBullet::CBullet()
{
	if (m_B_brsh == NULL)
		m_B_brsh = CreateSolidBrush(RGB(0, 100, 255));

	if (m_R_pen == NULL)
		m_R_pen = (HPEN)GetStockObject(NULL_PEN);

	m_BLActive  = false;					//��Ƽ�� ��Ȱ��ȭ�� ����
	m_LifeTime  = 4.0f;						//4��
	m_MoveSpeed = 800.0f;					//800�ȼ� / 1��
	m_HalfColl  = 20.0f;					//�浹�ݰ�
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
	//�Ѿ� �̵�ó��

	if(a_RT.right + 10.0f < m_CurPos.x)
		m_BLActive = false;
}

void CBullet::BulletRender(HDC a_hDC)
{
	Rectangle(a_hDC, (int)(m_CurPos.x - 12.0f), (int)(m_CurPos.y - 2.5f), 
					(int)(m_CurPos.x + 12.0f), (int)(m_CurPos.y + 2.5f));
}
