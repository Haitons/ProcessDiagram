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
	CString x2, y2, op;//比较 值1值2 比较符
	CString desc;//菱形内容
	int id = 4;  //图形所属编号为4，代表菱形
				 //list<Shape*> upJoin;//上连接点
				 //list<Shape*> downJoin;//下连接点
				 //list<Shape*> leftJoin;
				 //list<Shape*> rightJoin;
	CRect upMiddleJoinRect;//上黑点
	CRect downMiddleJoinRect;//下黑点
	CRect leftMiddleJoinRect;//左黑点
	CRect rightMiddleJoinRect;//右黑点
	int pointWidth = 5;//标记点的宽度
	void setMiddleRect(); //设置连接点矩形
	void setLinePos();//设置连接线的位置，实现线随图元动
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
	void onPress(int px, int py);//鼠标按下
	void onRelease(int px, int py);//鼠标释放
	void editDia();//跳转
	void connect(Shape* myline, CPoint point);//连线
	void Serialize(CArchive &ar); //重写串行化函数 
	int getId();
	CString getX2();
	CString getY2();
	CString getOP();
	CString getDesc();
	void setDesc();
	void connect(Shape* myline);//读入文件将线段连接到图元上
	bool b;//颜色标识
};

