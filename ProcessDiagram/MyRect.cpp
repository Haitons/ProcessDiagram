#include "stdafx.h"
#include "MyRect.h"

IMPLEMENT_SERIAL(MyRect, Shape, 2) //第二个宏的位置，第一个参数为当前类名，第二个参数为父类类名，第三个参数为该类的特定整型标识,该标识将用来解序(重新实例化)，最小为0
MyRect::MyRect()
{
	this->left = 20;
	this->up = 20;
	this->right = 150;
	this->down = 100;
	this->setMiddleRect();
	this->type = "MyRect";
}

MyRect::MyRect(CPoint point)
{
	this->left = point.x;
	this->up = point.y;
	this->right = this->left + 120;
	this->down = this->up + 80;
	this->setMiddleRect();
	this->type = "MyRect";
}

int MyRect::getUp()
{
	return this->up;
}

int MyRect::getDown()
{
	return this->down;
}

int MyRect::getLeft()
{
	return this->left;
}


int MyRect::getRight()
{
	return this->right;
}

void MyRect::setMiddleRect()
{
	//改变上下结合点的位置
	int x_middle = (this->left + this->right) / 2;
	this->upMiddleJoinRect.SetRect(x_middle - 2, this->up, x_middle + 3, this->up + this->pointWidth);
	this->downMiddleJoinRect.SetRect(x_middle - 2, this->down - this->pointWidth, x_middle + 3, this->down);
}

void MyRect::setLinePos()
{
	//更新相连线段的起始位置，使线随图动
	list<Shape*>::iterator it;
	for (it = this->upJoin.begin(); it != this->upJoin.end(); it++) {
		(*it)->setEnd((this->left + this->right) / 2, this->up);
	}
	for (it = this->downJoin.begin(); it != this->downJoin.end(); it++) {
		(*it)->setStart((this->left + this->right) / 2, this->down);
	}
}

MyRect::~MyRect()
{
}



void MyRect::onDraw(CDC * pDC, boolean active)
{
	if (b)
		pDC->SelectObject(pen);
	else
		pDC->SelectObject(pencil);
	pDC->Rectangle(this->left, this->up, this->right, this->down);
	pDC->TextOutW(this->left + 10, this->up + 10, this->desc);//显示内容
															  //更新连接矩形的坐标
	this->setMiddleRect();
	//更新相连线段的起始点
	this->setLinePos();
	//显示连接点
	CBrush brush(RGB(0, 0, 0));
	pDC->FillRect(upMiddleJoinRect, &brush);
	pDC->FillRect(downMiddleJoinRect, &brush);
	if (active) {
		//显示四个角，表示是当前活动图元
		CRect r1(this->left, this->up, this->left + 5, this->up + 5);
		CRect r2(this->left, this->down - 5, this->left + 5, this->down);
		CRect r3(this->right - 5, this->up, this->right, this->up + 5);
		CRect r4(this->right - 5, this->down - 5, this->right, this->down);
		pDC->FillRect(r1, &brush);
		pDC->FillRect(r2, &brush);
		pDC->FillRect(r3, &brush);
		pDC->FillRect(r4, &brush);
	}
	brush.DeleteObject();
}

boolean MyRect::isShowDia()
{
	return 0 == this->state;
}

boolean MyRect::isActive(CPoint p)
{
	CRect rc(getLeft(), getUp(), getRight(), getDown());
	if (rc.PtInRect(p)) {
		return true;
	}
	return false;
}

void MyRect::offSet(int cx, int cy)
{
	this->up += cy;
	this->left += cx;
	this->right += cx;
	this->down += cy;
}

void MyRect::onMove(int cx, int cy)
{
	//鼠标移动
	if (0 == state) {
		this->offSet(cx, cy);
	}
	else if (1 == state) {//左
		this->onSize(-cx, 0); this->offSet(cx / 2, 0);
	}
	else if (2 == state) {//上
		this->onSize(0, -cy); this->offSet(0, cy / 2);
	}
	else if (3 == state) {//右
		this->onSize(cx, 0); this->offSet(cx / 2, 0);
	}
	else if (4 == state) {//下
		this->onSize(0, cy); this->offSet(0, cy / 2);
	}
	else if (5 == state) {//左上
		this->onSize(-cx, -cy); this->offSet(cx / 2, cy / 2);
	}
	else if (6 == state) {//右上
		this->onSize(cx, -cy); this->offSet(cx / 2, cy / 2);
	}
	else if (7 == state) {//左下
		this->onSize(-cx, cy); this->offSet(cx / 2, cy / 2);
	}
	else if (8 == state) {//右下
		this->onSize(cx, cy); this->offSet(cx / 2, cy / 2);
	}
}

