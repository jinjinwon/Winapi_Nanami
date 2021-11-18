#include "framework.h"
#include "CMonster_Mgr.h"
#include "CBullet.h"
#include "GlobalValue.h"

void CMonster_Mgr::MonMgr_Init(HWND a_hWnd)
{
	m_hWnd = a_hWnd;

	//----몬스터 이미지 로딩하기
	Image* a_ImgNode = NULL;
	a_ImgNode = Image::FromFile(_T(".\\MonsterImg\\missile.png"));
	m_ImgList.push_back(a_ImgNode);

	a_ImgNode = Image::FromFile(_T(".\\MonsterImg\\Zombi1.png"));
	m_ImgList.push_back(a_ImgNode);
	//----몬스터 이미지 로딩하기

	//----몬스터 메모리풀로 미리 만들어 놓기
	CMonster* a_Node = NULL;
	for (int aii = 0; aii < 20; aii++)
	{
		a_Node = new CMonster();
		a_Node->Init_Unit();
		m_MonList.push_back(a_Node);
	}
	//----몬스터 메모리풀로 미리 만들어 놓기
}

void CMonster_Mgr::MonMgr_Update(float a_DeltaTime, CHero* a_Hero)
{
	//---------- 주기적인 Monster Spawn   
	SpawnMonster(a_DeltaTime);
	//---------- 주기적인 Monster Spawn 

	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == false)
			continue;

		m_MonList[ii]->Update_Unit(a_DeltaTime, a_Hero);

	}//for (int ii = 0; ii < m_MonList.size(); ii++)
}

void CMonster_Mgr::MonMgr_Render(HDC a_hDC)
{
	//--- 몬스터 이미지 그리기...
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == false)
			continue;

		m_MonList[ii]->Render_Unit(a_hDC);
	}
	//--- 몬스터 이미지 그리기...
}

void CMonster_Mgr::MonMgr_Destroy()
{
	//-------------몬스터 이미지 제거하기
	for (int aii = 0; aii < m_ImgList.size(); aii++)
	{
		if (m_ImgList[aii] != NULL)
		{
			delete m_ImgList[aii];
			m_ImgList[aii] = NULL;
		}
	}
	m_ImgList.clear();
	//-------------몬스터 이미지 제거하기

	//몬스터 메모리풀 제거하기... 
	for (int aii = 0; aii < m_MonList.size(); aii++)
	{
		if (m_MonList[aii] != NULL)
		{
			m_MonList[aii]->Destroy_Unit();

			delete m_MonList[aii];
			m_MonList[aii] = NULL;
		}
	}
	m_MonList.clear();
	//몬스터 메모리풀 제거하기... 
}

void CMonster_Mgr::SpawnMonster(float a_DeltaTime)
{
	if (m_DiffSpeed < 350.0f)
	{
		m_DiffSpeed += (a_DeltaTime * 3.0f); //DifficultyTime
		if (350.0f < m_DiffSpeed)
			m_DiffSpeed = 350.0f;
	}

	if (m_DiffSpawn < 3.0f)
	{
		m_DiffSpawn += (a_DeltaTime * 0.03f); //DifficultySpawn
		if (3.0f < m_DiffSpawn)
			m_DiffSpawn = 3.0f;
	}

	if (m_SpawnLim < 10) 
	{
		m_DiffLimit += (a_DeltaTime * 0.03f); //DifficultyLimit
		if (10.0f < m_DiffLimit)
			m_DiffLimit = 10.0f;
		m_SpawnLim = (int)m_DiffLimit;
	}

	//--- 몬스터 Active 감시 및 마리수 카운트 
	static int s_MonCount = 0;
	s_MonCount = 0;
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == true)
		{
			s_MonCount++;
		}
	}
	//--- 몬스터 Active 감시 및 마리수 카운트 

	//---------- 주기적인 Monster Spawn         //몬스터 랜덤 생성
	static float a_SpawnTime = 0.0f;
	a_SpawnTime = a_SpawnTime - a_DeltaTime;

	if (a_SpawnTime < 0.0f)
	{
		if (m_SpawnLim <= s_MonCount)
			return;

		for (int ii = 0; ii < m_MonList.size(); ii++)
		{
			if (m_MonList[ii]->m_isActive == false)
			{
				GetClientRect(m_hWnd, &m_cRT); // 클라이언트 화면의 크기를 받는다

				//////--------Random 하게 화면 밖 영역에서 스폰 좌표 생성하는 부분 
				float a_RndX = 0.0f;
				float a_RndY = 0.0f;
	
				a_RndX = m_cRT.right + ((rand() % 101) + 50);
				a_RndY = (rand() % (m_cRT.bottom - 50)) + 25;			
				//////--------Random 하게 화면 밖 영역에서 스폰 좌표 생성하는 부분 

				CT_Type a_SpType = CT_Zombi1;
				Image* a_RefImg = GetSpMonType(a_SpType);
				m_MonList[ii]->m_CharicType = a_SpType;
				m_MonList[ii]->Spawn(a_RndX, a_RndY, a_RefImg);
				m_MonList[ii]->m_Speed = m_DiffSpeed;

				break;

			}//if (m_MonList[ii]->m_isActive == false)
		}//for (int ii = 0; ii < m_MonList.size(); ii++)

		a_SpawnTime = (float)((rand() % 2) + 2);
		a_SpawnTime = a_SpawnTime - m_DiffSpawn;
		if (a_SpawnTime < 0.3f)
			a_SpawnTime = 0.3f;
	}//if (a_SpawnTime < 0.0f)
	//---------- 주기적인 Monster Spawn  
}

void CMonster_Mgr::TakeDamage_MonMgr(CBullet* a_RefBullet)
{
	if (a_RefBullet == NULL)
		return;

	float a_Damage = 80.0f;
	static Vector2D a_CacBVec;

	//--총알이 몬스터에 맞았으면 제거해 준다. 몬스터 제거 총알 제거
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == false)
			continue;

		a_CacBVec = m_MonList[ii]->m_CurPos - a_RefBullet->m_CurPos;
		if (a_CacBVec.Magnitude() <
			(m_MonList[ii]->m_HalfColl + a_RefBullet->m_HalfColl))   //몬스터의 반지름 20 + 총알의 반지름 20
		{
			m_MonList[ii]->TakeDamage(a_Damage);

			a_RefBullet->m_BLActive = false;  //총알 제거
			break;
		}
	}
	//총알이 몬스터에 맞았으면 제거해 준다. 몬스터 제거 총알 제거
}

Image* CMonster_Mgr::GetSpMonType(CT_Type& a_SpType)
{
	Image* a_RefImg = m_ImgList[0];
	a_SpType = CT_Zombi1;

	int a_Rnd = rand() % 4;
	if (a_Rnd <= 0)
	{
		a_RefImg = m_ImgList[1];
		a_SpType = CT_Zombi2;
	}

	return a_RefImg;
}


CMonster_Mgr g_Mon_Mgr;