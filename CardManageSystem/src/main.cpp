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
				C_Menu();	//У԰���˵�
				cin >> str1;
				if (str1 == "1")	C_New();//�½�У԰��
				else if (str1 == "2")	C_Inquire();//��ѯУ԰��
				else if (str1 == "3")	C_Charge();//У԰����ֵ
				else if (str1 == "4")	C_Bind();//�󶨿�����
				else if (str1 == "5")	C_Delete();//ɾ��У԰��
				else if (str1 == "0")
					flag1 = false;
				else
					cout << "��������ȷ��������" << endl;
			}
		}
		else if (str0 == "2") {
			bool flag1 = true;
			while (flag1) {
				system("CLS");
				D_Menu();	//����˵�
				cin >> str1;
				if (str1 == "1")	D_New();//�½����
				else if (str1 == "2")	D_Inquire();//��ѯ���
				else if (str1 == "3")	D_Charge();//�����ֵ
				else if (str1 == "4")	D_Delete();//ɾ�����
				else if (str1 == "0")
					flag1 = false;
				else
					cout << "��������ȷ��������" << endl;
			}
		}
		else if (str0 == "3") {
			bool flag1 = true;
			while (flag1) {
				system("CLS");
				U_Menu();	//�û��˵�
				cin >> str1;
				if (str1 == "1" && isadmin)	U_Add();//�½��û�
				else if (str1 == "2")	U_Manage();//��������
				else if (str1 == "3" && isadmin)	U_Delete();//ɾ���û�
				else if (str1 == "0")
					flag1 = false;
				else {
					cout << "���������޲���Ȩ�ޣ�" << endl;
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
			cout << "��������ȷ��������" << endl;
	}
	cout << "��лʹ�ã����ڱ��沢�˳�������" << endl;
	Sleep(666);
	return 0;
}

