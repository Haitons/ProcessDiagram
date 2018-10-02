#include "stdafx.h"
#include "Factory.h"


Factory::Factory()
{
}


Factory::~Factory()
{
}

Shape * Factory::createShape(CString type, CPoint point)
{
	Shape* shape = NULL;
	if ("MyRect" == type) {
		shape = new MyRect(point);
	}
	else if ("MyRoundRect" == type) {
		shape = new MyRoundRect(point);
	}
	else if ("Diamond" == type) {
		shape = new Diamond(point);
	}
	else if ("Parallelogram" == type) {
		shape = new Parallelogram(point);
	}
	else if ("MyLine" == type) {
		shape = new MyLine(point);
	}
	return shape;
}

Shape * Factory::createShape(CString type)
{
	Shape* shape = NULL;
	if ("MyRect" == type) {
		shape = new MyRect();
	}
	else if ("MyRoundRect" == type) {
		shape = new MyRoundRect();
	}
	else if ("Diamond" == type) {
		shape = new Diamond();
	}
	else if ("Parallelogram" == type) {
		shape = new Parallelogram();
	}
	else if ("MyLine" == type) {
		shape = new MyLine();
	}
	return shape;
}
