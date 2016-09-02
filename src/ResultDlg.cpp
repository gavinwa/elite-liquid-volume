// ResultDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EtLiquidVolume.h"
#include "ResultDlg.h"
#include "afxdialogex.h"

// CResultDlg dialog

IMPLEMENT_DYNAMIC(CResultDlg, CDialogEx)

CResultDlg::CResultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResultDlg::IDD, pParent)
	, m_result(0)
{
}

CResultDlg::~CResultDlg()
{
}

void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CResultDlg, CDialogEx)
END_MESSAGE_MAP()


// CResultDlg message handlers
void CResultDlg::SetResult(double result)
{
	m_result = result;
}

BOOL CResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString resultStr;
	resultStr.Format(_T("%.3f"), m_result);
	GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(resultStr);
	GetDlgItem(IDC_EDIT_RESULT)->SetFocus();
	return TRUE;
}
