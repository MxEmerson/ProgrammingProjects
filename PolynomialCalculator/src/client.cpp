#include "pch.h"
#include "client.h"
#include "polynomial.h"

using namespace std;

typedef list<Poly> LISTPoly;
LISTPoly Polys;
LISTPoly::iterator iter;

void Load() {
	string tempstr;
	int TotalPolyAmount = 0;	//����ʽ����
	ifstream load;
	load.open("data", ios::in);
	if (!load.is_open()) {
		load.close();
		ofstream firstload;
		firstload.open("data");
		firstload.close();
		load.open("data");
	}		//��δ�ܴ��ļ�"data"������ʹ��ofstream�½�

	if (!load.is_open()) {
		cout << "���ļ�ʧ�ܣ������˳����򡣡���";
		Sleep(666);
		exit(1);
	}		//����δ�ܴ��ļ�"data"���򱨴��˳�

	while (getline(load, tempstr, '\n')) {
		TotalPolyAmount++;
	}		//��ͳ�������ķ���ͳ�ƶ���ʽ�м���

	load.close();
	load.open("data");
	for (int i = 0; i < TotalPolyAmount; i++) {
		load >> tempstr;
		Poly tempoly;
		tempoly.setpoly(tempstr);
		Polys.push_back(tempoly);
	}
	load.close();
}

void Printmenu() {
	cout << endl;
	cout << endl;
	cout << '\t' << "#################################################" << endl;
	cout << '\t' << "#              ��ӭʹ�ö���ʽ������             #" << endl;
	cout << '\t' << "#                   �汾��v1.0                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   ָ���б�                                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   1  ����ʽ�ӷ�����      2  ����ʽ��������    #" << endl;
	cout << '\t' << "#   3  ����ʽ�˷�����      4  ����ʽ��ֵ����    #" << endl;
	cout << '\t' << "#   5  ����ʽ������      6  ����ʽ�Ƚ�        #" << endl;
	cout << '\t' << "#   7  �½����ö���ʽ      8  ɾ�����ö���ʽ    #" << endl;
	cout << '\t' << "#   9  �鿴���ö���ʽ      0  ���沢�˳�        #" << endl;
	cout << '\t' << "#################################################" << endl;
	cout << endl;
	cout << endl;
	cout << "�������Ӧָ��ǰ��������";
}

int Examine(string str) {
	for (iter = Polys.begin(); iter != Polys.end(); iter++) {
		if (iter->getName() == str)
			return 2;
	}
	regex pattern( "^(([A-Za-z]\\w{0,19})=)?(\\((-?\\d{1,9})(\\.\\d{1,15})?,\\d{1,9}\\)){1,99}$", regex::icase );
	if (!regex_match(str, pattern))
		return 0;
	smatch result;
	double numbers[202] = { 0 };
	double coef[100] = { 0 };
	int power[100] = { 0 };
	string reg("\\-?\\d+(\\.\\d+)?");
	regex pattern1(reg, regex::icase);
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
			return 0;
	}
	return 1;
}

void Plus() {
	system("CLS");
	cout << "���ڽ��ж���ʽ�ӷ����㡣����" << endl;
	string str1, str2;
	cout << "�������һ������ʽ������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0); {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str1;
	}
	cout << "������ڶ�������ʽ������������0��" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == 0) {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str2;
	}
	Poly poly1;
	Poly poly2;
	if (Examine(str1) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str1)
				poly1.setpoly(iter->getPolystr());
		}
	}
	else
		poly1.setpoly(str1);
	if (Examine(str2) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str2)
				poly2.setpoly(iter->getPolystr());
		}
	}
	else
		poly2.setpoly(str2);
	Poly poly3(poly1,poly2,1);
	cout << "������Ϊ��" << endl;
	cout << poly3.getPrintstr() << endl;
	cout << "�Ƿ񱣴�ö���ʽΪ���ö���ʽ��y/n" << endl;
	string tempstr;
	cin >> tempstr;
	while (tempstr != "y" && tempstr != "n") {
		cout << "�����ʽ�������������룺" << endl;
		cin >> tempstr;
	}
	if (tempstr == "y") {
		poly3.setname();
		poly3.transnumber();
		Polys.push_back(poly3);
	}
}

void Minus() {
	system("CLS");
	cout << "���ڽ��ж���ʽ�������㡣����" << endl;
	string str1, str2;
	cout << "�������һ������ʽ������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str1;
	}
	cout << "������ڶ�������ʽ������������0��" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == 0) {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str2;
	}
	Poly poly1;
	Poly poly2;
	if (Examine(str1) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str1)
				poly1.setpoly(iter->getPolystr());
		}
	}
	else
		poly1.setpoly(str1);
	if (Examine(str2) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str2)
				poly2.setpoly(iter->getPolystr());
		}
	}
	else
		poly2.setpoly(str2);
	Poly poly3(poly1, poly2, 2);
	cout << "������Ϊ��" << endl;
	cout << poly3.getPrintstr() << endl;
	cout << "�Ƿ񱣴�ö���ʽΪ���ö���ʽ��y/n" << endl;
	string tempstr;
	cin >> tempstr;
	while (tempstr != "y" && tempstr != "n") {
		cout << "�����ʽ�������������룺" << endl;
		cin >> tempstr;
	}
	if (tempstr == "y") {
		poly3.setname();
		poly3.transnumber();
		Polys.push_back(poly3);
	}
}

