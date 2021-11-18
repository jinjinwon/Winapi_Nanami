#include "framework.h"
#include "CMonster.h"
#include "CHero.h"
#include <math.h>
#include "GlobalValue.h"

HBRUSH CMonster::m_R_brsh = NULL;

CMonster::CMonster()
{
	m_isActive = false;

	m_MaxHP = 200.0f;
	m_CurHP = 200.0f;

	m_Speed = 200.0f; //150.0f;
	m_HalfColl = 20;

	if (m_R_brsh == NULL)
		m_R_brsh = CreateSolidBrush(RGB(255, 0, 0));
}

CMonster::~CMonster()
{
	if (m_R_brsh != NULL)
	{
		DeleteObject(m_R_brsh);
		m_R_brsh = NULL;
	}
}

void CMonster::Init_Unit()
{
}

void CMonster::Update_Unit(float a_DeltaTime, CHero* a_Hero)
{
	Vector2D a_CacVec = a_Hero->m_CurPos - m_CurPos;

	//-----------Monster AI
	if (a_Hero->m_HalfColl + m_HalfColl < a_CacVec.Magnitude())
	{
		if (m_CharicType == CT_Zombi1)
		{
			//추적
			m_DirVec = a_CacVec;

			m_DirVec.Normalize();
			m_DirVec.x = -1.0f;

			m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_Speed));
		}
		else
		{   //싸인 곡선에 의한 이동 구현
			m_CurPos.x = m_CurPos.x + (-1.0f * a_DeltaTime * m_Speed);
			m_CurPos.y = m_CurPos.y + sin(-m_CurPos.x / (m_Speed * 0.6f));
		}
	}

	//---------- 몬스터 공격 처리 부분
	if (a_CacVec.Magnitude() < (a_Hero->m_HalfColl + m_HalfColl + 10.0f))
	{
		//몬스터가 주인공 공격 공격 
		a_Hero->TakeDamage(50);

		m_isActive = false;
	}

	//---------- 몬스터가 화면 밖으로 나갔으면 제거 
	if (m_CurPos.x < -20.0f)
	{
		m_isActive = false;
	}
}

void CMonster::Render_Unit(HDC a_hDC)
{
	if (m_SocketImg == NULL)
		return;

	//---- HP Bar Render
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hDC, m_R_brsh);
	static float a_CacMXX = 0.0f;
	static float a_CacMYY = (int)(m_HalfHeight * 0.8f);
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CacMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_CurHP / (float)m_MaxHP);

	a_CacMYY = (int)(m_HalfHeight * 0.83f);
	if (m_CharicType == CT_Zombi1)
	{
		a_CacMXX += 9.0f;
		a_CacMYY = (int)(m_HalfHeight * 1.2f);
	}

	Rectangle(a_hDC, m_CurPos.x - a_CacMXX, m_CurPos.y - a_CacMYY,
		m_CurPos.x - a_CacMXX + a_CurHpSize,
		m_CurPos.y - (a_CacMYY + 10.0f));
	SelectObject(a_hDC, h_Old_Brush);

	Graphics graphics(a_hDC);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth,
		m_CurPos.y - (int)(m_HalfHeight * 1.2f),
		(float)m_ImgSizeX, (float)m_ImgSizeY);
}

void CMonster::Destroy_Unit()
{
}

void CMonster::Spawn(float a_XX, float a_YY, Image* a_RefImg)
{
	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_isActive = true;

	m_CurHP = m_MaxHP;

	m_SocketImg = a_RefImg;
	LoadUnitSize();
}

void CMonster::LoadUnitSize()
{
	if (m_SocketImg != NULL)
	{
		m_ImgSizeX = m_SocketImg->GetWidth(); 
		m_ImgSizeY = m_SocketImg->GetHeight();

		m_HalfWidth = m_ImgSizeX / 2;		  
		m_HalfHeight = m_ImgSizeY / 2;		  
	}
}

void CMonster::TakeDamage(float a_Value)
{
	m_CurHP = m_CurHP - a_Value;

	if (m_CurHP <= 0.0f) //몬스터 사망 처리
	{
		CHero::m_PointCount += 10;
		m_isActive = false;
	}
}