#include "stdafx.h"
#include "EtLiquidVolume.h"
#include "EtLiquidVolumeDlg.h"
#include "ResultDlg.h"
#include "afxdialogex.h"
#include <vector>
#include "Liquid.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double q(double v, double c, double m, double d, double rou)
{
	return (v * c * v) / (22.4 * d * rou) * 0.000000001;
}

// CEtLiquidVolumeDlg �Ի���
CEtLiquidVolumeDlg::CEtLiquidVolumeDlg(CWnd* pParent /*=NULL*/)
	: CColorfulDlg(CEtLiquidVolumeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CEtLiquidVolumeDlg::~CEtLiquidVolumeDlg()
{
	delete m_liqDB;
}

void CEtLiquidVolumeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbxLiqName);
	DDX_Control(pDX, IDC_EDIT6, m_editConcentration);
	DDX_Control(pDX, IDC_EDIT7, m_editVelocity);
	DDX_Control(pDX, IDC_EDIT_PURITY, m_editPurity);
	DDX_Control(pDX, IDC_EDIT3, m_editDensity);
	DDX_Control(pDX, IDC_EDIT4, m_editMolWeight);
	DDX_Control(pDX, IDC_EDIT5, m_editBoilingPoint);
}

BEGIN_MESSAGE_MAP(CEtLiquidVolumeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CEtLiquidVolumeDlg::OnCbnLiqNameSelectionChanged)
	ON_EN_KILLFOCUS(IDC_EDIT_PURITY, &CEtLiquidVolumeDlg::OnKillfocusEditPurity)
END_MESSAGE_MAP()


// CEtLiquidVolumeDlg ��Ϣ�������

BOOL CEtLiquidVolumeDlg::OnInitDialog()
{
	CColorfulDlg::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ����ĳ�ʼ������
	m_liqDB = LiquidDB::getInstance();
	m_liqDB->Load();
	vector<CString> liqs = m_liqDB->getLiquidList();
	for (auto itor = liqs.begin(); itor != liqs.end(); ++itor)
	{
		Liquid liq = m_liqDB->getLiquidByName(*itor);
		if (!liq.m_name.IsEmpty())
		{
			m_cbxLiqName.AddString(liq.m_name);
		}
	}

	m_editConcentration.SetWindowTextW(_T("1"));
	m_editVelocity.SetWindowTextW(_T("1000"));
	m_editPurity.SetWindowTextW(_T("100"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEtLiquidVolumeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CEtLiquidVolumeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEtLiquidVolumeDlg::OnOK()
{
	if (!isPurityValid())
		return;

	// calculate
	double v = getEditCtrlNumber(m_editVelocity);
	double c = 	getEditCtrlNumber(m_editConcentration);
	double m = getEditCtrlNumber(m_editMolWeight);
	double d = getEditCtrlNumber(m_editDensity);
	double b = getEditCtrlNumber(m_editBoilingPoint);

	double result = q(v, c, m, d, b);

	CResultDlg resultDlg;
	resultDlg.SetResult(result);
	resultDlg.DoModal();
}

BOOL CEtLiquidVolumeDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE)
	{
		return TRUE; // avoid quit by [escape] key.
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CEtLiquidVolumeDlg::OnCbnLiqNameSelectionChanged()
{
	int idx = m_cbxLiqName.GetCurSel();
	CString liqName;
	m_cbxLiqName.GetLBText(idx, liqName);
	Liquid liq = m_liqDB->getLiquidByName(liqName);
	CString str;
	str.Format(_T("%.0f"), liq.m_boilingPoint);
	m_editBoilingPoint.SetWindowTextW(str);
	str.Format(_T("%.0f"), liq.m_density);
	m_editDensity.SetWindowTextW(str);
	str.Format(_T("%.0f"), liq.m_molecularWeight);
	m_editMolWeight.SetWindowTextW(str);
}

void CEtLiquidVolumeDlg::OnKillfocusEditPurity()
{
	if (!isPurityValid())
		return;
}

int CEtLiquidVolumeDlg::getEditCtrlNumber(const CEdit & editCtrl)
{
	CString txt;
	editCtrl.GetWindowTextW(txt);
	return _ttoi(txt);
}

bool CEtLiquidVolumeDlg::isPurityValid()
{
	CString purityTxt;
	m_editPurity.GetWindowTextW(purityTxt);
	int purity = _ttoi(purityTxt);
	if (purity < 1 || purity > 100)
	{
		m_editPurity.SetWindowTextW(_T("100"));
		m_editPurity.SetFocus();
		m_editPurity.SetSel(0, m_editPurity.GetWindowTextLengthW());
		return false;
	}
	return true;
}
