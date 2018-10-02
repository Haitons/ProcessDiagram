#pragma once
#include"InputDlg.h"
#include"JudgeDlg.h"
#include<list>
using namespace std;
/*
图元基类
子类：矩形MyRect,平行四边形Parallelogram,菱形Diamond,圆角矩形MyRoundRect,线Myline
*/
class Shape :public CObject
{
protected:
	CString type;//图元类型
public:
	list<Shape*> upJoin;//上连接点
	list<Shape*> downJoin;//下连接点
	list<Shape*> leftJoin;//左连接点
	list<Shape*> rightJoin;//右连接点
public:
	DECLARE_SERIAL(Shape)    //第一个宏的位置，参数为当前类名
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
	virtual boolean isShowDia();//判断当前位置是否应该显示输入框
	virtual boolean isActive(CPoint p);//判断当前鼠标点击位置是否在该图元内
	virtual void onDraw(CDC *pDC, boolean active);
	virtual void offSet(int cx, int cy);//位移
	virtual void onMove(int cx, int cy);//移动
	virtual void onSize(int cx, int cy);//改变大小
	virtual void onPress(int px, int py);//鼠标按下
	virtual void onRelease(int px, int py);//鼠标释放
	virtual void onDelete();
	virtual void editDia();//显示输入框，并输入数据的相关操作
	virtual void connect(Shape* myline, CPoint point);//将线段连接到图元上
	virtual void setMiddleRect(); //设置连接点矩形
	virtual boolean isLine();//图元是否是线
	void Serialize(CArchive &ar); //重写串行化函数 
	virtual CRect getUpMiddleJoinRect();
	virtual CRect getDownMiddleJoinRect();
	virtual void addUpJoin(Shape* shape);
	virtual void addDownJoin(Shape* shape);
	virtual int getId();  //获取图形所属编号
	virtual CString getDesc(); //获取图形的输入内容
	virtual CString getX2();
	virtual CString getY2();
	virtual CString getOP();
	virtual void connect(Shape* myline);//读入文件将线段连接到图元上
};

