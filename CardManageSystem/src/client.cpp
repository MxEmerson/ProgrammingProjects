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
	}		//��δ�ܴ��ļ�"data"������ʹ��ofstream�½�

	if (!load.is_open()) {
		cout << "���ļ�ʧ�ܣ������˳����򡣡���";
		Sleep(666);
		exit(1);
	}		//����δ�ܴ��ļ�"data"���򱨴��˳�

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
		//����־�ļ�
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
	}		//��δ�ܴ��ļ�"data"������ʹ��ofstream�½�

	if (!load.is_open()) {
		cout << "���ļ�ʧ�ܣ������˳����򡣡���";
		Sleep(666);
		exit(1);
	}		//����δ�ܴ��ļ�"data"���򱨴��˳�

	while (getline(load, tempstr, '\n')) {
		amount++;
	}		//��ͳ�������ķ���ͳ��У԰���ж�����
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
		//����־�ļ�
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
	cout << "�������û�����";
	while (1) {	
		cin >> str1;
		if (str1 == "admin") {
			cout << "���������룺";
			while (security < 3) {		//3���������ֱ���˳�����
				cin >> str2;
				if (str2 == admin.getPassword()) {
					system("CLS");
					return true;
				}
				else {
					security++;
					cout << "���������������ȷ�����룡" << endl;
					cout << "������" << 3 - security << "��������᣺";
				}
			}
			cout << "�������������ѳ���3�Σ�ϵͳ�����Զ��˳���" << endl;
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
			cout << "���������������ڵ��û�����" << endl;
		}
	}
	security = 0;
	cout << "���������룺";
	while (security < 3) {		//3���������ֱ���˳�����
		cin >> str2;
		if (str2 == users[usernumber].getPassword()) {
			system("CLS");
			return false;
		}
		else {
			security++;
			cout << "���������������ȷ��6λ����Կ��" << endl;
			cout << "������" << 3 - security << "��������᣺";
		}
	}
	cout << "�������������ѳ���3�Σ�ϵͳ�����Զ��˳���" << endl;
	Sleep(666);
	exit(0);
}

void Menu(){
	cout << endl;
	cout << endl;
	cout << '\t' << "#######################################" << endl;
	cout << '\t' << "#        ��ӭʹ��У԰������ϵͳ       #" << endl;
	cout << '\t' << "#              �汾��v1.0             #" << endl;
	cout << '\t' << "#                                     #" << endl;
	cout << '\t' << "#   ָ���б�                        #" << endl;
	cout << '\t' << "#                                     #" << endl;
	cout << '\t' << "#   1  У԰������     2  �������   #" << endl;
	cout << '\t' << "#   3  �û�����       4  ֧���ӿ�     #" << endl;
	cout << '\t' << "#   0  ���沢���                     #" << endl;
	cout << '\t' << "#                                     #" << endl;
	cout << '\t' << "#######################################" << endl;
	cout << endl;
	cout << endl;
	cout << "�������Ӧָ��ǰ��������";
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
		cout << '\t' << "#   ָ���б�                        #" << endl;
		cout << '\t' << "#                                     #" << endl;
		cout << '\t' << "#   1  У԰��֧��     2  ���֧��   #" << endl;
		cout << '\t' << "#   0  �����ϼ��˵�                   #" << endl;
		cout << '\t' << "#                                     #" << endl;
		cout << '\t' << "#######################################" << endl;
		cout << endl;
		cout << endl;
		cout << "�������Ӧָ��ǰ��������";
		cin >> str1;
		if (str1 == "1") {
			system("CLS");
			cout << "���ڽ���У԰��֧��������" << endl;
			cout << "������У԰�����ţ�";
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
				cout << "�������" << endl;
				cin >> money;
				if (money > 0 && ccards[i].getBalance() - money >= 0) {
					ccards[i].Pay(money);
					string logstr = getTime()+"ʹ�����֧��"+to_string(money)+"Ԫ";
					ccards[i].writeLog(logstr);
					cout << "ʹ��У԰��֧���ɹ���Ŀǰ��" << ccards[i].getBalance() << endl;
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
							string logstr = getTime() + "ʹ�ð󶨵Ĵ��"+to_string(dcards[j].getCnumber())+"֧��" + to_string(money) + "Ԫ";
							ccards[i].writeLog(logstr);
							logstr = getTime() + "ʹ�ð󶨵�У԰��" + to_string(ccards[i].getCnumber()) + "֧��" + to_string(money) + "Ԫ";
							dcards[j].writeLog(logstr);
							cout << "У԰�����㣬ʹ��У԰���󶨵Ĵ��"<<dcards[j].getCnumber()<<"֧���ɹ������Ŀǰ��" << dcards[j].getBalance() << endl;
							Sleep(666);
						}
						else {
							cout << "֧��ʧ�ܣ�" << endl;
							Sleep(666);
						}
					}
				}
			}
			else {
				cout << "��У԰�������ڣ��������ء�����" << endl;
				Sleep(666);
			}
		}
		else if (str1 == "2") {
			system("CLS");
			cout << "���ڽ��д��֧��������" << endl;
			cout << "�����봢����ţ�";
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
				cout << "�������" << endl;
				cin >> money;
				if (dcards[i].getBalance() - money > dcards[i].getCredit()) {
					dcards[i].Pay(money);
					string logstr = getTime() + "ʹ�����֧��" + to_string(money) + "Ԫ";
					dcards[i].writeLog(logstr);
					cout << "ʹ�ô��" << dcards[i].getCnumber() << "֧���ɹ������Ŀǰ��" << dcards[i].getBalance() << endl;
					Sleep(666);
				}
				else {
					cout << "֧��ʧ�ܣ�" << endl;
					Sleep(666);
				}
			}
			else {
				cout << "�ô�������ڣ��������ء�����" << endl;
				Sleep(666);
			}
		}
		else if (str1 == "0")
			flag1 = false;
		else
			cout << "��������ȷ��������" << endl;
	}
}

