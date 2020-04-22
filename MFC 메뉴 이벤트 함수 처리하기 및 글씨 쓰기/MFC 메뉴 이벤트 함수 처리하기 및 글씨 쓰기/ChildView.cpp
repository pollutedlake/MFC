
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFC 메뉴 이벤트 함수 처리하기 및 글씨 쓰기.h"
#include "ChildView.h"
#include "CMyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_KOREA, &CChildView::OnKorea)
	ON_COMMAND(ID_CHINA, &CChildView::OnChina)
	ON_UPDATE_COMMAND_UI(ID_CHINA, &CChildView::OnUpdateChina)
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
	dc.TextOut(30, 30, m_str);

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnKorea()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bKorea = true;
	m_bChina = false;
	m_str = _T("한국을 선택하였습니다.");
	Invalidate();

	CMyDialog dlg;
	dlg.DoModal();
}


void CChildView::OnChina()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bKorea = false;
	m_bChina = true;
	m_str = _T("중국을 선택하였습니다.");
	Invalidate();
}


void CChildView::OnUpdateChina(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_bChina == true) {
		pCmdUI->SetText(_T("한국을 선택 하여라"));		// ID_CHINA 메뉴의 Caption을 변경
		pCmdUI->SetCheck(true);		// ID_CHINA 메뉴에 체크 표시
	}

	if (m_bKorea == true) {
		pCmdUI->SetText(_T("중국"));
		pCmdUI->SetCheck(false);		// ID_CHINA 메뉴에 체크 표시 해제
	}
}
