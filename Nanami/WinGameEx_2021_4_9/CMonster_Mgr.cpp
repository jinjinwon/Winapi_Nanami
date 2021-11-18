#include "framework.h"
#include "CMonster_Mgr.h"
#include "CBullet.h"
#include "GlobalValue.h"

void CMonster_Mgr::MonMgr_Init(HWND a_hWnd)
{
	m_hWnd = a_hWnd;

	//----���� �̹��� �ε��ϱ�
	Image* a_ImgNode = NULL;
	a_ImgNode = Image::FromFile(_T(".\\MonsterImg\\missile.png"));
	m_ImgList.push_back(a_ImgNode);

	a_ImgNode = Image::FromFile(_T(".\\MonsterImg\\Zombi1.png"));
	m_ImgList.push_back(a_ImgNode);
	//----���� �̹��� �ε��ϱ�

	//----���� �޸�Ǯ�� �̸� ����� ����
	CMonster* a_Node = NULL;
	for (int aii = 0; aii < 20; aii++)
	{
		a_Node = new CMonster();
		a_Node->Init_Unit();
		m_MonList.push_back(a_Node);
	}
	//----���� �޸�Ǯ�� �̸� ����� ����
}

void CMonster_Mgr::MonMgr_Update(float a_DeltaTime, CHero* a_Hero)
{
	//---------- �ֱ����� Monster Spawn   
	SpawnMonster(a_DeltaTime);
	//---------- �ֱ����� Monster Spawn 

	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == false)
			continue;

		m_MonList[ii]->Update_Unit(a_DeltaTime, a_Hero);

	}//for (int ii = 0; ii < m_MonList.size(); ii++)
}

void CMonster_Mgr::MonMgr_Render(HDC a_hDC)
{
	//--- ���� �̹��� �׸���...
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == false)
			continue;

		m_MonList[ii]->Render_Unit(a_hDC);
	}
	//--- ���� �̹��� �׸���...
}

void CMonster_Mgr::MonMgr_Destroy()
{
	//-------------���� �̹��� �����ϱ�
	for (int aii = 0; aii < m_ImgList.size(); aii++)
	{
		if (m_ImgList[aii] != NULL)
		{
			delete m_ImgList[aii];
			m_ImgList[aii] = NULL;
		}
	}
	m_ImgList.clear();
	//-------------���� �̹��� �����ϱ�

	//���� �޸�Ǯ �����ϱ�... 
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
	//���� �޸�Ǯ �����ϱ�... 
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

	//--- ���� Active ���� �� ������ ī��Ʈ 
	static int s_MonCount = 0;
	s_MonCount = 0;
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == true)
		{
			s_MonCount++;
		}
	}
	//--- ���� Active ���� �� ������ ī��Ʈ 

	//---------- �ֱ����� Monster Spawn         //���� ���� ����
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
				GetClientRect(m_hWnd, &m_cRT); // Ŭ���̾�Ʈ ȭ���� ũ�⸦ �޴´�

				//////--------Random �ϰ� ȭ�� �� �������� ���� ��ǥ �����ϴ� �κ� 
				float a_RndX = 0.0f;
				float a_RndY = 0.0f;
	
				a_RndX = m_cRT.right + ((rand() % 101) + 50);
				a_RndY = (rand() % (m_cRT.bottom - 50)) + 25;			
				//////--------Random �ϰ� ȭ�� �� �������� ���� ��ǥ �����ϴ� �κ� 

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
	//---------- �ֱ����� Monster Spawn  
}

void CMonster_Mgr::TakeDamage_MonMgr(CBullet* a_RefBullet)
{
	if (a_RefBullet == NULL)
		return;

	float a_Damage = 80.0f;
	static Vector2D a_CacBVec;

	//--�Ѿ��� ���Ϳ� �¾����� ������ �ش�. ���� ���� �Ѿ� ����
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == false)
			continue;

		a_CacBVec = m_MonList[ii]->m_CurPos - a_RefBullet->m_CurPos;
		if (a_CacBVec.Magnitude() <
			(m_MonList[ii]->m_HalfColl + a_RefBullet->m_HalfColl))   //������ ������ 20 + �Ѿ��� ������ 20
		{
			m_MonList[ii]->TakeDamage(a_Damage);

			a_RefBullet->m_BLActive = false;  //�Ѿ� ����
			break;
		}
	}
	//�Ѿ��� ���Ϳ� �¾����� ������ �ش�. ���� ���� �Ѿ� ����
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