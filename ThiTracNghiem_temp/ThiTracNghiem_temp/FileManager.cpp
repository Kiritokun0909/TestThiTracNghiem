#include "FileManager.h"

//Read/Write file subject list
void FILE_MANAGER::readFileSubject(ListSubject& listSub)
{
	ifstream inFile;
	inFile.open(subjects_list_file_path, ios_base::in);

	Subject sub;
	string id, name;
	//getline(inFile, id);
	while (inFile.good())
	{
		//Doc file ma va ten mon hoc
		getline(inFile, id, ','); sub.setId(id);
		if (id == "") continue;
		getline(inFile, name, '\n'); sub.setName(name);

		//Luu mon hoc vao list subject
		if (listSub.AddSubject(sub) != 1) break;
	}

	inFile.close();
}
void FILE_MANAGER::saveFileSubject(ListSubject& listSub)
{
	ofstream outFile;
	outFile.open(subjects_list_file_path, ios_base::out);

	int size = listSub.GetSize();
	
	//Co can thiet ghi so luong mon hoc ra khong ?
	////Ghi so luong mon hoc
	//outFile << size << '\n';

	//Ghi cac mon hoc (bao gom id va ten mon hoc) vao file
	Subject* ptr;
	for (int i = 0; i < size; i++)
	{
		ptr = listSub.GetNode(i);
		outFile << ptr->getId() << ',' << ptr->getName() << '\n';
	}

	outFile.close();
}


//	READ FILE
ListMark* FILE_MANAGER::readFileMark(string id_student, ListSubject& listSub)
{
	ifstream inFile;
	inFile.open(mark_list_file_path + id_student + ".csv", ios_base::in);

	ListMark* listMark = new ListMark();
	Subject* sub_ptr;
	string str_tmp;
	while (inFile.good())
	{
		Mark mark_tmp;
		//Doc ten subject va cho con tro tro vao mon hoc trong list Subject
		getline(inFile, str_tmp, ',');
		//Doc \n neu file rong ko co data
		//Doc "" de bo qua khi doc het data cua file
		if (str_tmp == "" || str_tmp == "\n") continue;
		sub_ptr = listSub.SearchSubject(str_tmp, &listSub, &ListSubject::SearchByID);
		mark_tmp.setSubject(sub_ptr);

		//Neu sinh vien da thi mon nay => tang so luong nguoi da thi mon nay 
		if (sub_ptr != nullptr) sub_ptr->setNumTested((sub_ptr->getNumTested()) + 1);	

		//Doc diem cua sinh vien (stof: convert string to float)
		getline(inFile, str_tmp, '\n');; mark_tmp.setMark(stof(str_tmp));

		//Them diem vao danh sach diem cua sinh vien
		listMark->AddMark(mark_tmp);
	}

	inFile.close();

	//Neu mang rong => xoa vung nho va tra ve null (do da tao san o constructor)
	if (listMark->GetSize() == 0)
	{
		delete listMark;
		return nullptr;
	}
	return listMark;
}
ListStudent* FILE_MANAGER::readFileStudent(string id_class, ListSubject& listSub)
{
	ifstream inFile;
	inFile.open(student_list_file_path + id_class + ".csv", ios_base::out);

	ListStudent* listStudent = new ListStudent();
	ListMark* ptr_list_mark = nullptr;
	string str_tmp;  char a_tmp;
	while (inFile.good())
	{
		Student stu_tmp;
		//Doc id/ho va ten cua sinh vien
		getline(inFile, str_tmp, ','); stu_tmp.setIdStudent(str_tmp);
		if (str_tmp == "" || str_tmp == "\n") continue;
		getline(inFile, str_tmp, ','); stu_tmp.setLastName(str_tmp);
		getline(inFile, str_tmp, ','); stu_tmp.setFirstName(str_tmp);

		//Doc gioi tinh
		getline(inFile, str_tmp, ','); 
		a_tmp = str_tmp[0];
		stu_tmp.setGender(a_tmp);

		//Doc password
		getline(inFile, str_tmp, '\n'); stu_tmp.setPassword(str_tmp);

		//Doc danh sach diem cua sinh vien
		ptr_list_mark = readFileMark(stu_tmp.getIdStudent(), listSub);
		//Neu danh sach diem trong file khac rong => xoa vung nho khoi tao o contrustor
		if (ptr_list_mark != nullptr)
		{
			delete stu_tmp.getListMark();	
			stu_tmp.setListMark(ptr_list_mark);	//Cho con tro danh sach tro den vung nho cua danh sach doc tu file
		}

		//Luu thong tin sinh vien vao danh sach
		listStudent->AddStudent(stu_tmp);
	}

	inFile.close();
	return listStudent;	//Do listStudent cua class constructor dat = nullptr nen ko phai xet dieu kien nhu doc list mark
}
void FILE_MANAGER::readFileClass(ListClass& listClass, ListSubject& listSub)
{
	ifstream inFile;
	inFile.open(class_list_file_path, ios_base::in);

	ListStudent* ptr_list_stu;
	string str_tmp;
	while (inFile.good())
	{
		Class c_temp;
		//Doc ma lop
		getline(inFile, str_tmp, ','); c_temp.setId(str_tmp);
		if (str_tmp == "" || str_tmp == "\n") continue;

		//Doc ten lop
		getline(inFile, str_tmp, '\n'); c_temp.setName(str_tmp);

		//Doc danh sach sinh vien cua lop
		ptr_list_stu = readFileStudent(c_temp.getId(), listSub);
		//Neu danh sach trong file khac rong => xoa vung nho khoi tao o contrustor
		c_temp.setList(ptr_list_stu);		//Cho con tro danh sach tro den vung nho cua danh sach doc tu file

		//Them lop vao danh sach cac lop
		listClass.AddClass(c_temp);
	}

	inFile.close();
}


//	SAVE FILE
void FILE_MANAGER::saveFileMark(string student_id, ListMark* listMark)
{
	ofstream outFile;
	outFile.open(mark_list_file_path + student_id + ".csv", ios_base::out);

	for (Node<Mark>* p = listMark->GetMarkHead(); p != nullptr; p = p->next)
	{
		outFile << p->data.getSubject()->getId() << ',' << p->data.getMark() << '\n';
	}

	outFile.close();
}
void FILE_MANAGER::saveFileStudent(string class_id, ListStudent* listStu)
{
	ofstream outFile;
	outFile.open(student_list_file_path + class_id + ".csv", ios_base::out);

	for (Node<Student>* p = listStu->GetStudentHead(); p != nullptr; p = p->next)
	{
		outFile << p->data.getIdStudent() << ',';
		outFile << p->data.getLastName() << ',';
		outFile << p->data.getFirstName() << ',';
		outFile << p->data.getGender() << ',';
		outFile << p->data.getPassword() << ',';
		saveFileMark(p->data.getIdStudent(), p->data.getListMark());
		outFile << '\n';
	}

	outFile.close();
}
void FILE_MANAGER::saveFileClass(ListClass& listClass)
{
	ofstream outFile;
	outFile.open(class_list_file_path, ios_base::out);

	Class* c_ptr;
	int size = listClass.GetSize();
	for (int i = 0; i < size; i++)
	{
		c_ptr = listClass.GetNode(i);
		outFile << c_ptr->getId() << ',';
		outFile << c_ptr->getName() << '\n';
		saveFileStudent(c_ptr->getId(), c_ptr->getListStudent());
	}

	outFile.close();
}