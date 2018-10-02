#pragma once
#include <string>
#include <vector>
#include <stack>
#include <map>

//结点类
class node
{
public:
	int type;//结点类型
	std::string iden;//字符
	std::string oper;//运算符
	double num;//数字
	node() {
		type = 0;
	}
	node(std::string str, int t) {
		if (t == 1) {
			iden = str;
			type = 1;//1为字符
		}
		else if (t == 2) {
			oper = str;
			type = 2;//2为运算符
		}
	}
	node(double d) {
		node();
		type = 3;//3为数字
		num = d;
	}
};

class Analyze
{
public:
#define NUMERROR 1		//非法变量名称，数字开头了
#define FENHAOERROR 2	//表达式没有以;号结束
#define CHARERROR 4		//非法字符
#define FUZHIERROR 8	//赋值符号非法
#define EXPERROR 16		//表达式非法
#define OPERATORERROR 32//操作符非法

	static std::map<std::string, double> identable;//变量表
	static void identify(std::map<std::string, double>* m);//定义变量
	static double findIdenValue(std::string str);//寻找变量值

	Analyze();

	int inspectStr(std::string s);//检查错误
	node* calculate();//计算求值
	void clear();//清空

private:
	std::string str;
	std::vector<node*> nodeArray;
	std::map<std::string, int> priority;
	char special[11];
	std::string Operator[13];

	void string_replace(std::string&s1, const std::string&s2, const std::string&s3);
	int split();//拆分字符串
	int inspectEqual();//判断=是否合法
	int inspect(int re);//判断整个语句是否合法
	int compare(std::string str1, std::string str2);//比较优先级
	node* deal(node* op, node* op1, node* op2);//操作符求值

	bool isSpecial(char ch);
	bool isNum(char ch);
	bool isChar(char ch);
	bool isSubOperator(std::string str);
	bool isOperator(std::string str);
	bool isInspectSuccess;
};