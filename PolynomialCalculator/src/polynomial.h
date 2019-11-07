#pragma once
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "pch.h"

using namespace std;

class Poly {
private:
	int term;
	double coef[100];
	int power[100];
	bool isnamed;
	string name;
	string polystr;
	string printstr;
public:
	Poly();
	~Poly();
	Poly(string str);
	Poly(Poly& poly1, Poly& poly2, int oper);
	const int getTerm() const;
	const bool getIsnamed() const;
	const string getName() const;
	const string getPolystr() const;
	const string getPrintstr() const;
	void transnumber();
	void transpoly(string str);
	bool havename(string str);
	void setname();
	void setpoly(string str);
	void derivate();
	double evaluate(double x);
	string transprint();
};

#endif