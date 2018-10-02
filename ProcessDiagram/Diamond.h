#pragma once
#include "Shape.h"
#include"MyLine.h"
#include<list>
using namespace std;
class Diamond :
	public Shape
{
private:
	int up, down;
	int left, right;
	int state = -1;
	CString x2, y2, op;//�Ƚ� ֵ1ֵ2 �ȽϷ�
	CString desc;//��������
	int id = 4;  //ͼ���������Ϊ4����������
				 //list<Shape*> upJoin;//�����ӵ�
				 //list<Shape*> downJoin;//�����ӵ�
				 //list<Shape*> leftJoin;
				 //list<Shape*> rightJoin;
	CRect upMiddleJoinRect;//�Ϻڵ�
	CRect downMiddleJoinRect;//�ºڵ�
	CRect leftMiddleJoinRect;//��ڵ�
	CRect rightMiddleJoinRect;//�Һڵ�
	int pointWidth = 5;//��ǵ�Ŀ��
	void setMiddleRect(); //�������ӵ����
	void setLinePos();//���������ߵ�λ�ã�ʵ������ͼԪ��
	int getUp();
	int getDown();
	int getLeft();
	int getRight();
public:
	Diamond();
	Diamond(CPoint point);
	~Diamond();
	void setDesc(CString desc);
	void onDraw(CDC* pDC, boolean active);
	boolean isShowDia();
	boolean isActive(CPoint p);
	void offSet(int cx, int cy);
	void onMove(int cx, int cy);
	void onSize(int cx, int cy);
	void onPress(int px, int py);//��갴��
	void onRelease(int px, int py);//����ͷ�
	void editDia();//��ת
	void connect(Shape* myline, CPoint point);//����
	void Serialize(CArchive &ar); //��д���л����� 
	int getId();
	CString getX2();
	CString getY2();
	CString getOP();
	CString getDesc();
	void setDesc();
	void connect(Shape* myline);//�����ļ����߶����ӵ�ͼԪ��
	bool b;//��ɫ��ʶ
};

