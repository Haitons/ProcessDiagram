
// ProcessDiagramDoc.h : CProcessDiagramDoc ��Ľӿ�
//


#pragma once
#include"Shape.h"
#include<list>
#include"Factory.h"
using namespace std;

class CProcessDiagramDoc : public CDocument
{
protected: // �������л�����
	CProcessDiagramDoc();
	DECLARE_DYNCREATE(CProcessDiagramDoc)

// ����
public:
	list<Shape*> shapes;
// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CProcessDiagramDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
