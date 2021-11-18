#pragma once

#include "CBullet.h"

#include <vector>
using namespace std;

class CMonster_Mgr;

class CBullet_Mgr
{
private:
	vector<CBullet*> m_BullList;  //<--- ÃÑ¾Ë Ç® ¹æ½Ä

public:
	void BLMgr_Init();
	void BLMgr_Update(float a_DeltaTime, HWND a_hWnd, CMonster_Mgr* a_MonMgr = nullptr);
	void BLMgr_Render(HDC a_hDC);
	void BLMgr_Destroy();

	void SpawnBullet(Vector2D a_StartV, Vector2D a_TargetV);
};

extern CBullet_Mgr g_Bullet_Mgr;
