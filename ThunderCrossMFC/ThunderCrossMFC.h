
// ThunderCrossMFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CThunderCrossMFCApp: 
// �йش����ʵ�֣������ ThunderCrossMFC.cpp
//

class CThunderCrossMFCApp : public CWinApp
{
public:
	CThunderCrossMFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CThunderCrossMFCApp theApp;
