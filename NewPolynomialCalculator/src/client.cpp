#include "pch.h"
#include "client.h"
#include "polynomial.h"

using namespace std;

void Printmenu()
{
	cout << endl;
	cout << endl;
	cout << '\t' << "#################################################" << endl;
	cout << '\t' << "#              ��ӭʹ�ö���ʽ������             #" << endl;
	cout << '\t' << "#                   �汾��v2.0                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   ָ���б�                                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   1  ����ʽ�ӷ�����      2  ����ʽ��������    #" << endl;
	cout << '\t' << "#   3  ����ʽ�˷�����      4  ����ʽ��ֵ����    #" << endl;
	cout << '\t' << "#   5  ����ʽ������      0  �˳�����          #" << endl;
	cout << '\t' << "#################################################" << endl;
	cout << endl;
	cout << endl;
	cout << "�������Ӧָ��ǰ��������";
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
		cout << "���ڽ��ж���ʽ�ӷ����㡣����" << endl;
	else if (oper == 2)
		cout << "���ڽ��ж���ʽ�������㡣����" << endl;
	else
		cout << "���ڽ��ж���ʽ�˷����㡣����" << endl;
	string str1, str2;
	cout << "�������һ������ʽ������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == false) {
		cout << "�����ʽ�������������룺" << endl;
		cin >> str1;
	}
	cout << "������ڶ�������ʽ������������0��" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == false) {
		cout << "�����ʽ�������������룺" << endl;
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
	cout << "������Ϊ��" << endl;
	cout << poly3.getPolystr() << endl;
	cout << endl << "��������������˵�������";
	cin.ignore();
	getchar();
}

void Evaluate()
{
	system("CLS");
	cout << "���ڽ��ж���ʽ��ֵ���㡣����" << endl;
	string str1;
	cout << "���������ʽ������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "�����ʽ�������������룺" << endl;
		cin >> str1;
	}
	Poly poly1(str1);
	cout << "������x��ֵ��" << endl << "x=";
	double x;
	cin >> x;
	cout << "����ʽ��ֵΪ" << poly1.evaluate(x) << endl;
	cout << endl << "��������������˵�������";
	cin.ignore();
	getchar();
}

void Derivation()
{
	system("CLS");
	cout << "���ڽ��ж���ʽ�����㡣����" << endl;
	string str1;
	cout << "���������ʽ������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str1;
	}
	Poly poly1(str1);
	poly1.derivate();
	cout << "������Ϊ��" << endl;
	cout << poly1.getPolystr() << endl;
	cout << endl << "��������������˵�������";
	cin.ignore();
	getchar();
}
