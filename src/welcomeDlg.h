#pragma once

// CWelcomeDlg dialog

class CWelcomeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWelcomeDlg)

public:
	CWelcomeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWelcomeDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_WELCOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	afx_msg void OnPaint();

	CImage m_logoImage;
};
