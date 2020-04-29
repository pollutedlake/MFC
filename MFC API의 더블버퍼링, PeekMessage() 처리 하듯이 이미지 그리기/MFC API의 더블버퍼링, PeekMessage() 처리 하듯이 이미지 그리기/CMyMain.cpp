#include "pch.h"
#include "framework.h"
#include "CMyMain.h"
#include <mmsystem.h>		// timeGetTime() �Լ� ����� ���Ͽ�...
#pragma comment(lib, "winmm.lib")		// timeGetTime() �Լ� ����� ���Ͽ�...
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

	//--- �ĸ� ����� ����
	// DC�� �ٿ��� Bitmap(�̹���) �� ��ȭ���� �ϳ� ����� �´�.
	m_Bitmap.CreateCompatibleBitmap(pDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	// ����ȭ���� ũ�⸦ ������ �Լ�
	backBuffDC.CreateCompatibleDC(pDC);
	backBuffDC.SelectObject(&m_Bitmap);
	//--- �ĸ� ����� ����

	//------ MFC���� �⺻ GDI ������� �̹��� �ε� ���
	m_hBmpImgDC.CreateCompatibleDC(pDC);
	HBITMAP a_hBMP = (HBITMAP)LoadImage(NULL, _T(".\\RscTrunk\\Zone01.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hTexImgBMP.Attach(a_hBMP);
	m_hBmpImgDC.SelectObject(&m_hTexImgBMP);

	BITMAP bm;
	GetObject(m_hTexImgBMP, sizeof(BITMAP), &bm);		// ��Ʈ�� ���� ���
	m_TexImgWidth = bm.bmWidth;
	m_TexImgHeight = bm.bmHeight;
	//------ MFC���� �⺻ GDI ������� �̹��� �ε� ���

	//------ GDI+ �ʱ�ȭ
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	// gdiplusToken <--- �������� GdiplusShutdown���� ����ϹǷ� �����ʼ�
	//------ GDI+ �ʱ�ȭ

	//------ �ش� ��ο��� �̹��� �ҷ�����
	m_pImage = Image::FromFile(_T(".\\RscTrunk\\n002.png"));		// ĳ���� �ε�
	//------ �ش� ��ο��� �̹��� �ҷ�����
}

void CMyMain::MainUpdate()
{
	//------ DeltaTime ������ ���
	timeBeginPeriod(1);		// ���е��� ���̱� ���� �Լ� ���
	m_CurTime = timeGetTime();
	m_DeltaTime = (float)((m_CurTime - m_LastTime) * 0.001f);
	m_LastTime = m_CurTime;
	timeEndPeriod(1);
	//------ DeltaTime ������ ���

	 //------- ĳ���� Ű���� �̵�ó��
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
		a_KDirVec.Normalize(); //��������
		m_CurPos = m_CurPos + (a_KDirVec * (m_DeltaTime * m_Speed));
	}
	//------- ĳ���� Ű���� �̵�ó��
}

void CMyMain::MainRender(CDC* pDC, CRect& a_dRT)
{
	//---------- DC ȭ�� �����
	backBuffDC.PatBlt(0, 0, a_dRT.right, a_dRT.bottom, BLACKNESS);
	//---------- DC ȭ�� �����

	 //CRect a_dRT;
	//CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//if (pMainFrame != NULL)
	//{
	//    CChildView* m_pView = &pMainFrame->m_wndView;  //CChildView Ŭ������ ���ٹ�
	//    if (m_pView != NULL)
	//    {
	//        m_pView->GetClientRect(&a_dRT); //DC ����� ������ ���
	//    }
	//}

	//backBuffDC.BitBlt(0, 0, m_TexImgWidth, m_TexImgHeight, &m_hBmpImgDC, 0, 0, SRCCOPY);

	backBuffDC.StretchBlt(0, 0, a_dRT.right, a_dRT.bottom,
		&m_hBmpImgDC, 0, 0, m_TexImgWidth, m_TexImgHeight, SRCCOPY);

	Graphics graph(backBuffDC.GetSafeHdc()); //or pDC->m_hDC ��� GDC+ ��ü �ϳ� ����
	if (m_pImage != NULL)
	{
		graph.DrawImage(m_pImage,
			Rect(m_CurPos.x, m_CurPos.y, m_pImage->GetWidth(), m_pImage->GetHeight()),
			0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), UnitPixel);
	}

	//---- ȭ�� ��ȯ
	pDC->BitBlt(0, 0, a_dRT.right, a_dRT.bottom, &backBuffDC, 0, 0, SRCCOPY);
}

void CMyMain::MainDestroy()
{
	//--- ����� ����
	m_Bitmap.DeleteObject();
	backBuffDC.DeleteDC();
	//--- ����� ����

	//------ �⺻ GDI ������� ��� �̹��� �ε� �ߴ� ���ҽ� ����
	m_hTexImgBMP.DeleteObject();
	m_hBmpImgDC.DeleteDC();
	//------ �⺻ GDI ������� ��� �̹��� �ε� �ߴ� ���ҽ� ����

	//--- GDI+ �̹��� ���� �κ�
	if (m_pImage != NULL) {
		delete m_pImage;
		m_pImage = NULL;
	}
	//--- GDI+ �̹��� ���� �κ�

	//--- GDI+ ���� // �� �������� ���� �Ѵ�.
	if (gdiplusToken != NULL) {
		GdiplusShutdown(gdiplusToken);
		gdiplusToken = NULL;
	}
	//--- GDI+ ����
}
