
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "DC에 글씨쓰기와 그림 그리기.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_NewPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	m_NewBrush.CreateSolidBrush(RGB(0, 192, 0));

	m_NewFont.CreateFont(		// object의 생성
		20,		// 문자 높이
		0,		// 문자 폭
		0,		// 기울기 각도
		0,		// 문자 방향
		FW_HEAVY,		// 문자 굵기
		FALSE,		// 문자 기울림 모양
		FALSE,		// 밑 줄
		FALSE,		// 취소선
		DEFAULT_CHARSET,		// 문자 셋
		OUT_DEFAULT_PRECIS,		// 출력 정확도
		CLIP_DEFAULT_PRECIS,		// 킬립핑 정확도
		DEFAULT_QUALITY,		// 출력의 질
		DEFAULT_PITCH,		// 자간 거리
		_T("궁서")		// 문자 모양
	);
}

CChildView::~CChildView()
{
	m_NewPen.DeleteObject();
	m_NewBrush.DeleteObject();
	m_NewFont.DeleteObject();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	dc.TextOut(10, 10, _T("안녕하세요"));
	dc.Rectangle(100, 10, 200, 110);
	
	pOldPen = dc.SelectObject(&m_NewPen);

	dc.TextOut(10, 210, _T("안녕하세요"));
	dc.Rectangle(100, 160, 200, 260);

	pOldBrush = dc.SelectObject(&m_NewBrush);
	dc.TextOut(10, 310, _T("안녕하세요"));
	dc.Rectangle(100, 310, 200, 410);

	pOldFont = dc.SelectObject(&m_NewFont);

	dc.TextOut(10, 460, _T("안녕하세요"));
	dc.Rectangle(160, 460, 260, 560);

	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	MessageBox(_T("내용"), _T("테스트"), MB_OK);

	CWnd::OnLButtonDown(nFlags, point);
}
