#include "pch.h"
#include "framework.h"
#include "CMyMain.h"
#include <mmsystem.h>		// timeGetTime() 함수 사용을 위하여...
#pragma comment(lib, "winmm.lib")		// timeGetTime() 함수 사용을 위하여...
#include "MainFrm.h"

CMyMain::CMyMain()
{
}

CMyMain::~CMyMain()
{
}

void CMyMain::MainInit(CDC* pDC)
{
	m_LastTime = timeGetTime();

	//--- 후면 백버퍼 생성
	// DC에 붙여줄 Bitmap(이미지) 빈 도화지를 하나 만들어 온다.
	m_Bitmap.CreateCompatibleBitmap(pDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	// 바탕화면의 크기를 얻어오는 함수
	backBuffDC.CreateCompatibleDC(pDC);
	backBuffDC.SelectObject(&m_Bitmap);
	//--- 후면 백버퍼 생성

	//------ MFC에서 기본 GDI 방식으로 이미지 로딩 방법
	m_hBmpImgDC.CreateCompatibleDC(pDC);
	HBITMAP a_hBMP = (HBITMAP)LoadImage(NULL, _T(".\\RscTrunk\\Zone01.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hTexImgBMP.Attach(a_hBMP);
	m_hBmpImgDC.SelectObject(&m_hTexImgBMP);

	BITMAP bm;
	GetObject(m_hTexImgBMP, sizeof(BITMAP), &bm);		// 비트맵 정보 얻기
	m_TexImgWidth = bm.bmWidth;
	m_TexImgHeight = bm.bmHeight;
	//------ MFC에서 기본 GDI 방식으로 이미지 로딩 방법

	//------ GDI+ 초기화
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	// gdiplusToken <--- 마지막에 GdiplusShutdown에서 사용하므로 저장필수
	//------ GDI+ 초기화

	//------ 해당 경로에서 이미지 불러오기
	m_pImage = Image::FromFile(_T(".\\RscTrunk\\n002.png"));		// 캐릭터 로딩
	//------ 해당 경로에서 이미지 불러오기
}

void CMyMain::MainUpdate()
{
	//------ DeltaTime 얻어오는 방법
	timeBeginPeriod(1);		// 정밀도를 높이기 위한 함수 사용
	m_CurTime = timeGetTime();
	m_DeltaTime = (float)((m_CurTime - m_LastTime) * 0.001f);
	m_LastTime = m_CurTime;
	timeEndPeriod(1);
	//------ DeltaTime 얻어오는 방법

	 //------- 캐릭터 키보드 이동처리
	static Vector2D a_KDirVec;
	a_KDirVec.x = 0.0f;
	a_KDirVec.y = 0.0f;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
	{
		a_KDirVec.x -= 1.0f;
	}
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
	{
		a_KDirVec.x += 1.0f;
	}
	if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
	{
		a_KDirVec.y -= 1.0f;
	}
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
	{
		a_KDirVec.y += 1.0f;
	}

	if (a_KDirVec.x != 0.0f || a_KDirVec.y != 0.0f)
	{
		a_KDirVec.Normalize(); //단위벡터
		m_CurPos = m_CurPos + (a_KDirVec * (m_DeltaTime * m_Speed));
	}
	//------- 캐릭터 키보드 이동처리
}

void CMyMain::MainRender(CDC* pDC, CRect& a_dRT)
{
	//---------- DC 화면 지우기
	backBuffDC.PatBlt(0, 0, a_dRT.right, a_dRT.bottom, BLACKNESS);
	//---------- DC 화면 지우기

	 //CRect a_dRT;
	//CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//if (pMainFrame != NULL)
	//{
	//    CChildView* m_pView = &pMainFrame->m_wndView;  //CChildView 클래스에 접근법
	//    if (m_pView != NULL)
	//    {
	//        m_pView->GetClientRect(&a_dRT); //DC 사이즈를 얻어오는 방법
	//    }
	//}

	//backBuffDC.BitBlt(0, 0, m_TexImgWidth, m_TexImgHeight, &m_hBmpImgDC, 0, 0, SRCCOPY);

	backBuffDC.StretchBlt(0, 0, a_dRT.right, a_dRT.bottom,
		&m_hBmpImgDC, 0, 0, m_TexImgWidth, m_TexImgHeight, SRCCOPY);

	Graphics graph(backBuffDC.GetSafeHdc()); //or pDC->m_hDC 사용 GDC+ 객체 하나 선언
	if (m_pImage != NULL)
	{
		graph.DrawImage(m_pImage,
			Rect(m_CurPos.x, m_CurPos.y, m_pImage->GetWidth(), m_pImage->GetHeight()),
			0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), UnitPixel);
	}

	//---- 화면 전환
	pDC->BitBlt(0, 0, a_dRT.right, a_dRT.bottom, &backBuffDC, 0, 0, SRCCOPY);
}

void CMyMain::MainDestroy()
{
	//--- 백버퍼 삭제
	m_Bitmap.DeleteObject();
	backBuffDC.DeleteDC();
	//--- 백버퍼 삭제

	//------ 기본 GDI 방식으로 배경 이미지 로딩 했던 리소스 제거
	m_hTexImgBMP.DeleteObject();
	m_hBmpImgDC.DeleteDC();
	//------ 기본 GDI 방식으로 배경 이미지 로딩 했던 리소스 제거

	//--- GDI+ 이미지 제거 부분
	if (m_pImage != NULL) {
		delete m_pImage;
		m_pImage = NULL;
	}
	//--- GDI+ 이미지 제거 부분

	//--- GDI+ 해제 // 맨 마지막에 해제 한다.
	if (gdiplusToken != NULL) {
		GdiplusShutdown(gdiplusToken);
		gdiplusToken = NULL;
	}
	//--- GDI+ 해제
}
