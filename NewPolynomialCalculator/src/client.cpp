#include "pch.h"
#include "client.h"
#include "polynomial.h"

using namespace std;

void Printmenu()
{
	cout << endl;
	cout << endl;
	cout << '\t' << "#################################################" << endl;
	cout << '\t' << "#              欢迎使用多项式计算器             #" << endl;
	cout << '\t' << "#                   版本：v2.0                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   指令列表：                                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   1  多项式加法运算      2  多项式减法运算    #" << endl;
	cout << '\t' << "#   3  多项式乘法运算      4  多项式求值运算    #" << endl;
	cout << '\t' << "#   5  多项式求导运算      0  退出程序          #" << endl;
	cout << '\t' << "#################################################" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入对应指令前的整数：";
}

bool Examine(std::string str)
{
	string reg("\\-?(\\d{1,15}(\\.\\d{1,9})?)?x(\\^\\d{1,15})?([\\+\\-](\\d{1,15}(\\.\\d{1,9})?)?x(\\^\\d{1,15})?){0,98}([\\+\\-]\\d{1,15}(\\.\\d{1,9})?)?");
	regex pattern(reg, regex::icase);
	if (!regex_match(str, pattern))
		return false;
	smatch result;
	double numbers[202] = { 0 };
	double coef[100] = { 0 };
	int power[100] = { 0 };
	string reg1("\\-?\\d+(\\.\\d+)?");
	regex pattern1(reg1, regex::icase);
	string::const_iterator iter = str.begin();
	string::const_iterator iterEnd = str.end();
	string temp;
	int i = 0;
	while (std::regex_search(iter, iterEnd, result, pattern1)) {
		temp = result[0];
		numbers[i] = stod(temp);
		i++;
		iter = result[0].second;
	}
	for (int j = 0, k = 0; j < i / 2; j++, k += 2) {
		coef[j] = numbers[k];
		power[j] = numbers[k + 1];
	}
	for (int j = 1; j < i / 2; j++) {
		if (power[j] >= power[j - 1] || coef[j] == 0)
			return false;
	}
	return true;
}

void Operation(int oper)
{
	system("CLS");
	if (oper == 1)
		cout << "正在进行多项式加法运算。。。" << endl;
	else if (oper == 2)
		cout << "正在进行多项式减法运算。。。" << endl;
	else
		cout << "正在进行多项式乘法运算。。。" << endl;
	string str1, str2;
	cout << "请输入第一个多项式，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == false) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> str1;
	}
	cout << "请输入第二个多项式，返回请输入0：" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == false) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> str2;
	}
	Poly poly1(str1);
	Poly poly2(str2);
	Poly poly3;
	if (oper == 1)
		poly3 = poly1 + poly2;
	else if (oper == 2)
		poly3 = poly1 - poly2;
	else
		poly3 = poly1 * poly2;
	cout << "计算结果为：" << endl;
	cout << poly3.getPolystr() << endl;
	cout << endl << "按任意键返回主菜单。。。";
	cin.ignore();
	getchar();
}

void Evaluate()
{
	system("CLS");
	cout << "正在进行多项式求值运算。。。" << endl;
	string str1;
	cout << "请输入多项式，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> str1;
	}
	Poly poly1(str1);
	cout << "请输入x的值：" << endl << "x=";
	double x;
	cin >> x;
	cout << "多项式的值为" << poly1.evaluate(x) << endl;
	cout << endl << "按任意键返回主菜单。。。";
	cin.ignore();
	getchar();
}

void Derivation()
{
	system("CLS");
	cout << "正在进行多项式求导运算。。。" << endl;
	string str1;
	cout << "请输入多项式，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
		cin >> str1;
	}
	Poly poly1(str1);
	poly1.derivate();
	cout << "计算结果为：" << endl;
	cout << poly1.getPolystr() << endl;
	cout << endl << "按任意键返回主菜单。。。";
	cin.ignore();
	getchar();
}
