#pragma once
#include "afxwin.h"

class LiquidDB;

// CEtLiquidVolumeDlg �Ի���
class CEtLiquidVolumeDlg : public CDialogEx
{
// ����
public:
	CEtLiquidVolumeDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CEtLiquidVolumeDlg();

// �Ի�������
	enum { IDD = IDD_ETLIQUIDVOLUME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	BOOL PreTranslateMessage(MSG* pMsg);

// ʵ��
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
