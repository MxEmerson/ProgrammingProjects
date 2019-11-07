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
			cout << "请输入正确的表达式！" << endl;
	}
	cout << "感谢使用，正在退出。。。" << endl;
	Sleep(666);
	return 0;
}