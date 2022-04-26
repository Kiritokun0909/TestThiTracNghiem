#pragma once
#include "Subject.h"
#include "LinkedList.h"
#include <iostream>
using namespace std;

class Mark
{
public:
	//Getter/Setter fucntions
	float getMark() const;
	void setMark(float mark);

	Subject* getSubject() const;
	void setSubject(Subject* new_sub);

	//Constructor
	Mark();
	Mark(Subject* ptrSubject, float mark);

private:
	Subject* idSubject;
	float mark;
};



class ListMark
{
private:
	LinkedList<Mark> listMark;
public:
	ListMark();
	~ListMark();

	int AddMark(Mark);
	Node<Mark>* GetMarkHead();

	template <typename S>
	int DeleteMarkBase(S cmp, bool clearAll)
	{
		return listMark.DeleteBase(cmp, clearAll);
	}

	template <typename S>
	Node<Mark>* FindMark(S cmp)
	{
		return listMark.FindElement(cmp);
	}
	// only base on idSub(idSubject)

	void SortListStudent(bool (*cmp)(Mark, Mark));
};

