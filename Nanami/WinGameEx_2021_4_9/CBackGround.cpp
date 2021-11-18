#include "framework.h"
#include "CBackGround.h"

void CBackGround::BG_Init(HWND a_hWnd)
{
    //-------- 기본 GDI 방식으로 배경 이미지 로딩
    HDC a_hdc = GetDC(a_hWnd);
    m_hBackImgDC = CreateCompatibleDC(a_hdc);                                   //<-- MainDC의 복사본을 만든다.
    m_hBackImgBMP = (HBITMAP)LoadImage(NULL, _T("./RscTrunk/sky2.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SelectObject(m_hBackImgDC, m_hBackImgBMP);                                  //복사본 DC에 로딩된 HBITMAP을 붙여서 준비시키기...
    ReleaseDC(a_hWnd, a_hdc);

    BITMAP bm;
    GetObject(m_hBackImgBMP, sizeof(BITMAP), &bm);                              //비트맵 정보 얻기
    m_BackImgWidth = bm.bmWidth;                                                //BMP 원본 가로 사이즈 얻어오기...
    m_BackImgHeight = bm.bmHeight;                                              //BMP 원본 세로 사이즈 얻어오기...

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
    //--- 기본 GDI 방식으로 배경 이미지 그리기...
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
    //-------- 기본 GDI 방식으로 배경 이미지 제거
    if (m_hBackImgDC != NULL)
    {
        DeleteDC(m_hBackImgDC);
        m_hBackImgDC = NULL;
    }
}

CBackGround g_BGround;
