#include "stdafx.h"
#include "analyze.h"

std::map<std::string, double> init()
{
	std::map<std::string, double> temp;
	return temp;
}

std::map<std::string, double> Analyze::identable(init());

Analyze::Analyze() {
	special[0] = '+';
	special[1] = '-';
	special[2] = '*';
	special[3] = '/';
	special[4] = '(';
	special[5] = ')';
	special[6] = '=';
	special[7] = '>';
	special[8] = '<';
	special[9] = '&';
	special[10] = '|';

	Operator[0] = "+";
	Operator[1] = "-";
	Operator[2] = "*";
	Operator[3] = "/";
	Operator[4] = "(";
	Operator[5] = ")";
	Operator[6] = "=";
	Operator[7] = ">";
	Operator[8] = "<";
	Operator[9] = ">=";
	Operator[10] = "<=";
	Operator[11] = "&&";
	Operator[12] = "||";

	priority["#"] = 0;
	priority["="] = 1;
	priority["("] = 99;
	priority[")"] = 2;
	priority["&&"] = 3;
	priority["||"] = 3;
	priority[">"] = 4;
	priority["<"] = 4;
	priority[">="] = 4;
	priority["<="] = 4;
	priority["+"] = 5;
	priority["-"] = 5;
	priority["*"] = 6;
	priority["/"] = 6;
	isInspectSuccess = false;
}

void Analyze::identify(std::map<std::string, double>* m) {
	for (std::map<std::string, double>::iterator it = m->begin(); it != m->end(); it++) {
		Analyze::identable[(*it).first] = (*it).second;
	}
}

double Analyze::findIdenValue(std::string str) {
	if (identable.find(str) != identable.end())
		return identable.find(str)->second;
	else {
		identable[str] = 0;
		return 0;
	}
	return 0;
}

void Analyze::string_replace(std::string&s1, const std::string&s2, const std::string&s3)
{
	std::string::size_type pos = 0;
	std::string::size_type a = s2.size();
	std::string::size_type b = s3.size();
	while ((pos = s1.find(s2, pos)) != std::string::npos)
	{
		s1.erase(pos, a);
		s1.insert(pos, s3);
		pos += b;
	}
}

int Analyze::split() {				//拆分语句
	bool bnum = false;
	bool biden = false;
	bool bop = false;
	std::string op = "";
	std::string iden = "";
	double num = 0;

	if (str[str.size() - 1] != ';')	return FENHAOERROR;

	for (int i = 0; i < str.size(); i++) {
		if (isSpecial(str[i])) {
			if (bnum) {
				bnum = false;
				nodeArray.push_back(new node(num));
				num = 0;
			}
			else if (biden) {
				biden = false;
				nodeArray.push_back(new node(iden, 1));
				iden = "";
			}
			op += str[i];
			bop = true;
			if (!isSubOperator(op)) {
				if (isOperator(op)) {
					bop = false;
					nodeArray.push_back(new node(op, 2));
					op = "";
				}
				else {
					return OPERATORERROR;
				}
			}
		}
		else if (str[i] == ';') {
			if (bnum) {
				bnum = false;
				nodeArray.push_back(new node(num));
				num = 0;
			}
			else if (biden) {
				biden = false;
				nodeArray.push_back(new node(iden, 1));
				iden = "";
			}
			else if (bop) {
				if (isOperator(op)) {
					bop = false;
					nodeArray.push_back(new node(op, 2));
					op = "";
				}
				else {
					return OPERATORERROR;
				}
			}
		}
		else if (isNum(str[i])) {
			if (biden) {
				iden += str[i];
			}
			else {
				if (bop) {
					if (isOperator(op)) {
						bop = false;
						nodeArray.push_back(new node(op, 2));
						op = "";
					}
					else {
						return OPERATORERROR;
					}
				}
				num *= 10;
				num += (str[i] - '0');
				bnum = true;
			}
		}
		else if (isChar(str[i])) {
			if (bop) {
				if (isOperator(op)) {
					bop = false;
					nodeArray.push_back(new node(op, 2));
					op = "";
				}
				else {
					return OPERATORERROR;
				}
			}
			else if (bnum) {
				return  NUMERROR;
			}
			biden = true;
			iden += str[i];
		}
		else {
			return CHARERROR;
		}
	}
	return 0;	//拆分成功，没有书写错误
}

int Analyze::inspectEqual() {				//检查赋值符号错误
	int re = 0;
	int i = 0;
	int k = -1;
	for (std::vector<node*>::iterator it = nodeArray.begin(); it != nodeArray.end(); it++) {
		node* temp = *it;
		if (temp->type == 2) {		//操作符
			if (temp->oper == "=") {
				if (i == 0 || i > 1) {
					re = FUZHIERROR;					//赋值符号位置不对
				}
				else {
					k = i;
				}
			}
		}
		i++;
	}
	if (re)	return re;
	if (k == -1) return -1;
	return 0;
}

