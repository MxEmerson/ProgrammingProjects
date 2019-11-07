#pragma once
#include "pch.h"
using namespace std;

class User {
public:
	User();
	~User();
	const string getName()const;
	const string getPassword()const;
	virtual bool isAdmin();
	void setName(string str);
	void setPassword(string str);
private:
	string name;
	string password;
};

class Admin :public User {
public:
	Admin();
	~Admin();
	bool isAdmin();
};