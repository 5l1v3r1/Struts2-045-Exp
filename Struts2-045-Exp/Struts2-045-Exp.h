
// Struts2-045-Exp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CStruts2045ExpApp:
// �йش����ʵ�֣������ Struts2-045-Exp.cpp
//

class CStruts2045ExpApp : public CWinApp
{
public:
	CStruts2045ExpApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStruts2045ExpApp theApp;