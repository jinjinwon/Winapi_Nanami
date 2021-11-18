#include "framework.h"
#include "CHero.h"
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "CBullet_Mgr.h"

HBRUSH CHero::m_R_brsh = NULL;
int	   CHero::m_PointCount = 0;

void CHero::Init_Unit(HWND a_hWnd)
{
	m_ImgData = Image::FromFile(_T(".\\Nanami\\left_walk\\n031.png"));
	m_SocketImg = m_ImgData;
	LoadUnitSize();

	//-------주인공 좌표 초기화 부분
	RECT a_Crt;
	GetClientRect(a_hWnd, &a_Crt);
	m_CurPos.x = (float)(a_Crt.right / 2);
	m_CurPos.y = (float)(a_Crt.bottom / 2);

	if (m_R_brsh == NULL)
		m_R_brsh = CreateSolidBrush(RGB(255, 0, 0));
}

void CHero::Update_Unit(float a_DeltaTime, RECT& a_RT, DWORD a_CurTime)
{
	//------------- 동시키 처리 방법(대각선 이동을 위해)
	static Vector2D a_CacDir;
	a_CacDir.x = 0.0f;
	a_CacDir.y = 0.0f;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) ||
		(GetAsyncKeyState('A') & 0x8000))
	{
		a_CacDir.x -= 1.0f;
	}
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
		(GetAsyncKeyState('D') & 0x8000))
	{
		a_CacDir.x += 1.0f;
	}
	if ((GetAsyncKeyState(VK_UP) & 0x8000) ||
		(GetAsyncKeyState('W') & 0x8000))
	{
		a_CacDir.y -= 1.0f;
	}
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) ||
		(GetAsyncKeyState('S') & 0x8000))
	{
		a_CacDir.y += 1.0f;
	}

	if (a_CacDir.x != 0.0f || a_CacDir.y != 0.0f)
	{
		a_CacDir.Normalize();
		m_CurPos = m_CurPos + (a_CacDir * (a_DeltaTime * m_Speed));
	}

	HeroLimitMove(a_RT);

	//----총알 발사 
	if (m_BLCycle < m_AttackSpeed)
		m_BLCycle = m_BLCycle + a_DeltaTime;

	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		if (m_AttackSpeed <= m_BLCycle)
		{
			Vector2D a_TargetV;
			Vector2D a_ForWordV = { 1.0f, 0.0f };
			a_TargetV = m_CurPos + a_ForWordV;
			g_Bullet_Mgr.SpawnBullet(m_CurPos, a_TargetV);

			m_BLCycle = 0.0f;
		}
	}
}

void CHero::Render_Unit(HDC a_hDC)
{
	//---- HP Bar Render
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hDC, m_R_brsh);
	static float a_CacMXX = 0.0f;
	static float a_CacMYY = (int)(m_HalfHeight * 0.8f);
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CacMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_CurHP / (float)m_MaxHp);

	a_CacMYY = m_HalfHeight;

	Rectangle(a_hDC, m_CurPos.x - a_CacMXX, m_CurPos.y - a_CacMYY,
		m_CurPos.x - a_CacMXX + a_CurHpSize,
		m_CurPos.y - (a_CacMYY + 10.0f));

	SelectObject(a_hDC, h_Old_Brush);

	Graphics graphics(a_hDC);

	if (m_SocketImg != NULL)
	{
		graphics.DrawImage(m_SocketImg,
			m_CurPos.x - (m_SocketImg->GetWidth() / 2.0f),
			m_CurPos.y - (m_SocketImg->GetHeight() / 2.0f * 1.2f),
			m_SocketImg->GetWidth(),
			m_SocketImg->GetHeight());
	}
}

void CHero::Destroy_Unit()
{
	if (m_ImgData != NULL)
	{
		delete m_ImgData;
		m_ImgData = NULL;
	}
}

void CHero::TakeDamage(float a_Damage)
{
	//몬스터가 주인공 공격 
	m_CurHP = m_CurHP - (int)a_Damage;

	if (m_CurHP <= 0)
	{
		m_CurHP = 0;
	}
}

void CHero::LoadUnitSize()
{
	if (m_SocketImg != NULL)
	{
		m_ImgSizeX = m_SocketImg->GetWidth();
		m_ImgSizeY = m_SocketImg->GetHeight();

		m_HalfWidth = m_ImgSizeX / 2;
		m_HalfHeight = m_ImgSizeY / 2;
	}
}

void CHero::HeroLimitMove(RECT& a_RT)
{
	static float a_CacLXXX = 0.0f;
	static float a_CacLYYY = 0.0f;

	a_CacLXXX = 15;
	if (m_CurPos.x < a_CacLXXX)
	{
		m_CurPos.x = a_CacLXXX;
	}

	if ((float)(a_RT.right - a_CacLXXX) < m_CurPos.x)
	{
		m_CurPos.x = (float)(a_RT.right - a_CacLXXX);
	}

	a_CacLYYY = 30;
	if (m_CurPos.y < a_CacLYYY)
	{
		m_CurPos.y = a_CacLYYY;
	}

	if ((float)(a_RT.bottom - a_CacLYYY) < m_CurPos.y)
	{
		m_CurPos.y = (float)(a_RT.bottom - a_CacLYYY);
	}
}
CHero g_Hero;