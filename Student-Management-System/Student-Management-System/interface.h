#pragma once
#include "stdio.h"
#include <cstdio>
#include "accounts.h"
using namespace std;


void File_read_config(FILE* file_config);
void File_read_students();
void File_read_accounts();



//�������ļ������˻���Ϣ���ڴ�ռ�
void Interface_init();

//�Ա�������˻���Ϣ�Ƿ����ڴ�
void Login_account();
void printf_welcome();

void menu_for_user();
void menu_for_admi();
void submenu_for_admi();

void file_save_all();
void save_students();
void save_accounts();
account* printf_login();