
// MFC API의 더블버퍼링, PeekMessage() 처리 하듯이 이미지 그리기.h: MFC API의 더블버퍼링, PeekMessage() 처리 하듯이 이미지 그리기 애플리케이션의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CMFCAPI의더블버퍼링PeekMessage처리하듯이이미지그리기App:
// 이 클래스의 구현에 대해서는 MFC API의 더블버퍼링, PeekMessage() 처리 하듯이 이미지 그리기.cpp을(를) 참조하세요.
//

class CMFCAPI의더블버퍼링PeekMessage처리하듯이이미지그리기App : public CWinApp
{
public:
	CMFCAPI의더블버퍼링PeekMessage처리하듯이이미지그리기App() noexcept;


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMFCAPI의더블버퍼링PeekMessage처리하듯이이미지그리기App theApp;
