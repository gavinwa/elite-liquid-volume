#pragma once

class CColorfulDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColorfulDlg)

public:
	CColorfulDlg(UINT nID, CWnd* pParent = NULL);   // standard constructor
	virtual ~CColorfulDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	HBRUSH m_brush;
};
