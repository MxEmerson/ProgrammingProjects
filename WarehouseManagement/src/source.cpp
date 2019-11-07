#include "source.h"
#include "pch.h"

using namespace std;

typedef struct GoodA {
	string name;
	int amount;
}Good;			//声明一个结构体

typedef list<Good> LISTGoods;
LISTGoods Goods;				//建立双向链表
LISTGoods::iterator iter;		//声明迭代器

//从文件加载数据写入程序
void Loading() {
	string tempstr;
	int tempint;
	int TotalGoodsAmount = 0;	//货物种类
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
		TotalGoodsAmount++;
	}		//用统计行数的方法统计货物有多少种

	load.close();
	load.open("data");
	for (int i = 0; i < TotalGoodsAmount; i++) {
		load >> tempstr >> tempint;
		struct GoodA tempstruct;
		tempstruct.name = tempstr;
		tempstruct.amount = tempint;
		Goods.push_back(tempstruct);
	}		//将文件中的数据
	load.close();
}

//登录
void Login() {
	int security = 0;
	char password[7] = { "000000" };		//预先给定产品密钥
	char str[7];
	cout << "请输入6位数密钥：";
	while (security < 3) {		//3次输入错误直接退出程序
		cin >> str;
		if (strcmp(password, str) == 0) {
			system("CLS");
			return;
		}
		else {
			security++;
			cout << "输入错误！请输入正确的6位数密钥！" << endl;
			cout << "您还有" << 3 - security << "次输入机会：";
		}
	}
	cout << "您输入错误次数已超过3次，系统即将自动退出。" << endl;
	Sleep(666);
	exit(0);
}

//输出菜单
void Menu() {
	cout << endl;
	cout << '\t' << "###############################################" << endl;
	cout << '\t' << "#            欢迎使用仓库管理系统             #" << endl;
	cout << '\t' << "#                 版本：v1.0                  #" << endl;
	cout << '\t' << "#                 指令列表：                  #" << endl;
	cout << '\t' << "#  1  进货                   2  出货          #" << endl;
	cout << '\t' << "#  3  清空仓库               4  输出库存表单  #" << endl;
	cout << '\t' << "#  5  保存并退出                              #" << endl;
	cout << '\t' << "###############################################" << endl;
	cout << endl;
	cout << "请输入对应指令前的整数：";
}

//进货
void Stock() {
	system("CLS");
	int location = 0;
	string name;
	char numberstr[100];
	cout << "正在进行进货操作。。。" << endl;
	cout << "货物名称应大于0字符，小于100字符。" << endl;
	cout << "请输入货物名称：";
	cin >> name;
	bool flag = false;
	for (iter = Goods.begin(); iter != Goods.end(); iter++) {	//使用迭代器遍历库存
		if (iter->name == name) {
			flag = true;
			break;
		}
	}
	if (flag) {			//如果库存中已有输入的货物，则增加库存
		cout << "已在库存中查询到该货物,目前库存：" << iter->amount << endl;
		cout << "请注意单个货物的库存总量不能超过999999999。" << endl;
		cout << "请输入进货量：";
		cin.ignore();	//处理stdin的缓冲区
		fgets(numberstr, 100, stdin);
		while (atoi(numberstr) <= 0 || atoi(numberstr) + iter->amount >= 999999999) {	//判断输入是否非法或容量是否足够
			cout << "请输入正确的整数！" << endl;
			fgets(numberstr, 100, stdin);
		}
		iter->amount += atoi(numberstr);
	}
	else {				//如果库存中没有该货物，则
		cout << "目前库存中无该货物。" << endl;
		cout << "请注意单个货物的库存总量不能超过999999999。" << endl;
		cout << "请输入进货量：";
		cin.ignore();	//处理stdin的缓冲区
		fgets(numberstr, 100, stdin);
		while (atoi(numberstr) <= 0 || atoi(numberstr) >= 999999999) {		//判断输入是否非法或容量是否足够
			cout << "请输入正确的整数！" << endl;
			fgets(numberstr, 100, stdin);
		}
		struct GoodA tempstruct;
		tempstruct.name = name;
		tempstruct.amount = atoi(numberstr);
		Goods.push_back(tempstruct);		//存入链表
	}
	cout << "进货成功，即将返回主菜单。。。" << endl;
	Sleep(666);
	system("CLS");
	return;
}

//出货
void Deliver() {
	system("CLS");
	int location = 0;
	string name;
	char numberstr[100];
	cout << "正在进行出货操作。。。" << endl;
	cout << "货物名称应大于0字符，小于100字符。" << endl;
	cout << "请输入货物名称：";
	bool flag = false;
	cin >> name;
	for (iter = Goods.begin(); iter != Goods.end(); iter++) {
		if (iter->name == name) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "已在库存中查询到该货物,目前库存：" << iter->amount << endl;
		cout << "请注意货物的库存总量不能小于0。" << endl;
		cout << "请输入出货量：";
		cin.ignore();	//处理stdin的缓冲区
		fgets(numberstr, 100, stdin);
		while (atoi(numberstr) <= 0 || iter->amount - atoi(numberstr) < 0) {		//判断输入是否非法或库存是否足够
			cout << "请输入正确的整数！" << endl;
			fgets(numberstr, 100, stdin);
		}
		if (iter->amount - atoi(numberstr) > 0)		//还有剩余
			iter->amount -= atoi(numberstr);
		else
			Goods.erase(iter);		//库存刚好为0
	}
	else {
		cout << "目前库存中无该货物。" << endl;
		cout << "即将返回主菜单。。。" << endl;
		Sleep(666);
		system("CLS");
		return;
	}
	cout << "出货成功，即将返回主菜单。。。" << endl;
	Sleep(666);
	system("CLS");
	return;
}

//清空仓库
void Empty() {
	string key;
	string truekey = "000000";
	cout << "请输入密钥：";		//输入密钥防止误操作
	cin >> key;
	if (key != truekey) {
		cout << "密钥输入错误，即将返回主菜单。。。";
		Sleep(666);
		system("CLS");
		return;
	}
	for (iter = Goods.begin(); iter != Goods.end();){
		iter = Goods.erase(iter);
	}
	cout << "清空仓库成功，即将返回主菜单。。。";
	Sleep(666);
	system("CLS");
	return;
}

//输出表单
void List() {
	system("CLS");
	cout << "货物名称" << '\t' << "库存" << endl;
	for (iter = Goods.begin(); iter != Goods.end(); iter++) {		//使用迭代器遍历并输出库存
		cout << iter->name << '\t' << '\t' << iter->amount << endl;
	}
	cout << endl << "按任意键返回主菜单。。。";
	cin.ignore();
	getchar();
	system("CLS");
	return;
}

//将更改写入文件保存并退出
void SaveAndExit() {
	ofstream saving("data", ios::trunc);
	for (iter = Goods.begin(); iter != Goods.end(); iter++) {		//使用迭代器遍历并输出库存到文件
		saving << iter->name << " " << iter->amount << endl;
	}
	saving.close();
}