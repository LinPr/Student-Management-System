#pragma once
#include <string>
using namespace std;

struct student
{

	string name;
	unsigned int id;
	int age;
	int gender; //femeal = false, male = true

	student* next;

	student() :name(""), id(0), age(0), gender(0), next(nullptr) {};
	student(string _name, unsigned int _id, int _age, int _gender) :
		name(_name), id(_id), age(_age), gender(_gender), next(nullptr) {};
};



void print_student(student* stu);
void print_all_students();
//按学号顺序插入指定位置
student* Init_student();

void Add_student(string new_name, unsigned int new_id, int new_age, int new_gender);

bool Search_all(string name);
student* Search_by_name(string name);
student* Search_by_id(unsigned int id);

//按照学生的id查找,找到后修改
bool Modify_student(unsigned int id);

//删除指定学生的信息
bool Delete_student(unsigned int id);

