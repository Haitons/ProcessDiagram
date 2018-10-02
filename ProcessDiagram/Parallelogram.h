#pragma once
#include "Shape.h"
#include"MyLine.h"
#include<list>
using namespace std;
class Parallelogram :
	public Shape
{
private:
	int up, down;
	int left, right;
	int state = -1;
	CString desc;
	int id = 2;   //ƽ���ı��α��Ϊ2
				  //list<Shape*> upJoin;//�����ӵ�
				  //list<Shape*> downJoin;//�����ӵ�
	CRect upMiddleJoinRect;//�Ϻڵ�
	CRect downMiddleJoinRect;//�ºڵ�
	int pointWidth = 5;//��ǵ�Ŀ��
	void setMiddleRect(); //�������ӵ����
	void setLinePos();//���������ߵ�λ��
	int getUp();
	int getDown();
	int getLeft();
	int getRight();
public:
	DECLARE_SERIAL(Parallelogram)    //��һ�����λ�ã�����Ϊ��ǰ����
	Parallelogram();
	Parallelogram(CPoint point);
	~Parallelogram();
	void onDraw(CDC* pDC, boolean active);
	void setDesc(CString desc);
	boolean isShowDia();
	boolean isActive(CPoint p);
	void offSet(int cx, int cy);
	void onMove(int cx, int cy);
	void onSize(int cx, int cy);
	void onPress(int px, int py);//��갴��
	void onRelease(int px, int py);//����ͷ�
	void editDia();
	void connect(Shape* myline, CPoint point);
	void Serialize(CArchive &ar); //��д���л����� 
	int getId();
	CString getDesc();
	void connect(Shape* myline);//�����ļ����߶����ӵ�ͼԪ��
	bool b;
};

