//main����

#include "pch.h"
#include "source.h"

using namespace std;

int main() {
	Loading();
	Login();
	int flag = 0;
	string str;
	while (flag == 0) {
		Menu();
		cin >> str;
		if		(str == "1")	Stock();
		else if (str == "2")	Deliver();
		else if (str == "3")	Empty();
		else if (str == "4")	List();
		else if (str == "5") {
			SaveAndExit();
			flag = 1;
		}
		else
			cout << "��������ȷ��������" << endl;
	}
	cout << "��лʹ�ã����ڱ��沢�˳�������" << endl;
	Sleep(666);
	return 0;
}