void C_Menu(){
	cout << endl;
	cout << endl;
	cout << '\t' << "########################################" << endl;
	cout << '\t' << "#        ��ӭʹ��У԰������ϵͳ        #" << endl;
	cout << '\t' << "#              �汾��v1.0              #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   У԰���������                     #" << endl;
	cout << '\t' << "#   ָ���б�                         #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   1  �½�У԰��     2  У԰����ѯ    #" << endl;
	cout << '\t' << "#   3  У԰����ֵ     4  �󶨿�����    #" << endl;
	cout << '\t' << "#   5  ɾ��У԰��     0  �����ϼ��˵�  #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "########################################" << endl;
	cout << endl;
	cout << endl;
	cout << "�������Ӧָ��ǰ��������";
}

void C_New(){
	system("CLS");
	cout << "�������У԰��������" << endl;
	string str1, str2, str3;
	int cnumber, snumber;
	cout << "�����뿨�ţ�����������0��" << endl;
	cin.ignore();
	cin >> cnumber;
	if (cnumber == 0)return;
	bool flag = Examine(cnumber);
	while (!flag); {
		cout << "�����ʽ�������������룺" << endl;
		cin >> cnumber;
		flag = Examine(cnumber);
	}
	cout << "����������������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (!Examine(str1)) {
		cout << "�����ʽ�������������룺" << endl;
		cin >> str1;
	}
	cout << "������ѧԺ������������0��" << endl;
	cin >> str2;
	if (str2 == "0")return;
	while (!Examine(str2)) {
		cout << "�����ʽ�������������룺" << endl;
		cin >> str2;
	}
	cout << "������ѧ�ţ�����������0��" << endl;
	cin >> snumber;
	if (snumber == 0)return;
	while (!Examine(snumber)) {
		cout << "�����ʽ�������������룺" << endl;
		cin >> snumber;
	}
	cout << "��˶��½�������Ϣ��" << endl;
	cout << "���ţ�" << cnumber << endl;
	cout << "������" << str1 << endl;
	cout << "ѧԺ��" << str2 << endl;
	cout << "ѧ�ţ�" << snumber << endl;
	cout << "ȷ���½�������y��ȡ�������������ַ���" << endl;
	cin >> str3;
	if (str3 == "y") {
		campus_card temp;
		temp.setName(str1);
		temp.setAcademy(str2);
		temp.setCnumber(cnumber);
		temp.setSnumber(snumber);
		ccards.push_back(temp);
		cout << "�½��ɹ����������ز˵�������";
		Sleep(666);
	}
	else
		return;
}

