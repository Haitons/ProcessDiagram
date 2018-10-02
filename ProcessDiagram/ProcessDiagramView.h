
// ProcessDiagramView.h : CProcessDiagramView 类的接口
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
protected: // 仅从序列化创建
	CProcessDiagramView();
	DECLARE_DYNCREATE(CProcessDiagramView)
private:
	int x = 0;
	int y = 0;
	Shape* activeShape = NULL;//当前活动图元的指针
	CString type;//图元类型
	boolean isNewShape = false;//用于判断是否产生新图元的标记
	Factory factory;
public:
	CDC memDC; //首先定义一个显示设备对象
	CBitmap memBitmap;//定义一个位图对象 
// 特性
public:
	CProcessDiagramDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CProcessDiagramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // ProcessDiagramView.cpp 中的调试版本
inline CProcessDiagramDoc* CProcessDiagramView::GetDocument() const
   { return reinterpret_cast<CProcessDiagramDoc*>(m_pDocument); }
#endif

