#pragma once
#include <string>
using namespace std;



struct account
{
	string user_name;
	string password;
	int admi;
	account() : user_name(""), password(""), admi(0), next(nullptr) {};
	account(string _user_name, string _code, int _adimi) :
		user_name(_user_name), password(_code), admi(_adimi), next(nullptr){};
	account* next;
};


account* Init_account();
void print_account(account* acc);
void print_all_accounts();
void Add_user_account(string new_user_name, string new_password, int new_admi);
account* Search_user_account(string name);
void Modify_user_account(string name);
bool Delete_user_account(string name);