void C_Inquire(){
	int cnumber;
	int i;
	cout << "���ڽ���У԰����ѯ������" << endl;
	cout << "������У԰�����ţ�";
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
		cout << "��У԰�������ڣ��������ء�����" << endl;
		Sleep(666);
	}
}

void C_Charge(){
	int cnumber;
	int i;
	cout << "���ڽ���У԰����ֵ������" << endl;
	cout << "������У԰�����ţ�";
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
		cout << "��ѡ���ֵ��ʽ��" << endl;
		cout << "�ֽ��ֵ������1�����ת��������2�����������������ַ���";
		cin >> str;
		if (str == "1") {
			cout << "�������ֵ��";
			cin >> money;
			if (money > 0 && money <= 500) {
				cout << "������Ϊ����" << ccards[i].getCnumber() << "��У԰����ֵ" << money << "Ԫ��" << endl;
				cout << "ȷ��������y��ȡ�������������ַ���" << endl;
				cin >> str;
				if (str == "y") {
					ccards[i].charge(money);
					string logstr = getTime() + "ʹ���ֽ��ֵ" + to_string(money) + "Ԫ";
					ccards[i].writeLog(logstr);
					cout << "��ֵ�ɹ�����������" << endl;
					Sleep(666);
				}
				else {
					cout << "��ȡ������������" << endl;
					Sleep(666);
				}
			}
		}
		else if (str == "2") {
			int cnumber2;
			int j;
			cout << "�����봢����ţ�";
			cin >> cnumber2;
			bool flag = false;
			for (j = 0; j < dcards.size(); j++) {
				if (cnumber2 == dcards[j].getCnumber()) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				cout << "�ô�������ڣ��������ء�����" << endl;
				Sleep(666);
				return;
			}
			cout << "�������ֵ��";
			cin >> money;
			if (money > 0 && money <= 500 && dcards[j].getBalance() - money > -dcards[j].getCredit()) {
				cout << "������Ϊ����" << dcards[i].getCnumber() << "��У԰����ֵ" << money << "Ԫ��" << endl;
				cout << "ȷ��������y��ȡ�������������ַ���" << endl;
				cin >> str;
				if (str == "y") {
					dcards[j].Pay(money);
					ccards[i].charge(money);
					string logstr = getTime() + "ʹ�ô��" + to_string(dcards[j].getCnumber()) + "��ֵ" + to_string(money) + "Ԫ";
					ccards[i].writeLog(logstr);
					logstr = getTime() + "ΪУ԰��" + to_string(ccards[i].getCnumber()) + "��ֵ" + to_string(money) + "Ԫ";
					dcards[j].writeLog(logstr);
					cout << "��ֵ�ɹ�����������" << endl;
					Sleep(666);
				}
				else {
					cout << "��ȡ������������" << endl;
					Sleep(666);
				}
			}
			else {
				cout << "�������������㣬�������ء�����";
				Sleep(666);
			}
		}
	}
	else {
		cout << "�ô�������ڣ��������ء�����" << endl;
		Sleep(666);
	}
}

void C_Bind(){
	int cnumber, dnumber;
	int i;
	cout << "���ڽ���У԰���󶨹�������" << endl;
	cout << "������У԰�����ţ�";
	cin >> cnumber;
	bool flag = false;
	for (i = 0; i < ccards.size(); i++) {
		if (cnumber == ccards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "���������󶨵Ĵ�����ţ�" << endl;
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
			cout << "�ô�������ڣ��������ء�����" << endl;
			Sleep(666);
			return;
		}
		ccards[i].setBinding(dnumber);
		string logstr = getTime() + "�󶨴��" + to_string(dcards[j].getCnumber());
		ccards[i].writeLog(logstr);
		dcards[j].setBinding(ccards[i].getCnumber());
		logstr = getTime() + "��У԰��" + to_string(ccards[i].getCnumber());
		dcards[j].writeLog(logstr);
	}
	else {
		cout << "��У԰�������ڣ��������ء�����" << endl;
		Sleep(666);
	}
}

