#pragma once
#include"pch.h"

bool Login();//��¼
void Load();//����
void Menu();//���˵�

void Pay();//֧��

void C_Menu();//У԰���˵�
void C_New();//�½�У԰��
void C_Inquire();//��ѯУ԰��
void C_Charge();//У԰����ֵ
void C_Bind();//�󶨿�����
void C_Delete();//ɾ��У԰��

void D_Menu();//����˵�
void D_New();//�½����
void D_Inquire();//��ѯ���
void D_Charge();//�����ֵ
void D_Credit();//���ö�ȹ���
void D_Delete();//ɾ�����

void U_Menu();//�û�����˵�
void U_Add();//�½��û�
void U_Manage();//��������
void U_Delete();//ɾ���û�

bool Examine(int num);
bool Examine(double money);
bool Examine(std::string str);

std::string getTime();

void SaveAndExit();//���沢�˳�
