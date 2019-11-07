#include "pch.h"
#include "client.h"

using namespace std;

int main() {
	Load();
	int flag = 0;
	string str;
	while (flag == 0) {
		system("CLS");
		Printmenu();
		cin >> str;
		if      (str == "1")	Plus();
		else if (str == "2")	Minus();
		else if (str == "3")	Multiply();
		else if (str == "4")	Evaluate();
		else if (str == "5")	Derivation();
		else if (str == "6")	Compare();
		else if (str == "7")	AddPoly();
		else if (str == "8")	DeletePoly();
		else if (str == "9")	PolyList();
		else if (str == "0") {
			SaveAndExit();
			flag = 1;
		}
		else
			cout << "请输入正确的整数！" << endl;
	}
	cout << "感谢使用，正在保存并退出。。。" << endl;
	Sleep(666);
	return 0;
}


