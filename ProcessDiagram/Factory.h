#pragma once
#include"Shape.h"
#include"MyRect.h"
#include"MyRoundRect.h"
#include"Diamond.h"
#include"Parallelogram.h"
#include"MyLine.h"
/*
图形对象生成
*/
class Factory
{
public:
	Factory();
	~Factory();
	//创建图元
	static Shape* createShape(CString type, CPoint point);
	static Shape* createShape(CString type);
};

