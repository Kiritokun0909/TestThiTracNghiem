#pragma once
#include <iostream> 
#include "MarkScript.h"
#include "LinkedList.h"
using namespace std;
class Student
{
private:
	string idStudent;	//ma so sinh vien
	string lastName;	//ho va ten dem
	string firstName;	//ten chinh
	char gender;		//M: con trai, F: con gai, U: khong xac dinh
	string password;	//mat khau
	ListMark* listMark;	// con tro tro den danh sanh diem cua 1 sinh vien

public:
#pragma region Getter
	string getIdStudent() const;
	string getLastName() const;
	string getFirstName() const;
	char getGender() const;
	string getPassword() const;
	ListMark* getList() const;
#pragma endregion

#pragma region Setter
	void setIdStudent(string id);
	void setLastName(string last_name);
	void setFirstName(string first_name);
	void setGender(char gender);
	void setPassword(string password);
	void setList(ListMark* other_listMark);
#pragma endregion
	
#pragma region  Constructor/DeConstructor
	Student();
	Student(string id, string lastname, string, char, string);

	~Student();
#pragma endregion
};

class ListStudent
{
private:
	LinkedList<Student> listStudent;
public:
	ListStudent();
	~ListStudent();
	
	int AddStudent(Student);
	Node<Student>* GetStudentHead();

	template <typename S>
	int DeleteStudentWith(S cmp, bool clearAll)  // delete base on idStudent
	{
		return listStudent.DeleteBase(cmp, clearAll);
	}
	template <typename S>
	Node<Student>* FindStudent(S cmp)
	{
		return listStudent.FindElement(cmp);
	}
	void SortListStudent(bool (*cmp)(Student, Student));
};

