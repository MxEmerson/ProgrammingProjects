#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include "pch.h"

void Load();		//加载常用多项式

void Printmenu();	//打印菜单

int Examine(std::string str);		//检查多项式输入是否合法

void Plus();		//多项式加法

void Minus();		//多项式减法

void Multiply();	//多项式乘法

void Evaluate();	//多项式求值

void Derivation();	//多项式求导

void Compare();		//多项式比较

void AddPoly();		//添加常用多项式

void DeletePoly();	//删除常用多项式

void PolyList();	//查看常用多项式

void SaveAndExit();	//保存并提出

#endif