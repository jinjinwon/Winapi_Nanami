#pragma once

#include "Vector2D.h"

//----- GDI+ Image 사용을 위한 헤더 추가
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image 사용을 위한 헤더 추가

class CHero;  //전방선언
enum  CT_Type;

class CMonster
{
	Image* m_SocketImg = nullptr;	//애니 소켓처럼 사용할 포인터

	int		m_ImgSizeX;			//이미지의 가로 사이즈
	int		m_ImgSizeY;			//이미지의 세로 사이즈
	int		m_HalfWidth = 15;	//기본 이미지의 가로 반사이즈
	int		m_HalfHeight = 15;	//기본 이미지의 세로 반사이즈

public:
	bool	     m_isActive = false;	    //액티브 상태 변수
	CT_Type		 m_CharicType;		//캐릭터 종류가 "몬스터"인지? "나나미"인지?
	static		 HBRUSH	m_R_brsh;   //레드브러쉬 
	float        m_MaxHP = 200.0f;  //최대 체력치
	float        m_CurHP = 200.0f;  //현재 체력

	////--- 몬스터 좌표 계산용 변수들....
	Vector2D     m_CurPos;			//현재 좌표   //#include "Vector2D.h"
	float        m_Speed = 150.0f;	//이동 속도
	Vector2D     m_DirVec;			//이동 방향
	float        m_HalfColl = 20;   //몬스터의 충돌 반경
	////--- 몬스터 좌표 계산용 변수들....

public:
	CMonster();
	~CMonster();

public:
	void Init_Unit();
	void Update_Unit(float a_DeltaTime, CHero* a_Hero);
	void Render_Unit(HDC a_hDC);
	void Destroy_Unit();

	void Spawn(float a_XX, float a_YY, Image* a_RefImg = nullptr);
	void LoadUnitSize();

	void TakeDamage(float a_Value = 10.0f);
};

