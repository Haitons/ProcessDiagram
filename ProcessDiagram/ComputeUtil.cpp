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

void ComputeUtil::input(CString text)    //���������
{
	if (text.Find(' ') != -1)
		text.Remove(' ');
	int npos = text.Find('=');
	x1 = text.Left(npos);     //�洢 = ����ߵı���
	text.Delete(0, npos + 1);    //ɾ�� =�ż�ǰ���
	int npos1 = text.Find(',');
	a = _ttoi((text.Left(npos1)));  //�洢 ,��ǰ��ֵ
	text.Delete(0, npos1 + 1);   //ɾ�� ���ż���ǰ��
	npos = text.Find('=');
	if (text.Find(' ') != -1)
		text.Remove(' ');
	y1 = text.Left(npos);
	text.Delete(0, npos + 1);
	b = _ttoi(text);
}

CString ComputeUtil::ouput(CString text)    //���������
{
	CString s("��ֵΪ:"), answer;

	if (text.Find(' ') != -1)
		text.Remove(' ');

	if (text.Find(',') != -1) {   //output�������

	}
	else {      //outputһ������
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
		else {             //����������������������ǳ�����ֱ��output

			return text;
		}
	}
}

void ComputeUtil::compute(CString text)    //���������
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
	t->num;//�����ǽ��
	CString z;
	int npos = text.Find('=');
	z = text.Left(npos);     //�洢 = ����ߵı���
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

