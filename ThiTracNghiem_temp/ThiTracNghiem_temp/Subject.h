#pragma once
#include <iostream>
#include <string>
using namespace std;
#define MAX_LIST 10000

//STRUCT MON HOC
class Subject
{
public:
	//Constructor & Destructor
	Subject() { };
	~Subject() { };

	//Copy constructor
	Subject(string id, string name);
	Subject(Subject* other_sub);

	//Functions
	string getId() const;
	void setId(string id);

	string getName() const;
	void setName(string name);

private:
	string id = "";	//max id contain 15 characters
	string name = "";
};


//STRUCT DANH SACH MON HOC
class ListSubject
{
private:
	Subject* nodes[MAX_LIST]{ nullptr };
	int size = 0;
public:
	//Constructor & Destructor
	ListSubject() { }
	~ListSubject() { }

	//Functions
	int GetSize() { return this->size; }
	Subject* GetNode(int index);

	bool SearchByID(int, string);
	bool SearchByName(int, string);
	Subject* SearchSubject(string str, ListSubject* listSub, bool(ListSubject::* cmp)(int, string));
	void ClearList();

	//Them mon hoc theo trinh tu id
	int StringCompare(const string& str1, const string& str2);
	int AddSubject(Subject new_Sub);

	//Them mon hoc theo vi tri
	int AddSubjectAt(Subject new_Sub, int index);
	int DelSubjectAt(int index);

	//Thay doi ten/id mon hoc dua vao vi tri
	int ChangeSubjectId(string new_id, int index);
	int ChangeSubjectName(string new_name, int index);
};