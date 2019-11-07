#pragma once
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "pch.h"

using namespace std;

class Poly {
private:
	int term;//����
	double coef[100];//ϵ��
	int power[100];//����
	string polystr;//�ַ�����ʽ
public:
	Poly();
	~Poly();
	Poly(string str);
	void transpoly(string str);//��ȡ�ַ�������
	void transstr();//������ת��Ϊ�ַ���
	string transimple(string s);//���ַ����򻯣�ȥ�������0��С���㣩
	Poly operator + (Poly& poly2);
	Poly operator - (Poly& poly2);
	Poly operator * (Poly& poly2);
	void derivate();//��
	double evaluate(double x);//��ֵ
	const int getTerm() const;
	const string getPolystr() const;
};

#endif