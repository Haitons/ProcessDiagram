#pragma once
#include <string>
#include <cctype>
#include <stack>
#include "analyze.h"


class ComputeUtil
{
public:
	CString x1, y1;
	int a, b;
	Analyze analyze;

	ComputeUtil();
	~ComputeUtil();
	CString getX1();
	CString getY1();
	int getA();
	int getB();
	void input(CString text);//处理输入框
	CString ouput(CString text);//处理输出框
	void compute(CString text);//处理运算框
	//判断数值
	bool judgeOne(CString x2, CString y2, CString op);
	bool judgeTwo(CString x2, CString y2, CString op);
};

