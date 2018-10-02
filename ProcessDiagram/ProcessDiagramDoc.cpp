
// ProcessDiagramDoc.cpp : CProcessDiagramDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CProcessDiagramDoc 构造/析构

CProcessDiagramDoc::CProcessDiagramDoc()
{
	// TODO: 在此添加一次性构造代码

}

CProcessDiagramDoc::~CProcessDiagramDoc()
{
}

BOOL CProcessDiagramDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CProcessDiagramDoc 序列化

void CProcessDiagramDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		//存到文件里
		ar << this->shapes.size();//图元个数
		list<Shape*>::iterator sit;
		for (sit = this->shapes.begin(); sit != this->shapes.end(); sit++) {
			ar << (*sit)->getType();
			(*sit)->Serialize(ar);
		}
	}
	else
	{
		// TODO: 在此添加加载代码
		this->shapes.clear();
		Factory factory;
		int count;//图元个数
		ar >> count;
		//产生每个图元
		for (int i = 0; i < count; i++) {
			CString type;
			ar >> type;
			Shape* shape = factory.createShape(type);
			shape->Serialize(ar);
			this->shapes.push_back(shape);
			shape->setMiddleRect();
		}
		//建立连接
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

// 缩略图的支持
void CProcessDiagramDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CProcessDiagramDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CProcessDiagramDoc 诊断

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


// CProcessDiagramDoc 命令
