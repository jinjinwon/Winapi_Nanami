#include "framework.h"
#include "CMyMain.h"
#include "CBackGround.h"
#include "CHero.h"
#include "CBullet_Mgr.h"
#include "CMonster_Mgr.h"
#include "CUI_Manager.h"

#include <Mmsystem.h>               
#include <time.h>					
#pragma comment(lib, "winmm.lib")   


void CMyMain::GameInit(HWND a_hWnd)
{
    m_hWnd = a_hWnd;

    //-------- GDI+ 초기화(프로젝트 시작하자마자 한번만 해 주면 된다.)
    GdiplusStartupInput gdiplusStartInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartInput, NULL);

    //---- 후면 BackDC 생성
    HDC a_hdc = GetDC(m_hWnd);
    m_hBackDC = CreateCompatibleDC(a_hdc);

    //BackDC에 붙여줄 가상의 Bitmap(이미지)를 하나 만들어 준다. 
    m_hBackBitmap = CreateCompatibleBitmap(a_hdc,
                        GetSystemMetrics(SM_CXSCREEN), 
                        GetSystemMetrics(SM_CYSCREEN));
    SelectObject(m_hBackDC, m_hBackBitmap);
    ReleaseDC(m_hWnd, a_hdc);

    srand((unsigned)time(NULL));  //랜덤 초기화

    m_LastTime = timeGetTime();

    //-------- 백그라운드 초기화
    g_BGround.BG_Init(m_hWnd);

    //-------- 주인공 초기화
    g_Hero.Init_Unit(m_hWnd);

    //-------- 총알 매니저 초기화
    g_Bullet_Mgr.BLMgr_Init();

    //-------- 몬스터 매니저 초기화
    g_Mon_Mgr.MonMgr_Init(m_hWnd);

    //-------- GUI 초기화
    g_GUI_Mgr.UIMgr_Init();

}

void CMyMain::GameUpdate()
{
    if (m_hBackDC == NULL)
        return;

    if (g_Hero.m_CurHP <= 0.0f) //GameOver 처리
        return;

    timeBeginPeriod(1);  //timeGetTime() 함수의 정밀도를 높이기 위한 함수
    m_CurTime = timeGetTime();
    m_DeltaTime = (m_CurTime - m_LastTime) * 0.001f;
    m_LastTime = m_CurTime;
    timeEndPeriod(1);

    GetClientRect(m_hWnd, &m_Rect);

    //-------- 백그라운드 업데이트
    g_BGround.BG_Update(m_DeltaTime, m_Rect);

    //-------- 주인공 업데이트
    g_Hero.Update_Unit(m_DeltaTime, m_Rect, m_CurTime);

    //-------- 몬스터 매니저 업데이트
    g_Mon_Mgr.MonMgr_Update(m_DeltaTime, &g_Hero);

    //-------- 총알 매니저 업데이트
    g_Bullet_Mgr.BLMgr_Update(m_DeltaTime, m_hWnd, &g_Mon_Mgr);
}

void CMyMain::GameRender(HDC hdc)
{
    if (m_hBackDC == NULL)
        return;

    RECT a_RT;
    GetClientRect(m_hWnd, &a_RT);

    //-------- 백그라운드 랜더
    g_BGround.BG_Render(m_hBackDC, a_RT);

    //--- 몬스터 이미지 그리기...
    g_Mon_Mgr.MonMgr_Render(m_hBackDC);

    //----주인공 그려주기
    g_Hero.Render_Unit(m_hBackDC);

    //----총알 그려주기
    g_Bullet_Mgr.BLMgr_Render(m_hBackDC);

    //----GUI 그려주기
    g_GUI_Mgr.UIMgr_Render(m_hBackDC, g_Hero.m_PointCount);

    BitBlt(hdc, 0, 0, a_RT.right, a_RT.bottom, m_hBackDC, 0, 0, SRCCOPY);
}

void CMyMain::GameEnd()
{
    //----주인공 지우기
    g_Hero.Destroy_Unit();

    //-------- 백그라운드 제거
    g_BGround.BG_Destroy();

    //----총알 지우기
    g_Bullet_Mgr.BLMgr_Destroy();

    //--- 몬스터 지우기...
    g_Mon_Mgr.MonMgr_Destroy();

    //-------- GUI 지우기...
    g_GUI_Mgr.UIMgr_Destroy();

    //------- 후면 BackDC 제거
    if (m_hBackBitmap != NULL)
    {
        DeleteObject(m_hBackBitmap);
        m_hBackBitmap = NULL;
    }

    if (m_hBackDC != NULL)
    {
        DeleteDC(m_hBackDC);
        m_hBackDC = NULL;
    }

    //----- GDI+ 해제 //다른 모든 이미지 제거 후 맨 마지막에 하번 해야 한다.
    if (gdiplusToken != NULL)
    {
        GdiplusShutdown(gdiplusToken);
        gdiplusToken = NULL;
    }
}

CMyMain g_CMyMain; //변수의 정의