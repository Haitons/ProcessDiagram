
// ProcessDiagramView.cpp : CProcessDiagramView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CProcessDiagramView ����/����

CProcessDiagramView::CProcessDiagramView()
{
	// TODO: �ڴ˴���ӹ������

}

CProcessDiagramView::~CProcessDiagramView()
{
}

BOOL CProcessDiagramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CProcessDiagramView ����

void CProcessDiagramView::OnDraw(CDC* pDC)
{
	CProcessDiagramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect r1;
	GetClientRect(&r1);
	memDC.FillSolidRect(0, 0, r1.Width(), r1.Height(), RGB(255, 255, 255));
	//��ʾ����ͼԪ
	list<Shape*>::iterator sit;
	for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end(); sit++) {
		boolean sign = (*sit) == this->activeShape;//sign���ڱ���Ƿ��ǻͼԪ
		if (!sign) {
			(*sit)->onDraw(&memDC, sign);
		}
	}
	//�����ʾ�ͼԪ
	if (NULL != this->activeShape) {
		this->activeShape->onDraw(&memDC, true);
	}
	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	pDC->BitBlt(0, 0, r1.Width(), r1.Height(), &memDC, 0, 0, SRCCOPY);

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CProcessDiagramView ��ӡ

BOOL CProcessDiagramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CProcessDiagramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CProcessDiagramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CProcessDiagramView ���

#ifdef _DEBUG
void CProcessDiagramView::AssertValid() const
{
	CView::AssertValid();
}

void CProcessDiagramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProcessDiagramDoc* CProcessDiagramView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProcessDiagramDoc)));
	return (CProcessDiagramDoc*)m_pDocument;
}
#endif //_DEBUG


// CProcessDiagramView ��Ϣ�������


void CProcessDiagramView::OnCreateRoundRect()
{
	// TODO: �ڴ���������������
	//�˵�������Բ�Ǿ���
	this->type = "MyRoundRect";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreateRectangle()
{
	// TODO: �ڴ���������������
	//�˵�����������
	this->type = "MyRect";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreatePal()
{
	// TODO: �ڴ���������������
	//�˵�������ƽ���ı���
	this->type = "Parallelogram";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreateDiamond()
{
	// TODO: �ڴ���������������
	//�˵�����������
	this->type = "Diamond";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreateLine()
{
	// TODO: �ڴ���������������
	//�˵�������������
	this->type = "MyLine";
	this->isNewShape = true;
}


void CProcessDiagramView::OnCreateProcess()
{
	// TODO: �ڴ���������������
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
		if ((*it)->getId() == 1) {    //�����Բ�Ǿ��Σ���ʼ������

			((MyRoundRect *)(*it))->b = true;
			RedrawWindow();
			text = (*it)->getDesc();     //��ȡ���е���������

			MessageBox(text);
			if (text.Find(start) != -1) {    //����ǿ�ʼ	
				it = (*it)->downJoin.begin();

			}
		}

		else if ((*it)->getId() == 2) {          //�����ƽ���ı��Σ����������
			((Parallelogram *)(*it))->b = true;
			RedrawWindow();
			text = (*it)->getDesc();     //��ȡ���е���������
			MessageBox(text);
			if (text.Find(output) != -1) { //����������
				text.Replace(output, NULL);
				MessageBox(comp.ouput(text));

				(*it)->setDesc(comp.ouput(text));

				it = (*it)->downJoin.begin();
			}
			else {  //����������
				comp.input(text);
				it = (*it)->downJoin.begin();
			}
		}
		else if ((*it)->getId() == 3) {         //����Ǿ���-
			((MyRect *)(*it))->b = true;
			RedrawWindow();
			text = (*it)->getDesc();  //��ȡ���е���������
			MessageBox(text);
			comp.compute(text);
			it = (*it)->downJoin.begin();
		}


		else if ((*it)->getId() == 4) {    //��������� �жϿ�

			list<Shape *> ::iterator pit;
			CString op = (*it)->getOP();
			CString x2 = (*it)->getX2();
			CString y2 = (*it)->getY2();
			((Diamond *)(*it))->b = true;
			RedrawWindow();
			MessageBox((*it)->getDesc());
			if (op.GetLength() > 1) {  //��>= ���� <= ���� !=
				if (comp.judgeTwo(x2, y2, op)) {   //��Y��֧
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
						MessageBox(_T("û���ҵ�Y��֧������ͼ������"));
				}
				else {   //��N��֧
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
						MessageBox(_T("û���ҵ�N��֧������ͼ������"));
				}
			}
			else {    //��< ��> �� =
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
						MessageBox(_T("û���ҵ�Y��֧������ͼ������"));
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
						MessageBox(_T("û���ҵ�N��֧������ͼ������"));
				}

			}
		}


		else if ((*it)->getId() == 5) {         //������߶�
			((MyLine *)(*it))->b = true;
			it = (*it)->downJoin.begin();
		}


	} while (((*it)->getDesc()).Find(end) == -1);
	((MyRoundRect *)(*it))->b = true;
	RedrawWindow();
}


void CProcessDiagramView::OnCancle()
{
	// TODO: �ڴ���������������
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
	//��ʼ��
	//ʹ��˫���壬��������
	// TODO: �ڴ����ר�ô����/����û���

	//��ȡ��Ļ��С
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (NULL != this->activeShape) {//����ǰ�ͼԪָ����Ϊ��
		this->activeShape->onRelease(point.x, point.y);
		this->activeShape = NULL;
	}
	if (isNewShape) {//����ӵ�ͼԪ��ȷ��λ��

		this->activeShape = factory.createShape(this->type, point);
		if (NULL != this->activeShape) {
			this->GetDocument()->shapes.push_back(this->activeShape);
		}
		//this->isNewShape = false;
		return;
	}
	//ȷ����ǰ�ͼԪ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��������ͼԪ�ı��isNewShape��Ϊfalse	
	if (isNewShape) {
		this->isNewShape = false;
		return;
	}
	//����ǰ�ͼԪΪֱ�ߣ����ж��ƶ���ı���ֱ�ߣ��Ƿ����ӵ�ĳ��ͼԪ��
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�ƶ�
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

	// TODO: �ڴ˴������Ϣ����������
	//delete�����д�ŵ�����ͼԪ
	memBitmap.DeleteObject();
	memDC.DeleteDC();
	list<Shape*>::iterator sit;
	for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end(); sit++) {
		delete (*sit);
	}
}


BOOL CProcessDiagramView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return false;
}



