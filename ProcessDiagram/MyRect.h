#pragma once
#include"Shape.h"
#include"MyLine.h"
#include<list>
using namespace std;
class MyRect :public Shape
{
private:
	int up, down;
	int left, right;
	int state = -1;
	CString desc;
	int id = 3;  //���α��Ϊ3
				 //list<Shape*> upJoin;//�����ӵ�
				 //list<Shape*> downJoin;//�����ӵ�
	CRect upMiddleJoinRect;//�Ϻڵ�
	CRect downMiddleJoinRect;//�ºڵ�
	int pointWidth = 5;//��ǵ�Ŀ��
	void setMiddleRect(); //�������ӵ����
	void setLinePos();//���������ߵ�λ�ã�ʵ������ͼԪ��
	int getUp();
	int getDown();
	int getLeft();
	int getRight();
public:
	DECLARE_SERIAL(MyRect)    //��һ�����λ�ã�����Ϊ��ǰ����
	MyRect();
	MyRect(CPoint point);
	~MyRect();
	boolean isShowDia();
	boolean isActive(CPoint p);
	void onDraw(CDC *pDC, boolean active);
	void offSet(int cx, int cy);
	void onMove(int cx, int cy);
	void onSize(int cx, int cy);
	void onPress(int px, int py);//��갴��
	void onRelease(int px, int py);//����ͷ�
	void editDia();//����dia������desc
	void connect(Shape* myline, CPoint point);//����
	void Serialize(CArchive &ar); //��д���л����� 
	list<Shape*> getUpJoin();
	list<Shape*> getDownJoin();
	CString getDesc();
	int getId();
	void connect(Shape* myline);//�����ļ����߶����ӵ�ͼԪ��
	bool b;
};

