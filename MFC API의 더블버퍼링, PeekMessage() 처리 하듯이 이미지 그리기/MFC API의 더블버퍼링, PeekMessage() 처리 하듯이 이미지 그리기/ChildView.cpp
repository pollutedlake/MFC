
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFC API의 더블버퍼링, PeekMessage() 처리 하듯이 이미지 그리기.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
	if (m_MyMain != NULL) {
		m_MyMain->MainDestroy();

		delete m_MyMain;
		m_MyMain = NULL;
	}
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
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
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_MyMain = new CMyMain();

	CDC* pDC = GetDC();
	m_MyMain->MainInit(pDC);		// <--- 게임 초기화
	ReleaseDC(pDC);

	return 0;
}

void CChildView::MyRender()
{
	if (m_MyMain == NULL)
		return;

	m_MyMain->MainUpdate();    //<---- 분리 해도 되고...

	static CDC* pDC = NULL;
	pDC = GetDC();
	static CRect a_rect;
	GetWindowRect(&a_rect);
	m_MyMain->MainRender(pDC, a_rect);
	ReleaseDC(pDC);
}