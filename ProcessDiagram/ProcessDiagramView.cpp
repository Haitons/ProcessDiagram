
// ProcessDiagramView.cpp : CProcessDiagramView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ProcessDiagram.h"
#endif

#include "ProcessDiagramDoc.h"
#include "ProcessDiagramView.h"

#include"ComputeUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProcessDiagramView

IMPLEMENT_DYNCREATE(CProcessDiagramView, CView)

BEGIN_MESSAGE_MAP(CProcessDiagramView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CProcessDiagramView::OnCreateRoundRect)
	ON_COMMAND(ID_32772, &CProcessDiagramView::OnCreateRectangle)
	ON_COMMAND(ID_32773, &CProcessDiagramView::OnCreatePal)
	ON_COMMAND(ID_32774, &CProcessDiagramView::OnCreateDiamond)
	ON_COMMAND(ID_32775, &CProcessDiagramView::OnCreateLine)
	ON_COMMAND(ID_32776, &CProcessDiagramView::OnCreateProcess)
	ON_COMMAND(ID_32777, &CProcessDiagramView::OnCancle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
//	ON_WM_MBUTTONDBLCLK()
ON_WM_LBUTTONDBLCLK()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CProcessDiagramView 构造/析构

CProcessDiagramView::CProcessDiagramView()
{
	// TODO: 在此处添加构造代码

}

CProcessDiagramView::~CProcessDiagramView()
{
}

BOOL CProcessDiagramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CProcessDiagramView 绘制

void CProcessDiagramView::OnDraw(CDC* pDC)
{
	CProcessDiagramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	CRect r1;
	GetClientRect(&r1);
	memDC.FillSolidRect(0, 0, r1.Width(), r1.Height(), RGB(255, 255, 255));
	//显示所有图元
	list<Shape*>::iterator sit;
	for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end(); sit++) {
		boolean sign = (*sit) == this->activeShape;//sign用于标记是否是活动图元
		if (!sign) {
			(*sit)->onDraw(&memDC, sign);
		}
	}
	//最后显示活动图元
	if (NULL != this->activeShape) {
		this->activeShape->onDraw(&memDC, true);
	}
	//将内存中的图拷贝到屏幕上进行显示
	pDC->BitBlt(0, 0, r1.Width(), r1.Height(), &memDC, 0, 0, SRCCOPY);

	// TODO: 在此处为本机数据添加绘制代码
}


// CProcessDiagramView 打印

BOOL CProcessDiagramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CProcessDiagramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CProcessDiagramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CProcessDiagramView 诊断

#ifdef _DEBUG
void CProcessDiagramView::AssertValid() const
{
	CView::AssertValid();
}

void CProcessDiagramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProcessDiagramDoc* CProcessDiagramView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProcessDiagramDoc)));
	return (CProcessDiagramDoc*)m_pDocument;
}
#endif //_DEBUG


// CProcessDiagramView 消息处理程序


