#include "stdafx.h"
#include "Diamond.h"


void Diamond::setMiddleRect()
{
	//改变上下结合点的位置
	int x_middle = (this->left + this->right) / 2;
	int y_middle = (this->up + this->down) / 2;
	this->upMiddleJoinRect.SetRect(x_middle - 2, this->up, x_middle + 3, this->up + this->pointWidth);
	this->downMiddleJoinRect.SetRect(x_middle - 2, this->down - this->pointWidth, x_middle + 3, this->down);
	this->leftMiddleJoinRect.SetRect(this->left, y_middle - 2, this->left + this->pointWidth, y_middle + 3);
	this->rightMiddleJoinRect.SetRect(this->right, y_middle - 2, this->right + this->pointWidth, y_middle + 3);
}

void Diamond::setLinePos()
{
	//更新相连线段的起始位置，使线随图动
	list<Shape*>::iterator it;
	for (it = this->upJoin.begin(); it != this->upJoin.end(); it++) {
		(*it)->setEnd((this->left + this->right) / 2, this->up);
	}
	for (it = this->downJoin.begin(); it != this->downJoin.end(); it++) {
		(*it)->setStart((this->left + this->right) / 2, this->down);
	}
	for (it = this->leftJoin.begin(); it != this->leftJoin.end(); it++) {
		(*it)->setStart(this->left, (this->up + this->down) / 2);
	}
	for (it = this->rightJoin.begin(); it != this->rightJoin.end(); it++) {
		(*it)->setStart(this->right, (this->up + this->down) / 2);
	}
}

int Diamond::getUp()
{
	return this->up;
}

int Diamond::getDown()
{
	return this->down;
}

int Diamond::getLeft()
{
	return this->left;
}

int Diamond::getRight()
{
	return this->right;
}

Diamond::Diamond()
{
	this->left = 20;
	this->up = 20;
	this->right = 150;
	this->down = 100;
	this->type = "Diamond";
}

Diamond::Diamond(CPoint point)
{
	this->left = point.x;
	this->up = point.y;
	this->right = this->left + 120;
	this->down = this->up + 80;
	this->type = "Diamond";
}


Diamond::~Diamond()
{
}

void Diamond::setDesc(CString desc)
{
	this->desc = desc;
}

void Diamond::onDraw(CDC * pDC, boolean active)
{
	if (b)
		pDC->SelectObject(pen);
	else
		pDC->SelectObject(pencil);
	CPoint poly[4];//确定4个顶点 
	int x_middle = (this->right + this->left) / 2;
	int y_middle = (this->down + this->up) / 2;
	poly[0] = CPoint(x_middle, this->up);
	poly[1] = CPoint(this->right, y_middle);
	poly[2] = CPoint(x_middle, this->down);
	poly[3] = CPoint(this->left, y_middle);
	pDC->Polygon(poly, 4);

	pDC->TextOutW(this->left + 15, y_middle - 10, this->desc);

	//更新连接矩形的坐标
	this->setMiddleRect();
	//更新相连线段的起始点
	this->setLinePos();
	//显示连接点
	CBrush brush(RGB(0, 0, 0));
	pDC->FillRect(upMiddleJoinRect, &brush);
	pDC->FillRect(downMiddleJoinRect, &brush);
	pDC->FillRect(leftMiddleJoinRect, &brush);
	pDC->FillRect(rightMiddleJoinRect, &brush);
	if (active) {
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
boolean Diamond::isShowDia()
{
	return 0 == this->state;
}
boolean Diamond::isActive(CPoint p)
{
	CRect rc(getLeft(), getUp(), getRight(), getDown());
	if (rc.PtInRect(p)) {
		return true;
	}
	return false;
}
void Diamond::offSet(int cx, int cy)
{
	this->up += cy;
	this->left += cx;
	this->right += cx;
	this->down += cy;
}

void Diamond::onMove(int cx, int cy)
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

void Diamond::onSize(int cx, int cy)
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

void Diamond::onPress(int px, int py)
{
	if ((this->left + 5) < px && px < (this->right - 5) && (this->up + 5) < py && py < (this->down - 5)) {
		state = 0;//选中中间
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

void Diamond::onRelease(int px, int py)
{
	this->state = -1;
}

void Diamond::editDia()
{
	JudgeDlg jd;
	jd.x2 = this->x2;
	jd.y2 = this->y2;
	jd.text_op = this->op;
	if (IDOK == jd.DoModal())
	{
		this->x2 = jd.x2;
		this->y2 = jd.y2;
		this->op = jd.text_op;
		this->desc = this->x2 + this->op + this->y2;
	}
	
}

void Diamond::connect(Shape* myline, CPoint point)
{
	MyLine* line = dynamic_cast<MyLine*>(myline);
	if (NULL != line) {
		CRect r;
		if (this->upMiddleJoinRect.PtInRect(point) && r.IntersectRect(line->getDownMiddleJoinRect(), this->upMiddleJoinRect)) {
			//线的终点是否与图元上连接点重合
			this->upJoin.push_back(line);
			line->setEnd((this->left + this->right) / 2, this->up);
			line->addDownJoin(this);
		}
		else if (this->downMiddleJoinRect.PtInRect(point) && r.IntersectRect(line->getUpMiddleJoinRect(), this->downMiddleJoinRect)) {
			//线的起点是否与图元下连接点重合
			this->downJoin.push_back(line);
			line->setStart((this->left + this->right) / 2, this->down);
			line->addUpJoin(this);
		}
	}
	myline = line;
}
/*
connect(Shape * myline)
{
MyLine* line = dynamic_cast<MyLine*>(myline);
if (NULL != line) {
CRect r;
if (r.IntersectRect(line->getDownMiddleJoinRect(), this->upMiddleJoinRect)) {
//线的终点是否与图元上连接点重合
this->upJoin.push_back(line);
line->setEnd((this->left + this->right) / 2, this->up);
line->addDownJoin(this);
}
else if (r.IntersectRect(line->getUpMiddleJoinRect(), this->downMiddleJoinRect)) {
//线的起点是否与图元下连接点重合
this->downJoin.push_back(line);
line->setStart((this->left + this->right) / 2, this->down);
line->addUpJoin(this);
}
else if (r.IntersectRect(line->getUpMiddleJoinRect(), this->leftMiddleJoinRect)) {
//线的起点是否与图元左连接点重合
this->leftJoin.push_back(line);
line->setStart(this->left, (this->up + this->down) / 2);
line->addUpJoin(this);
}
else if (r.IntersectRect(line->getUpMiddleJoinRect(), this->rightMiddleJoinRect)) {
//线的起点是否与图元右连接点重合
this->rightJoin.push_back(line);
line->setStart(this->right, (this->up + this->down) / 2);
line->addUpJoin(this);
}
}
}
*/
void Diamond::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		ar << this->up << this->down << this->left << this->right << this->desc << this->x2 << this->op << this->y2;
	}
	else
	{
		ar >> this->up >> this->down >> this->left >> this->right >> this->desc >> this->x2 >> this->op >> this->y2;
	}
}

int Diamond::getId()
{
	return id;
}



CString Diamond::getX2()
{
	return x2;
}

CString Diamond::getY2()
{
	return y2;
}

CString Diamond::getOP()
{
	return op;
}

CString Diamond::getDesc()
{
	return desc;
}

void Diamond::setDesc()
{
	desc = x2 + op + y2;
}

void Diamond::connect(Shape * myline)
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
