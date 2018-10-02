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
	void input(CString text);//���������
	CString ouput(CString text);//���������
	void compute(CString text);//���������
	//�ж���ֵ
	bool judgeOne(CString x2, CString y2, CString op);
	bool judgeTwo(CString x2, CString y2, CString op);
};

