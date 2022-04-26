#include "Class.h"

//Cau truc lop
void Class::setAll(string id, string name)
{
	this->id = id;
	this->name = name;
}

//Cau truc danh sach lop
int ListClass::GetSize() const
{
	return size;
}

Class* ListClass::GetNode(int pos)
{
	if (pos < 0 || pos >= size) return nullptr;
	return &nodes[pos];
}


bool ListClass::SearchByID(int pos, string id) {
	return nodes[pos].getId() == id;
}
bool ListClass::SearchByName(int pos, string name) {
	return nodes[pos].getName() == name;
}
Class* ListClass::SearchClass(string s, ListClass* obj, bool(ListClass::* cmp)(int, string))
{
	//Tim kiem tuyen tinh (O(n))
	for (int i = 0; i < size; i++)
		if ((obj->*cmp)(i, s)) { return &nodes[i]; }
	return nullptr;
}


int ListClass::StringCompare(const string& s1, const string& s2)
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
int ListClass::AddClass(Class c)
{
	//return: 	1 them thanh cong, 
	//			0 them khong thanh cong do bi trung, 
	//			-1 them khong thanh cong do mang da day.
	
	if (size == MAX_LIST) return -1;

	//Tim vi tri thich hop de them vao
	string id = c.getId();
	int pos = size, cmp;
	for (int i = 0; i < size; i++)
	{
		cmp = StringCompare(nodes[i].getId(), id);
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
	nodes[pos] = c;
	size++;
	return 1;	//Them thanh cong
}
//Xoa o vi tri
int ListClass::DeleteClass(int pos)
{
	//Cac truong hop khong the xoa
	if (pos < 0 || pos >= size) return 0;

	for (int i = pos; i < size - 1; i++)
	{
		nodes[i] = nodes[i + 1];
	}
	nodes[size - 1].setAll("", "");
	size--;
	return 1;	//Them thanh cong
}