#include "pch.h"
#include "client.h"

using namespace std;

int main() {
	string str;
	while (1) {
		system("CLS");
		Printmenu();
		cin >> str;
		if (str == "1")	Operation(1);
		else if (str == "2")	Operation(2);
		else if (str == "3")	Operation(3);
		else if (str == "4")	Evaluate();
		else if (str == "5")	Derivation();
		else if (str == "0")
			break;
		else
			cout << "��������ȷ��������" << endl;
	}
	cout << "��лʹ�ã������˳�������" << endl;
	Sleep(666);
	return 0;
}
