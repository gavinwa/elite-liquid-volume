#pragma once
#include "afxwin.h"

class LiquidDB;

// CEtLiquidVolumeDlg 对话框
class CEtLiquidVolumeDlg : public CDialogEx
{
// 构造
public:
	CEtLiquidVolumeDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CEtLiquidVolumeDlg();

// 对话框数据
	enum { IDD = IDD_ETLIQUIDVOLUME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	BOOL PreTranslateMessage(MSG* pMsg);

// 实现
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOK();
	afx_msg void OnCbnLiqNameSelectionChanged();
	afx_msg void OnKillfocusEditPurity();

	DECLARE_MESSAGE_MAP()

private:
	bool isPurityValid();

	CComboBox m_cbxLiqName;
	double m_editConcentration;
	double m_editVelocity;
	double m_editPurity;
	double m_editDensity;
	double m_editMolWeight;
	double m_editBoilingPoint;

	LiquidDB *m_liqDB;
public:
};
