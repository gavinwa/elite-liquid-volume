// welcomeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EtLiquidVolume.h"
#include "colorfulDlg.h"
#include "afxdialogex.h"


// CWelcomeDlg dialog

IMPLEMENT_DYNAMIC(CColorfulDlg, CDialogEx)

CColorfulDlg::CColorfulDlg(UINT nID, CWnd* pParent)
	: CDialogEx(nID, pParent)
{
}

CColorfulDlg::~CColorfulDlg()
{
}

void CColorfulDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CColorfulDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CColorfulDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_brush = CreateSolidBrush(RGB(158,216,246));
	return TRUE;
}

HBRUSH CColorfulDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkColor(RGB(158,216,246));
	return m_brush;
}
