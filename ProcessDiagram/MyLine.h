#pragma once
#include"Shape.h"
#include<list>
using namespace std;
class MyLine :public Shape
{
private:
	CPoint start, end, middle;
	int state = -1;
	CString desc;
	int id = 5;  //���������Ϊ5
	///list<Shape*> upJoin;//�����ӵ�
	//list<Shape*> downJoin;//�����ӵ�
	void setMiddle();//�����е�
	void setMiddleRect();//�������ӵ����
	CRect upMiddleJoinRect;
	CRect downMiddleJoinRect;
public:
	CRect getUpMiddleJoinRect();
	CRect getDownMiddleJoinRect();
	void addUpJoin(Shape* shape);
	void addDownJoin(Shape* shape);
	void setStart(int x, int y);
	void setEnd(int x, int y);
	MyLine();
	MyLine(CPoint p);
	~MyLine();
	void onDraw(CDC* pDC, boolean active);
	boolean isShowDia();
	boolean isActive(CPoint p);
	void onSize(int cx, int cy);
	void offSet(int cx, int cy);
	void onMove(int cx, int cy);
	void onPress(int px, int py);//��갴��
	void onRelease(int px, int py);//����ͷ�
	void editDia();
	boolean isLine();
	void Serialize(CArchive &ar); //��д���л����� 
	list<Shape*> getUpJoin();
	list<Shape*> getDownJoin();
	int getId();
	CString getDesc();
	bool b;
};

