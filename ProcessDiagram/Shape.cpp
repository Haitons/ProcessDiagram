#include "stdafx.h"
#include "Shape.h"

IMPLEMENT_SERIAL(Shape, CObject, 1) 
//第二个宏的位置，第一个参数为当前类名，第二个参数为父类类名，第三个参数为该类的特定整型标识,该标识将用来解序(重新实例化)，最小为0
Shape::Shape()
{
	this->type = "Shape";
	pen.CreatePen(0, 2, RGB(255, 0, 0));
	pencil.CreatePen(0, 1, RGB(0, 0, 0));
}


Shape::~Shape()
{
}

list<Shape*> Shape::getUpJoin()
{
	return this->upJoin;
}

list<Shape*> Shape::getDownJoin()
{
	return this->downJoin;
}

list<Shape*> Shape::getleftJoin()
{
	return this->leftJoin;
}

list<Shape*> Shape::getRightJoin()
{
	return this->rightJoin;
}
void Shape::setStart(int x, int y)
{
}

void Shape::setEnd(int x, int y)
{
}

CString Shape::getType()
{
	return this->type;
}

void Shape::setDesc(CString desc)
{
}


boolean Shape::isShowDia()
{
	return boolean();
}

boolean Shape::isActive(CPoint p)
{
	return boolean();
}

void Shape::onDraw(CDC * pDC, boolean active)
{
}

void Shape::offSet(int cx, int cy)//位移
{
}

void Shape::onMove(int cx, int cy)
{

}

void Shape::onSize(int cx, int cy)
{

}

void Shape::onPress(int px, int py)
{

}

void Shape::onRelease(int px, int py)
{

}

void Shape::onDelete()
{
	delete(this);
}

void Shape::editDia()
{

}

void Shape::connect(Shape* myline, CPoint point)
{
}

void Shape::setMiddleRect()
{
}

boolean Shape::isLine()
{
	return false;
}

void Shape::Serialize(CArchive & ar)
{
}

CRect Shape::getUpMiddleJoinRect()
{
	return CRect();
}

CRect Shape::getDownMiddleJoinRect()
{
	return CRect();
}

void Shape::addUpJoin(Shape * shape)
{
}

void Shape::addDownJoin(Shape * shape)
{
}
int Shape::getId() {
	return int();
}

CString Shape::getDesc() {
	return CString();
}

CString Shape::getX2()
{
	return CString();
}

CString Shape::getY2()
{
	return CString();
}

CString Shape::getOP()
{
	return CString();
}

void Shape::connect(Shape * myline)
{
}
