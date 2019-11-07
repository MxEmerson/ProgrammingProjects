#include"client.h"
#include"card.h"
#include"user.h"
#include"pch.h"

vector<User> users;
vector<campus_card> ccards;
vector<deposit_card> dcards;

void Load(){
	string tempstr, name, academy, username, password;
	int cnumber, snumber, bindnumber, bindcard;
	double balance;
	int amount = 0;
	ifstream load;
	load.open("users", ios::in);
	if (!load.is_open()) {
		load.close();
		ofstream firstload;
		firstload.open("users");
		firstload.close();
		load.open("users");
	}
	while (getline(load, tempstr, '\n')) {
		amount++;
	}
	load.close();
	load.open("users");
	for (int i = 0; i < amount; i++) {
		load >> username >> password;
		User tempuser;
		tempuser.setName(username);
		tempuser.setPassword(password);
		users.push_back(tempuser);
	}

	amount = 0;
	load.open("cdata", ios::in);
	if (!load.is_open()) {
		load.close();
		ofstream firstload;
		firstload.open("cdata");
		firstload.close();
		load.open("cdata");
	}		//若未能打开文件"data"，则尝试使用ofstream新建

	if (!load.is_open()) {
		cout << "打开文件失败，即将退出程序。。。";
		Sleep(666);
		exit(1);
	}		//若仍未能打开文件"data"，则报错并退出

	while (getline(load, tempstr, '\n')) {
		amount++;
	}
	load.close();
	load.open("cdata");
	for (int i = 0; i < amount; i++) {
		load >> name >> academy >> cnumber >> snumber >> balance;
		campus_card temp;
		temp.setName(name);
		temp.setAcademy(academy);
		temp.setCnumber(cnumber);
		temp.setSnumber(snumber);
		temp.charge(balance);
		load >> bindnumber;
		for (int j = 0; j < bindnumber; j++) {
			load >> bindcard;
			temp.setBinding(bindnumber);
		}
		ifstream logload;
		//打开日志文件
		string filename = "clog/" + to_string(temp.getCnumber());
		logload.open(filename, ios::in);
		if (logload.is_open()) {
			int logamount = 0;
			string tempstr2, tempstr3;
			while (getline(logload, tempstr2, '\n')) {
				logamount++;
			}
			logload.close();
			logload.open(filename);
			for (int j = 0; j < logamount; j++) {
				logload >> tempstr2 >> tempstr3;
				tempstr2 += " " + tempstr3;
				temp.writeLog(tempstr2);
			}
		}
		logload.close();
		ccards.push_back(temp);
	}
	load.close();

	string date;
	double credit;
	amount = 0;
	load.open("ddata", ios::in);
	if (!load.is_open()) {
		load.close();
		ofstream firstload;
		firstload.open("ddata");
		firstload.close();
		load.open("ddata");
	}		//若未能打开文件"data"，则尝试使用ofstream新建

	if (!load.is_open()) {
		cout << "打开文件失败，即将退出程序。。。";
		Sleep(666);
		exit(1);
	}		//若仍未能打开文件"data"，则报错并退出

	while (getline(load, tempstr, '\n')) {
		amount++;
	}		//用统计行数的方法统计校园卡有多少张
	amount /= 2;
	load.close();
	load.open("ddata");
	for (int i = 0; i < amount; i++) {
		load >> name >> date >> cnumber >> credit >> balance;
		deposit_card temp;
		temp.setName(name);
		temp.setDate(date);
		temp.setCnumber(cnumber);
		temp.setCredit(credit);
		temp.charge(balance);
		load >> bindnumber;
		for (int j = 0; j < bindnumber; j++) {
			load >> bindcard;
			temp.setBinding(bindnumber);
		}
		ifstream logload;
		//打开日志文件
		string filename = "dlog/" + to_string(temp.getCnumber());
		logload.open(filename, ios::in);
		if (logload.is_open()) {
			int logamount = 0;
			string tempstr2, tempstr3;
			while (getline(logload, tempstr2, '\n')) {
				logamount++;
			}
			logload.close();
			logload.open(filename);
			for (int j = 0; j < logamount; j++) {
				logload >> tempstr2 >> tempstr3;
				tempstr2 += " " + tempstr3;
				temp.writeLog(tempstr2);
			}
		}
		logload.close();
		dcards.push_back(temp);
	}
	load.close();
}

