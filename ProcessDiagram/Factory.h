#pragma once
#include"Shape.h"
#include"MyRect.h"
#include"MyRoundRect.h"
#include"Diamond.h"
#include"Parallelogram.h"
#include"MyLine.h"
/*
ͼ�ζ�������
*/
class Factory
{
public:
	Factory();
	~Factory();
	//����ͼԪ
	static Shape* createShape(CString type, CPoint point);
	static Shape* createShape(CString type);
};

