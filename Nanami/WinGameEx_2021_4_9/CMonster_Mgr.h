#pragma once

#include <vector>
using namespace std;

#include "CMonster.h"

class CBullet;

class CMonster_Mgr
{
	HWND m_hWnd;
	RECT   m_cRT;					  //���� ����

public:
	vector<Image*>    m_ImgList;      //���� �̹��� ����Ʈ
	vector<CMonster*> m_MonList;	  //<--- �޸� Ǯ ���

	int	   m_SpawnLim = 6;			  //�ʵ忡 �����ϴ� ���� ������ ���� ����

	float	m_DiffSpeed = 200.0f;     //���̵��� ���� ���� �̵��ӵ� ����
	float   m_DiffSpawn = 0.0f;       //���̵��� ���� ���� �����ֱ� ����
	float   m_DiffLimit = 6.0f;       //���̵��� ���� ���� ���������� ����

public:
	void MonMgr_Init(HWND a_hWnd);
	void MonMgr_Update(float a_DeltaTime, CHero* a_Hero);
	void MonMgr_Render(HDC a_hDC);
	void MonMgr_Destroy();

	void SpawnMonster(float a_DeltaTime);
	void TakeDamage_MonMgr(CBullet* a_RefBullet);
	Image* GetSpMonType(CT_Type& a_SpType);
};

extern 	CMonster_Mgr g_Mon_Mgr;