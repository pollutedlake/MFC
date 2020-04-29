#pragma once

#include "Vector2D.h"

//------ GDI+ Image 사용을 위한 헤더 추가
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image 사용을 위한 헤더 추가

class CMyMain
{
	//--- 후면 백버퍼 생성을 위한 변수
	CBitmap m_Bitmap;
	CDC backBuffDC;
	//--- 후면 백버퍼 생성을 위한 변수

	//--- DeltaTime 관련 변수
	float m_DeltaTime;
	DWORD m_LastTime;
	DWORD m_CurTime;
	//--- DeltaTime 관련 변수

	//--- 주인공 좌표 계산용 변수들...
	Vector2D m_CurPos = { 300,100 };
	float m_Speed = 300.0f;
	//--- 주인공 좌표 계산용 변수들...

	//------ Bmp 로딩용
	CDC m_hBmpImgDC;
	CBitmap m_hTexImgBMP;
	int m_TexImgWidth;
	int m_TexImgHeight;
	//------ Bmp 로딩용

	//------ GDI+ 에서 사용할 변수
	ULONG_PTR gdiplusToken = NULL;		// 마지막에 GdiplusShutdown에서 사용하므로 저장필수
	//------ GDI+ 에서 사용할 변수

	//------ GDI+ 이미지 로딩용 변수
	Image* m_pImage = NULL;
	//------ GDI+ 이미지 로딩용 변수

public:
	CMyMain();
	~CMyMain();

public:
	void MainInit(CDC* pDC);
	void MainUpdate();		// 게임의 연산 담당부분
	void MainRender(CDC* pDC, CRect& a_dRT);
	void MainDestroy();
};

