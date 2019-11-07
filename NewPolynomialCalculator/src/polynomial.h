#pragma once
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "pch.h"

using namespace std;

class Poly {
private:
	int term;//项数
	double coef[100];//系数
	int power[100];//次数
	string polystr;//字符串形式
public:
	Poly();
	~Poly();
	Poly(string str);
	void transpoly(string str);//提取字符串数据
	void transstr();//将数据转换为字符串
	string transimple(string s);//将字符串简化（去掉多余的0和小数点）
	Poly operator + (Poly& poly2);
	Poly operator - (Poly& poly2);
	Poly operator * (Poly& poly2);
	void derivate();//求导
	double evaluate(double x);//求值
	const int getTerm() const;
	const string getPolystr() const;
};

#endif