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
			cout << "��������ȷ��ǰ׺���ʽ��";
			cin >> str1;
			Ex.ReadExpr(str1);
			Ex.WriteExpr();
			ExStr = Ex.getStr();
		}
		else if (str == "2")
		{
			system("CLS");
			cout << "���ڽ��кϲ���������������" << endl;
			Ex.MergeConst();
			Ex.WriteExpr();
			ExStr = Ex.getStr();
			cout << "�ϲ��ɹ��������������˵���" << endl;
			Sleep(666);
		}
		else if (str == "3")
		{
			system("CLS");
			char var;
			int c;
			cout << "����������ֵ�ı�������";
			cin >> var;
			cout << "��������Ӧֵ����λ������";
			cin >> c;
			cout << "���ڽ��и�ֵ����������" << endl;
			Ex.Assign(var, c);
			Ex.WriteExpr();
			ExStr = Ex.getStr();
			cout << "��ֵ�ɹ��������������˵�������" << endl;
			Sleep(666);
		}
		else if (str == "4")
		{
			system("CLS");
			cout << "�ñ��ʽ��ֵΪ��" << Ex.Value() << endl;
			cout << "����������˵���" << endl;
			getchar();
		}
		else if (str == "5")
		{
			system("CLS");
			string str1;
			char ch;
			cout << "������ڶ������ʽ��";
			cin >> str1;
			Expression NEx(str1);
			cout << "��ѡ��ϲ��������Ӽ��˳�����";
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
			cout << "��ֵ�ɹ��������������˵�������" << endl;
			Sleep(666);
		}
		else if (str == "0")
			break;
		else
			cout << "��������ȷ��������" << endl;
	}
	cout << "��лʹ�ã������˳�������" << endl;
	Sleep(666);
	return 0;
}

void Printmenu()
{
	cout << endl;
	cout << endl;
	cout << '\t' << "#################################################" << endl;
	cout << '\t' << "#              ��ӭʹ�ñ��ʽ������             #" << endl;
	cout << '\t' << "#                   �汾��v1.0                  #" << endl;
	cout << '\t' << "#   ��ǰ���ʽ��" << ExStr << endl;
	cout << '\t' << "#   ָ���б�                                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   1  ��ȡ�µı��ʽ      2  �ϲ���������      #" << endl;
	cout << '\t' << "#   3  �Ա�����ֵ          4  ��ǰ���ʽ��ֵ    #" << endl;
	cout << '\t' << "#   5  �������ϱ��ʽ      0  �˳�����          #" << endl;
	cout << '\t' << "#################################################" << endl;
	cout << endl;
	cout << endl;
	cout << "�������Ӧָ��ǰ��������";
}