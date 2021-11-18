#pragma once

#include "Vector2D.h"

//----- GDI+ Image 사용을 위한 헤더 추가
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image 사용을 위한 헤더 추가

class CHero
{
	Image* m_SocketImg;			//이미지 소켓
	Image* m_ImgData;			//이미지 로딩용 포인터 변수

	float  m_Speed = 300.0f;	//이동 속도 변수

	float  m_AttackSpeed = 0.2f;    //공격속도
	float  m_BLCycle = 0.0f;		//공격 주기 계산용 변수

	int    m_ImgSizeX;			//이미지의 가로 사이즈
	int    m_ImgSizeY;			//이미지의 세로 사이즈
	int    m_HalfWidth = 15;	//기본 이미지의 가로 반사이즈
	int    m_HalfHeight = 15;	//기본 이미지의 세로 반사이즈

public:
	//----- 유저 캐릭터의 머리위 Hp 바에 필요한 변수
	int      m_CurHP = 150;
	int      m_MaxHp = 150;
	static   HBRUSH	 m_R_brsh;
	//----- 유저 캐릭터의 머리위 Hp 바에 필요한 변수

	Vector2D  m_CurPos;				//캐릭터의 위치 좌표 변수

	////---------- 가감속 관련 변수
	//double		m_LerpDur = 400.0;  //m_LerpDuration 보간 시간 0.5초
	//Vector2D	m_SvDir = { 0.0f, 0.0f };

	//bool        m_IsAccel_X = false;
	//double		m_PER_X = 0.0f;
	//DWORD		m_TimeGap_X = 0;		//시간 격차
	//int			m_DcsGap_X = 0;         //DecreaseGap 감속 계산용 변수, 마이너스값이 나올 수 있다.
	//DWORD		m_AccStTime_X = 0;		//acceleration
	//DWORD		m_CurTime_X = 0;

	//bool        m_IsAccel_Y = false;
	//double		m_PER_Y = 0.0f;
	//DWORD		m_TimeGap_Y = 0;		//시간 격차
	//int			m_DcsGap_Y = 0;         //DecreaseGap 감속 계산용 변수, 마이너스값이 나올 수 있다.
	//DWORD		m_AccStTime_Y = 0;		//acceleration
	//DWORD		m_CurTime_Y = 0;
	////---------- 가감속 관련 변수

	float     m_HalfColl = 20.0f;   //주인공의 충돌 반경

	//------ 능력치
	static   int	m_PointCount;		//점수 
	//------ 능력치

public:
	void Init_Unit(HWND a_hWnd);
	void Update_Unit(float a_DeltaTime, RECT& a_RT, DWORD a_CurTime = 0);
	void Render_Unit(HDC a_hDC);
	void Destroy_Unit();

	void TakeDamage(float a_Damage = 10.0f);

private:
	void LoadUnitSize();
	void HeroLimitMove(RECT& a_RT);
};

extern CHero g_Hero;