void C_Delete(){
	int cnumber;
	vector<campus_card>::iterator iter;
	int i;
	cout << "���ڽ���У԰��ɾ��������" << endl;
	cout << "������У԰�����ţ�";
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
		cout << "ȷ��ɾ�����ſ���ȷ��������y��ȡ�������������ַ���" << endl;
		cin >> str;
		if (str == "y") {
			ccards.erase(iter);
			cout << "ɾ���ɹ����������ء�����";
			Sleep(666);
		}
	}
	else {
		cout << "��У԰�������ڣ��������ء�����" << endl;
		Sleep(666);
	}
}

void D_Menu(){
	cout << endl;
	cout << endl;
	cout << '\t' << "########################################" << endl;
	cout << '\t' << "#        ��ӭʹ��У԰������ϵͳ        #" << endl;
	cout << '\t' << "#              �汾��v1.0              #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   ����������                     #" << endl;
	cout << '\t' << "#   ָ���б�                         #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   1  �½����     2  �����ѯ    #" << endl;
	cout << '\t' << "#   3  �����ֵ     4  ���ö�ȹ���  #" << endl;
	cout << '\t' << "#   5  ɾ�����     0  �����ϼ��˵�  #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "########################################" << endl;
	cout << endl;
	cout << endl;
	cout << "�������Ӧָ��ǰ��������";
}

void D_New(){
	system("CLS");
	cout << "������Ӵ��������" << endl;
	string str1, str2, str3, date;
	int cnumber;
	double credit;
	cout << "�����뿨�ţ�����������0��" << endl;
	cin >> cnumber;
	if (cnumber == 0)return;
	while (!Examine(cnumber)); {
		cout << "�����ʽ�������������룺" << endl;
		cin >> cnumber;
	}
	cout << "������ֿ�������������������0��" << endl;
	cin >> str1;
	if (str1 == "0")return;
	while (!Examine(str1)) {
		cout << "�����ʽ�������������룺" << endl;
		cin >> str1;
	}
	cout << "���������ö�ȣ�����������0��" << endl;
	cin >> credit;
	if (credit == 0)return;
	while (!Examine(credit)) {
		cout << "�����ʽ�������������룺" << endl;
		cin >> credit;
	}
	cout << "��˶��½�������Ϣ��" << endl;
	cout << "���ţ�" << cnumber << endl;
	cout << "�ֿ���������" << str1 << endl;
	cout << "���ö�ȣ�" << credit << endl;
	cout << "ȷ���½�������y��ȡ�������������ַ���" << endl;
	cin >> str3;
	if (str3 == "y") {
		date = getTime();
		deposit_card temp;
		temp.setName(str1);
		temp.setCnumber(cnumber);
		temp.setCredit(credit);
		temp.setDate(date);
		dcards.push_back(temp);
		cout << "�½��ɹ����������ز˵�������";
		Sleep(666);
	}
	else
		return;
}

void D_Inquire(){
	int cnumber;
	int i;
	cout << "���ڽ��д����ѯ������" << endl;
	cout << "�����봢����ţ�";
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
		cout << "�ô�������ڣ��������ء�����" << endl;
		Sleep(666);
	}
}

