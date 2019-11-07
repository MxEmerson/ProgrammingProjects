#include "polynomial.h"

Poly::Poly()
{
	term = 0;
	polystr = "0";
}

Poly::~Poly()
{
}

Poly::Poly(string str)
{
	transpoly(str);
}

void Poly::transpoly(string str) {
	string tempstr;
	double numbers[202] = { 0 };
	memset(coef, 0, sizeof(double) * 100);
	memset(power, 0, sizeof(int) * 100);
	int i = 0, j = 0;
	while (i < str.size()) {
		tempstr = "";
		while (str[i] != 'x' && i < str.size()) {
			tempstr += str[i];
			i++;
		}
		if (tempstr.size() == 0)
			numbers[j] = 1;
		else if (tempstr == "-")
			numbers[j] = -1;
		else
			numbers[j] = stod(tempstr);
		j++;
		if (i >= str.size())
			break;
		else
			i+=2;

		tempstr = "";
		while ((str[i] != '+' && str[i] != '-') && i < str.size()) {
			tempstr += str[i];
			i++;
		}
		numbers[j] = stoi(tempstr);
		j++;
		if (i >= str.size())
			break;
	}
	term = 0;
	for (int l = 0, k = 0; l < j / 2; l++, k += 2) {
		coef[l] = numbers[k];
		power[l] = numbers[k + 1];
		term++;
	}
	transstr();
}

void Poly::transstr()
{
	polystr = "";
	for (int i = 0; i < term; i++) {
		if (coef[i] > -0.000001 && coef[i] < 0.000001)
			continue;
		if (coef[i] > 0 && i > 0)
			polystr += "+";
		polystr += transimple(to_string(coef[i]));
		if (power[i] > 1) {
			polystr += "x^";
			polystr += to_string(power[i]);
		}
		else if (power[i] == 1) {
			polystr += "x";
		}
	}
}

string Poly::transimple(string numstr)
{
	int length = numstr.size();
	for (string::iterator i = numstr.end()-1; i!=numstr.begin(); i--){
		if (*i == '0') {
			numstr.erase(i);
		}
		else if (*i == '.'){
			numstr.erase(i);
			return numstr;
		}
		else{
			return numstr;
		}
	}
}

Poly Poly::operator+(Poly& poly2)
{
	Poly poly;
	int terms = 0;
	for (int i = 0 ,j = 0; i < 100 && this->coef[i] != 0; i++) {
		bool flag = true;
		for (; j < 100 && poly2.coef[j] != 0; j++) {
			if (poly2.power[j] > this->power[i]) {
				poly.coef[terms] = poly2.coef[j];
				poly.power[terms] = poly2.power[j];
				terms++;
				flag = true;
			}
			else if (poly2.power[j] == this->power[i]) {
				poly.coef[terms] = this->coef[i] + poly2.coef[j];
				poly.power[terms] = poly2.power[j];
				terms++;
				flag = false;
			}
			else
				break;
		}
		if (flag) {
			poly.coef[terms] = this->coef[i];
			poly.power[terms] = this->power[i];
			terms++;
		}
	}
	poly.term = terms;
	poly.transstr();
	return poly;
}

Poly Poly::operator-(Poly& poly2)
{
	for (int i = 0; i < 100 && poly2.coef[i] != 0; i++) {
		poly2.coef[i] = 0 - poly2.coef[i];
	}
	Poly poly;
	int terms = 0;
	for (int i = 0, j = 0; i < 100 && this->coef[i] != 0; i++) {
		bool flag = true;
		for (; j < 100 && poly2.coef[j] != 0; j++) {
			if (poly2.power[j] > this->power[i]) {
				poly.coef[terms] = poly2.coef[j];
				poly.power[terms] = poly2.power[j];
				terms++;
				flag = true;
			}
			else if (poly2.power[j] == this->power[i]) {
				poly.coef[terms] = this->coef[i] + poly2.coef[j];
				poly.power[terms] = poly2.power[j];
				terms++;
				flag = false;
			}
			else
				break;
		}
		if (flag) {
			poly.coef[terms] = this->coef[i];
			poly.power[terms] = this->power[i];
			terms++;
		}
	}
	poly.term = terms;
	poly.transstr();
	return poly;
}

Poly Poly::operator*(Poly& poly2)
{
	Poly poly;
	int terms = 0;
	double tempcoef[202];
	int tempower[202];
	for (int i = 0; i < 100 && this->coef[i] != 0; i++) {
		for (int j = 0; j < 100 && poly2.coef[j] != 0; j++) {
			tempcoef[terms] = this->coef[i] * poly2.coef[j];
			tempower[terms] = this->power[i] + poly2.power[j];
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
		cout << "³¤¶ÈÒç³ö¡£" << endl;
		Poly errorpoly;
		return errorpoly;
	}
	for (int i = 0; i < terms; i++) {
		poly.coef[i] = tempcoef[i];
		poly.power[i] = tempower[i];
	}
	poly.term = terms;
	for (int i = 0; i < poly.term - 1; i++) {
		if (poly.power[i] == poly.power[i + 1]) {
			poly.coef[i] += poly.coef[i + 1];
			for (int j = i + 1; j < poly.term; j++) {
				poly.coef[j] = poly.coef[j + 1];
				poly.power[j] = poly.power[j + 1];
				poly.coef[j + 1] = 0;
				poly.power[j + 1] = 0;
			}
			poly.term--;
		}
	}
	poly.transstr();
	return poly;
}

void Poly::derivate()
{
	for (int i = 0; i < term; i++) {
		coef[i] *= power[i];
		power[i] -= 1;
		if (power[i] == -1) {
			power[i]++;
			term--;
		}
	}
	this->transstr();
}

double Poly::evaluate(double x)
{
	double value = 0;
	for (int i = 0; i < term; i++) {
		value += pow(x, power[i]) * coef[i];
	}
	return value;
}

const int Poly::getTerm() const
{
	return term;
}

const string Poly::getPolystr() const
{
	return polystr;
}