int Analyze::inspect(int re) {				//检查语法错误
	int errorID = 0;

	std::vector<node*>::iterator it = nodeArray.begin();
	if (re == 0) {
		if ((*it)->type != 1) {
			errorID = EXPERROR;
			return errorID;
		}
		it = it + 2;
	}
	node* temp = *it;
	if (temp->type == 2 && temp->oper != "(") {
		errorID = EXPERROR;
		return errorID;
	}

	int bracketnum = 0;
	for (; it != nodeArray.end() - 1; it++) {
		temp = *it;
		node* temp1 = *(it + 1);
		if (temp->type == 1 || temp->type == 3) {	//变量或者常数
			if (temp1->type != 2) {
				errorID = EXPERROR;
				return errorID;
			}
			else if (temp1->oper == "(") {
				errorID = EXPERROR;
				return errorID;
			}
		}
		else if (temp->type == 2) {					//操作符
			if (temp->oper == ")") {
				if (temp1->type != 2) {
					errorID = EXPERROR;
					return errorID;
				}
				else if (temp1->oper == "(") {
					errorID = EXPERROR;
					return errorID;
				}
				bracketnum--;
				if (bracketnum < 0) {
					errorID = EXPERROR;
					return errorID;
				}
			}
			else {
				if (temp->oper == "(")
					bracketnum++;
				if (temp1->type == 2 && temp1->oper != "(") {
					errorID = EXPERROR;
					return errorID;
				}
			}
		}
	}
	if ((*it)->type == 2) {
		if ((*it)->oper == ")")
			bracketnum--;
		else {
			errorID = EXPERROR;
			return errorID;
		}
	}
	if (bracketnum != 0) {
		errorID = EXPERROR;
		return errorID;
	}
}

int Analyze::inspectStr(std::string s) {
	clear();
	if (s == "")
		return EXPERROR;
	str = s;
	string_replace(str, " ", "");
	if (str[str.size() - 1] != ';')
		str.insert(str.end(), ';');
	isInspectSuccess = true;

	int errorID = 0;
	errorID |= split();			//拆分字符串
	if (errorID != 0) {
		nodeArray.clear();
		isInspectSuccess = false;
		return errorID;
	}

	int re = inspectEqual();		//判断等号
	if (re != -1 && re != 0) {
		errorID |= re;
		nodeArray.clear();
		isInspectSuccess = false;
		return errorID;
	}

	errorID |= inspect(re);
	if (errorID != 0) {
		nodeArray.clear();
		isInspectSuccess = false;
	}
	return errorID;
}

int Analyze::compare(std::string str1, std::string str2) {
	if (str1 == "(") {
		if (str2 == ")")
			return 2;
		return 1;
	}
	if (priority.find(str2)->second >= priority.find(str1)->second)
		return 1;
	return 0;
}

node* Analyze::calculate() {
	if (!isInspectSuccess)	return NULL;
	std::stack<node*> st;
	std::vector<node*> tempArray;
	st.push(new node("#", 2));
	for (std::vector<node*>::iterator it = nodeArray.begin(); it != nodeArray.end(); it++) {
		node* temp = *it;
		if (temp->type != 2) {
			tempArray.push_back(temp);
		}
		else {
			while (1) {
				int re = compare(st.top()->oper, temp->oper);
				if (re == 1) {				//优先级高
					st.push(temp);
					break;
				}
				else if (re == 2) {			//()情况
					st.pop();
					break;
				}
				else if (re == 0) {			//优先级小
					tempArray.push_back(st.top());
					st.pop();
				}
			}
		}
	}
	while (st.size() != 1) {
		tempArray.push_back(st.top());
		st.pop();
	}

	st.pop();	//清空
	for (std::vector<node*>::iterator it = tempArray.begin(); it != tempArray.end(); it++) {
		node* temp = *it;
		if (temp->type == 1 || temp->type == 3) {
			st.push(temp);
		}
		else {
			node* op2 = st.top();
			st.pop();
			node* op1 = st.top();
			st.pop();
			node* re = deal(temp, op1, op2);
			st.push(re);
		}
	}
	return st.top();
}

void Analyze::clear() {
	str = "";
	nodeArray.clear();
	isInspectSuccess = false;
}

bool Analyze::isSpecial(char ch) {
	for (int i = 0; i < 11; i++) {
		if (ch == special[i])
			return true;
	}
	return false;
}

bool Analyze::isNum(char ch) {
	if (ch >= '0'&&ch <= '9')
		return true;
	return false;
}

bool Analyze::isChar(char ch) {
	if (ch >= 'a'&&ch <= 'z')
		return true;
	if (ch >= 'A'&&ch <= 'Z')
		return true;
	return false;
}

bool Analyze::isSubOperator(std::string str) {
	if (str.size() == 1) {
		for (int i = 9; i < 13; i++) {
			if (str[0] == Operator[i][0])
				return true;
		}
	}
	return false;
}

bool Analyze::isOperator(std::string str) {
	for (int i = 0; i < 13; i++) {
		if (str == Operator[i])
			return true;
	}
	return false;
}

node* Analyze::deal(node* op, node* op1, node* op2) {
	double num1;
	if (op1->type == 1)
		num1 = findIdenValue(op1->iden);
	else
		num1 = op1->num;
	double num2;
	if (op2->type == 1)
		num2 = findIdenValue(op2->iden);
	else
		num2 = op2->num;

	if (op->oper == "+") {
		return new node(num1 + num2);
	}
	else if (op->oper == "-") {
		return new node(num1 - num2);
	}
	else if (op->oper == "*") {
		return new node(num1 * num2);
	}
	else if (op->oper == "/") {
		if (num2 == 0) return new node(0.0);
		return new node(num1 / num2);
	}
	else if (op->oper == ">") {
		if (num1 > num2) return new node(1.0);
		return new node(0.0);
	}
	else if (op->oper == "<") {
		if (num1 < num2) return new node(1.0);
		return new node(0.0);
	}
	else if (op->oper == ">=") {
		if (num1 >= num2) return new node(1.0);
		return new node(0.0);
	}
	else if (op->oper == "<=") {
		if (num1 <= num2) return new node(1.0);
		return new node(0.0);
	}
	else if (op->oper == "&&") {
		if (num1 && num2) return new node(1.0);
		return new node(0.0);
	}
	else if (op->oper == "||") {
		if (num1 || num2) return new node(1.0);
		return new node(0.0);
	}
	else if (op->oper == "=") {
		if (op1->type == 1) {
			identable[op1->iden] = num2;
			return new node(num2);
		}
		return new node(0.0);
	}

	return new node(0.0);
}