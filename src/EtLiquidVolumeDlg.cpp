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
	return (v * c * m) / (22.4 * d * rou) * 0.1;
}

// CEtLiquidVolumeDlg 对话框
CEtLiquidVolumeDlg::CEtLiquidVolumeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEtLiquidVolumeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_editConcentration = 0.0;
	m_editVelocity = 0.0;
	m_editPurity = 0.0;
	m_editDensity = 0.0;
	m_editMolWeight = 0.0;
	m_editBoilingPoint = 0.0;
}

CEtLiquidVolumeDlg::~CEtLiquidVolumeDlg()
{
	delete m_liqDB;
}

void CEtLiquidVolumeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LIQNAME, m_cbxLiqName);
	DDX_Text(pDX, IDC_EDIT_CONCENTRATION, m_editConcentration);
	DDX_Text(pDX, IDC_EDIT_VELOCITY, m_editVelocity);
	DDX_Text(pDX, IDC_EDIT_PURITY, m_editPurity);
	DDX_Text(pDX, IDC_EDIT_DENSITY, m_editDensity);
	DDX_Text(pDX, IDC_EDIT_MOLWEIGHT, m_editMolWeight);
	DDX_Text(pDX, IDC_EDIT_BOILINGPOINT, m_editBoilingPoint);
}

BEGIN_MESSAGE_MAP(CEtLiquidVolumeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_LIQNAME, &CEtLiquidVolumeDlg::OnCbnLiqNameSelectionChanged)
	ON_EN_KILLFOCUS(IDC_EDIT_PURITY, &CEtLiquidVolumeDlg::OnKillfocusEditPurity)
END_MESSAGE_MAP()


// CEtLiquidVolumeDlg 消息处理程序

BOOL CEtLiquidVolumeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 额外的初始化代码
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

	m_editConcentration = 1;
	m_editVelocity = 1000;
	m_editPurity = 100;
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEtLiquidVolumeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CEtLiquidVolumeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEtLiquidVolumeDlg::OnOK()
{
	if (!isPurityValid())
		return;

	UpdateData(TRUE);

	double result = q(m_editVelocity, m_editConcentration, m_editMolWeight, m_editPurity, m_editDensity);

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

	m_editBoilingPoint = liq.m_boilingPoint;
	m_editDensity = liq.m_density;
	m_editMolWeight = liq.m_molecularWeight;
	m_editVelocity = liq.m_velocity;
	m_editConcentration = liq.m_concentration;
	m_editPurity = liq.m_purity;

	UpdateData(FALSE);
}

void CEtLiquidVolumeDlg::OnKillfocusEditPurity()
{
	if (!isPurityValid())
		return;
}

bool CEtLiquidVolumeDlg::isPurityValid()
{
	UpdateData(TRUE);

	if (m_editPurity < 1 || m_editPurity > 100)
	{
		m_editPurity = 100.000;
		UpdateData(FALSE);
		CEdit * pur = (CEdit *)GetDlgItem(IDC_EDIT_PURITY);
		pur->SetFocus();
		pur->SetSel(0, pur->GetWindowTextLengthW());
		return false;
	}
	return true;
}

