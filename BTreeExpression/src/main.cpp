#include <iostream>
#include <string>
#include <windows.h>
#include "Expression.h"
using namespace std;

string ExStr;

void Printmenu();

int main()
{
	string str;
	ExStr = "NULL";
	Expression Ex;
	Expression NEx;
	while (1)
	{
		system("CLS");
		Printmenu();
		cin >> str;
		if (str == "1")
		{
			system("CLS");
			Ex.DelExpr();
			string str1;
			cout << "请输入正确的前缀表达式：";
			cin >> str1;
			Ex.ReadExpr(str1);
			Ex.WriteExpr();
			ExStr = Ex.getStr();
		}
		else if (str == "2")
		{
			system("CLS");
			cout << "正在进行合并常数操作。。。" << endl;
			Ex.MergeConst();
			Ex.WriteExpr();
			ExStr = Ex.getStr();
			cout << "合并成功，即将返回主菜单。" << endl;
			Sleep(666);
		}
		else if (str == "3")
		{
			system("CLS");
			char var;
			int c;
			cout << "请输入欲赋值的变量名：";
			cin >> var;
			cout << "请输入相应值（个位数）：";
			cin >> c;
			cout << "正在进行赋值操作。。。" << endl;
			Ex.Assign(var, c);
			Ex.WriteExpr();
			ExStr = Ex.getStr();
			cout << "赋值成功，即将返回主菜单。。。" << endl;
			Sleep(666);
		}
		else if (str == "4")
		{
			system("CLS");
			cout << "该表达式的值为：" << Ex.Value() << endl;
			cout << "按任意键主菜单。" << endl;
			getchar();
		}
		else if (str == "5")
		{
			system("CLS");
			string str1;
			char ch;
			cout << "请输入第二个表达式：";
			cin >> str1;
			Expression NEx(str1);
			cout << "请选择合并方法（加减乘除）：";
			cin >> ch;
			switch (ch)
			{
			case '+':
				Ex = Ex + NEx;
				break;
			case '-':
				Ex = Ex - NEx;
				break;
			case '*':
				Ex = Ex * NEx;
				break;
			case '/':
				Ex = Ex / NEx;
				break;
			default:
				break;
			}
			Ex.WriteExpr();
			ExStr = Ex.getStr();
			cout << "赋值成功，即将返回主菜单。。。" << endl;
			Sleep(666);
		}
		else if (str == "0")
			break;
		else
			cout << "请输入正确的整数！" << endl;
	}
	cout << "感谢使用，正在退出。。。" << endl;
	Sleep(666);
	return 0;
}

void Printmenu()
{
	cout << endl;
	cout << endl;
	cout << '\t' << "#################################################" << endl;
	cout << '\t' << "#              欢迎使用表达式计算器             #" << endl;
	cout << '\t' << "#                   版本：v1.0                  #" << endl;
	cout << '\t' << "#   当前表达式：" << ExStr << endl;
	cout << '\t' << "#   指令列表：                                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   1  读取新的表达式      2  合并常数运算      #" << endl;
	cout << '\t' << "#   3  对变量赋值          4  当前表达式求值    #" << endl;
	cout << '\t' << "#   5  构建复合表达式      0  退出程序          #" << endl;
	cout << '\t' << "#################################################" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入对应指令前的整数：";
}