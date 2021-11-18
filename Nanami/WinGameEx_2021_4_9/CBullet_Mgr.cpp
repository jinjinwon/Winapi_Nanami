#include "framework.h"
#include "CBullet_Mgr.h"
#include "CMonster_Mgr.h"

void CBullet_Mgr::BLMgr_Init()
{
	//----총알 메모리풀로 미리 만들어 놓기	
	CBullet* a_BLNode = NULL;
	for (int aii = 0; aii < 200; aii++)
	{
		a_BLNode = new CBullet();
		m_BullList.push_back(a_BLNode);
	}
}

void CBullet_Mgr::BLMgr_Update(float a_DeltaTime, HWND a_hWnd, CMonster_Mgr* a_MonMgr)
{
	RECT a_Crt;
	GetClientRect(a_hWnd, &a_Crt);

	for (int aii = 0; aii < m_BullList.size(); aii++)
	{
		if (m_BullList[aii]->m_BLActive == false)
			continue;

		m_BullList[aii]->BulletUpdate(a_DeltaTime, a_Crt);

		if (a_MonMgr != nullptr)
			a_MonMgr->TakeDamage_MonMgr(m_BullList[aii]);
	}
}

void CBullet_Mgr::BLMgr_Render(HDC a_hDC)
{
	static HGDIOBJ a_Old_pen;
	static HGDIOBJ a_Old_brsh;

	a_Old_pen = SelectObject(a_hDC, CBullet::m_R_pen);
	//HGDIOBJ 모든 GDI object의 집합														
	a_Old_brsh = SelectObject(a_hDC, CBullet::m_B_brsh);

	for (int aii = 0; aii < m_BullList.size(); aii++)
	{
		if (m_BullList[aii]->m_BLActive == false)
			continue;

		m_BullList[aii]->BulletRender(a_hDC);

	}

	SelectObject(a_hDC, a_Old_pen); //기존 펜으로 교체
	SelectObject(a_hDC, a_Old_brsh);//기존 브러쉬로 교체
}

void CBullet_Mgr::BLMgr_Destroy()
{
	//총알 메모리풀 제거하기... 
	for (int aii = 0; aii < m_BullList.size(); aii++)
	{
		if (m_BullList[aii] != NULL)
		{
			delete m_BullList[aii];
			m_BullList[aii] = NULL;
		}
	}
	m_BullList.clear();
}

void CBullet_Mgr::SpawnBullet(Vector2D a_StartV, Vector2D a_TargetV)
{
	CBullet* a_BNode = NULL;

	for (int aii = 0; aii < m_BullList.size(); aii++)
	{
		if (m_BullList[aii]->m_BLActive == false)
		{
			a_BNode = m_BullList[aii];
			break;
		}
	}

	if (a_BNode == NULL)
	{
		a_BNode = new CBullet();
		m_BullList.push_back(a_BNode);
	}

	a_BNode->m_CurPos.x = a_StartV.x;
	a_BNode->m_CurPos.y = a_StartV.y;

	a_BNode->m_DirVec = a_TargetV - a_StartV;
	a_BNode->m_DirVec.Normalize();
	a_BNode->m_CurPos = a_BNode->m_CurPos + a_BNode->m_DirVec * 20.0f;
	a_BNode->m_BLActive = true;
	a_BNode->m_LifeTime = 3.0f;
}

CBullet_Mgr g_Bullet_Mgr;