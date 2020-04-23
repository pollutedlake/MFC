// CMyDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC 메뉴 이벤트 함수 처리하기 및 글씨 쓰기.h"
#include "CMyDialog.h"
#include "afxdialogex.h"


// CMyDialog 대화 상자

IMPLEMENT_DYNAMIC(CMyDialog, CDialogEx)

CMyDialog::CMyDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	memset(&DiaData, 0, sizeof(DiaData));
}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMyDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyDialog 메시지 처리기

DialogData* CMyDialog::GetDialogData()
{
	return &DiaData;
}

void CMyDialog::SetConfigData(DialogData* data)
{
	DiaData = *data;
}

BOOL CMyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//CComboBox* m_TradeCombo = (CComboBox*)GetDlgItem(IDC_DIG_TRADE);
	//m_TradeCombo->AddString(_T("불가능"));
	//m_TradeCombo->AddString(_T("가능"));
	//m_TradeCombo->SetCurSel(0);		// 기본 값 선택

	//CComboBox* m_MultiCombo = (CComboBox*)GetDlgItem(IDC_DIG_MULTI);
	//m_MultiCombo->AddString(_T("불가능"));
	//m_MultiCombo->AddString(_T("가능"));
	//m_MultiCombo->SetCurSel(0);		// 기본 값 선택

	//------ 값 세팅 부분
	((CComboBox*)GetDlgItem(IDC_DIG_TRADE))->SetCurSel(DiaData.m_Trade);
	((CComboBox*)GetDlgItem(IDC_DIG_MULTI))->SetCurSel(DiaData.m_Mult);

	if (DiaData.m_Graphic == 0) {
		((CButton*)GetDlgItem(IDC_DIG_GRAPHIC_HIGHER))->SetCheck(TRUE);
	}
	else if (DiaData.m_Graphic == 1) {
		((CButton*)GetDlgItem(IDC_DIG_GRAPHIC_NORMAL))->SetCheck(TRUE);
	}

	((CButton*)GetDlgItem(IDC_DIG_SHOWCHAR))->SetCheck(DiaData.m_ViewChar);

	if (DiaData.m_AutoPick == true) {
		((CButton*)GetDlgItem(IDC_DIG_AUTOPICK_YES))->SetCheck(TRUE);
	}
	else {
		((CButton*)GetDlgItem(IDC_DIG_AUTOPICK_NO))->SetCheck(TRUE);
	}

	((CButton*)GetDlgItem(IDC_DIG_AUTOATTACK))->SetCheck(DiaData.m_AutoAtt);
	//------ 값 세팅 부분

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMyDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DiaData.m_Trade = ((CComboBox*)GetDlgItem(IDC_DIG_TRADE))->GetCurSel();
	DiaData.m_Mult = ((CComboBox*)GetDlgItem(IDC_DIG_MULTI))->GetCurSel();

	if (((CButton*)GetDlgItem(IDC_DIG_GRAPHIC_HIGHER))->GetCheck()) {
		DiaData.m_Graphic = 0;
	}
	else if (((CButton*)GetDlgItem(IDC_DIG_GRAPHIC_NORMAL))->GetCheck()) {
		DiaData.m_Graphic = 1;
	}

	DiaData.m_ViewChar = ((CButton*)GetDlgItem(IDC_DIG_SHOWCHAR))->GetCheck();

	if (((CButton*)GetDlgItem(IDC_DIG_AUTOPICK_YES))->GetCheck()) {
		DiaData.m_AutoPick = true;
	}
	else if (((CButton*)GetDlgItem(IDC_DIG_AUTOPICK_NO))->GetCheck()) {
		DiaData.m_AutoPick = false;
	}

	DiaData.m_AutoAtt = ((CButton*)GetDlgItem(IDC_DIG_AUTOATTACK))->GetCheck();

	CDialogEx::OnOK();
}