#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include "pch.h"

void Load();		//���س��ö���ʽ

void Printmenu();	//��ӡ�˵�

int Examine(std::string str);		//������ʽ�����Ƿ�Ϸ�

void Plus();		//����ʽ�ӷ�

void Minus();		//����ʽ����

void Multiply();	//����ʽ�˷�

void Evaluate();	//����ʽ��ֵ

void Derivation();	//����ʽ��

void Compare();		//����ʽ�Ƚ�

void AddPoly();		//��ӳ��ö���ʽ

void DeletePoly();	//ɾ�����ö���ʽ

void PolyList();	//�鿴���ö���ʽ

void SaveAndExit();	//���沢���

#endif