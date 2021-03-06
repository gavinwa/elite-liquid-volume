
// EtLiquidVolume.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "EtLiquidVolume.h"
#include "EtLiquidVolumeDlg.h"
#include "welcomeDlg.h"
#include "Liquid.h"


#include <comdef.h>//初始化一下com口
#include "GdiPlus.h"
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEtLiquidVolumeApp

BEGIN_MESSAGE_MAP(CEtLiquidVolumeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CEtLiquidVolumeApp 构造

CEtLiquidVolumeApp::CEtLiquidVolumeApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CEtLiquidVolumeApp 对象

CEtLiquidVolumeApp theApp;


// CEtLiquidVolumeApp 初始化

BOOL CEtLiquidVolumeApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	CWelcomeDlg welcomeDlg;
	welcomeDlg.DoModal();

	CEtLiquidVolumeDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CEtLiquidVolumeApp::ExitInstance()
{
	GdiplusShutdown(m_gdiplusToken);
	return CWinApp::ExitInstance();
}
