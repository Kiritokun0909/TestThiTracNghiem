#pragma once
#include <iostream>
#include <string>
#include "StudentScript.h"
using namespace std;
#define MAX_LIST 10000

class Class
{
public:
	//Constructor
	Class() { id = "", name = "", listStudent = nullptr; }
	~Class() { }

	//Setter
	void setAll(string _id, string _name);
	void setId(string _id) { this->id = _id; }
	void setName(string _name) { this->name = _name; }
	void setList(ListStudent* _other) { this->listStudent = _other; }

	//Getter
	string getId() { return id; }
	string getName() { return name; }
	ListStudent* getListStudent() { return listStudent; }

private:
	string id;
	string name;
	ListStudent* listStudent;	//Lop tro den danh sach sinh vien
};

class ListClass
{
private:
	Class nodes[MAX_LIST];	//Danh sach tuyen tinh
	int size = 0;
public:
	//Constructor & Destructor
	ListClass() { }
	~ListClass() { }

	int GetSize() const;
	Class* GetNode(int index);

	bool SearchByID(int, string);
	bool SearchByName(int, string);
	Class* SearchClass(string str, ListClass* listClass, bool(ListClass::* cmp)(int, string));

	int StringCompare(const string& str1, const string& str2);
	int AddClass(Class new_class);	//Them theo trinh tu
	int DeleteClass(int index);	//Xoa o vi tri
};