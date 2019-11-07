#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include "pch.h"

void Printmenu();	//打印菜单

bool Examine(std::string str);		//检查多项式输入是否合法

void Operation(int oper);		//多项式运算

void Evaluate();	//多项式求值

void Derivation();	//多项式求导


#endif