#include "source.h"
#include "pch.h"

using namespace std;

typedef struct GoodA {
	string name;
	int amount;
}Good;			//����һ���ṹ��

typedef list<Good> LISTGoods;
LISTGoods Goods;				//����˫������
LISTGoods::iterator iter;		//����������

//���ļ���������д�����
void Loading() {
	string tempstr;
	int tempint;
	int TotalGoodsAmount = 0;	//��������
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
		TotalGoodsAmount++;
	}		//��ͳ�������ķ���ͳ�ƻ����ж�����

	load.close();
	load.open("data");
	for (int i = 0; i < TotalGoodsAmount; i++) {
		load >> tempstr >> tempint;
		struct GoodA tempstruct;
		tempstruct.name = tempstr;
		tempstruct.amount = tempint;
		Goods.push_back(tempstruct);
	}		//���ļ��е�����
	load.close();
}

//��¼
void Login() {
	int security = 0;
	char password[7] = { "000000" };		//Ԥ�ȸ�����Ʒ��Կ
	char str[7];
	cout << "������6λ����Կ��";
	while (security < 3) {		//3���������ֱ���˳�����
		cin >> str;
		if (strcmp(password, str) == 0) {
			system("CLS");
			return;
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

//����˵�
void Menu() {
	cout << endl;
	cout << '\t' << "###############################################" << endl;
	cout << '\t' << "#            ��ӭʹ�òֿ����ϵͳ             #" << endl;
	cout << '\t' << "#                 �汾��v1.0                  #" << endl;
	cout << '\t' << "#                 ָ���б�                  #" << endl;
	cout << '\t' << "#  1  ����                   2  ����          #" << endl;
	cout << '\t' << "#  3  ��ղֿ�               4  �������  #" << endl;
	cout << '\t' << "#  5  ���沢�˳�                              #" << endl;
	cout << '\t' << "###############################################" << endl;
	cout << endl;
	cout << "�������Ӧָ��ǰ��������";
}

//����
void Stock() {
	system("CLS");
	int location = 0;
	string name;
	char numberstr[100];
	cout << "���ڽ��н�������������" << endl;
	cout << "��������Ӧ����0�ַ���С��100�ַ���" << endl;
	cout << "������������ƣ�";
	cin >> name;
	bool flag = false;
	for (iter = Goods.begin(); iter != Goods.end(); iter++) {	//ʹ�õ������������
		if (iter->name == name) {
			flag = true;
			break;
		}
	}
	if (flag) {			//����������������Ļ�������ӿ��
		cout << "���ڿ���в�ѯ���û���,Ŀǰ��棺" << iter->amount << endl;
		cout << "��ע�ⵥ������Ŀ���������ܳ���999999999��" << endl;
		cout << "�������������";
		cin.ignore();	//����stdin�Ļ�����
		fgets(numberstr, 100, stdin);
		while (atoi(numberstr) <= 0 || atoi(numberstr) + iter->amount >= 999999999) {	//�ж������Ƿ�Ƿ��������Ƿ��㹻
			cout << "��������ȷ��������" << endl;
			fgets(numberstr, 100, stdin);
		}
		iter->amount += atoi(numberstr);
	}
	else {				//��������û�иû����
		cout << "Ŀǰ������޸û��" << endl;
		cout << "��ע�ⵥ������Ŀ���������ܳ���999999999��" << endl;
		cout << "�������������";
		cin.ignore();	//����stdin�Ļ�����
		fgets(numberstr, 100, stdin);
		while (atoi(numberstr) <= 0 || atoi(numberstr) >= 999999999) {		//�ж������Ƿ�Ƿ��������Ƿ��㹻
			cout << "��������ȷ��������" << endl;
			fgets(numberstr, 100, stdin);
		}
		struct GoodA tempstruct;
		tempstruct.name = name;
		tempstruct.amount = atoi(numberstr);
		Goods.push_back(tempstruct);		//��������
	}
	cout << "�����ɹ��������������˵�������" << endl;
	Sleep(666);
	system("CLS");
	return;
}

//����
void Deliver() {
	system("CLS");
	int location = 0;
	string name;
	char numberstr[100];
	cout << "���ڽ��г�������������" << endl;
	cout << "��������Ӧ����0�ַ���С��100�ַ���" << endl;
	cout << "������������ƣ�";
	bool flag = false;
	cin >> name;
	for (iter = Goods.begin(); iter != Goods.end(); iter++) {
		if (iter->name == name) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "���ڿ���в�ѯ���û���,Ŀǰ��棺" << iter->amount << endl;
		cout << "��ע�����Ŀ����������С��0��" << endl;
		cout << "�������������";
		cin.ignore();	//����stdin�Ļ�����
		fgets(numberstr, 100, stdin);
		while (atoi(numberstr) <= 0 || iter->amount - atoi(numberstr) < 0) {		//�ж������Ƿ�Ƿ������Ƿ��㹻
			cout << "��������ȷ��������" << endl;
			fgets(numberstr, 100, stdin);
		}
		if (iter->amount - atoi(numberstr) > 0)		//����ʣ��
			iter->amount -= atoi(numberstr);
		else
			Goods.erase(iter);		//���պ�Ϊ0
	}
	else {
		cout << "Ŀǰ������޸û��" << endl;
		cout << "�����������˵�������" << endl;
		Sleep(666);
		system("CLS");
		return;
	}
	cout << "�����ɹ��������������˵�������" << endl;
	Sleep(666);
	system("CLS");
	return;
}

//��ղֿ�
void Empty() {
	string key;
	string truekey = "000000";
	cout << "��������Կ��";		//������Կ��ֹ�����
	cin >> key;
	if (key != truekey) {
		cout << "��Կ������󣬼����������˵�������";
		Sleep(666);
		system("CLS");
		return;
	}
	for (iter = Goods.begin(); iter != Goods.end();){
		iter = Goods.erase(iter);
	}
	cout << "��ղֿ�ɹ��������������˵�������";
	Sleep(666);
	system("CLS");
	return;
}

//�����
void List() {
	system("CLS");
	cout << "��������" << '\t' << "���" << endl;
	for (iter = Goods.begin(); iter != Goods.end(); iter++) {		//ʹ�õ�����������������
		cout << iter->name << '\t' << '\t' << iter->amount << endl;
	}
	cout << endl << "��������������˵�������";
	cin.ignore();
	getchar();
	system("CLS");
	return;
}

//������д���ļ����沢�˳�
void SaveAndExit() {
	ofstream saving("data", ios::trunc);
	for (iter = Goods.begin(); iter != Goods.end(); iter++) {		//ʹ�õ����������������浽�ļ�
		saving << iter->name << " " << iter->amount << endl;
	}
	saving.close();
}