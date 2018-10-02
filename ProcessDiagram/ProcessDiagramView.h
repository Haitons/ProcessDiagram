
// ProcessDiagramView.h : CProcessDiagramView ��Ľӿ�
//

#pragma once
#include"MyRect.h"
#include"MyRoundRect.h"
#include"Diamond.h"
#include"Parallelogram.h"
#include"Factory.h"
#include <iterator>

class CProcessDiagramView : public CView
{
protected: // �������л�����
	CProcessDiagramView();
	DECLARE_DYNCREATE(CProcessDiagramView)
private:
	int x = 0;
	int y = 0;
	Shape* activeShape = NULL;//��ǰ�ͼԪ��ָ��
	CString type;//ͼԪ����
	boolean isNewShape = false;//�����ж��Ƿ������ͼԪ�ı��
	Factory factory;
public:
	CDC memDC; //���ȶ���һ����ʾ�豸����
	CBitmap memBitmap;//����һ��λͼ���� 
// ����
public:
	CProcessDiagramDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CProcessDiagramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCreateRoundRect();
	afx_msg void OnCreateRectangle();
	afx_msg void OnCreatePal();
	afx_msg void OnCreateDiamond();
	afx_msg void OnCreateLine();
	afx_msg void OnCreateProcess();
	afx_msg void OnCancle();
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // ProcessDiagramView.cpp �еĵ��԰汾
inline CProcessDiagramDoc* CProcessDiagramView::GetDocument() const
   { return reinterpret_cast<CProcessDiagramDoc*>(m_pDocument); }
#endif

