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
	int id = 1;//圆角矩形编号为1
	int roundWidth = 30;
	int roundLegth = 30;
	//list<Shape*> upJoin;//上连接点
	//list<Shape*> downJoin;//下连接点
	CRect upMiddleJoinRect;//上黑点
	CRect downMiddleJoinRect;//下黑点
	int pointWidth = 5;//标记点的宽度
	void setMiddleRect(); //设置连接点矩形
	void setLinePos();//设置连接线的位置，实现线随图元动
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
	void onPress(int px, int py);//鼠标按下
	void onRelease(int px, int py);//鼠标释放
	void editDia();
	void connect(Shape* myline, CPoint point);//连线
	void Serialize(CArchive &ar); //重写串行化函数 
	int getId();
	CString getDesc();
	void connect(Shape* myline);//读入文件将线段连接到图元上
	bool b;
};

