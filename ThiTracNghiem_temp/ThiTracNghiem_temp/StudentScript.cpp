#include "StudentScript.h"

#pragma region Student
string Student::getIdStudent() const
{
    return idStudent;
}

string Student::getLastName() const
{
    return lastName;
}

string Student::getFirstName() const
{
    return firstName;
}

char Student::getGender() const
{
    return gender;
}

string Student::getPassword() const
{
    return password;
}

ListMark* Student::getList() const
{
    return listMark;
}

void Student::setIdStudent(string _id) 
{
    this->idStudent = _id;
}

void Student::setLastName(string _lastName)
{
    this->lastName = _lastName;
}

void Student::setFirstName(string _firstName) 
{
    this->firstName = _firstName;
}

void Student::setGender(char _gender) 
{
    this->gender = _gender;
}

void Student::setPassword(string _password) 
{
    this->password = _password;
}

void Student::setList(ListMark* other) 
{
    this->listMark = other;
}


Student::Student() : idStudent(""), lastName(""), firstName(""), gender('M'), password(""), listMark(nullptr) {}

Student::Student(string _idStudent, string _lastName, string _firstName, char _gender, string _password)
{
    idStudent = _idStudent;
    lastName = _lastName;
    firstName = _firstName;
    gender = _gender;
    password = _password;
    listMark = nullptr;
}

Student::~Student() {};
#pragma endregion

#pragma region ListStudent
ListStudent::ListStudent() {};
ListStudent::~ListStudent() {};

int ListStudent::AddStudent(Student _data)
{
    return listStudent.AddNode(_data);
}

Node<Student>* ListStudent::GetStudentHead()
{
    return listStudent.GetHead();
}

void ListStudent::SortListStudent(bool (*cmp)(Student, Student))
{
    listStudent.Sort(cmp);
}
#pragma endregion


