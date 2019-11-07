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
	const double getBalance()const;//余额
	const int getCnumber()const;//卡号
	const string getName()const;//姓名
private:
	double balance;//余额
	int cnumber;//卡号
	string name;//姓名
	vector<string> log;//日志
};

class campus_card :public card{
public:
	campus_card();
	~campus_card();
	void pay();//支付
	void inquire();//查询
	void setSnumber(int num);//设置学号
	void setAcademy(string str);//设置学院
	void setBinding(int num);//设置绑定卡
	void deleteBinding(int num);//删除绑定卡
	const int getSnumber()const;//学号
	const string getAcademy()const;//学院
	const int getBindnumber()const;
	const int getBinding(int i)const;
private:
	int snumber;//学号
	int bindnumber;//绑定卡数量
	string academy;//学院
	vector<int> binding;//绑定的卡
};

class deposit_card :public card {
public:
	deposit_card();
	~deposit_card();
	void pay();//支付
	void inquire();//查询
	void setBinding(int num);//设置绑定卡（被动设置）
	void deleteBinding(int num);//删除绑定卡
	void setCredit(double num);//设置信用额度
	void setDate(string str);//设置发卡日期
	const double getCredit()const;//设置信用额度
	const string getDate()const;//发卡日期
	const int getBindnumber()const;
	const int getBinding(int i)const;
private:
	double credit;//透支额度
	int bindnumber;
	string date;//发卡日期
	vector<int> binding;//绑定的卡
};
