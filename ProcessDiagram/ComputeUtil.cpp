#include "stdafx.h"
#include "ComputeUtil.h"
#include <string>
#include <stack>
#include <vector>
#include <map>
using namespace std;


ComputeUtil::ComputeUtil()
{
}


ComputeUtil::~ComputeUtil()
{
}

CString ComputeUtil::getX1()
{
	return x1;
}

CString ComputeUtil::getY1()
{
	return y1;
}

int ComputeUtil::getA()
{
	return a;
}

int ComputeUtil::getB()
{
	return b;
}

void ComputeUtil::input(CString text)    //处理输入框
{
	if (text.Find(' ') != -1)
		text.Remove(' ');
	int npos = text.Find('=');
	x1 = text.Left(npos);     //存储 = 号左边的变量
	text.Delete(0, npos + 1);    //删掉 =号及前面的
	int npos1 = text.Find(',');
	a = _ttoi((text.Left(npos1)));  //存储 ,号前的值
	text.Delete(0, npos1 + 1);   //删掉 ，号及以前的
	npos = text.Find('=');
	if (text.Find(' ') != -1)
		text.Remove(' ');
	y1 = text.Left(npos);
	text.Delete(0, npos + 1);
	b = _ttoi(text);
}

CString ComputeUtil::ouput(CString text)    //处理输出框
{
	CString s("的值为:"), answer;

	if (text.Find(' ') != -1)
		text.Remove(' ');

	if (text.Find(',') != -1) {   //output多个变量

	}
	else {      //output一个变量
		answer = text;
		answer += s;
		if (text == x1) {
			s.Format(_T("%d"), a);
			answer += s;
			return answer;
		}
		else if (text == y1) {
			s.Format(_T("%d"), b);
			answer += s;
			return answer;
		}
		else {             //如果不是那两个变量，则是常量，直接output

			return text;
		}
	}
}

void ComputeUtil::compute(CString text)    //处理运算框
{
	std::string x11 = "", y11 = "";
	for (int i = 0; i < x1.GetLength(); i++) {
		x11 += x1[i];
	}
	for (int i = 0; i < y1.GetLength(); i++) {
		y11 += y1[i];
	}
	std::string temp = "";
	for (int i = 0; i < text.GetLength(); i++) {
		temp += text[i];
	}
	analyze.identable[x11] = a;
	analyze.identable[y11] = b;
	analyze.inspectStr(temp);
	node* t = analyze.calculate();
	t->num;//这里是结果
	CString z;
	int npos = text.Find('=');
	z = text.Left(npos);     //存储 = 号左边的变量
	if (z == x1)
		a = t->num;
	else // (z == y1)
		b = t->num;
	
}

bool ComputeUtil::judgeOne(CString x2, CString y2, CString op)
{
	if (op == "=") {
		if (((x2 == x1) && (y2 == y1)) || ((x2 == y1) && (y2 == x1))) {
			if (a == b)
				return TRUE;
			else
				return FALSE;

		}
	}
	else if (op == "<") {
		if ((x2 == x1) && (y2 == y1)) {
			if (a < b)
				return TRUE;
			else
				return FALSE;
		}
		else if ((x2 == y1) && (y2 == x1)) {
			if (b < a)
				return TRUE;
			else
				return FALSE;
		}
	}
	else if (op == ">") {
		if ((x2 == x1) && (y2 == y1)) {
			if (a > b)
				return TRUE;
			else
				return FALSE;
		}
		else if ((x2 == y1) && (y2 == x1)) {
			if (b > a)
				return TRUE;
			else
				return FALSE;
		}
	}
}

bool ComputeUtil::judgeTwo(CString x2, CString y2, CString op)
{
	if (op.Find('=') != -1)
		op.Remove('=');
	if (op == "<") {
		if ((x2 == x1) && (y2 == y1)) {
			if (a <= b)
				return TRUE;
			else
				return FALSE;
		}
		else if ((x2 == y1) && (y2 == x1)) {
			if (b <= a)
				return TRUE;
			else
				return FALSE;
		}
	}
	else if (op == ">") {
		if ((x2 == x1) && (y2 == y1)) {
			if (a >= b)
				return TRUE;
			else
				return FALSE;
		}
		else if ((x2 == y1) && (y2 == x1)) {
			if (b >= a)
				return TRUE;
			else
				return FALSE;
		}
	}
	else if (op == "!") {
		if (((x2 == x1) && (y2 == y1)) || ((x2 == y1) && (y2 == x1))) {
			if (a != b)
				return TRUE;
			else
				return FALSE;

		}
	}
}

