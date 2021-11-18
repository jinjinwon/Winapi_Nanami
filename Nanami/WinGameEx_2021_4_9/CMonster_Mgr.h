#pragma once

#include <vector>
using namespace std;

#include "CMonster.h"

class CBullet;

class CMonster_Mgr
{
	HWND m_hWnd;
	RECT   m_cRT;					  //계산용 변수

public:
	vector<Image*>    m_ImgList;      //몬스터 이미지 리스트
	vector<CMonster*> m_MonList;	  //<--- 메모리 풀 방식

	int	   m_SpawnLim = 6;			  //필드에 등장하는 몬스터 마리수 제어 변수

	float	m_DiffSpeed = 200.0f;     //난이도에 따른 몬스터 이동속도 변수
	float   m_DiffSpawn = 0.0f;       //난이도에 따른 몬스터 스폰주기 변수
	float   m_DiffLimit = 6.0f;       //난이도에 따른 몬스터 스폰마리수 변수

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