void CProcessDiagramView::OnCreateRoundRect()
{
	// TODO: 在此添加命令处理程序代码
	//菜单栏产生圆角矩形
	this->type = "MyRoundRect";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreateRectangle()
{
	// TODO: 在此添加命令处理程序代码
	//菜单栏产生矩形
	this->type = "MyRect";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreatePal()
{
	// TODO: 在此添加命令处理程序代码
	//菜单栏产生平行四边形
	this->type = "Parallelogram";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreateDiamond()
{
	// TODO: 在此添加命令处理程序代码
	//菜单栏产生菱形
	this->type = "Diamond";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreateLine()
{
	// TODO: 在此添加命令处理程序代码
	//菜单栏产生连接线
	this->type = "MyLine";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreateProcess()
{
	// TODO: 在此添加命令处理程序代码
	list<Shape *> ::iterator it;
	CString start("start");
	CString end("end");
	CString input("input");
	CString output("output");
	CString text;
	ComputeUtil comp;
	bool Flag = FALSE;
	it = this->GetDocument()->shapes.begin();
	do {
		if ((*it)->getId() == 1) {    //如果是圆角矩形，开始结束框

			((MyRoundRect *)(*it))->b = true;
			RedrawWindow();
			text = (*it)->getDesc();     //获取框中的输入内容

			MessageBox(text);
			if (text.Find(start) != -1) {    //如果是开始	
				it = (*it)->downJoin.begin();

			}
		}

		else if ((*it)->getId() == 2) {          //如果是平行四边形，输入输出框
			((Parallelogram *)(*it))->b = true;
			RedrawWindow();
			text = (*it)->getDesc();     //获取框中的输入内容
			MessageBox(text);
			if (text.Find(output) != -1) { //如果是输出框
				text.Replace(output, NULL);
				MessageBox(comp.ouput(text));

				(*it)->setDesc(comp.ouput(text));

				it = (*it)->downJoin.begin();
			}
			else {  //如果是输入框
				comp.input(text);
				it = (*it)->downJoin.begin();
			}
		}
		else if ((*it)->getId() == 3) {         //如果是矩形-
			((MyRect *)(*it))->b = true;
			RedrawWindow();
			text = (*it)->getDesc();  //获取框中的输入内容
			MessageBox(text);
			comp.compute(text);
			it = (*it)->downJoin.begin();
		}


		else if ((*it)->getId() == 4) {    //如果是菱形 判断框

			list<Shape *> ::iterator pit;
			CString op = (*it)->getOP();
			CString x2 = (*it)->getX2();
			CString y2 = (*it)->getY2();
			((Diamond *)(*it))->b = true;
			RedrawWindow();
			MessageBox((*it)->getDesc());
			if (op.GetLength() > 1) {  //是>= 或者 <= 或者 !=
				if (comp.judgeTwo(x2, y2, op)) {   //到Y分支
					Flag = FALSE;
					for (pit = (*it)->downJoin.begin(); pit != (*it)->downJoin.end(); pit++) {
						if ((*pit)->getDesc() == "Y")
						{
							((MyLine *)(*pit))->b = true;
							RedrawWindow();
							it = (*pit)->downJoin.begin();
							Flag = TRUE;
							break;
						}
					}
					if (Flag == FALSE)
						MessageBox(_T("没有找到Y分支！流程图结束！"));
				}
				else {   //到N分支
					Flag = FALSE;
					for (pit = (*it)->downJoin.begin(); pit != (*it)->downJoin.end(); pit++) {
						if ((*pit)->getDesc() == "N")
						{
							((MyLine *)(*pit))->b = true;
							RedrawWindow();
							it = (*pit)->downJoin.begin();
							Flag = TRUE;
							break;
						}
					}
					if (Flag == FALSE)
						MessageBox(_T("没有找到N分支！流程图结束！"));
				}
			}
			else {    //是< 、> 、 =
				if (comp.judgeOne(x2, y2, op)) {
					Flag = FALSE;
					for (pit = (*it)->downJoin.begin(); pit != (*it)->downJoin.end(); pit++) {
						if ((*pit)->getDesc() == "Y")
						{
							((MyLine *)(*pit))->b = true;
							RedrawWindow();
							it = (*pit)->downJoin.begin();
							Flag = TRUE;
							break;
						}
					}
					if (Flag == FALSE)
						MessageBox(_T("没有找到Y分支！流程图结束！"));
				}
				else {
					Flag = FALSE;
					for (pit = (*it)->downJoin.begin(); pit != (*it)->downJoin.end(); pit++) {
						if ((*pit)->getDesc() == "N")
						{
							((MyLine *)(*pit))->b = true;
							RedrawWindow();
							it = (*pit)->downJoin.begin();
							Flag = TRUE;
							break;
						}
					}
					if (Flag == FALSE)
						MessageBox(_T("没有找到N分支！流程图结束！"));
				}

			}
		}


		else if ((*it)->getId() == 5) {         //如果是线段
			((MyLine *)(*it))->b = true;
			it = (*it)->downJoin.begin();
		}


	} while (((*it)->getDesc()).Find(end) == -1);
	((MyRoundRect *)(*it))->b = true;
	RedrawWindow();
}


void CProcessDiagramView::OnCancle()
{
	// TODO: 在此添加命令处理程序代码
	CString end("end");
	bool Endflag = FALSE;
	list<Shape *> ::iterator it;
	it = this->GetDocument()->shapes.begin();
	do {
		((MyLine *)(*it))->b = false;
		((MyRect *)(*it))->b = false;
		((MyRoundRect *)(*it))->b = false;
		((Parallelogram *)(*it))->b = false;
		((Diamond *)(*it))->b = false;
		RedrawWindow();


		if ((*it)->getId() == 4) {
			list<Shape *> ::iterator pit;
			for (pit = (*it)->downJoin.begin(); pit != (*it)->downJoin.end(); pit++) {
				((MyLine *)(*it))->b = false;
			}
		}
		if ((*it)->getDesc().Find(end) == -1)
			it = (*it)->downJoin.begin();
		else
			Endflag = TRUE;
	} while (!Endflag);
}

void CProcessDiagramView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//初始化
	//使用双缓冲，避免闪屏
	// TODO: 在此添加专用代码和/或调用基类

	//获取屏幕大小
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	//CRect r1;
	//GetClientRect(&r1);
	CDC* pDC = GetDC();
	if (!memDC.m_hDC) {
		memDC.CreateCompatibleDC(pDC);
		memBitmap.CreateCompatibleBitmap(pDC, cx, cy);
		//memBitmap.CreateCompatibleBitmap(pDC, r1.Width(), r1.Height());
		ReleaseDC(pDC);
		memDC.SelectObject(&memBitmap);
	}

}


void CProcessDiagramView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (NULL != this->activeShape) {//将当前活动图元指针置为空
		this->activeShape->onRelease(point.x, point.y);
		this->activeShape = NULL;
	}
	if (isNewShape) {//新添加的图元，确定位置

		this->activeShape = factory.createShape(this->type, point);
		if (NULL != this->activeShape) {
			this->GetDocument()->shapes.push_back(this->activeShape);
		}
		//this->isNewShape = false;
		return;
	}
	//确定当前活动图元
	list<Shape*>::iterator sit;
	for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end(); sit++) {
		if ((*sit)->isActive(point)) {
			this->activeShape = (*sit);
			break;
		}
	}
	if (NULL != this->activeShape) {
		this->activeShape->onPress(point.x, point.y);
	}
	this->x = point.x;
	this->y = point.y;
	Invalidate(TRUE);
	CView::OnLButtonDown(nFlags, point);
}


void CProcessDiagramView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//将生成新图元的标记isNewShape置为false	
	if (isNewShape) {
		this->isNewShape = false;
		return;
	}
	//若当前活动图元为直线，则判断移动或改变后的直线，是否被连接到某个图元上
	if (NULL != this->activeShape) {
		MyLine* line = dynamic_cast<MyLine*>(this->activeShape);
		if (NULL != line) {
			list<Shape*>::iterator sit;
			for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end(); sit++) {
				if (!(*sit)->isLine()) {
					(*sit)->connect(activeShape, point);
				}
			}
		}
		this->activeShape->onRelease(point.x, point.y);
	}
	list<Shape*> sll = this->GetDocument()->shapes;
	Invalidate(TRUE);
	CView::OnLButtonUp(nFlags, point);
}