void MyRect::onSize(int cx, int cy)
{
	this->up -= cy / 2;
	this->left -= cx / 2;
	this->right += cx / 2;
	this->down += cy / 2;
	//最小size
	if (this->down - this->up<this->pointWidth * 2) {
		this->down = this->up + this->pointWidth * 2;
	}
	if (this->right - this->left<this->pointWidth * 3) {
		this->right = this->left + this->pointWidth * 3;
	}
}

void MyRect::onPress(int px, int py)
{
	if ((this->left + 5) < px && px < (this->right - 5) && (this->up + 5) < py && py < (this->down - 5)) {
		state = 0;//选中中间放
	}
	else if ((this->left - 5) < px && px < (this->left + 5) && (this->up - 5) < py && py < (this->up + 5)) {
		state = 5;//选中左上角
	}
	else if ((this->right - 5) < px && (this->right + 5) > px && (this->up - 5) < py && py < (this->up + 5)) {
		state = 6;//选中右上角
	}
	else if ((this->left - 5) < px && px < (this->left + 5) && (this->down - 5) < py && py < (this->down + 5)) {
		state = 7;//选中左下角
	}
	else if ((this->right - 5) < px && (this->right + 5) > px && (this->down - 5) < py && py < (this->down + 5)) {
		state = 8;//选中右下角
	}
	else if ((this->left - 5) < px && px < (this->left + 5) && (this->up) < py && py < (this->down)) {
		state = 1;//选中左边
	}
	else if ((this->up - 5) < py && py < (this->up + 5) && (this->left) < px && px < (this->right)) {
		state = 2;//选中上边
	}
	else if ((this->right - 5) < px && (this->right + 5) > px && (this->up) < py && py < (this->down)) {
		state = 3;//选中右边
	}
	else if ((this->down - 5) < py && (this->down + 5) > py && (this->left) < px && px < (this->right)) {
		state = 4;//选中下边
	}
}

void MyRect::onRelease(int px, int py)
{
	this->state = -1;
}

void MyRect::editDia()
{
	InputDlg rd;
	rd.desc = this->desc;
	if (IDOK == rd.DoModal())
	{
		this->desc = rd.desc;
	}
}

void MyRect::connect(Shape* myline, CPoint point)
{
	if ("MyLine" == myline->getType()) {
		CRect r;
		if (this->upMiddleJoinRect.PtInRect(point) && r.IntersectRect(myline->getDownMiddleJoinRect(), this->upMiddleJoinRect)) {
			//线的终点是否与图元上连接点重合
			this->upJoin.push_back(myline);
			myline->setEnd((this->left + this->right) / 2, this->up);
			myline->addDownJoin(this);
		}
		else if (this->downMiddleJoinRect.PtInRect(point) && r.IntersectRect(myline->getUpMiddleJoinRect(), this->downMiddleJoinRect)) {
			//线的起点是否与图元下连接点重合
			this->downJoin.push_back(myline);
			myline->setStart((this->left + this->right) / 2, this->down);
			myline->addUpJoin(this);
		}
	}
}

void MyRect::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		ar << this->up << this->down << this->left << this->right << this->desc;
	}
	else
	{
		ar >> this->up >> this->down >> this->left >> this->right >> this->desc;
	}
}

list<Shape*> MyRect::getUpJoin()
{
	return this->upJoin;
}

list<Shape*> MyRect::getDownJoin()
{
	return this->downJoin;
}

int MyRect::getId() {
	return id;
}

void MyRect::connect(Shape * myline)
{
	if ("MyLine" == myline->getType()) {
		CRect r;
		if (r.IntersectRect(myline->getDownMiddleJoinRect(), this->upMiddleJoinRect)) {
			//线的终点是否与图元上连接点重合
			this->upJoin.push_back(myline);
			myline->setEnd((this->left + this->right) / 2, this->up);
			myline->addDownJoin(this);
		}
		else if (r.IntersectRect(myline->getUpMiddleJoinRect(), this->downMiddleJoinRect)) {
			//线的起点是否与图元下连接点重合
			this->downJoin.push_back(myline);
			myline->setStart((this->left + this->right) / 2, this->down);
			myline->addUpJoin(this);
		}
	}
}

CString MyRect::getDesc() {
	return desc;
}
