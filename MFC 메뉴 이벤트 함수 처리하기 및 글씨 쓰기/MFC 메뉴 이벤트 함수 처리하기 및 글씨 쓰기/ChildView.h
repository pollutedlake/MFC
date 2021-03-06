﻿
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	// ChildView에서도 값이 저장될 수 있어야 되므로 구조체 변수를 선언해 준다.
	DialogData DIData;

	CString m_str = _T("테스트");
	bool m_bKorea = false;
	bool m_bChina = false;

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKorea();
	afx_msg void OnChina();
	afx_msg void OnUpdateChina(CCmdUI* pCmdUI);
	afx_msg void OnUpdateKorea(CCmdUI* pCmdUI);
};