void D_Charge(){
	int cnumber;
	int i;
	cout << "���ڽ��д����ֵ������" << endl;
	cout << "�����봢����ţ�";
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
		cout << "��ѡ���ֵ��ʽ��" << endl;
		cout << "�ֽ��ֵ������1�����ת��������2�����������������ַ���";
		cin >> str;
		if (str == "1") {
			cout << "�������ֵ��";
			cin >> money;
			if (money > 0 && money <= 500) {
				cout << "������Ϊ����" << dcards[i].getCnumber() << "�Ĵ����ֵ" << money << "Ԫ��" << endl;
				cout << "ȷ��������y��ȡ�������������ַ���" << endl;
				cin >> str;
				if (str == "y") {
					dcards[i].charge(money);
					string logstr = getTime() + "ʹ���ֽ��ֵ" + to_string(money) + "Ԫ";
					dcards[i].writeLog(logstr);
					cout << "��ֵ�ɹ�����������" << endl;
					Sleep(666);
				}
				else {
					cout << "��ȡ������������" << endl;
					Sleep(666);
				}
			}
		}
		else if (str == "2") {
			int cnumber2;
			int j;
			cout << "�����봢����ţ�";
			cin >> cnumber2;
			bool flag = false;
			for (j = 0; j < dcards.size(); j++) {
				if (cnumber2 == dcards[j].getCnumber()) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				cout << "�ô�������ڣ��������ء�����" << endl;
				Sleep(666);
				return;
			}
			cout << "�������ֵ��";
			cin >> money;
			if (money > 0 && money <= 500 && dcards[j].getBalance() - money > -dcards[j].getCredit()) {
				cout << "������Ϊ����" << dcards[i].getCnumber() << "�Ĵ����ֵ" << money << "Ԫ��" << endl;
				cout << "ȷ��������y��ȡ�������������ַ���" << endl;
				cin >> str;
				if (str == "y") {
					dcards[j].pay();
					dcards[i].charge(money);
					string logstr = getTime() + "�ɿ���"+ to_string(dcards[j].getCnumber()) + "�Ĵ��ת��" + to_string(money) + "Ԫ";
					dcards[i].writeLog(logstr);
					logstr = getTime() + "�򿨺�" + to_string(dcards[i].getCnumber()) + "�Ĵ��ת��" + to_string(money) + "Ԫ";
					dcards[j].writeLog(logstr);
					cout << "��ֵ�ɹ�����������" << endl;
					Sleep(666);
				}
				else {
					cout << "��ȡ������������" << endl;
					Sleep(666);
				}
			}
		}
	}
	else {
		cout << "�ô�������ڣ��������ء�����" << endl;
		Sleep(666);
	}
}

void D_Credit(){
	int cnumber;
	int i;
	double credit;
	cout << "�������ô�����ö�ȡ�����" << endl;
	cout << "�����봢����ţ�";
	cin >> cnumber;
	bool flag = false;
	for (i = 0; i < dcards.size(); i++) {
		if (cnumber == dcards[i].getCnumber()) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "�ÿ�Ŀǰ�����Ϊ" << dcards[i].getCredit() << "Ԫ��" << endl;
		cout << "�ÿ�Ŀǰ�����ö��Ϊ" << dcards[i].getCredit() << "Ԫ��" << endl;
		cout << "��������µ����ö�ȣ�" << endl;
		cin >> credit;
		if (dcards[i].getBalance() < -credit) {
			cout << "���㣬������ö��ʧ�ܣ��������ء�����";
			Sleep(666);
			return;
		}
		else if (credit > 10000) {
			cout << "�����ʽ���󣬱�����ö��ʧ�ܣ��������ء�����";
			Sleep(666);
			return;
		}
		else {
			dcards[i].setCredit(credit);
			string logstr = getTime() + "���ö�ȸ���Ϊ" + to_string(credit);
			dcards[i].writeLog(logstr);
			cout << "������ö�ȳɹ����������ء�����";
			Sleep(666);
			return;
		}
	}
	else {
		cout << "�ô�������ڣ��������ء�����" << endl;
		Sleep(666);
	}
}

void D_Delete(){
	int cnumber;
	vector<deposit_card>::iterator iter;
	int i;
	cout << "���ڽ��д��ɾ��������" << endl;
	cout << "�����봢����ţ�";
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
		cout << "ȷ��ɾ�����ſ���ȷ��������y��ȡ�������������ַ���" << endl;
		cin >> str;
		if (str == "y") {
			dcards.erase(iter);
			cout << "ɾ���ɹ����������ء�����";
			Sleep(666);
		}
	}
	else {
		cout << "�ô�������ڣ��������ء�����" << endl;
		Sleep(666);
	}
}

