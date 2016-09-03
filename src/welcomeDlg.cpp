// welcomeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EtLiquidVolume.h"
#include "welcomeDlg.h"

bool LoadImageFromResource(CImage *pImage, UINT nResID, LPCTSTR lpTyp)
{
	if (pImage == NULL)
		return false;

	pImage->Destroy();
	// 查找资源
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL)
		return false;

	// 加载资源
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// 锁定内存中的指定资源
	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);
	// 解除内存中的指定资源 
	::GlobalUnlock(hNew);
	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht == S_OK)
		pImage->Load(pStream);

	GlobalFree(hNew);
	::FreeResource(hImgData);
	return true;
}

// CWelcomeDlg dialog

IMPLEMENT_DYNAMIC(CWelcomeDlg, CDialogEx)

	CWelcomeDlg::CWelcomeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWelcomeDlg::IDD, pParent)
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
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CWelcomeDlg message handlers
BOOL CWelcomeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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


void CWelcomeDlg::OnPaint()
{
	CImage image;
	LoadImageFromResource(&image, IDB_PNG_LOGO, _T("PNG"));
	ASSERT(!image.IsNull());

	if (image.GetBPP() == 32) //确认该图像包含Alpha通道
	{
		for (int i=0; i < image.GetWidth(); ++i)
		{
			for (int j=0; j < image.GetHeight(); ++j)
			{
				byte *pByte = (byte *)image.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}

	CDC *pDC = new CClientDC(GetDlgItem(IDC_STATIC_LOGO));
	image.Draw(pDC->m_hDC, 0, 0, image.GetWidth()/5, image.GetHeight()/5);
	image.Destroy();
	delete pDC;
}