void CProcessDiagramView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//移动
	int cx = point.x - this->x;
	int cy = point.y - this->y;
	if (NULL != this->activeShape) {
		this->activeShape->onMove(cx, cy);
	}
	this->x = point.x;
	this->y = point.y;
	Invalidate(TRUE);
	CView::OnMouseMove(nFlags, point);
}


void CProcessDiagramView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	//delete链表中存放的所有图元
	memBitmap.DeleteObject();
	memDC.DeleteDC();
	list<Shape*>::iterator sit;
	for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end(); sit++) {
		delete (*sit);
	}
}


BOOL CProcessDiagramView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return false;
}



void CProcessDiagramView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//修改图元显示的语句
	list<Shape*>::iterator sit;
	//确定当前活动的图元
	for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end(); sit++) {
		if ((*sit)->isActive(point)) {
			this->activeShape = (*sit);
			break;
		}
	}
	//调用该图元的方法，修改图元语句
	if (NULL != this->activeShape) {
		this->activeShape->onPress(point.x, point.y);
		if (this->activeShape->isShowDia()) {
			this->activeShape->editDia();
		}
	}
	this->x = point.x;
	this->y = point.y;
	this->OnLButtonUp(nFlags, point);
	CView::OnLButtonDblClk(nFlags, point);
}


void CProcessDiagramView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_DELETE)//键盘按键为delete键
	{
		if (NULL != this->activeShape) {//当前存在选中图元，则删除
			if (MessageBox(_T("确定删除"), _T("删除图元"), MB_ICONEXCLAMATION | MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
				list<Shape*>::iterator sit;
				//从图元链表中删除选中图元
				list<Shape*> sll = this->GetDocument()->shapes;
				for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end();) {
					if ((*sit) == this->activeShape) {//在链表中找到当前的活动图元

													  //当前图元的所有上图元
						list<Shape*>::iterator upit;
						list<Shape*> uplist = (*sit)->getUpJoin();
						//for (upit = ((*sit)->getUpJoin().begin()); upit != ((*sit)->getUpJoin().end()); upit++) {
						for (upit = (*sit)->upJoin.begin(); upit != (*sit)->upJoin.end(); upit++) {
							//上图元的所有向下的指针
							list<Shape*>::iterator it;
							list<Shape*> upDownList = (*upit)->getDownJoin();
							//for (it = ((*upit)->getDownJoin().begin()); it != ((*upit)->getDownJoin().end()); ) {
							for (it = (*upit)->downJoin.begin(); it != (*upit)->downJoin.end(); ) {
								if ((*sit) == (*it)) {
									it = (*upit)->downJoin.erase(it);
									break;
								}
								else {
									it++;
								}
							}
						}
						//当前图元的所有下图元
						list<Shape*>::iterator downit;
						list<Shape*> downlist = (*sit)->getDownJoin();
						//for (downit = ((*sit)->getDownJoin().begin()); downit != ((*sit)->getDownJoin().end()); downit++){
						for (downit = (*sit)->downJoin.begin(); downit != (*sit)->downJoin.end(); downit++) {
							//下图元的所有向上的指针
							list<Shape*>::iterator it;
							list<Shape*> downUpList = (*downit)->getUpJoin();
							//for (it = ((*downit)->getUpJoin().begin()); it != ((*downit)->getUpJoin().end());) {
							for (it = (*downit)->upJoin.begin(); it != (*downit)->upJoin.end(); ) {
								if ((*sit) == (*it)) {
									it = (*downit)->upJoin.erase(it);
									break;
								}
								else {
									it++;
								}
							}
						}

						sit = this->GetDocument()->shapes.erase(sit);
					}
					else {
						sit++;
					}
				}
				delete(this->activeShape);
				this->activeShape = NULL;
			}
		}
		else {//当前没有选中图元，则提示消息
			MessageBox(_T("请先选中图元"));
		}

	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
