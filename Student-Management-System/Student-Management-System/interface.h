#pragma once
#include "stdio.h"
#include <cstdio>
#include "accounts.h"
using namespace std;


void File_read_config(FILE* file_config);
void File_read_students();
void File_read_accounts();



//从配置文件加载账户信息到内存空间
void Interface_init();

//对比输入的账户信息是否在内存
void Login_account();
void printf_welcome();

void menu_for_user();
void menu_for_admi();
void submenu_for_admi();

void file_save_all();
void save_students();
void save_accounts();
account* printf_login();