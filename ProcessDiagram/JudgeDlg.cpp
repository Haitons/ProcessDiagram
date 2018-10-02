// JudgeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProcessDiagram.h"
#include "JudgeDlg.h"
#include "afxdialogex.h"


// JudgeDlg 对话框

IMPLEMENT_DYNAMIC(JudgeDlg, CDialogEx)

JudgeDlg::JudgeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, x2(_T(""))
	, y2(_T(""))
	, text_op(_T(""))
{

}

JudgeDlg::~JudgeDlg()
{
}

void JudgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, x2);
	DDX_Text(pDX, IDC_EDIT2, y2);
	DDX_Text(pDX, IDC_EDIT1, text_op);
}


BEGIN_MESSAGE_MAP(JudgeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &JudgeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// JudgeDlg 消息处理程序


void JudgeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