void Multiply() {
	system("CLS");
	cout << "���ڽ��ж���ʽ�˷����㡣����" << endl;
	string str1, str2;
	cout << "�������һ������ʽ������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str1;
	}
	cout << "������ڶ�������ʽ������������0��" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == 0) {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str2;
	}
	Poly poly1;
	Poly poly2;
	if (Examine(str1) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str1)
				poly1.setpoly(iter->getPolystr());
		}
	}
	else
		poly1.setpoly(str1);
	if (Examine(str2) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str2)
				poly2.setpoly(iter->getPolystr());
		}
	}
	else
		poly2.setpoly(str2);
	Poly poly3(poly1, poly2, 3);
	cout << "������Ϊ��" << endl;
	cout << poly3.getPrintstr() << endl;
	cout << "�Ƿ񱣴�ö���ʽΪ���ö���ʽ��y/n" << endl;
	string tempstr;
	cin >> tempstr;
	while (tempstr != "y" && tempstr != "n") {
		cout << "�����ʽ�������������룺" << endl;
		cin >> tempstr;
	}
	if (tempstr == "y") {
		poly3.setname();
		poly3.transnumber();
		Polys.push_back(poly3);
	}
}

void Evaluate() {
	system("CLS");
	cout << "���ڽ��ж���ʽ��ֵ���㡣����" << endl;
	string str1;
	cout << "���������ʽ������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str1;
	}
	Poly poly1;
	if (Examine(str1) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str1)
				poly1.setpoly(iter->getPolystr());
		}
	}
	else
		poly1.setpoly(str1);
	cout << "������x��ֵ��" << endl << "x=";
	double x;
	cin >> x;
	cout << "����ʽ��ֵΪ" << poly1.evaluate(x) << endl;
	cout << endl << "��������������˵�������";
	cin.ignore();
	getchar();
}

void Derivation() {
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
	Poly poly1;
	if (Examine(str1) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str1)
				poly1.setpoly(iter->getPolystr());
		}
	}
	else
		poly1.setpoly(str1);
	poly1.derivate();
	cout << "������Ϊ��" << endl;
	cout << poly1.getPrintstr() << endl;
	cout << "�Ƿ񱣴�ö���ʽΪ���ö���ʽ��y/n" << endl;
	string tempstr;
	cin >> tempstr;
	while (tempstr != "y" && tempstr != "n") {
		cout << "�����ʽ�������������룺" << endl;
		cin >> tempstr;
	}
	if (tempstr == "y") {
		poly1.setname();
		poly1.transnumber();
		Polys.push_back(poly1);
	}
}

void Compare() {
	system("CLS");
	cout << "���ڽ��ж���ʽ�Ƚϡ�����" << endl;
	string str1, str2;
	cout << "�������һ������ʽ������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str1;
	}
	cout << "������ڶ�������ʽ������������0��" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == 0) {
		cout << "�����ʽ�����δ��ѯ�����ö���ʽ�����������룺" << endl;
		cin >> str2;
	}
	Poly poly1;
	Poly poly2;
	if (Examine(str1) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str1)
				poly1.setpoly(iter->getPolystr());
		}
	}
	else
		poly1.setpoly(str1);
	if (Examine(str2) == 2) {
		for (iter = Polys.begin(); iter != Polys.end(); iter++) {
			if (iter->getName() == str2)
				poly2.setpoly(iter->getPolystr());
		}
	}
	else
		poly2.setpoly(str2);
	Poly poly3(poly1, poly2, 2);
	if (poly3.getTerm() == 0)
		cout << "����������ʽ��ȡ�" << endl;
	else
		cout << "����������ʽ����ȡ�" <<endl;
}

void AddPoly() {
	string str;
	system("CLS");
	cout << "������ӳ��ö���ʽ������" << endl;
	cout << "���������ʽ������������0��";
	cin >> str;
	if (str == "0")return;
	while (Examine(str) != 1) {
		cout << "�����ʽ�������������룺" << endl;
		cin >> str;
	}
	Poly tempoly(str);
	Polys.push_back(tempoly);
	cout << "��ӳ��ö���ʽ�ɹ���" << endl;
	cout << "�����������˵�������" << endl;
	Sleep(666);
	system("CLS");
	return;
}

void DeletePoly() {
	string str;
	system("CLS");
	cout << "����׼��ɾ�����ö���ʽ������" << endl;
	cout << "�����볣�ö���ʽ�����ƣ�����������0��";
	cin >> str;
	if (str == "0")return;
	bool flag = false;
	for (iter = Polys.begin(); iter != Polys.end(); iter++) {
		if (iter->getName() == str) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "�Ѳ�ѯ���ö���ʽ��"<< endl;
		cout << iter->getPrintstr() << endl;
		cout << "ȷ��ɾ����y/n" << endl;
		string tempstr;
		cin >> tempstr;
		while (tempstr != "y" && tempstr != "n") {
			cout << "�����ʽ�������������룺" << endl;
			cin >> tempstr;
		}
		if (tempstr == "y") {
			Polys.erase(iter);
			cout << "ɾ���ɹ��������������˵�������" << endl;
			Sleep(666);
			system("CLS");
			return;
		}
		else {
			cout << "ȡ���ɹ��������������˵�������" << endl;
			Sleep(666);
			system("CLS");
			return;
		}
	}
	else {
		cout << "δ��ѯ���ó��ö���ʽ��" << endl;
		cout << "�����������˵�������" << endl;
		Sleep(666);
		system("CLS");
		return;
	}
}

void PolyList() {
	system("CLS");
	cout << '\t' << '\t' << "���ö���ʽ" << endl;
	for (iter = Polys.begin(); iter != Polys.end(); iter++) {
		cout << iter->getPrintstr() << endl;
	}
	cout << endl << "��������������˵�������";
	cin.ignore();
	getchar();
	system("CLS");
	return;
}

void SaveAndExit() {
	ofstream saving("data", ios::trunc);
	for (iter = Polys.begin(); iter != Polys.end(); iter++) {
		saving << iter->getPolystr() << endl;
	}
	saving.close();
}