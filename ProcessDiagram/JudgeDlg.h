#pragma once


// JudgeDlg �Ի���

class JudgeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(JudgeDlg)

public:
	JudgeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~JudgeDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString x2;
	CString y2;
	CString text_op;
	afx_msg void OnBnClickedButton1();
};
