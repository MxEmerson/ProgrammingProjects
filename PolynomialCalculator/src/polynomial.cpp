#include "pch.h"
#include "polynomial.h"

using namespace std;
typedef list<Poly> LISTPoly;

Poly::Poly() {
	term = 0;
	memset(coef, 0, sizeof(double)*100);
	memset(power, 0, sizeof(int)*100);
	isnamed = false;
}

Poly::~Poly() {

}

Poly::Poly(string str) {
	term = 0;
	memset(coef, 0, sizeof(double) * 100);
	memset(power, 0, sizeof(int) * 100);
	isnamed = false;
	polystr = str;
	this->transpoly(str);
	if (this->havename(str)) {
		string tempstr = str;
		string::size_type position = tempstr.find("=");
		position++;
		name=tempstr.substr(0, position);
		isnamed = true;
	}
	printstr = this->transprint();
}

void Poly::setpoly(string str) {
	polystr = str;
	this->transpoly(str);
	if (this->havename(str)) {
		string tempstr = str;
		string::size_type position = tempstr.find("=");
		position++;
		name = tempstr.substr(0, position);
		isnamed = true;
	}
	printstr = this->transprint();
}

Poly::Poly(Poly& poly1, Poly& poly2, int oper) {
	isnamed = false;
	term = 0;
	if (oper == 1 || oper == 2) {
		if (oper == 2) {
			for (int i = 0; i < 100 && poly2.coef[i] != 0; i++) {
				poly2.coef[i] = 0 - poly2.coef[i];
			}
		}
		int terms = 0;
		int terms2 = 0;
		for (int i = 0; i < 100 && poly1.coef[i] != 0; i++) {
			bool flag = true;
			for (int j = terms2; j < 100 && poly2.coef[j] != 0; j++) {
				if (poly2.power[j] > poly1.power[i]) {
					coef[terms] = poly2.coef[j];
					power[terms] = poly2.power[j];
					terms++;
					terms2++;
					flag = true;
				}
				else if (poly2.power[j] == poly1.power[i]) {
					coef[terms] = poly1.coef[i] + poly2.coef[j];
					power[terms] = poly2.power[j];
					if (coef[terms] != 0) {
						terms++;
					}
					terms2++;
					flag = false;
				}
				else
					break;
			}
			if (flag) {
				coef[terms] = poly1.coef[i];
				power[terms] = poly1.power[i];
				terms++;
			}
		}
		while (poly2.coef[terms2] != 0) {
			coef[terms] = poly2.coef[terms2];
			power[terms] = poly2.power[terms2];
			terms++;
			terms2++;
		}
		term = terms;
	}
	else if (oper == 3) {
		//乘法
		int terms = 0;
		int terms2 = 0;
		double tempcoef[202];
		int tempower[202];
		for (int i = 0; i < 100 && poly1.coef[i] != 0; i++) {
			for (int j = 0; j < 100 && poly2.coef[j] != 0; j++) {
				tempcoef[terms] = poly1.coef[i] * poly2.coef[j];
				tempower[terms] = poly1.power[i] + poly2.power[j];
				terms++;
			}
		}
		int tempint = 0;
		double tempdouble = 0;
		for (int i = 0; i < terms - 1; i++) 
			for (int j = 0; j < terms - 1 - i; j++) { 
				if (tempower[j] < tempower[j + 1]) { 
					tempint = tempower[j];
					tempdouble = tempcoef[j];
					tempower[j] = tempower[j + 1];
					tempcoef[j] = tempcoef[j + 1];
					tempower[j + 1] = tempint;
					tempcoef[j + 1] = tempdouble;
				}
			}
		for (int i = 0; i < terms - 1; i++) {
			if (tempower[i] == tempower[i + 1]) {
				tempcoef[i] += tempcoef[i + 1];
				for (int j = i + 1; j < terms; j++) {
					tempcoef[j] = tempcoef[j + 1];
					tempower[j] = tempower[j + 1];
					tempcoef[j + 1] = 0;
					tempower[j + 1] = 0;
				}
				terms--;
			}
		}
		if (terms >= 100) {
			cout << "长度溢出。" << endl;
			return;
		}
		for (int i = 0; i < terms; i++) {
			coef[i] = tempcoef[i];
			power[i] = tempower[i];
		}
		term = terms;
		for (int i = 0; i < term - 1; i++) {
			if (power[i] == power[i + 1]) {
				coef[i] += coef[i + 1];
				for (int j = i + 1; j < term; j++) {
					coef[j] = coef[j + 1];
					power[j] = power[j + 1];
					coef[j + 1] = 0;
					power[j + 1] = 0;
				}
				term--;
			}
		}
	}
	printstr = this->transprint();
}

