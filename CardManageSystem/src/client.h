#pragma once
#include"pch.h"

bool Login();//登录
void Load();//加载
void Menu();//主菜单

void Pay();//支付

void C_Menu();//校园卡菜单
void C_New();//新建校园卡
void C_Inquire();//查询校园卡
void C_Charge();//校园卡充值
void C_Bind();//绑定卡管理
void C_Delete();//删除校园卡

void D_Menu();//储蓄卡菜单
void D_New();//新建储蓄卡
void D_Inquire();//查询储蓄卡
void D_Charge();//储蓄卡充值
void D_Credit();//信用额度管理
void D_Delete();//删除储蓄卡

void U_Menu();//用户管理菜单
void U_Add();//新建用户
void U_Manage();//更改密码
void U_Delete();//删除用户

bool Examine(int num);
bool Examine(double money);
bool Examine(std::string str);

std::string getTime();

void SaveAndExit();//保存并退出
