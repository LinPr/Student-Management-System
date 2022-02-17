#define _CRT_SECURE_NO_WARNINGS

#include "students.h"
#include "accounts.h"
#include "interface.h"
#include <string>
#include <iostream>

using namespace std;
extern account* acc_head;
extern student* stu_head;


//定义文件存放的位置

const char config_txt[] = "./config.txt";
//const char students_txt[] = "./students.txt";
//const char accounts_txt[] = "./accounts.txt";
char file_students_path[20];
char file_accounts_path[20];


//从配置文件加载账户信息到内存空间
void Interface_init()
{
	//首先先创建另外两个文件存储的信息，config文件一定存在
	FILE* file_config = fopen(config_txt, "r");
	if (file_config == NULL) {
		printf("Cannot open %s\n", config_txt);
		exit(1);
	}
	printf("open %s successfully\n", config_txt);
	//fclose(file_config);
	File_read_config(file_config);

	printf_welcome();

	File_read_students();
	File_read_accounts();

	Login_account();
}

void File_read_config(FILE* file_config)
{


	//读取config文件里面存储的另外两个文件的路径
	file_config = fopen(config_txt, "r");
	fscanf(file_config, "%s%s", file_students_path, file_accounts_path);
	
	printf("%s\n", file_students_path);
	printf("%s\n", file_accounts_path);
	fclose(file_config);

	//按照路径打开另外两个文件
	FILE* file_students = fopen(file_students_path, "r");
	if (file_students == NULL)
	{
		//如果文件不存在就创建一个空文件
		file_students = fopen(file_students_path, "w");
		printf("create a empty %s file\n", file_students_path);
	}
	fclose(file_students);

	FILE* file_accounts = fopen(file_accounts_path, "r");
	if (file_accounts == NULL)
	{
		//如果文件不存在就创建一个空文件
		file_accounts = fopen(file_accounts_path, "w");
		printf("create a empty %s file\n", file_accounts_path);
	}
	fclose(file_accounts);

}


//格式化读取数据到内存
void File_read_students()
{
	FILE* file_students = fopen(file_students_path, "r");
	if (file_students == NULL) {
		printf("Cannot open %s\n", file_students_path);
		exit(1);
	}
	printf("open %s successfully\n", file_students_path);

	Init_student();

	char name[15];	unsigned int id;	int age;	int gender;

	while (fscanf(file_students, "%s %u %d %d", name, &id, &age, &gender) != EOF)
	{
		//这个add可以用与将从文件读取的students加入内存
		//也可用与在程序运行时将学生信息加入内存
		Add_student(name, id, age, gender);
	}
	
	fclose(file_students);

	print_all_students();

}
void File_read_accounts()
{
	FILE* file_accounts = fopen(file_accounts_path, "r");
	if (file_accounts == NULL) {
		printf("Cannot open %s\n", file_accounts_path);
		exit(1);
	}
	printf("open %s successfully\n", file_accounts_path);

	Init_account();

	char user_name[15];	char password[15];	int admi;

	while (fscanf(file_accounts, "%s%s%d", user_name, password, &admi) != EOF)
	{
		//这个add可以用与将从文件读取的students加入内存
		//也可用与在程序运行时将学生信息加入内存
		Add_user_account(user_name, password, admi);
	}

	fclose(file_accounts);

	print_all_accounts();

}

void file_save_all()
{
	save_students();
	save_accounts();
}
void save_students()
{
	FILE* file_students = fopen(file_students_path, "w");
	if (file_students == NULL) {
		printf("Cannot write %s\n", file_students_path);
		exit(1);
	}
	student* tmp = stu_head->next;
	while (tmp != nullptr)
	{
		const char* name = tmp->name.data();
		fprintf(file_students, "%s\n%u\n%d\n%d\n", name, tmp->id, tmp->age, tmp->gender);
		tmp = tmp->next;
	}
	fclose(file_students);
	printf("saved all students' information to %s\n", file_students_path);
}

void save_accounts()
{
	FILE* file_accounts = fopen(file_accounts_path, "w");
	if (file_accounts == NULL) {
		printf("Cannot write %s\n", file_accounts_path);
		exit(1);
	}
	account* tmp = acc_head->next;
	while (tmp != nullptr)
	{
		const char* user_name = tmp->user_name.data();
		const char* password = tmp->password.data();
		fprintf(file_accounts, "%s\n%s\n%d\n", user_name, password, tmp->admi);
		tmp = tmp->next;
	}
	fclose(file_accounts);
	printf("saved all accounts' information to %s\n", file_accounts_path);

}





