#include "framework.h"
#include "CBackGround.h"

void CBackGround::BG_Init(HWND a_hWnd)
{
    //-------- �⺻ GDI ������� ��� �̹��� �ε�
    HDC a_hdc = GetDC(a_hWnd);
    m_hBackImgDC = CreateCompatibleDC(a_hdc);                                   //<-- MainDC�� ���纻�� �����.
    m_hBackImgBMP = (HBITMAP)LoadImage(NULL, _T("./RscTrunk/sky2.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SelectObject(m_hBackImgDC, m_hBackImgBMP);                                  //���纻 DC�� �ε��� HBITMAP�� �ٿ��� �غ��Ű��...
    ReleaseDC(a_hWnd, a_hdc);

    BITMAP bm;
    GetObject(m_hBackImgBMP, sizeof(BITMAP), &bm);                              //��Ʈ�� ���� ���
    m_BackImgWidth = bm.bmWidth;                                                //BMP ���� ���� ������ ������...
    m_BackImgHeight = bm.bmHeight;                                              //BMP ���� ���� ������ ������...

    if (m_hBackImgBMP != NULL)
    {
        DeleteObject(m_hBackImgBMP);
        m_hBackImgBMP = NULL;
    }

}

void CBackGround::BG_Update(float a_DeltaTime, RECT& a_RT)
{
    m_CurPos.x = m_CurPos.x + (m_SclDir.x * (a_DeltaTime * 150.0f));

    if(m_CurPos.x <= -(float)a_RT.right)
    {
        m_CurPos.x = 0.0f;
    }
}

void CBackGround::BG_Render(HDC a_hdc, RECT& a_RT)
{
    //--- �⺻ GDI ������� ��� �̹��� �׸���...
    if (m_hBackImgDC != NULL)
    {
        StretchBlt(a_hdc, m_CurPos.x, m_CurPos.y, a_RT.right, a_RT.bottom,
            m_hBackImgDC, 0, 0, m_BackImgWidth, m_BackImgHeight, SRCCOPY);

        StretchBlt(a_hdc, m_CurPos.x + (float)a_RT.right, m_CurPos.y, a_RT.right, a_RT.bottom,
            m_hBackImgDC, 0, 0, m_BackImgWidth, m_BackImgHeight, SRCCOPY);
    }
}

void CBackGround::BG_Destroy()
{
    //-------- �⺻ GDI ������� ��� �̹��� ����
    if (m_hBackImgDC != NULL)
    {
        DeleteDC(m_hBackImgDC);
        m_hBackImgDC = NULL;
    }
}

CBackGround g_BGround;