bool Login(){
	Admin admin;
	int security = 0;
	string str1;
	string str2;
	int usernumber;
	cout << "请输入用户名：";
	while (1) {	
		cin >> str1;
		if (str1 == "admin") {
			cout << "请输入密码：";
			while (security < 3) {		//3次输入错误直接退出程序
				cin >> str2;
				if (str2 == admin.getPassword()) {
					system("CLS");
					return true;
				}
				else {
					security++;
					cout << "输入错误，请输入正确的密码！" << endl;
					cout << "您还有" << 3 - security << "次输入机会：";
				}
			}
			cout << "您输入错误次数已超过3次，系统即将自动退出。" << endl;
			Sleep(666);
			exit(0);
		}
		bool flag = false;
		for (int i = 0; i < users.size(); i++) {
			if (str1 == users[i].getName()) {
				usernumber = i;
				flag = true;
				break;
			}
		}
		if (flag) {
			system("CLS");
			break;
		}
		else {
			cout << "输入错误，请输入存在的用户名！" << endl;
		}
	}
	security = 0;
	cout << "请输入密码：";
	while (security < 3) {		//3次输入错误直接退出程序
		cin >> str2;
		if (str2 == users[usernumber].getPassword()) {
			system("CLS");
			return false;
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

void Menu(){
	cout << endl;
	cout << endl;
	cout << '\t' << "#######################################" << endl;
	cout << '\t' << "#        欢迎使用校园卡管理系统       #" << endl;
	cout << '\t' << "#              版本：v1.0             #" << endl;
	cout << '\t' << "#                                     #" << endl;
	cout << '\t' << "#   指令列表：                        #" << endl;
	cout << '\t' << "#                                     #" << endl;
	cout << '\t' << "#   1  校园卡管理     2  储蓄卡管理   #" << endl;
	cout << '\t' << "#   3  用户管理       4  支付接口     #" << endl;
	cout << '\t' << "#   0  保存并提出                     #" << endl;
	cout << '\t' << "#                                     #" << endl;
	cout << '\t' << "#######################################" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入对应指令前的整数：";
}

void Pay(){
	bool flag1 = true;
	string str1;
	int number;
	int i;
	while (flag1) {
		system("CLS");
		cout << endl;
		cout << endl;
		cout << '\t' << "#######################################" << endl;
		cout << '\t' << "#   指令列表：                        #" << endl;
		cout << '\t' << "#                                     #" << endl;
		cout << '\t' << "#   1  校园卡支付     2  储蓄卡支付   #" << endl;
		cout << '\t' << "#   0  返回上级菜单                   #" << endl;
		cout << '\t' << "#                                     #" << endl;
		cout << '\t' << "#######################################" << endl;
		cout << endl;
		cout << endl;
		cout << "请输入对应指令前的整数：";
		cin >> str1;
		if (str1 == "1") {
			system("CLS");
			cout << "正在进行校园卡支付。。。" << endl;
			cout << "请输入校园卡卡号；";
			cin >> number;
			bool flag2 = false;
			for (i = 0; i < ccards.size(); i++) {
				if (number == ccards[i].getCnumber()) {
					flag2 = true;
					break;
				}
			}
			if (flag2) {
				double money;
				cout << "请输入金额：" << endl;
				cin >> money;
				if (money > 0 && ccards[i].getBalance() - money >= 0) {
					ccards[i].Pay(money);
					string logstr = getTime()+"使用余额支付"+to_string(money)+"元";
					ccards[i].writeLog(logstr);
					cout << "使用校园卡支付成功，目前余额：" << ccards[i].getBalance() << endl;
					Sleep(666);
					return;
				}
				else {
					for (int k = 0; k < ccards[i].getBindnumber(); k++) {
						int j;
						bool flag3 = false;
						for (j = 0; j < dcards.size(); j++) {
							if (ccards[i].getBinding(k) == dcards[j].getCnumber()) {
								flag3 = true;
								break;
							}
						}
						if (flag3 && dcards[j].getBalance() - money > dcards[j].getCredit()) {
							dcards[j].Pay(money);
							string logstr = getTime() + "使用绑定的储蓄卡"+to_string(dcards[j].getCnumber())+"支付" + to_string(money) + "元";
							ccards[i].writeLog(logstr);
							logstr = getTime() + "使用绑定的校园卡" + to_string(ccards[i].getCnumber()) + "支付" + to_string(money) + "元";
							dcards[j].writeLog(logstr);
							cout << "校园卡余额不足，使用校园卡绑定的储蓄卡"<<dcards[j].getCnumber()<<"支付成功，储蓄卡目前余额：" << dcards[j].getBalance() << endl;
							Sleep(666);
						}
						else {
							cout << "支付失败！" << endl;
							Sleep(666);
						}
					}
				}
			}
			else {
				cout << "该校园卡不存在，即将返回。。。" << endl;
				Sleep(666);
			}
		}
		else if (str1 == "2") {
			system("CLS");
			cout << "正在进行储蓄卡支付。。。" << endl;
			cout << "请输入储蓄卡卡号；";
			cin >> number;
			bool flag2 = false;
			for (i = 0; i < ccards.size(); i++) {
				if (number == ccards[i].getCnumber()) {
					flag2 = true;
					break;
				}
			}
			if (flag2) {
				double money;
				cout << "请输入金额：" << endl;
				cin >> money;
				if (dcards[i].getBalance() - money > dcards[i].getCredit()) {
					dcards[i].Pay(money);
					string logstr = getTime() + "使用余额支付" + to_string(money) + "元";
					dcards[i].writeLog(logstr);
					cout << "使用储蓄卡" << dcards[i].getCnumber() << "支付成功，储蓄卡目前余额：" << dcards[i].getBalance() << endl;
					Sleep(666);
				}
				else {
					cout << "支付失败！" << endl;
					Sleep(666);
				}
			}
			else {
				cout << "该储蓄卡不存在，即将返回。。。" << endl;
				Sleep(666);
			}
		}
		else if (str1 == "0")
			flag1 = false;
		else
			cout << "请输入正确的整数！" << endl;
	}
}

void C_Menu(){
	cout << endl;
	cout << endl;
	cout << '\t' << "########################################" << endl;
	cout << '\t' << "#        欢迎使用校园卡管理系统        #" << endl;
	cout << '\t' << "#              版本：v1.0              #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   校园卡管理面板                     #" << endl;
	cout << '\t' << "#   指令列表：                         #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   1  新建校园卡     2  校园卡查询    #" << endl;
	cout << '\t' << "#   3  校园卡充值     4  绑定卡管理    #" << endl;
	cout << '\t' << "#   5  删除校园卡     0  返回上级菜单  #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "########################################" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入对应指令前的整数：";
}

void C_New(){
	system("CLS");
	cout << "正在添加校园卡。。。" << endl;
	string str1, str2, str3;
	int cnumber, snumber;
	cout << "请输入卡号，返回请输入0：" << endl;
	cin.ignore();
	cin >> cnumber;
	if (cnumber == 0)return;
	bool flag = Examine(cnumber);
	while (!flag); {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> cnumber;
		flag = Examine(cnumber);
	}
	cout << "请输入姓名，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (!Examine(str1)) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> str1;
	}
	cout << "请输入学院，返回请输入0：" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (!Examine(str2)) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> str2;
	}
	cout << "请输入学号，返回请输入0：" << endl;
	cin >> snumber;
	if (snumber == 0)return;
	while (!Examine(snumber)) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> snumber;
	}
	cout << "请核对新建卡的信息：" << endl;
	cout << "卡号：" << cnumber << endl;
	cout << "姓名：" << str1 << endl;
	cout << "学院：" << str2 << endl;
	cout << "学号：" << snumber << endl;
	cout << "确认新建请输入y，取消请输入其他字符：" << endl;
	cin >> str3;
	if (str3 == "y") {
		campus_card temp;
		temp.setName(str1);
		temp.setAcademy(str2);
		temp.setCnumber(cnumber);
		temp.setSnumber(snumber);
		ccards.push_back(temp);
		cout << "新建成功，即将返回菜单。。。";
		Sleep(666);
	}
	else
		return;
}

