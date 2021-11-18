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

    //-------- GDI+ �ʱ�ȭ(������Ʈ �������ڸ��� �ѹ��� �� �ָ� �ȴ�.)
    GdiplusStartupInput gdiplusStartInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartInput, NULL);

    //---- �ĸ� BackDC ����
    HDC a_hdc = GetDC(m_hWnd);
    m_hBackDC = CreateCompatibleDC(a_hdc);

    //BackDC�� �ٿ��� ������ Bitmap(�̹���)�� �ϳ� ����� �ش�. 
    m_hBackBitmap = CreateCompatibleBitmap(a_hdc,
                        GetSystemMetrics(SM_CXSCREEN), 
                        GetSystemMetrics(SM_CYSCREEN));
    SelectObject(m_hBackDC, m_hBackBitmap);
    ReleaseDC(m_hWnd, a_hdc);

    srand((unsigned)time(NULL));  //���� �ʱ�ȭ

    m_LastTime = timeGetTime();

    //-------- ��׶��� �ʱ�ȭ
    g_BGround.BG_Init(m_hWnd);

    //-------- ���ΰ� �ʱ�ȭ
    g_Hero.Init_Unit(m_hWnd);

    //-------- �Ѿ� �Ŵ��� �ʱ�ȭ
    g_Bullet_Mgr.BLMgr_Init();

    //-------- ���� �Ŵ��� �ʱ�ȭ
    g_Mon_Mgr.MonMgr_Init(m_hWnd);

    //-------- GUI �ʱ�ȭ
    g_GUI_Mgr.UIMgr_Init();

}

void CMyMain::GameUpdate()
{
    if (m_hBackDC == NULL)
        return;

    if (g_Hero.m_CurHP <= 0.0f) //GameOver ó��
        return;

    timeBeginPeriod(1);  //timeGetTime() �Լ��� ���е��� ���̱� ���� �Լ�
    m_CurTime = timeGetTime();
    m_DeltaTime = (m_CurTime - m_LastTime) * 0.001f;
    m_LastTime = m_CurTime;
    timeEndPeriod(1);

    GetClientRect(m_hWnd, &m_Rect);

    //-------- ��׶��� ������Ʈ
    g_BGround.BG_Update(m_DeltaTime, m_Rect);

    //-------- ���ΰ� ������Ʈ
    g_Hero.Update_Unit(m_DeltaTime, m_Rect, m_CurTime);

    //-------- ���� �Ŵ��� ������Ʈ
    g_Mon_Mgr.MonMgr_Update(m_DeltaTime, &g_Hero);

    //-------- �Ѿ� �Ŵ��� ������Ʈ
    g_Bullet_Mgr.BLMgr_Update(m_DeltaTime, m_hWnd, &g_Mon_Mgr);
}

void CMyMain::GameRender(HDC hdc)
{
    if (m_hBackDC == NULL)
        return;

    RECT a_RT;
    GetClientRect(m_hWnd, &a_RT);

    //-------- ��׶��� ����
    g_BGround.BG_Render(m_hBackDC, a_RT);

    //--- ���� �̹��� �׸���...
    g_Mon_Mgr.MonMgr_Render(m_hBackDC);

    //----���ΰ� �׷��ֱ�
    g_Hero.Render_Unit(m_hBackDC);

    //----�Ѿ� �׷��ֱ�
    g_Bullet_Mgr.BLMgr_Render(m_hBackDC);

    //----GUI �׷��ֱ�
    g_GUI_Mgr.UIMgr_Render(m_hBackDC, g_Hero.m_PointCount);

    BitBlt(hdc, 0, 0, a_RT.right, a_RT.bottom, m_hBackDC, 0, 0, SRCCOPY);
}

void CMyMain::GameEnd()
{
    //----���ΰ� �����
    g_Hero.Destroy_Unit();

    //-------- ��׶��� ����
    g_BGround.BG_Destroy();

    //----�Ѿ� �����
    g_Bullet_Mgr.BLMgr_Destroy();

    //--- ���� �����...
    g_Mon_Mgr.MonMgr_Destroy();

    //-------- GUI �����...
    g_GUI_Mgr.UIMgr_Destroy();

    //------- �ĸ� BackDC ����
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

    //----- GDI+ ���� //�ٸ� ��� �̹��� ���� �� �� �������� �Ϲ� �ؾ� �Ѵ�.
    if (gdiplusToken != NULL)
    {
        GdiplusShutdown(gdiplusToken);
        gdiplusToken = NULL;
    }
}

CMyMain g_CMyMain; //������ ����