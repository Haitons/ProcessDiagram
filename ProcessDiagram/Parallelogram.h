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
	int id = 2;   //平行四边形编号为2
				  //list<Shape*> upJoin;//上连接点
				  //list<Shape*> downJoin;//下连接点
	CRect upMiddleJoinRect;//上黑点
	CRect downMiddleJoinRect;//下黑点
	int pointWidth = 5;//标记点的宽度
	void setMiddleRect(); //设置连接点矩形
	void setLinePos();//设置连接线的位置
	int getUp();
	int getDown();
	int getLeft();
	int getRight();
public:
	DECLARE_SERIAL(Parallelogram)    //第一个宏的位置，参数为当前类名
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
	void onPress(int px, int py);//鼠标按下
	void onRelease(int px, int py);//鼠标释放
	void editDia();
	void connect(Shape* myline, CPoint point);
	void Serialize(CArchive &ar); //重写串行化函数 
	int getId();
	CString getDesc();
	void connect(Shape* myline);//读入文件将线段连接到图元上
	bool b;
};