//对比输入的账户信息是否在内存
void Login_account()
{
	account* tmp = printf_login();
	
	if (tmp == nullptr)
	{
		cout << "login failed !" << endl;
		return;
	}
	//如果是管理员账户，调用  menu_for_admi() 接口 
	if (tmp->admi == 1)
	{
		menu_for_admi();
	}
	else  //如果是普通用户，就调用 menu_for_user()接口
	{
		menu_for_user();
	}
	

}


//
void menu_for_user()
{
	int number;
	while (1)
	{
		cout << "*****	 this is a menu for users   *****" << endl;
		cout << "	1. search student by name" << endl;
		cout << "	2. search student by id" << endl;
		cout << "	3. exit" << endl << endl;

		cout << "check the menu and enter a number" << endl;
		cin >> number;

		switch (number)
		{
		case 1: {
			cout << "please enter name that you want to search " << endl;
			string name; cin >> name;
			student* stu = Search_by_name(name);
			print_student(stu);
		}break;
		case 2: {
			cout << "please enter id that you want to search " << endl;
			int id; cin >> id;
			student* stu = Search_by_id(id);
			print_student(stu);
		}break;
		case 3: {
			exit(0);
		}break;
		default:;
		}
	}
}

void menu_for_admi()
{
	int number;
	while (1)
	{
		cout << "*****	 this is a menu for admi   *****" << endl;
		cout << "	0. more options" << endl;
		cout << "	1. search student by name" << endl;
		cout << "	2. search student by id" << endl;
		cout << "	3. exit" << endl << endl;



		cout << "check the menu and enter a number" << endl;

		cin >> number;

		switch (number)
		{
		case 0:submenu_for_admi(); break;
		case 1: {
			cout << "please enter name that you want to search " << endl;
			string name; cin >> name;
			student* stu = Search_by_name(name);
			print_student(stu);
		}break;
		case 2: {
			cout << "please enter id that you want to search " << endl;
			int id; cin >> id;
			student* stu = Search_by_id(id);
			print_student(stu);
		}break;
		case 3: {
			exit(0);
		}break;
		default:;
		}
	
	}
}
void submenu_for_admi()
{

	int number;
	while (1)
	{
		cout << "*****	 more options   *****" << endl;
	
		cout << "	0.print all students and all accounts" << endl;
		cout << "	1. add student information" << endl;
		cout << "	2. modify student information" << endl;
		cout << "	3. delete student information" << endl;
		cout << "	4. add user account " << endl;
		cout << "	5. modify user account " << endl;
		cout << "	6. delete user account " << endl;
		cout << "	7. search user account " << endl;
		cout << "	8. return " << endl;
		cout << "	9. exit " << endl;


		cout << "check the menu and enter a number" << endl;
		cin >> number;
		switch (number)
		{
		case 0: {
			print_all_students();
			print_all_accounts();
		}break;
		case 1: {
			cout << "please enter \"name, id, age, gender\" in order" << endl;
			string new_name; unsigned int new_id; int new_age; int new_gender;
			cin >> new_name >> new_id >> new_age >> new_gender;
			Add_student(new_name, new_id, new_age, new_gender);
		}break;
		case 2: {
			cout << "please enter the \"id\" of student that u want to modify" << endl;
			int id; cin >> id;
			Modify_student(id);
		}break;
		case 3: {
			cout << "please enter the \"id\" of student that u want to delete" << endl;
			int id; cin >> id;
			Delete_student(id);
		}break;
		case 4: {
			cout << "please enter \"user_name, password, admi_power\" in order" << endl;
			string user_name; string password; int admi_power;
			cin >> user_name >> password >> admi_power;
			Add_user_account(user_name, password, admi_power);
		}break;
		case 5: {
			cout << "please enter \"user_name\" that u want to modify" << endl;
			string name; cin >> name;
			Modify_user_account(name);
		}break;
		case 6: {
			cout << "please enter \"user_name\" that u want to delete" << endl;
			string user_name; cin >> user_name;
			Delete_user_account(user_name);
		}break;
		case 7: {
			cout << "please enter \"user_name\" that u want to search" << endl;
			string user_name; cin >> user_name;
			Search_user_account(user_name);
		}break;
		case 8: {
			file_save_all();
			return;
		}break;
		case 9: {
			file_save_all();
			exit(0);
		}
		default:;

		};
	}
}


void printf_welcome()
{
	printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf(" *                                                   *\n");
	printf(" *              Student-Management-System            *\n");
	printf(" *                                                   *\n");
	printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
}

account* printf_login()
{
	printf("	* please enter user_name:\n");


	string user_name;
	cin >> user_name;
	account* tmp = Search_user_account(user_name);
	
	
	if (tmp == nullptr)
	{
		cout << "	* user_name error !" << endl;
		return nullptr;
	}

	printf("	* please enter password :\n");
	string password;
	cin >> password;
	if (password == tmp->password)
	{
		cout << "	* success! welcome to you " << tmp->user_name << endl;
	}
	return tmp;
}