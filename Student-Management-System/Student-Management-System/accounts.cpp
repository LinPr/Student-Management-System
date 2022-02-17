#include "accounts.h"
#include <iostream>


//this is a dummy accout
account* acc_head;


account* Init_account()
{
	acc_head = new account();

	if (acc_head == nullptr)
	{
		cout << "Initialize failed !" << endl;
		exit(1);
	}
	cout << "Initialize a stu_head node, this is a dummuy node" << endl;
	return acc_head;
}

void print_account(account* acc)
{
	printf("	   * * * * * * * * * *\n");
	cout << "	   * user_name :  " << acc->user_name << "     *" << endl;
	cout << "	   * prassword :  " << acc->password << endl;
	cout << "	   *   power   :  " << (acc->admi == 1 ? "admi" : "user") << endl;
	printf("	   * * * * * * * * * *\n");
	printf("\n");

}
void print_all_accounts()
{
	cout << "************  print all account:   ***********" << endl << endl;
	account* tmp = acc_head->next;
	while (tmp)
	{
		print_account(tmp);
		tmp = tmp->next;
	}
	cout << "***********************************************" << endl;
}
void Add_user_account(string new_user_name, string new_password, int new_admi)
{
	account* acc = new account(new_user_name, new_password, new_admi);
	acc->next = acc_head->next;
	acc_head->next = acc;
	cout << "you added a new account :" << endl;
	print_account(acc);

}
account* Search_user_account(string name)
{
	account* tmp;
	for (tmp = acc_head->next; tmp != nullptr; tmp = tmp->next)
	{
		if (tmp->user_name == name)
		{
			cout << "find this account : " << tmp->user_name << endl;
			//print_account(tmp);
			break;
		}
	}
	if (tmp == nullptr)
	{
		cout << "can't find this account : " << name << endl;
	}
	return tmp;
}
void Modify_user_account(string name)
{
	account* tmp = Search_user_account(name);
	if (tmp == nullptr)
	{
		cout << "enter name error" << endl;
		return;
	}
	cout << "please enter \"new user_name, new password \" in order" << endl;
	string new_user_name; string new_password;
	tmp->user_name = new_user_name;
	tmp->password = new_password;

	cout << "student : " << name << "new information after modifying is:" << endl;
	print_account(tmp);

}
bool Delete_user_account(string name)
{
	account* tmp = Search_user_account(name);
	if (tmp == nullptr)
	{
		cout << "Delete_student failed !! " << endl;
		return false;
	}
	account* pre = acc_head;
	while (pre->next != tmp)
	{
		pre = pre->next;
	}
	pre->next = tmp->next;
	cout << "you deleted this account" << endl;
	print_account(tmp);
	delete tmp;
	return true; 
}
