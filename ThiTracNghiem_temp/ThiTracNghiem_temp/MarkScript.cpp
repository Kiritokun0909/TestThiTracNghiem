#include "MarkScript.h"

#pragma region Mark
float Mark::getMark() const
{
    return mark;
}

void Mark::setMark(float _mark)
{
    this->mark = _mark;
}

Subject* Mark::getSubject() const
{
    return idSubject;
}

void Mark::setSubject(Subject* subject)
{
    this->idSubject = subject;
}

Mark::Mark() : idSubject(nullptr), mark(0) {};

Mark::Mark(Subject* _idSubject, float _mark)
{
    this->idSubject = _idSubject;
    this->mark = _mark;
}

#pragma endregion

#pragma region ListMark
ListMark::ListMark() {};
ListMark::~ListMark() {};
int ListMark::AddMark(Mark _data)
{
    return listMark.AddNode(_data);
}

Node<Mark>* ListMark::GetMarkHead()
{
    return listMark.GetHead();
}

int ListMark::GetSize()
{
    if (listMark.GetHead() == nullptr) return 0;
    return listMark.getSize();
}

void ListMark::ClearList()
{
    listMark.ClearList();
}

void ListMark::SortListStudent(bool(*cmp)(Mark, Mark))
{
    listMark.Sort(cmp);
}


#pragma endregion


