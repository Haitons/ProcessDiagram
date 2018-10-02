#pragma once


// JudgeDlg 对话框

class JudgeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(JudgeDlg)

public:
	JudgeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~JudgeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString x2;
	CString y2;
	CString text_op;
	afx_msg void OnBnClickedButton1();
};
