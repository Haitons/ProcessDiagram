// InputDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessDiagram.h"
#include "InputDlg.h"
#include "afxdialogex.h"


// InputDlg �Ի���

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


// InputDlg ��Ϣ�������


void InputDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