void C_Inquire(){
	int cnumber;
	int i;
	cout << "正在进行校园卡查询。。。" << endl;
	cout << "请输入校园卡卡号；";
	cin >> cnumber;
	bool flag = false;
	for (i = 0; i < ccards.size(); i++) {
		if (cnumber == ccards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag)
		ccards[i].inquire();
	else {
		cout << "该校园卡不存在，即将返回。。。" << endl;
		Sleep(666);
	}
}

void C_Charge(){
	int cnumber;
	int i;
	cout << "正在进行校园卡充值。。。" << endl;
	cout << "请输入校园卡卡号；";
	cin >> cnumber;
	bool flag = false;
	for (i = 0; i < ccards.size(); i++) {
		if (cnumber == ccards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		string str;
		double money;
		cout << "请选择充值方式：" << endl;
		cout << "现金充值请输入1，储蓄卡转账请输入2，返回请输入其他字符：";
		cin >> str;
		if (str == "1") {
			cout << "请输入充值金额：";
			cin >> money;
			if (money > 0 && money <= 500) {
				cout << "您即将为卡号" << ccards[i].getCnumber() << "的校园卡充值" << money << "元。" << endl;
				cout << "确认请输入y，取消请输入其他字符：" << endl;
				cin >> str;
				if (str == "y") {
					ccards[i].charge(money);
					string logstr = getTime() + "使用现金充值" + to_string(money) + "元";
					ccards[i].writeLog(logstr);
					cout << "充值成功，即将返回" << endl;
					Sleep(666);
				}
				else {
					cout << "已取消，即将返回" << endl;
					Sleep(666);
				}
			}
		}
		else if (str == "2") {
			int cnumber2;
			int j;
			cout << "请输入储蓄卡卡号；";
			cin >> cnumber2;
			bool flag = false;
			for (j = 0; j < dcards.size(); j++) {
				if (cnumber2 == dcards[j].getCnumber()) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				cout << "该储蓄卡不存在，即将返回。。。" << endl;
				Sleep(666);
				return;
			}
			cout << "请输入充值金额：";
			cin >> money;
			if (money > 0 && money <= 500 && dcards[j].getBalance() - money > -dcards[j].getCredit()) {
				cout << "您即将为卡号" << dcards[i].getCnumber() << "的校园卡充值" << money << "元。" << endl;
				cout << "确认请输入y，取消请输入其他字符：" << endl;
				cin >> str;
				if (str == "y") {
					dcards[j].Pay(money);
					ccards[i].charge(money);
					string logstr = getTime() + "使用储蓄卡" + to_string(dcards[j].getCnumber()) + "充值" + to_string(money) + "元";
					ccards[i].writeLog(logstr);
					logstr = getTime() + "为校园卡" + to_string(ccards[i].getCnumber()) + "充值" + to_string(money) + "元";
					dcards[j].writeLog(logstr);
					cout << "充值成功，即将返回" << endl;
					Sleep(666);
				}
				else {
					cout << "已取消，即将返回" << endl;
					Sleep(666);
				}
			}
			else {
				cout << "输入金额错误或余额不足，即将返回。。。";
				Sleep(666);
			}
		}
	}
	else {
		cout << "该储蓄卡不存在，即将返回。。。" << endl;
		Sleep(666);
	}
}

void C_Bind(){
	int cnumber, dnumber;
	int i;
	cout << "正在进行校园卡绑定管理。。。" << endl;
	cout << "请输入校园卡卡号；";
	cin >> cnumber;
	bool flag = false;
	for (i = 0; i < ccards.size(); i++) {
		if (cnumber == ccards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "请输入欲绑定的储蓄卡卡号：" << endl;
		cin >> dnumber;
		bool flag2 = false;
		int j;
		for (j = 0; j < dcards.size(); j++) {
			if (dnumber == dcards[j].getCnumber()) {
				flag2 = true;
				break;
			}
		}
		if (!flag2) {
			cout << "该储蓄卡不存在，即将返回。。。" << endl;
			Sleep(666);
			return;
		}
		ccards[i].setBinding(dnumber);
		string logstr = getTime() + "绑定储蓄卡" + to_string(dcards[j].getCnumber());
		ccards[i].writeLog(logstr);
		dcards[j].setBinding(ccards[i].getCnumber());
		logstr = getTime() + "绑定校园卡" + to_string(ccards[i].getCnumber());
		dcards[j].writeLog(logstr);
	}
	else {
		cout << "该校园卡不存在，即将返回。。。" << endl;
		Sleep(666);
	}
}

void C_Delete(){
	int cnumber;
	vector<campus_card>::iterator iter;
	int i;
	cout << "正在进行校园卡删除。。。" << endl;
	cout << "请输入校园卡卡号；";
	cin >> cnumber;
	bool flag = false;
	for (i = 0, iter = ccards.begin(); i < ccards.size(); i++,iter++) {
		if (cnumber == ccards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		string str;
		ccards[i].inquire();
		cout << "确定删除这张卡吗？确定请输入y，取消请输入其他字符：" << endl;
		cin >> str;
		if (str == "y") {
			ccards.erase(iter);
			cout << "删除成功，即将返回。。。";
			Sleep(666);
		}
	}
	else {
		cout << "该校园卡不存在，即将返回。。。" << endl;
		Sleep(666);
	}
}

void D_Menu(){
	cout << endl;
	cout << endl;
	cout << '\t' << "########################################" << endl;
	cout << '\t' << "#        欢迎使用校园卡管理系统        #" << endl;
	cout << '\t' << "#              版本：v1.0              #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   储蓄卡管理面板                     #" << endl;
	cout << '\t' << "#   指令列表：                         #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   1  新建储蓄卡     2  储蓄卡查询    #" << endl;
	cout << '\t' << "#   3  储蓄卡充值     4  信用额度管理  #" << endl;
	cout << '\t' << "#   5  删除储蓄卡     0  返回上级菜单  #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "########################################" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入对应指令前的整数：";
}

void D_New(){
	system("CLS");
	cout << "正在添加储蓄卡。。。" << endl;
	string str1, str2, str3, date;
	int cnumber;
	double credit;
	cout << "请输入卡号，返回请输入0：" << endl;
	cin >> cnumber;
	if (cnumber == 0)return;
	while (!Examine(cnumber)); {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> cnumber;
	}
	cout << "请输入持卡人姓名，返回请输入0：" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (!Examine(str1)) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> str1;
	}
	cout << "请输入信用额度，返回请输入0：" << endl;
	cin >> credit;
	if (credit == 0)return;
	while (!Examine(credit)) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> credit;
	}
	cout << "请核对新建卡的信息：" << endl;
	cout << "卡号：" << cnumber << endl;
	cout << "持卡人姓名：" << str1 << endl;
	cout << "信用额度：" << credit << endl;
	cout << "确认新建请输入y，取消请输入其他字符：" << endl;
	cin >> str3;
	if (str3 == "y") {
		date = getTime();
		deposit_card temp;
		temp.setName(str1);
		temp.setCnumber(cnumber);
		temp.setCredit(credit);
		temp.setDate(date);
		dcards.push_back(temp);
		cout << "新建成功，即将返回菜单。。。";
		Sleep(666);
	}
	else
		return;
}

void D_Inquire(){
	int cnumber;
	int i;
	cout << "正在进行储蓄卡查询。。。" << endl;
	cout << "请输入储蓄卡卡号；";
	cin >> cnumber;
	bool flag = false;
	for (i = 0; i < dcards.size(); i++) {
		if (cnumber == dcards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag)
		dcards[i].inquire();
	else {
		cout << "该储蓄卡不存在，即将返回。。。" << endl;
		Sleep(666);
	}
}

void D_Charge(){
	int cnumber;
	int i;
	cout << "正在进行储蓄卡充值。。。" << endl;
	cout << "请输入储蓄卡卡号；";
	cin >> cnumber;
	bool flag = false;
	for (i = 0; i < dcards.size(); i++) {
		if (cnumber == dcards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		string str;
		double money;
		cout << "请选择充值方式：" << endl;
		cout << "现金充值请输入1，储蓄卡转账请输入2，返回请输入其他字符：";
		cin >> str;
		if (str == "1") {
			cout << "请输入充值金额：";
			cin >> money;
			if (money > 0 && money <= 500) {
				cout << "您即将为卡号" << dcards[i].getCnumber() << "的储蓄卡充值" << money << "元。" << endl;
				cout << "确认请输入y，取消请输入其他字符：" << endl;
				cin >> str;
				if (str == "y") {
					dcards[i].charge(money);
					string logstr = getTime() + "使用现金充值" + to_string(money) + "元";
					dcards[i].writeLog(logstr);
					cout << "充值成功，即将返回" << endl;
					Sleep(666);
				}
				else {
					cout << "已取消，即将返回" << endl;
					Sleep(666);
				}
			}
		}
		else if (str == "2") {
			int cnumber2;
			int j;
			cout << "请输入储蓄卡卡号；";
			cin >> cnumber2;
			bool flag = false;
			for (j = 0; j < dcards.size(); j++) {
				if (cnumber2 == dcards[j].getCnumber()) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				cout << "该储蓄卡不存在，即将返回。。。" << endl;
				Sleep(666);
				return;
			}
			cout << "请输入充值金额：";
			cin >> money;
			if (money > 0 && money <= 500 && dcards[j].getBalance() - money > -dcards[j].getCredit()) {
				cout << "您即将为卡号" << dcards[i].getCnumber() << "的储蓄卡充值" << money << "元。" << endl;
				cout << "确认请输入y，取消请输入其他字符：" << endl;
				cin >> str;
				if (str == "y") {
					dcards[j].pay();
					dcards[i].charge(money);
					string logstr = getTime() + "由卡号"+ to_string(dcards[j].getCnumber()) + "的储蓄卡转入" + to_string(money) + "元";
					dcards[i].writeLog(logstr);
					logstr = getTime() + "向卡号" + to_string(dcards[i].getCnumber()) + "的储蓄卡转出" + to_string(money) + "元";
					dcards[j].writeLog(logstr);
					cout << "充值成功，即将返回" << endl;
					Sleep(666);
				}
				else {
					cout << "已取消，即将返回" << endl;
					Sleep(666);
				}
			}
		}
	}
	else {
		cout << "该储蓄卡不存在，即将返回。。。" << endl;
		Sleep(666);
	}
}

void D_Credit(){
	int cnumber;
	int i;
	double credit;
	cout << "正在设置储蓄卡信用额度。。。" << endl;
	cout << "请输入储蓄卡卡号；";
	cin >> cnumber;
	bool flag = false;
	for (i = 0; i < dcards.size(); i++) {
		if (cnumber == dcards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "该卡目前的余额为" << dcards[i].getCredit() << "元。" << endl;
		cout << "该卡目前的信用额度为" << dcards[i].getCredit() << "元。" << endl;
		cout << "请输入更新的信用额度：" << endl;
		cin >> credit;
		if (dcards[i].getBalance() < -credit) {
			cout << "余额不足，变更信用额度失败，即将返回。。。";
			Sleep(666);
			return;
		}
		else if (credit > 10000) {
			cout << "输入格式错误，变更信用额度失败，即将返回。。。";
			Sleep(666);
			return;
		}
		else {
			dcards[i].setCredit(credit);
			string logstr = getTime() + "信用额度更新为" + to_string(credit);
			dcards[i].writeLog(logstr);
			cout << "变更信用额度成功，即将返回。。。";
			Sleep(666);
			return;
		}
	}
	else {
		cout << "该储蓄卡不存在，即将返回。。。" << endl;
		Sleep(666);
	}
}

void D_Delete(){
	int cnumber;
	vector<deposit_card>::iterator iter;
	int i;
	cout << "正在进行储蓄卡删除。。。" << endl;
	cout << "请输入储蓄卡卡号；";
	cin >> cnumber;
	bool flag = false;
	for (i = 0, iter = dcards.begin(); i < dcards.size(); i++, iter++) {
		if (cnumber == dcards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		string str;
		dcards[i].inquire();
		cout << "确定删除这张卡吗？确定请输入y，取消请输入其他字符：" << endl;
		cin >> str;
		if (str == "y") {
			dcards.erase(iter);
			cout << "删除成功，即将返回。。。";
			Sleep(666);
		}
	}
	else {
		cout << "该储蓄卡不存在，即将返回。。。" << endl;
		Sleep(666);
	}
}

void U_Menu(){
	cout << endl;
	cout << endl;
	cout << '\t' << "########################################" << endl;
	cout << '\t' << "#        欢迎使用校园卡管理系统        #" << endl;
	cout << '\t' << "#              版本：v1.0              #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   用户账户管理面板                   #" << endl;
	cout << '\t' << "#   指令列表：                         #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   1  新建用户       2  修改密码      #" << endl;
	cout << '\t' << "#   3  删除用户       0  返回上级菜单  #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "########################################" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入对应指令前的整数：";
}

void U_Add(){
	system("CLS");
	cout << "正在新建用户。。。" << endl;
	string name, password, str;
	cout << "请输入用户名，返回请输入0：" << endl;
	cin >> name;
	if (name == "0")return;
	while (!Examine(name)); {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> name;
	}
	cout << "请输入密码，返回请输入0：" << endl;
	cin >> password;
	if (password == "0")return;
	while (!Examine(password)) {
		cout << "输入格式错误，请重新输入：" << endl;
		cin >> password;
	}
	cout << "请确认密码，返回请输入0：" << endl;
	cin >> str;
	if (str == "0")return;
	while (str!=password) {
		cout << "两次输入不匹配，请重新输入，返回请输入0：" << endl;
		cin >> str;
	}
	cout << "请核对新建用户的信息：" << endl;
	cout << "用户名：" << name << endl;
	cout << "密码：" << password << endl;
	cout << "确认新建请输入y，取消请输入其他字符：" << endl;
	cin >> str;
	if (str == "y") {
		User temp;
		temp.setName(name);
		temp.setPassword(password);
		users.push_back(temp);
		cout << "新建成功，即将返回菜单。。。";
		Sleep(666);
	}
	else
		return;
}

void U_Manage(){
	system("CLS");
	cout << "正在准备修改账户密码。。。" << endl;
	string name, password, str;
	vector<User>::iterator iter;
	int i;
	cout << "请输入用户名，返回请输入0：" << endl;
	cin >> name;
	if (name == "0")return;
	bool flag = false;
	for (i = 0, iter = users.begin(); i < users.size(); i++, iter++) {
		if (name == users[i].getName()) {
			flag = true;
			break;
		}
	}
	cout << "请输入旧密码，返回请输入0：" << endl;
	cin >> password;
	if (password == "0")return;
	else if (password != users[i].getPassword()) {
		cout << "密码错误，即将返回。。。" << endl;
		Sleep(666);
		return;
	}
	cout << "请输入新密码，返回请输入0：" << endl;
	cin >> password;
	if (password == "0")return;
	while (!Examine(password)) {
		cout << "请输入新密码，返回请输入0：" << endl;
	cin >> password;
	if (password == "0")return;
		cin >> password;
	}
	cout << "请确认密码，返回请输入0：" << endl;
	cin >> str;
	if (str == "0")return;
	while (str != password) {
		cout << "两次输入不匹配，请重新输入，返回请输入0：" << endl;
		cin >> str;
	}
	cout << "请核对修改后的用户信息：" << endl;
	cout << "用户名：" << name << endl;
	cout << "密码：" << password << endl;
	cout << "确认修改请输入y，取消请输入其他字符：" << endl;
	cin >> str;
	if (str == "y") {
		users[i].setPassword(password);
		cout << "修改成功，即将返回菜单。。。";
		Sleep(666);
	}
	else
		return;
}

void U_Delete(){
	string name, password;
	vector<User>::iterator iter;
	int i;
	cout << "正在准备删除用户。。。" << endl;
	cout << "请输入用户名；";
	cin >> name;
	bool flag = false;
	for (i = 0, iter = users.begin(); i < users.size(); i++, iter++) {
		if (name == users[i].getName()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		string str;
		cout << "请核对即将删除的用户信息：" << endl;
		cout << "用户名：" << name << endl;
		cout << "确定删除这名用户吗？确定请输入y，取消请输入其他字符：" << endl;
		cin >> str;
		if (str == "y") {
			users.erase(iter);
			cout << "删除成功，即将返回。。。";
			Sleep(666);
		}
	}
	else {
		cout << "该用户不存在，即将返回。。。" << endl;
		Sleep(666);
	}
}

void SaveAndExit(){
	ofstream saving("cdata", ios::trunc);
	for (int i = 0; i < ccards.size(); i++) {
		saving << ccards[i].getName() << " " << ccards[i].getAcademy() << " " << ccards[i].getCnumber() << " " << ccards[i].getSnumber() << " " << ccards[i].getBalance() << " ";
		saving << ccards[i].getBindnumber();
		for (int j = 0; j < ccards[i].getBindnumber(); j++)
			saving << " " << ccards[i].getBinding(j);
		saving << endl;
		string filename = "clog/" + to_string(ccards[i].getCnumber());
		ofstream savinglog(filename, ios::trunc);
		for (int j = 0; j < ccards[i].readLog().size(); j++) {
			savinglog << ccards[i].readLog()[j] << endl;
		}
	}
	saving.close();

	saving.open("ddata", ios::trunc);
	for (int i = 0; i < dcards.size(); i++) {
		saving << dcards[i].getName() << " " << dcards[i].getDate() << " " << dcards[i].getCnumber() << " " << dcards[i].getCredit() << " " << dcards[i].getBalance() << endl;
		saving << dcards[i].getBindnumber();
		for (int j = 0; j < dcards[i].getBindnumber(); j++)
			saving << " " << dcards[i].getBinding(j);
		saving << endl;
		string filename = "dlog/" + to_string(dcards[i].getCnumber());
		ofstream savinglog(filename, ios::trunc);
		for (int j = 0; j < dcards[i].readLog().size(); j++) {
			savinglog << dcards[i].readLog()[j] << endl;
		}
	}
	saving.close();

	saving.open("users", ios::trunc);
	for (int i = 0; i < users.size(); i++) {
		saving << users[i].getName() << " " << users[i].getPassword() << endl;
	}
	saving.close();
}

bool Examine(int num) {
	if (num > 0 && num <= 99999999)
		return true;
	else
		return false;
}

bool Examine(double money) {
	if (money > 0 && money < 1000)
		return true;
	else
		return false;
}

bool Examine(string str) {
	return true;
}

string getTime(){
	time_t rawtime;
	struct tm *info;
	char buffer[80];
	time( &rawtime );
	info = localtime( &rawtime );
	string tempstr = to_string(info->tm_year + 1900) + "-" + to_string(info->tm_mon + 1) + "-" + to_string(info->tm_mday) + "_";
	tempstr += to_string(info->tm_hour) + ":" + to_string(info->tm_min) + ":" + to_string(info->tm_sec);
	return tempstr;
}