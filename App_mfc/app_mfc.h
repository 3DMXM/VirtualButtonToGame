
// app_mfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Capp_mfcApp:
// �йش����ʵ�֣������ app_mfc.cpp
//

class Capp_mfcApp : public CWinAppEx
{
public:
	Capp_mfcApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Capp_mfcApp theApp;