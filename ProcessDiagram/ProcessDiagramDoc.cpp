
// ProcessDiagramDoc.cpp : CProcessDiagramDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ProcessDiagram.h"
#endif

#include "ProcessDiagramDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CProcessDiagramDoc

IMPLEMENT_DYNCREATE(CProcessDiagramDoc, CDocument)

BEGIN_MESSAGE_MAP(CProcessDiagramDoc, CDocument)
END_MESSAGE_MAP()


// CProcessDiagramDoc ����/����

CProcessDiagramDoc::CProcessDiagramDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CProcessDiagramDoc::~CProcessDiagramDoc()
{
}

BOOL CProcessDiagramDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CProcessDiagramDoc ���л�

void CProcessDiagramDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		//�浽�ļ���
		ar << this->shapes.size();//ͼԪ����
		list<Shape*>::iterator sit;
		for (sit = this->shapes.begin(); sit != this->shapes.end(); sit++) {
			ar << (*sit)->getType();
			(*sit)->Serialize(ar);
		}
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		this->shapes.clear();
		Factory factory;
		int count;//ͼԪ����
		ar >> count;
		//����ÿ��ͼԪ
		for (int i = 0; i < count; i++) {
			CString type;
			ar >> type;
			Shape* shape = factory.createShape(type);
			shape->Serialize(ar);
			this->shapes.push_back(shape);
			shape->setMiddleRect();
		}
		//��������
		list<Shape*>::iterator sit;
		for (sit = this->shapes.begin(); sit != this->shapes.end(); sit++) {
			if ((*sit)->isLine()) {
				list<Shape*>::iterator it;
				for (it = this->shapes.begin(); it != this->shapes.end(); it++) {
					if (!(*it)->isLine()) {
						(*it)->connect((*sit));
					}
				}
			}
		}
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CProcessDiagramDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CProcessDiagramDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CProcessDiagramDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CProcessDiagramDoc ���

#ifdef _DEBUG
void CProcessDiagramDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProcessDiagramDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CProcessDiagramDoc ����
