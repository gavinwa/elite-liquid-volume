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
	m_logoImage.Destroy();
}

void CWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWelcomeDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CWelcomeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LoadImageFromResource(&m_logoImage, IDB_PNG_LOGO, _T("PNG"));
	ASSERT(!m_logoImage.IsNull());

	if (m_logoImage.GetBPP() == 32) //确认该图像包含Alpha通道
	{
		for (int i=0; i < m_logoImage.GetWidth(); ++i)
		{
			for (int j=0; j < m_logoImage.GetHeight(); ++j)
			{
				byte *pByte = (byte *)m_logoImage.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}
	return TRUE;
}

void CWelcomeDlg::OnPaint()
{
	CDC *pDC = new CClientDC(GetDlgItem(IDC_STATIC_LOGO));
	m_logoImage.Draw(pDC->m_hDC, 0, 0, m_logoImage.GetWidth()/5, m_logoImage.GetHeight()/5);
	delete pDC;

	static int start = GetTickCount();
	int current = GetTickCount();
	if (current - start > 2000)
	{
		CWelcomeDlg::OnOK();
	}
}
