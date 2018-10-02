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
	int id = 5;  //线所属编号为5
	///list<Shape*> upJoin;//上连接点
	//list<Shape*> downJoin;//下连接点
	void setMiddle();//设置中点
	void setMiddleRect();//设置连接点矩形
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
	void onPress(int px, int py);//鼠标按下
	void onRelease(int px, int py);//鼠标释放
	void editDia();
	boolean isLine();
	void Serialize(CArchive &ar); //重写串行化函数 
	list<Shape*> getUpJoin();
	list<Shape*> getDownJoin();
	int getId();
	CString getDesc();
	bool b;
};

