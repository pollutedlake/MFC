#pragma once

#include "Vector2D.h"

//------ GDI+ Image ����� ���� ��� �߰�
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image ����� ���� ��� �߰�

class CMyMain
{
	//--- �ĸ� ����� ������ ���� ����
	CBitmap m_Bitmap;
	CDC backBuffDC;
	//--- �ĸ� ����� ������ ���� ����

	//--- DeltaTime ���� ����
	float m_DeltaTime;
	DWORD m_LastTime;
	DWORD m_CurTime;
	//--- DeltaTime ���� ����

	//--- ���ΰ� ��ǥ ���� ������...
	Vector2D m_CurPos = { 300,100 };
	float m_Speed = 300.0f;
	//--- ���ΰ� ��ǥ ���� ������...

	//------ Bmp �ε���
	CDC m_hBmpImgDC;
	CBitmap m_hTexImgBMP;
	int m_TexImgWidth;
	int m_TexImgHeight;
	//------ Bmp �ε���

	//------ GDI+ ���� ����� ����
	ULONG_PTR gdiplusToken = NULL;		// �������� GdiplusShutdown���� ����ϹǷ� �����ʼ�
	//------ GDI+ ���� ����� ����

	//------ GDI+ �̹��� �ε��� ����
	Image* m_pImage = NULL;
	//------ GDI+ �̹��� �ε��� ����

public:
	CMyMain();
	~CMyMain();

public:
	void MainInit(CDC* pDC);
	void MainUpdate();		// ������ ���� ���κ�
	void MainRender(CDC* pDC, CRect& a_dRT);
	void MainDestroy();
};

