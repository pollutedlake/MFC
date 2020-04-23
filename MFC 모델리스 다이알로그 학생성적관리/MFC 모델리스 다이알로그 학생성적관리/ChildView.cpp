
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFC 모델리스 다이알로그 학생성적관리.h"
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
	m_Button.DestroyWindow();		// <--- 버튼 제거

	m_pDlg->DestroyWindow();		// <<--- 다이알로그 박스 제거
	if (m_pDlg != NULL) {
		delete m_pDlg;
		m_pDlg = NULL;
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
	static bool isFirst = true;
	if (isFirst == true) {
		RECT a_wRT;
		GetWindowRect(&a_wRT);
		m_MainWPos.x = a_wRT.left;
		m_MainWPos.y = a_wRT.top;

		RECT a_cRT;
		GetClientRect(&a_cRT);
		m_MWTopLeft.x = 0;
		m_MWTopLeft.y = 0;
		ClientToScreen(&m_MWTopLeft);

		if (m_pDlg != NULL) {
			RECT a_dRT;
			m_pDlg->GetClientRect(&a_dRT);

			m_DlgSize.x = a_dRT.right;
			m_DlgSize.y = a_dRT.bottom;

			m_ChildWPos.x = a_wRT.left + a_cRT.right - m_DlgSize.x - 6;
			m_ChildWPos.y = m_MWTopLeft.y;
			m_pDlg->SetWindowPos(NULL, m_ChildWPos.x, m_ChildWPos.y, 0, 0, SWP_NOSIZE);
		}

		isFirst = false;
	}	// if (isFirst == true)

	TCHAR a_TempStr[256];
	for (int ii = 0; ii < m_StList.size(); ii++) {
		_stprintf_s(a_TempStr, _T("이름(%s) : 국어(%d) 영어(%d) 수학(%d) 총점(%d) 평균(%.1f)"), m_StList[ii].m_Name, m_StList[ii].m_Kor, m_StList[ii].m_Eng, m_StList[ii].m_Math, m_StList[ii].m_Total, m_StList[ii].m_Avg);

		dc.TextOut(50, 80 + (ii * 30), a_TempStr);
	}
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



BOOL CChildView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//------ 모델리스 다이알로그 박스가 부모 윈도우를 기준으로 정렬되게 하는 코드
	if (wParam == IDC_MYBTNDOWN) {
		RECT a_wRT;
		GetWindowRect(&a_wRT);
		m_MainWPos.x = a_wRT.left;
		m_MainWPos.y = a_wRT.top;

		RECT a_cRT;
		GetClientRect(&a_cRT);
		m_MWTopLeft.x = 0;
		m_MWTopLeft.y = 0;
		ClientToScreen(&m_MWTopLeft);

		if (m_pDlg != NULL) {
			RECT a_dRT;
			m_pDlg->GetClientRect(&a_dRT);

			m_DlgSize.x = a_dRT.right;
			m_DlgSize.y = a_dRT.bottom;

			m_ChildWPos.x = a_wRT.left + a_cRT.right - m_DlgSize.x - 6;
			m_ChildWPos.y = m_MWTopLeft.y;
			m_pDlg->SetWindowPos(NULL, m_ChildWPos.x, m_ChildWPos.y, 0, 0, SWP_NOSIZE);

			//--- 모델리스 다이알로그 박스 다시 보기
			m_pDlg->ShowWindow(SW_SHOW);
			//--- 모델리스 다이알로그 박스 다시 보기
		}
		//------ 모델리스 다이알로그 박스가 부모 윈도우를 기준으로 정렬되게 하는 코드
	}

	return CWnd::OnCommand(wParam, lParam);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_Button.Create(_T("다이알로그보기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(100, 20, 280, 56), this, IDC_MYBTNDOWN);

	//------ 모델리스 다이알로그 박스 생성
	m_pDlg = new CModelessDlg();
	m_pDlg->Create(IDD_DIALOG1, this);
	m_pDlg->ShowWindow(SW_SHOW);
	//------ 모델리스 다이알로그 박스 생성

	return 0;
}
