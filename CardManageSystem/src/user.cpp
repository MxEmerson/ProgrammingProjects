#include "user.h"
#include "pch.h"

User::User(){
	password = "000000";
}

User::~User(){
}

const string User::getName() const{
	return name;
}

const string User::getPassword() const{
	return password;
}

bool User::isAdmin(){
	return false;
}

void User::setName(string str){
	name = str;
}

void User::setPassword(string str){
	password = str;
}

Admin::Admin(){
	this->setPassword("000000");
}

Admin::~Admin(){
}

bool Admin::isAdmin(){
	return true;
}
