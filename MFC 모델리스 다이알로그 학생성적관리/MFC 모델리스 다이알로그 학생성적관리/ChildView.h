
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

#include "CModelessDlg.h"
#include <vector>
using namespace std;

#define IDC_MYBTNDOWN 25000
// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	CButton m_Button;
	CModelessDlg* m_pDlg = NULL;		// 다이알로그 박스 변수 추가

	//------ 모델리스 다이알로그 박스가 부모 윈도우를 기준으로 정렬되게 하는 코드용 변수
	POINT m_MainWPos;
	POINT m_ChildWPos;
	POINT m_MWTopLeft;
	POINT m_DlgSize;
	//------ 모델리스 다이알로그 박스가 부모 윈도우를 기준으로 정렬되게 하는 코드용 변수

	vector<Student> m_StList;

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
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

