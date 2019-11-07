#include "pch.h"
#include "client.h"
#include "polynomial.h"

using namespace std;

typedef list<Poly> LISTPoly;
LISTPoly Polys;
LISTPoly::iterator iter;

void Load() {
	string tempstr;
	int TotalPolyAmount = 0;	//多项式数量
	ifstream load;
	load.open("data", ios::in);
	if (!load.is_open()) {
		load.close();
		ofstream firstload;
		firstload.open("data");
		firstload.close();
		load.open("data");
	}		//若未能打开文件"data"，则尝试使用ofstream新建

	if (!load.is_open()) {
		cout << "打开文件失败，即将退出程序。。。";
		Sleep(666);
		exit(1);
	}		//若仍未能打开文件"data"，则报错并退出

	while (getline(load, tempstr, '\n')) {
		TotalPolyAmount++;
	}		//用统计行数的方法统计多项式有几个

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
	cout << '\t' << "#              欢迎使用多项式计算器             #" << endl;
	cout << '\t' << "#                   版本：v1.0                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   指令列表：                                  #" << endl;
	cout << '\t' << "#                                               #" << endl;
	cout << '\t' << "#   1  多项式加法运算      2  多项式减法运算    #" << endl;
	cout << '\t' << "#   3  多项式乘法运算      4  多项式求值运算    #" << endl;
	cout << '\t' << "#   5  多项式求导运算      6  多项式比较        #" << endl;
	cout << '\t' << "#   7  新建常用多项式      8  删除常用多项式    #" << endl;
	cout << '\t' << "#   9  查看常用多项式      0  保存并退出        #" << endl;
	cout << '\t' << "#################################################" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入对应指令前的整数：";
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
	cout << "正在进行多项式加法运算。。。" << endl;
	string str1, str2;
	cout << "请输入第一个多项式，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0); {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
		cin >> str1;
	}
	cout << "请输入第二个多项式，返回请输入0：" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == 0) {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
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
	cout << "计算结果为：" << endl;
	cout << poly3.getPrintstr() << endl;
	cout << "是否保存该多项式为常用多项式？y/n" << endl;
	string tempstr;
	cin >> tempstr;
	while (tempstr != "y" && tempstr != "n") {
		cout << "输入格式错误，请重新输入：" << endl;
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
	cout << "正在进行多项式减法运算。。。" << endl;
	string str1, str2;
	cout << "请输入第一个多项式，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
		cin >> str1;
	}
	cout << "请输入第二个多项式，返回请输入0：" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == 0) {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
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
	cout << "计算结果为：" << endl;
	cout << poly3.getPrintstr() << endl;
	cout << "是否保存该多项式为常用多项式？y/n" << endl;
	string tempstr;
	cin >> tempstr;
	while (tempstr != "y" && tempstr != "n") {
		cout << "输入格式错误，请重新输入：" << endl;
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
	cout << "正在进行多项式乘法运算。。。" << endl;
	string str1, str2;
	cout << "请输入第一个多项式，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
		cin >> str1;
	}
	cout << "请输入第二个多项式，返回请输入0：" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == 0) {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
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
	cout << "计算结果为：" << endl;
	cout << poly3.getPrintstr() << endl;
	cout << "是否保存该多项式为常用多项式？y/n" << endl;
	string tempstr;
	cin >> tempstr;
	while (tempstr != "y" && tempstr != "n") {
		cout << "输入格式错误，请重新输入：" << endl;
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
	cout << "正在进行多项式求值运算。。。" << endl;
	string str1;
	cout << "请输入多项式，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
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
	cout << "请输入x的值：" << endl << "x=";
	double x;
	cin >> x;
	cout << "多项式的值为" << poly1.evaluate(x) << endl;
	cout << endl << "按任意键返回主菜单。。。";
	cin.ignore();
	getchar();
}

void Derivation() {
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
	cout << "计算结果为：" << endl;
	cout << poly1.getPrintstr() << endl;
	cout << "是否保存该多项式为常用多项式？y/n" << endl;
	string tempstr;
	cin >> tempstr;
	while (tempstr != "y" && tempstr != "n") {
		cout << "输入格式错误，请重新输入：" << endl;
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
	cout << "正在进行多项式比较。。。" << endl;
	string str1, str2;
	cout << "请输入第一个多项式，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (Examine(str1) == 0) {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
		cin >> str1;
	}
	cout << "请输入第二个多项式，返回请输入0：" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (Examine(str2) == 0) {
		cout << "输入格式错误或未查询到常用多项式，请重新输入：" << endl;
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
		cout << "这两个多项式相等。" << endl;
	else
		cout << "这两个多项式不相等。" <<endl;
}

void AddPoly() {
	string str;
	system("CLS");
	cout << "正在添加常用多项式。。。" << endl;
	cout << "请输入多项式，返回请输入0：";
	cin >> str;
	if (str == "0")return;
	while (Examine(str) != 1) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> str;
	}
	Poly tempoly(str);
	Polys.push_back(tempoly);
	cout << "添加常用多项式成功。" << endl;
	cout << "即将返回主菜单。。。" << endl;
	Sleep(666);
	system("CLS");
	return;
}

void DeletePoly() {
	string str;
	system("CLS");
	cout << "正在准备删除常用多项式。。。" << endl;
	cout << "请输入常用多项式的名称，返回请输入0：";
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
		cout << "已查询到该多项式："<< endl;
		cout << iter->getPrintstr() << endl;
		cout << "确认删除吗？y/n" << endl;
		string tempstr;
		cin >> tempstr;
		while (tempstr != "y" && tempstr != "n") {
			cout << "输入格式错误，请重新输入：" << endl;
			cin >> tempstr;
		}
		if (tempstr == "y") {
			Polys.erase(iter);
			cout << "删除成功，即将返回主菜单。。。" << endl;
			Sleep(666);
			system("CLS");
			return;
		}
		else {
			cout << "取消成功，即将返回主菜单。。。" << endl;
			Sleep(666);
			system("CLS");
			return;
		}
	}
	else {
		cout << "未查询到该常用多项式。" << endl;
		cout << "即将返回主菜单。。。" << endl;
		Sleep(666);
		system("CLS");
		return;
	}
}

void PolyList() {
	system("CLS");
	cout << '\t' << '\t' << "常用多项式" << endl;
	for (iter = Polys.begin(); iter != Polys.end(); iter++) {
		cout << iter->getPrintstr() << endl;
	}
	cout << endl << "按任意键返回主菜单。。。";
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