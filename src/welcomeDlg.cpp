// welcomeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EtLiquidVolume.h"
#include "welcomeDlg.h"
#include "colorfulDlg.h"

// CWelcomeDlg dialog

IMPLEMENT_DYNAMIC(CWelcomeDlg, CColorfulDlg)

CWelcomeDlg::CWelcomeDlg(CWnd* pParent /*=NULL*/)
	: CColorfulDlg(CWelcomeDlg::IDD, pParent)
{
}

CWelcomeDlg::~CWelcomeDlg()
{
}

void CWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWelcomeDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CWelcomeDlg message handlers
BOOL CWelcomeDlg::OnInitDialog()
{
	CColorfulDlg::OnInitDialog();
	return TRUE;
}

void CWelcomeDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	SetTimer(TIMER_CLOSE_WELCOME, 2000, NULL);
}

void CWelcomeDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(TIMER_CLOSE_WELCOME);
	CWelcomeDlg::OnOK();
	CDialogEx::OnTimer(nIDEvent);
}
