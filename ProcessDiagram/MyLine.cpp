#include "stdafx.h"
#include "MyLine.h"


void MyLine::setMiddle()
{
	middle.x = (this->start.x + this->end.x) / 2;
	middle.y = (this->start.y + this->end.y) / 2;
}

void MyLine::setMiddleRect()
{
	this->upMiddleJoinRect.SetRect(start.x - 2, start.y - 2, start.x + 2, start.y + 2);
	this->downMiddleJoinRect.SetRect(end.x - 2, end.y - 2, end.x + 2, end.y + 2);
	this->setMiddle();
}

CRect MyLine::getUpMiddleJoinRect()
{
	return this->upMiddleJoinRect;
}

CRect MyLine::getDownMiddleJoinRect()
{
	return this->downMiddleJoinRect;
}

void MyLine::addUpJoin(Shape * shape)
{
	this->upJoin.push_back(shape);
}

void MyLine::addDownJoin(Shape * shape)
{
	this->downJoin.push_back(shape);
}

void MyLine::setStart(int x, int y)
{
	this->start.x = x;
	this->start.y = y;
}

void MyLine::setEnd(int x, int y)
{
	this->end.x = x;
	this->end.y = y;
}

MyLine::MyLine()
{
	this->start.x = 20;
	this->start.y = 20;
	this->end.x = 20;
	this->end.y = 100;
	this->setMiddle();
	this->setMiddleRect();
	this->type = "MyLine";
	this->desc = "";
}

MyLine::MyLine(CPoint p)
{
	this->start.x = p.x;
	this->start.y = p.y;
	this->end.x = p.x;
	this->end.y = p.y + 100;
	this->setMiddle();
	this->setMiddleRect();
	this->type = "MyLine";
	this->desc = "";

}


MyLine::~MyLine()
{
}

boolean MyLine::isShowDia()
{
	return 2 == this->state;
}

boolean MyLine::isActive(CPoint p)
{
	boolean sign = false;
	if (p.x >= start.x - 2 && p.x <= start.x + 2 && p.y >= start.y - 2 && p.y <= start.y + 2) {
		sign = true;//选中起点
	}
	else if (p.x >= middle.x - 2 && p.x <= middle.x + 2 && p.y >= middle.y - 2 && p.y <= middle.y + 2) {
		sign = true;//选中中间
	}
	else if (p.x >= end.x - 2 && p.x <= end.x + 2 && p.y >= end.y - 2 && p.y <= end.y + 2) {
		sign = true;//选中终点
	}
	return sign;
}

void MyLine::onSize(int cx, int cy)
{

}

void MyLine::offSet(int cx, int cy)
{
	start.x = start.x + cx;
	start.y = start.y + cy;
	end.x = end.x + cx;
	end.y = end.y + cy;
	this->setMiddle();
	this->setMiddleRect();
}

void MyLine::onMove(int cx, int cy)
{
	//鼠标移动
	if (1 == state) {//起点
		this->start.x += cx;
		this->start.y += cy;
		this->setMiddle();
		this->setMiddleRect();
	}
	else if (2 == state) {//中间
		this->offSet(cx, cy);
	}
	else if (3 == state) {//终点
		this->end.x += cx;
		this->end.y += cy;
		this->setMiddle();
		this->setMiddleRect();
	}
}

void MyLine::editDia()
{
	InputDlg rd;
	rd.desc = this->desc;
	if (IDOK == rd.DoModal())
	{
		this->desc = rd.desc;
	}
}

boolean MyLine::isLine()
{
	return true;
}

void MyLine::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		ar << this->start << this->middle << this->end << this->desc;
	}
	else
	{
		ar >> this->start >> this->middle >> this->end >> this->desc;
	}
}

list<Shape*> MyLine::getUpJoin()
{
	return this->upJoin;
}

list<Shape*> MyLine::getDownJoin()
{
	return this->downJoin;
}

void MyLine::onDraw(CDC * pDC, boolean active)
{
	if (b)
		pDC->SelectObject(pen);
	else
		pDC->SelectObject(pencil);
	this->setMiddleRect();
	pDC->Ellipse(this->upMiddleJoinRect);
	pDC->Ellipse(middle.x - 2, middle.y - 2, middle.x + 2, middle.y + 2);
	//pDC->Ellipse(end.x - 2, end.y - 2, end.x + 2, end.y + 2);
	pDC->MoveTo(this->start);
	pDC->LineTo(this->end);
	pDC->TextOutW(this->middle.x, this->middle.y - 10, this->desc);
	//画箭头
	CPoint p1, p2;
	double px = this->start.x - this->end.x;
	double py = this->start.y - this->end.y;
	int length = 10;//箭头长度
	double theta = 30 * 3.14 / 180;//箭头与直线的角度
	p1.x = px*cos(theta) - py*sin(theta);
	p1.y = px*sin(theta) + py*cos(theta);
	p2.x = px*cos(-theta) - py*sin(-theta);
	p2.y = px*sin(-theta) + py*cos(-theta);
	double x1_length = sqrt(p1.x*p1.x + p1.y*p1.y);
	double x2_length = sqrt(p2.x*p2.x + p2.y*p2.y);
	p1.x = p1.x*length / x1_length + this->end.x;
	p1.y = p1.y*length / x1_length + this->end.y;
	p2.x = p2.x*length / x2_length + this->end.x;
	p2.y = p2.y*length / x2_length + this->end.y;

	pDC->MoveTo(this->end);
	pDC->LineTo(p1);
	pDC->MoveTo(this->end);
	pDC->LineTo(p2);

	if (active) {

		CBrush brush(RGB(0, 0, 0));
		pDC->FillRect(upMiddleJoinRect, &brush);
		pDC->FillRect(downMiddleJoinRect, &brush);
		brush.DeleteObject();
	}
}

void MyLine::onPress(int px, int py)
{
	if (px >= start.x - 2 && px <= start.x + 2 && py >= start.y - 2 && py <= start.y + 2) {
		this->state = 1;//选中起点
	}
	else if (px >= middle.x - 2 && px <= middle.x + 2 && py >= middle.y - 2 && py <= middle.y + 2) {
		this->state = 2;//选中中间
	}
	else if (px >= end.x - 2 && px <= end.x + 2 && py >= end.y - 2 && py <= end.y + 2) {
		this->state = 3;//选中终点
	}
}

void MyLine::onRelease(int px, int py)
{
	this->state = -1;
}

int MyLine::getId()
{
	return id;
}

CString MyLine::getDesc()
{
	return desc;
}
