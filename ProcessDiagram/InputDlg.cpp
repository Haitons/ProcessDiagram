// InputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProcessDiagram.h"
#include "InputDlg.h"
#include "afxdialogex.h"


// InputDlg 对话框

IMPLEMENT_DYNAMIC(InputDlg, CDialogEx)

InputDlg::InputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, desc(_T(""))
{

}

InputDlg::~InputDlg()
{
}

void InputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, desc);
}


BEGIN_MESSAGE_MAP(InputDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &InputDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// InputDlg 消息处理程序


void InputDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
