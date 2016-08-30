#pragma once
#include "colorfulDlg.h"
#include "afxwin.h"

class LiquidDB;

// CEtLiquidVolumeDlg 对话框
class CEtLiquidVolumeDlg : public CColorfulDlg
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

	int getEditCtrlNumber(const CEdit &);

	bool isPurityValid();
	CComboBox m_cbxLiqName;
	CEdit m_editConcentration;
	CEdit m_editVelocity;
	CEdit m_editPurity;
	CEdit m_editDensity;
	CEdit m_editMolWeight;
	CEdit m_editBoilingPoint;

	LiquidDB *m_liqDB;
};
