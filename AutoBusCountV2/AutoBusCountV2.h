
// AutoBusCountV2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAutoBusCountV2App:
// �йش����ʵ�֣������ AutoBusCountV2.cpp
//

class CAutoBusCountV2App : public CWinApp
{
public:
	CAutoBusCountV2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAutoBusCountV2App theApp;