const int Poly::getTerm() const {
	return term;
}

const bool Poly::getIsnamed() const {
	return isnamed;
}

const string Poly::getName() const {
	return name;
}

const string Poly::getPolystr() const {
	return polystr;
}

const string Poly::getPrintstr() const {
	if (printstr.empty())
		return "0";
	return printstr;
}

void Poly::transnumber() {
	polystr = name + "=";
	for (int i = 0; i<term; i++) {
		polystr += "(";
		polystr += to_string(coef[i]);
		polystr += ",";
		polystr += to_string(power[i]);
		polystr += ")";
	}
}

void Poly::transpoly(string str) {
	if (this->havename(str)) {
		string::size_type i = str.find('=');
		name = str.substr(0, i);
		isnamed = true;
	}
	smatch result;
	double numbers[202] = { 0 };
	memset(coef, 0, sizeof(double) * 100);
	memset(power, 0, sizeof(int) * 100);
	string reg("\\-?\\d+(\\.\\d+)?");
	regex pattern1(reg, regex::icase);
	string::const_iterator iter = str.begin();
	string::const_iterator iterEnd = str.end();
	string temp;
	int i = 0;
	while (std::regex_search(iter, iterEnd, result, pattern1)) {
		temp = result[0];
		numbers[i] = stod(temp);
		i++;
		iter = result[0].second;
	}
	term = i / 2;
	for (int j = 0, k = 0; j < i / 2; j++, k += 2) {
		coef[j] = numbers[k];
		power[j] = numbers[k + 1];
	}
}

bool Poly::havename(string str) {
	string pattern{ "^[A-Za-z]\\w*=" };
	regex re(pattern);
	bool ret = regex_match(str, re);
	return ret;
}

void Poly::setname() {
	string str;
	string pattern{ "^[A-Za-z][A-Za-z_]{0,19}$" };
	regex re(pattern);
	cout << "请输入常用多项式的名称：" << endl;
	cin >> str;
	bool ret = regex_match(str, re);
	while (!ret) {
		cout << "格式错误，请输入只包含字母、数字和下划线的名称。" << endl;
		cout << "同时请注意首字符只能是字母，且总长度不大于20个字符。" << endl;
		cin >> str;
		bool ret = regex_match(str, re);
	}
	name = str;
	isnamed = true;
	printstr = this->transprint();
}

void Poly::derivate() {
	for (int i = 0; i < term; i++) {
		coef[i] *= power[i];
		power[i] -= 1;
		if (power[i] == -1) {
			power[i]++;
			term--;
		}
	}
	printstr = this->transprint();
}

double Poly::evaluate(double x) {
	double value = 0;
	for (int i = 0; i < term; i++) {
		value += pow(x, power[i]) * coef[i];
	}
	return value;
}

string Poly::transprint() {
	string str;
	if (isnamed == true)
		str = name + "=";
	for (int i = 0; i<term; i++) {
		if (i != 0 && coef[i] > 0) {
			str += "+";
		}
		string tempstr = to_string(coef[i]);
		string::size_type position = tempstr.find(".");
		position += 2;
		str += tempstr.substr(0, position);
		if (power[i] > 1) {
			str += "x^";
			str += to_string(power[i]);
		}
		else if (power[i] == 1) {
			str += "x";
		}
	}	
	return str;
}