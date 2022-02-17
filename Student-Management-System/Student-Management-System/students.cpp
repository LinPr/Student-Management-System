#include "students.h"
#include <iostream>
#include <cstdio>




//一个dummy结点
student* stu_head;

student* Init_student()
{
	stu_head = new student();
	if (stu_head == nullptr)
	{
		cout << "Initialize failed !" << endl;
		exit(1);
	}
	cout << "Initialize a stu_head node, this is a dummuy node" << endl;
	return stu_head;
}


void print_student(student* stu)
{
	printf("	   * * * * * * * * * *\n"); 
	cout << "	   *  name:  " << stu->name << "     *" << endl;
	printf("	   *   id :  %-8u*\n", stu->id);
	printf("	   *   age:  %-8d*\n",  stu->age);
	printf("	   * genda:  %-8s*\n", (stu->gender == 1 ? "male" : "female"));
	printf("	   * * * * * * * * * *\n");
	printf("\n");
}

void print_all_students()
{
	cout << "************  print all students:   ***********" << endl << endl;
	student* tmp = stu_head->next;
	while (tmp)
	{
		print_student(tmp);
		tmp = tmp->next;
	}
	cout << "***********************************************" << endl;
}

//根据学号从小到大插入链表
void Add_student(string new_name, unsigned int new_id, int new_age, int new_gender)
{
	student* stu_i = new student(new_name, new_id, new_age, new_gender);
	student* pre = stu_head;
	student* cur = stu_head->next;
	while (cur !=nullptr && cur->id < stu_i->id)
	{
		pre = cur;
		cur = cur->next;
	}
	stu_i->next = cur;
	pre->next = stu_i;
	print_student(stu_i);
}

bool Search_all(string name);

//找到的话就返回指向这个节点的指针
student* Search_by_name(string name)
{
	student* tmp;
	for (tmp = stu_head->next; tmp != nullptr ; tmp = tmp->next)
	{
		if (tmp->name == name)
		{
			cout << tmp->name << endl;
			break;
		}
			
	}

	if (tmp == nullptr)
	{
		cout << "can't find this student : " << name << endl;
	}
	return tmp;
	
}
student* Search_by_id(unsigned int id)
{
	student* tmp;
	for (tmp = stu_head->next; tmp != nullptr; tmp = tmp->next)
	{
		if (tmp->id == id)
		{
			cout << tmp->id << endl;
			break;
		}

	}

	if (tmp == nullptr)
	{
		cout << "can't find this student : " << id << endl;
	}
	return tmp;
}


//按照学生的id查找,找到后修改
bool Modify_student(unsigned int id)
{
	student* tmp = Search_by_id(id);
	if (tmp == nullptr)
	{
		cout << "can't find this student : " << id << endl;
		return false;
	}
	
	cout << "please enter \"name, age, gender\" in order" << endl;
	string new_name; int new_age; int new_gender;
	cin >> new_name >> new_age >> new_gender;
	tmp->name = new_name;
	tmp->age = new_age;
	tmp->gender = new_gender;
	
	cout << "student : " << id << "new information after modifying is:" << endl;
	print_student(tmp);
	return true;
}

//删除指定学生的信息
bool Delete_student(unsigned int id)
{
	student* tmp = Search_by_id(id);
	if (tmp == nullptr)
	{
		cout << "Delete_student failed !! " << endl;
		return false;
	}
	student* pre = stu_head;
	while (pre->next != tmp)
	{
		pre = pre->next;
	}
	pre->next = tmp->next;
	cout << "you have deleted this student's information" << endl;
	print_student(tmp);
	delete tmp;
	return true;
}

