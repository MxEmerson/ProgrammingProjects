#pragma once
#include"pch.h"

void Printmenu();	//打印菜单

bool Examine(std::string str);		//检查输入是否合法

int Pr(char ch);

int Operate(int first, int second, char op);

void Operation(std::string str);		//运算并输出结果