// CModelessDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFC 모델리스 다이알로그 학생성적관리.h"
#include "CModelessDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"


// CModelessDlg 대화 상자

IMPLEMENT_DYNAMIC(CModelessDlg, CDialogEx)

CModelessDlg::CModelessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CModelessDlg::~CModelessDlg()
{
}

void CModelessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelessDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CModelessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CModelessDlg 메시지 처리기


void CModelessDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEdit* m_pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	CString a_strName;
	m_pEdit->GetWindowText(a_strName);
	if (a_strName == _T("")) {
		return;
	}

	CEdit* m_pEditKor = (CEdit*)GetDlgItem(IDC_EDIT2);
	CString a_strKor;
	m_pEditKor->GetWindowText(a_strKor);
	if (a_strKor == _T("")) {
		return;
	}
	int m_iKor = _tstoi(a_strKor);

	CEdit* m_pEditEng = (CEdit*)GetDlgItem(IDC_EDIT3);
	CString a_strEng;
	m_pEditEng->GetWindowText(a_strEng);
	if (a_strEng == _T("")) {
		return;
	}
	int m_iEng = _tstoi(a_strEng);

	CEdit* m_pEditMath = (CEdit*)GetDlgItem(IDC_EDIT4);
	CString a_strMath;
	m_pEditMath->GetWindowText(a_strMath);
	if (a_strMath == _T("")) {
		return;
	}
	int m_iMath = _tstoi(a_strMath);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (pMainFrame != NULL) {
		CChildView* a_pView = &pMainFrame->m_wndView;
		Student a_StInfo;
		_tcsncpy_s(a_StInfo.m_Name, (TCHAR*)(LPCTSTR)a_strName, 128);
		a_StInfo.m_Kor = m_iKor;
		a_StInfo.m_Eng = m_iEng;
		a_StInfo.m_Math = m_iMath;
		a_StInfo.CalcJumsu();
		a_pView->m_StList.push_back(a_StInfo);

		a_pView->Invalidate();

		m_pEdit->SetWindowTextW(_T(""));
		m_pEditKor->SetWindowTextW(_T(""));
		m_pEditEng->SetWindowTextW(_T(""));
		m_pEditMath->SetWindowTextW(_T(""));
	}

	// CDialogEx::OnOK();		// <--- 주석처리하면 다이알로그 박스가 종료되지 않을 것이다.
}
