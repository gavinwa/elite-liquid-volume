
// EtLiquidVolume.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEtLiquidVolumeApp:
// �йش����ʵ�֣������ EtLiquidVolume.cpp
//

class CEtLiquidVolumeApp : public CWinApp
{
public:
	CEtLiquidVolumeApp();

// ��д
public:
	virtual BOOL InitInstance();
	int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

	ULONG_PTR m_gdiplusToken;
};

extern CEtLiquidVolumeApp theApp;