void CProcessDiagramView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�޸�ͼԪ��ʾ�����
	list<Shape*>::iterator sit;
	//ȷ����ǰ���ͼԪ
	for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end(); sit++) {
		if ((*sit)->isActive(point)) {
			this->activeShape = (*sit);
			break;
		}
	}
	//���ø�ͼԪ�ķ������޸�ͼԪ���
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nChar == VK_DELETE)//���̰���Ϊdelete��
	{
		if (NULL != this->activeShape) {//��ǰ����ѡ��ͼԪ����ɾ��
			if (MessageBox(_T("ȷ��ɾ��"), _T("ɾ��ͼԪ"), MB_ICONEXCLAMATION | MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
				list<Shape*>::iterator sit;
				//��ͼԪ������ɾ��ѡ��ͼԪ
				list<Shape*> sll = this->GetDocument()->shapes;
				for (sit = this->GetDocument()->shapes.begin(); sit != this->GetDocument()->shapes.end();) {
					if ((*sit) == this->activeShape) {//���������ҵ���ǰ�ĻͼԪ

													  //��ǰͼԪ��������ͼԪ
						list<Shape*>::iterator upit;
						list<Shape*> uplist = (*sit)->getUpJoin();
						//for (upit = ((*sit)->getUpJoin().begin()); upit != ((*sit)->getUpJoin().end()); upit++) {
						for (upit = (*sit)->upJoin.begin(); upit != (*sit)->upJoin.end(); upit++) {
							//��ͼԪ���������µ�ָ��
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
						//��ǰͼԪ��������ͼԪ
						list<Shape*>::iterator downit;
						list<Shape*> downlist = (*sit)->getDownJoin();
						//for (downit = ((*sit)->getDownJoin().begin()); downit != ((*sit)->getDownJoin().end()); downit++){
						for (downit = (*sit)->downJoin.begin(); downit != (*sit)->downJoin.end(); downit++) {
							//��ͼԪ���������ϵ�ָ��
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
		else {//��ǰû��ѡ��ͼԪ������ʾ��Ϣ
			MessageBox(_T("����ѡ��ͼԪ"));
		}

	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
