#pragma once
#include "Shape.h"
#include"MyLine.h"
#include<list>
using namespace std;
class MyRoundRect :
	public Shape
{
private:
	int up, down;
	int left, right;
	int state = -1;
	CString desc;
	int id = 1;//Բ�Ǿ��α��Ϊ1
	int roundWidth = 30;
	int roundLegth = 30;
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
	MyRoundRect();
	MyRoundRect(CPoint point);
	~MyRoundRect();
	void onDraw(CDC* pDC, boolean active);
	boolean isShowDia();
	boolean isActive(CPoint p);
	void offSet(int cx, int cy);
	void onMove(int cx, int cy);
	void onSize(int cx, int cy);
	void onPress(int px, int py);//��갴��
	void onRelease(int px, int py);//����ͷ�
	void editDia();
	void connect(Shape* myline, CPoint point);//����
	void Serialize(CArchive &ar); //��д���л����� 
	int getId();
	CString getDesc();
	void connect(Shape* myline);//�����ļ����߶����ӵ�ͼԪ��
	bool b;
};