void U_Menu(){
	cout << endl;
	cout << endl;
	cout << '\t' << "########################################" << endl;
	cout << '\t' << "#        ��ӭʹ��У԰������ϵͳ        #" << endl;
	cout << '\t' << "#              �汾��v1.0              #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   �û��˻��������                   #" << endl;
	cout << '\t' << "#   ָ���б�                         #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "#   1  �½��û�       2  �޸�����      #" << endl;
	cout << '\t' << "#   3  ɾ���û�       0  �����ϼ��˵�  #" << endl;
	cout << '\t' << "#                                      #" << endl;
	cout << '\t' << "########################################" << endl;
	cout << endl;
	cout << endl;
	cout << "�������Ӧָ��ǰ��������";
}

void U_Add(){
	system("CLS");
	cout << "�����½��û�������" << endl;
	string name, password, str;
	cout << "�������û���������������0��" << endl;
	cin >> name;
	if (name == "0")return;
	while (!Examine(name)); {
		cout << "�����ʽ�������������룺" << endl;
		cin >> name;
	}
	cout << "���������룬����������0��" << endl;
	cin >> password;
	if (password == "0")return;
	while (!Examine(password)) {
		cout << "�����ʽ�������������룺" << endl;
		cin >> password;
	}
	cout << "��ȷ�����룬����������0��" << endl;
	cin >> str;
	if (str == "0")return;
	while (str!=password) {
		cout << "�������벻ƥ�䣬���������룬����������0��" << endl;
		cin >> str;
	}
	cout << "��˶��½��û�����Ϣ��" << endl;
	cout << "�û�����" << name << endl;
	cout << "���룺" << password << endl;
	cout << "ȷ���½�������y��ȡ�������������ַ���" << endl;
	cin >> str;
	if (str == "y") {
		User temp;
		temp.setName(name);
		temp.setPassword(password);
		users.push_back(temp);
		cout << "�½��ɹ����������ز˵�������";
		Sleep(666);
	}
	else
		return;
}

void U_Manage(){
	system("CLS");
	cout << "����׼���޸��˻����롣����" << endl;
	string name, password, str;
	vector<User>::iterator iter;
	int i;
	cout << "�������û���������������0��" << endl;
	cin >> name;
	if (name == "0")return;
	bool flag = false;
	for (i = 0, iter = users.begin(); i < users.size(); i++, iter++) {
		if (name == users[i].getName()) {
			flag = true;
			break;
		}
	}
	cout << "����������룬����������0��" << endl;
	cin >> password;
	if (password == "0")return;
	else if (password != users[i].getPassword()) {
		cout << "������󣬼������ء�����" << endl;
		Sleep(666);
		return;
	}
	cout << "�����������룬����������0��" << endl;
	cin >> password;
	if (password == "0")return;
	while (!Examine(password)) {
		cout << "�����������룬����������0��" << endl;
	cin >> password;
	if (password == "0")return;
		cin >> password;
	}
	cout << "��ȷ�����룬����������0��" << endl;
	cin >> str;
	if (str == "0")return;
	while (str != password) {
		cout << "�������벻ƥ�䣬���������룬����������0��" << endl;
		cin >> str;
	}
	cout << "��˶��޸ĺ���û���Ϣ��" << endl;
	cout << "�û�����" << name << endl;
	cout << "���룺" << password << endl;
	cout << "ȷ���޸�������y��ȡ�������������ַ���" << endl;
	cin >> str;
	if (str == "y") {
		users[i].setPassword(password);
		cout << "�޸ĳɹ����������ز˵�������";
		Sleep(666);
	}
	else
		return;
}

void U_Delete(){
	string name, password;
	vector<User>::iterator iter;
	int i;
	cout << "����׼��ɾ���û�������" << endl;
	cout << "�������û�����";
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
		cout << "��˶Լ���ɾ�����û���Ϣ��" << endl;
		cout << "�û�����" << name << endl;
		cout << "ȷ��ɾ�������û���ȷ��������y��ȡ�������������ַ���" << endl;
		cin >> str;
		if (str == "y") {
			users.erase(iter);
			cout << "ɾ���ɹ����������ء�����";
			Sleep(666);
		}
	}
	else {
		cout << "���û������ڣ��������ء�����" << endl;
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