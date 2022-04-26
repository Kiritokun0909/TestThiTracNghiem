#include "Subject.h"

//Cau truc mon
//Copy constructor
Subject::Subject(string _id, string _name)
{
	this->id = _id;
	this->name = _name;
}
Subject::Subject(Subject* other) { *this = *other; }

string Subject::getId() const 
{
	return id;
}

void Subject::setId(string _id) 
{
	this->id = _id;
}

string Subject::getName() const 
{
	return name;
}

void Subject::setName(string _name)
{
	this->name = _name;
}

//Cau truc danh sach mon
//Functions
Subject* ListSubject::GetNode(int pos)
{
	if (pos < 0 || pos >= size) return nullptr;
	return nodes[pos];
}



bool  ListSubject::SearchByID(int pos, string id) {
	return nodes[pos]->getId() == id;
}
bool  ListSubject::SearchByName(int pos, string name) {
	return nodes[pos]->getName() == name;
}
Subject* ListSubject::SearchSubject(string s, ListSubject* obj, bool(ListSubject::* cmp)(int, string))
{
	for (int i = 0; i < size; i++)
		if ((obj->*cmp)(i, s)) return nodes[i];

	return nullptr;
}

void ListSubject::ClearList()
{
	for (int i = 0; i < MAX_LIST; i++) delete nodes[i];
	size = 0;
}

int ListSubject::StringCompare(const string& s1, const string& s2)
{
	//return: 	1 means s1 > s2, 
	//			0 means s1 == s2, 
	//			-1 means s1 < s2.

	int len1 = s1.size(), len2 = s2.size();
	for (int i = 0; i < len1 && i < len2; i++)
	{
		if (s1[i] < s2[i]) return -1;	//First character that s1 < s2
		else if (s1[i] > s2[i]) return 1;	//First character that s1 > s2
	}

	if (len1 == len2) return 0;	//s1 == s2: abc == abc
	if (len1 < len2) return -1;	//s1 < s2: abc < abcd
	return 1;	//s1 > s2: abcd > abc
}
int ListSubject::AddSubject(Subject new_sub)
{
	//return: 	1 them thanh cong, 
	//			0 them khong thanh cong do bi trung, 
	//			-1 them khong thanh cong do mang da day.

	if (size == MAX_LIST) return -1;

	string id = new_sub.getId();
	int pos = size, cmp;
	for (int i = 0; i < size; i++)
	{
		cmp = ListSubject::StringCompare(nodes[i]->getId(), id);
		if (cmp == 1)
		{
			pos = i;
			break;
		}
		else if (cmp == 0)
			return 0;
	}

	//Dich cac phan tu sang phai
	for (int i = size; i > pos; i--)
		nodes[i] = nodes[i - 1];

	//Them vao vi tri pos
	nodes[pos] = new Subject(new_sub);
	size++;
	return 1;	//Them thanh cong
}


int ListSubject::AddSubjectAt(Subject new_sub, int pos)
{
	//Khong the them mon hoc vi da day danh sach
	//Hoac do vi tri muon them nhap sai
	if (size == MAX_LIST || pos < 0) return 0;

	if (size == 0) pos = size; //Mang rong
	else if (pos > size) pos = size; //Neu pos > size thi them vao cuoi
	for (int i = size; i > pos; i--) nodes[i] = nodes[i - 1];
	nodes[pos] = new Subject(new_sub);
	size++;
	//Them thanh cong
	return 1;
}
int ListSubject::DelSubjectAt(int pos)
{
	//Khong the xoa vi danh sach rong
	//Hoac do vi tri muon xoa nhap sai
	if (pos < 0 || pos >= size) return 0;

	for (int i = pos; i < size; i++) nodes[i] = nodes[i + 1];
	//nodes[size - 1] = nullptr;	//Khong can vi mang con tro tu dong lam
	size--;
	//Xoa thanh cong
	return 1;
}


int ListSubject::ChangeSubjectId(string id, int pos)
{
	if (pos < 0 || pos >= size || id.size() > 15) return 0;

	nodes[pos]->setId(id);
	//Thay doi thanh cong
	return 1;
}
int ListSubject::ChangeSubjectName(string name, int pos)
{
	if (pos < 0 || pos >= size) return 0;

	nodes[pos]->setName(name);
	//Thay doi thanh cong
	return 1;
}


