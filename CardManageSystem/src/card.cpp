#include "pch.h"
#include "card.h"

card::card(){
	balance = 0;
	cnumber = -1;
	name = "default";
}

card::~card(){

}

void card::Pay(double money){
	balance -= money;
}

void card::charge(double money){
	balance += money;
}

void card::writeLog(string str){
	log.push_back(str);
}

vector<string> card::readLog(){
	return log;
}

void card::setCnumber(int num){
	cnumber = num;
}

void card::setName(string str){
	name = str;
}

const double card::getBalance() const{
	return balance;
}

const int card::getCnumber() const{
	return cnumber;
}

const string card::getName() const{
	return name;
}

campus_card::campus_card(){
	snumber = -1;
	bindnumber = 0;
	academy = "default";
}

campus_card::~campus_card(){
}

void campus_card::pay(){
	
}

void campus_card::inquire(){
	cout << "�ÿ�����Ϣ���£�" << endl;
	cout << "���ţ�" << getCnumber() << endl;
	cout << "������" << getName() << endl;
	cout << "ѧ�ţ�" << snumber << endl;
	cout << "ѧԺ��" << academy << endl;
	cout << "��" << getBalance() << endl;
	cout << "�󶨵Ĵ��������" << bindnumber << endl;
	if (bindnumber > 0) {
		cout << "�󶨵Ĵ�����ţ�" << endl;
		for (int i = 0; i < binding.size(); i++) {
			cout << binding[i] << endl;
		}
	}
	cout << endl;
	cout << "�Ƿ���ʾ�ÿ�����ˮ��ȷ��������y������ʾ�����������ַ���" << endl;
	string str;
	cin >> str;
	if (str == "y") {
		for (int i = 0; i < readLog().size();i++) {
			cout << readLog()[i] << endl;
		}
		getchar();
		cout << "�����������������" << endl;
	}
}

void campus_card::setSnumber(int num){
	snumber = num;
}

void campus_card::setAcademy(string str){
	academy = str;
}

void campus_card::setBinding(int num){
	binding.push_back(num);
	bindnumber += 1;
}

void campus_card::deleteBinding(int num){
	vector<int>::iterator iter;
	int i;
	bool flag = false;
	for (i = 0, iter = binding.begin(); i < binding.size(); i++, iter++) {
		if (num == binding[i]) {
			flag = true;
			break;
		}
	}
	if (flag) {
		string str;
		cout << "ȷ��ɾ�����ſ���ȷ��������y��ȡ�������������ַ���" << endl;
		cin >> str;
		if (str == "y") {
			binding.erase(iter);
			cout << "ɾ���ɹ����������ء�����";
			Sleep(666);
		}
	}
	else {
		cout << "�ð󶨿������ڣ��������ء�����" << endl;
		Sleep(666);
	}
}

const int campus_card::getSnumber() const{
	return snumber;
}

const string campus_card::getAcademy() const{
	return academy;
}

const int campus_card::getBindnumber() const{
	return bindnumber;
}

const int campus_card::getBinding(int i)const {
	return binding[i];
}

deposit_card::deposit_card(){
	credit = 0;
	bindnumber = 0;
}

deposit_card::~deposit_card(){
}

void deposit_card::pay()
{
}

void deposit_card::inquire(){
	cout << "�ÿ�����Ϣ���£�" << endl;
	cout << "���ţ�" << getCnumber() << endl;
	cout << "�ֿ���������" << getName() << endl;
	cout << "�������ڣ�" << getDate() << endl;
	cout << "͸֧��ȣ�" << credit << endl;
	cout << "��" << getBalance() << endl;
	cout << "�󶨵�У԰��������" << bindnumber << endl;
	if (bindnumber > 0) {
		cout << "�󶨵�У԰�����ţ�" << endl;
		for (int i = 0; i < binding.size(); i++) {
			cout << binding[i] << endl;
		}
	}
	cout << endl;
	cout << "�Ƿ���ʾ�ÿ�����ˮ��ȷ��������y������ʾ�����������ַ���" << endl;
	string str;
	cin >> str;
	if (str == "y") {
		for (int i = 0; i < readLog().size(); i++) {
			cout << readLog()[i] << endl;
		}
		cin.get();
		cout << "�����������������" << endl;
	}
}

void deposit_card::setBinding(int num){
	binding.push_back(num);
	bindnumber += 1;
}

void deposit_card::deleteBinding(int num){
	vector<int>::iterator iter;
	int i;
	bool flag = false;
	for (i = 0, iter = binding.begin(); i < binding.size(); i++, iter++) {
		if (num == binding[i]) {
			flag = true;
			break;
		}
	}
	if (flag) {
		binding.erase(iter);
		bindnumber -= 1;
	}
	else {
		cout << "�ڽ��У԰��ʱ��������" << endl;
		Sleep(666);
	}
}

void deposit_card::setCredit(double num){
	credit = num;
}

void deposit_card::setDate(string str){
	date = str;
}

const double deposit_card::getCredit() const{
	return credit;
}

const string deposit_card::getDate() const{
	return date;
}

const int deposit_card::getBindnumber() const{
	return bindnumber;
}

const int deposit_card::getBinding(int i) const{
	return binding[i];
}
