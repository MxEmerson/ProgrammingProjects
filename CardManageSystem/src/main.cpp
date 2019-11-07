#include "pch.h"
#include "client.h"

using namespace std;

int main() {
	Load();
	bool isadmin = Login();
	bool flag = true;
	string str0,str1;
	while (flag) {
		system("CLS");
		Menu();
		cin >> str0;
		if (str0 == "1") {
			bool flag1 = true;
			while (flag1) {
				system("CLS");
				C_Menu();	//校园卡菜单
				cin >> str1;
				if (str1 == "1")	C_New();//新建校园卡
				else if (str1 == "2")	C_Inquire();//查询校园卡
				else if (str1 == "3")	C_Charge();//校园卡充值
				else if (str1 == "4")	C_Bind();//绑定卡管理
				else if (str1 == "5")	C_Delete();//删除校园卡
				else if (str1 == "0")
					flag1 = false;
				else
					cout << "请输入正确的整数！" << endl;
			}
		}
		else if (str0 == "2") {
			bool flag1 = true;
			while (flag1) {
				system("CLS");
				D_Menu();	//储蓄卡菜单
				cin >> str1;
				if (str1 == "1")	D_New();//新建储蓄卡
				else if (str1 == "2")	D_Inquire();//查询储蓄卡
				else if (str1 == "3")	D_Charge();//储蓄卡充值
				else if (str1 == "4")	D_Delete();//删除储蓄卡
				else if (str1 == "0")
					flag1 = false;
				else
					cout << "请输入正确的整数！" << endl;
			}
		}
		else if (str0 == "3") {
			bool flag1 = true;
			while (flag1) {
				system("CLS");
				U_Menu();	//用户菜单
				cin >> str1;
				if (str1 == "1" && isadmin)	U_Add();//新建用户
				else if (str1 == "2")	U_Manage();//更改密码
				else if (str1 == "3" && isadmin)	U_Delete();//删除用户
				else if (str1 == "0")
					flag1 = false;
				else {
					cout << "输入错误或无操作权限！" << endl;
					Sleep(666);
				}	
			}
		}
		else if (str0 == "4")	Pay();
		else if (str0 == "0") {
			SaveAndExit();
			flag = false;
		}
		else
			cout << "请输入正确的整数！" << endl;
	}
	cout << "感谢使用，正在保存并退出。。。" << endl;
	Sleep(666);
	return 0;
}

