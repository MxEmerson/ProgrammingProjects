#include"pch.h"
#include"client.h"
using namespace std;

int main() {
	string str;
	while (1) {
		system("CLS");
		Printmenu();
		cin >> str;
		if (str == "0")	break;
		else if (Examine(str))	Operation(str);
		else
			cout << "��������ȷ�ı��ʽ��" << endl;
	}
	cout << "��лʹ�ã������˳�������" << endl;
	Sleep(666);
	return 0;
}