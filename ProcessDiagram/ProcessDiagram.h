
// ProcessDiagram.h : ProcessDiagram Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CProcessDiagramApp:
// �йش����ʵ�֣������ ProcessDiagram.cpp
//

class CProcessDiagramApp : public CWinAppEx
{
public:
	CProcessDiagramApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CProcessDiagramApp theApp;
