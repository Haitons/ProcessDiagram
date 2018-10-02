#include "stdafx.h"
#include "MyRect.h"

IMPLEMENT_SERIAL(MyRect, Shape, 2) //�ڶ������λ�ã���һ������Ϊ��ǰ�������ڶ�������Ϊ��������������������Ϊ������ض����ͱ�ʶ,�ñ�ʶ����������(����ʵ����)����СΪ0
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
	//�ı����½�ϵ��λ��
	int x_middle = (this->left + this->right) / 2;
	this->upMiddleJoinRect.SetRect(x_middle - 2, this->up, x_middle + 3, this->up + this->pointWidth);
	this->downMiddleJoinRect.SetRect(x_middle - 2, this->down - this->pointWidth, x_middle + 3, this->down);
}

void MyRect::setLinePos()
{
	//���������߶ε���ʼλ�ã�ʹ����ͼ��
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
	pDC->TextOutW(this->left + 10, this->up + 10, this->desc);//��ʾ����
															  //�������Ӿ��ε�����
	this->setMiddleRect();
	//���������߶ε���ʼ��
	this->setLinePos();
	//��ʾ���ӵ�
	CBrush brush(RGB(0, 0, 0));
	pDC->FillRect(upMiddleJoinRect, &brush);
	pDC->FillRect(downMiddleJoinRect, &brush);
	if (active) {
		//��ʾ�ĸ��ǣ���ʾ�ǵ�ǰ�ͼԪ
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
	//����ƶ�
	if (0 == state) {
		this->offSet(cx, cy);
	}
	else if (1 == state) {//��
		this->onSize(-cx, 0); this->offSet(cx / 2, 0);
	}
	else if (2 == state) {//��
		this->onSize(0, -cy); this->offSet(0, cy / 2);
	}
	else if (3 == state) {//��
		this->onSize(cx, 0); this->offSet(cx / 2, 0);
	}
	else if (4 == state) {//��
		this->onSize(0, cy); this->offSet(0, cy / 2);
	}
	else if (5 == state) {//����
		this->onSize(-cx, -cy); this->offSet(cx / 2, cy / 2);
	}
	else if (6 == state) {//����
		this->onSize(cx, -cy); this->offSet(cx / 2, cy / 2);
	}
	else if (7 == state) {//����
		this->onSize(-cx, cy); this->offSet(cx / 2, cy / 2);
	}
	else if (8 == state) {//����
		this->onSize(cx, cy); this->offSet(cx / 2, cy / 2);
	}
}

void MyRect::onSize(int cx, int cy)
{
	this->up -= cy / 2;
	this->left -= cx / 2;
	this->right += cx / 2;
	this->down += cy / 2;
	//��Сsize
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
		state = 0;//ѡ���м��
	}
	else if ((this->left - 5) < px && px < (this->left + 5) && (this->up - 5) < py && py < (this->up + 5)) {
		state = 5;//ѡ�����Ͻ�
	}
	else if ((this->right - 5) < px && (this->right + 5) > px && (this->up - 5) < py && py < (this->up + 5)) {
		state = 6;//ѡ�����Ͻ�
	}
	else if ((this->left - 5) < px && px < (this->left + 5) && (this->down - 5) < py && py < (this->down + 5)) {
		state = 7;//ѡ�����½�
	}
	else if ((this->right - 5) < px && (this->right + 5) > px && (this->down - 5) < py && py < (this->down + 5)) {
		state = 8;//ѡ�����½�
	}
	else if ((this->left - 5) < px && px < (this->left + 5) && (this->up) < py && py < (this->down)) {
		state = 1;//ѡ�����
	}
	else if ((this->up - 5) < py && py < (this->up + 5) && (this->left) < px && px < (this->right)) {
		state = 2;//ѡ���ϱ�
	}
	else if ((this->right - 5) < px && (this->right + 5) > px && (this->up) < py && py < (this->down)) {
		state = 3;//ѡ���ұ�
	}
	else if ((this->down - 5) < py && (this->down + 5) > py && (this->left) < px && px < (this->right)) {
		state = 4;//ѡ���±�
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
			//�ߵ��յ��Ƿ���ͼԪ�����ӵ��غ�
			this->upJoin.push_back(myline);
			myline->setEnd((this->left + this->right) / 2, this->up);
			myline->addDownJoin(this);
		}
		else if (this->downMiddleJoinRect.PtInRect(point) && r.IntersectRect(myline->getUpMiddleJoinRect(), this->downMiddleJoinRect)) {
			//�ߵ�����Ƿ���ͼԪ�����ӵ��غ�
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
			//�ߵ��յ��Ƿ���ͼԪ�����ӵ��غ�
			this->upJoin.push_back(myline);
			myline->setEnd((this->left + this->right) / 2, this->up);
			myline->addDownJoin(this);
		}
		else if (r.IntersectRect(myline->getUpMiddleJoinRect(), this->downMiddleJoinRect)) {
			//�ߵ�����Ƿ���ͼԪ�����ӵ��غ�
			this->downJoin.push_back(myline);
			myline->setStart((this->left + this->right) / 2, this->down);
			myline->addUpJoin(this);
		}
	}
}

CString MyRect::getDesc() {
	return desc;
}
