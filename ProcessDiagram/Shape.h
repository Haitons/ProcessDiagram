#pragma once
#include"InputDlg.h"
#include"JudgeDlg.h"
#include<list>
using namespace std;
/*
ͼԪ����
���ࣺ����MyRect,ƽ���ı���Parallelogram,����Diamond,Բ�Ǿ���MyRoundRect,��Myline
*/
class Shape :public CObject
{
protected:
	CString type;//ͼԪ����
public:
	list<Shape*> upJoin;//�����ӵ�
	list<Shape*> downJoin;//�����ӵ�
	list<Shape*> leftJoin;//�����ӵ�
	list<Shape*> rightJoin;//�����ӵ�
public:
	DECLARE_SERIAL(Shape)    //��һ�����λ�ã�����Ϊ��ǰ����
	Shape();
	~Shape();
	CPen pen;
	CPen pencil;
	virtual list<Shape*> getUpJoin();
	virtual list<Shape*> getDownJoin();
	virtual list<Shape*> getleftJoin();
	virtual list<Shape*> getRightJoin();
	virtual void setStart(int x, int y);
	virtual void setEnd(int x, int y);
	virtual CString getType();
	virtual void setDesc(CString desc);
	virtual boolean isShowDia();//�жϵ�ǰλ���Ƿ�Ӧ����ʾ�����
	virtual boolean isActive(CPoint p);//�жϵ�ǰ�����λ���Ƿ��ڸ�ͼԪ��
	virtual void onDraw(CDC *pDC, boolean active);
	virtual void offSet(int cx, int cy);//λ��
	virtual void onMove(int cx, int cy);//�ƶ�
	virtual void onSize(int cx, int cy);//�ı��С
	virtual void onPress(int px, int py);//��갴��
	virtual void onRelease(int px, int py);//����ͷ�
	virtual void onDelete();
	virtual void editDia();//��ʾ����򣬲��������ݵ���ز���
	virtual void connect(Shape* myline, CPoint point);//���߶����ӵ�ͼԪ��
	virtual void setMiddleRect(); //�������ӵ����
	virtual boolean isLine();//ͼԪ�Ƿ�����
	void Serialize(CArchive &ar); //��д���л����� 
	virtual CRect getUpMiddleJoinRect();
	virtual CRect getDownMiddleJoinRect();
	virtual void addUpJoin(Shape* shape);
	virtual void addDownJoin(Shape* shape);
	virtual int getId();  //��ȡͼ���������
	virtual CString getDesc(); //��ȡͼ�ε���������
	virtual CString getX2();
	virtual CString getY2();
	virtual CString getOP();
	virtual void connect(Shape* myline);//�����ļ����߶����ӵ�ͼԪ��
};

