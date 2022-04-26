#pragma once
#include "mylib.h"
#include <fstream>
using namespace std;

class FILE_MANAGER
{
private:
	string subjects_list_file_path = "Data/subjects_list.csv";
	
	string mark_list_file_path = "Data/Classes/Students/points_list/"; // + id_student.csv
	string student_list_file_path = "Data/Classes/Students/";	// + id_class.csv
	string class_list_file_path = "Data/Classes/classes_list.csv";
	
	string question_list_file_path = "Data/Questions.csv";
	string finish_questions_file_path = "Data/Finish_questions.csv";
public:
	//	READ/SAVE LIST SUBJECT
	void readFileSubject(ListSubject& listSubject);
	void saveFileSubject(ListSubject& listSubject);

	//	READ FILE
	//	How it works?
	//	1. Read classs (read all elements of each of class then go to step 2)
	//	2. Read the list students of that class
	//	3. Read the list mark of each student in that class
	//	4. Back to step 1 until finish all classes in the list
	// 
	//	Ques: Does it need to store the size of list?
	//
	ListMark* readFileMark(string student_id, ListSubject& listSub);
	ListStudent* readFileStudent(string class_id, ListSubject& listSub);
	void readFileClass(ListClass& listClass, ListSubject& listSubject);


	//	SAVE FILE
	//	Same with the read (class -> student -> mark)
	//
	void saveFileMark(string student_id, ListMark* listMark);
	void saveFileStudent(string class_id, ListStudent* listStudent);
	void saveFileClass(ListClass& listClass);
};