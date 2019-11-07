#pragma once
#include "pch.h"
using namespace std;

class card{
public:
	card();
	~card();
	virtual void pay() = 0;
	virtual void inquire() = 0;
	void Pay(double money);
	void charge(double money);
	void writeLog(string str);
	vector<string> readLog();
	void setCnumber(int num);
	void setName(string str);
	const double getBalance()const;//���
	const int getCnumber()const;//����
	const string getName()const;//����
private:
	double balance;//���
	int cnumber;//����
	string name;//����
	vector<string> log;//��־
};

class campus_card :public card{
public:
	campus_card();
	~campus_card();
	void pay();//֧��
	void inquire();//��ѯ
	void setSnumber(int num);//����ѧ��
	void setAcademy(string str);//����ѧԺ
	void setBinding(int num);//���ð󶨿�
	void deleteBinding(int num);//ɾ���󶨿�
	const int getSnumber()const;//ѧ��
	const string getAcademy()const;//ѧԺ
	const int getBindnumber()const;
	const int getBinding(int i)const;
private:
	int snumber;//ѧ��
	int bindnumber;//�󶨿�����
	string academy;//ѧԺ
	vector<int> binding;//�󶨵Ŀ�
};

class deposit_card :public card {
public:
	deposit_card();
	~deposit_card();
	void pay();//֧��
	void inquire();//��ѯ
	void setBinding(int num);//���ð󶨿����������ã�
	void deleteBinding(int num);//ɾ���󶨿�
	void setCredit(double num);//�������ö��
	void setDate(string str);//���÷�������
	const double getCredit()const;//�������ö��
	const string getDate()const;//��������
	const int getBindnumber()const;
	const int getBinding(int i)const;
private:
	double credit;//͸֧���
	int bindnumber;
	string date;//��������
	vector<int> binding;//�󶨵Ŀ�
};
