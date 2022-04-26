#include "mylib.h"
#include "FileManager.h"
using namespace std;

int checkAccount(ListClass& listClass, string username, string password)
{
	//return:	1 login successfully
	//			0 username is not existed
	//			-1 password is not corrected

	int size = listClass.GetSize();
	Class* c_ptr;
	ListStudent* list_stu;
	for (int i = 0; i < size; i++)
	{
		c_ptr = listClass.GetNode(i);
		list_stu = c_ptr->getListStudent();
		for (Node<Student>* p = list_stu->GetStudentHead(); p != nullptr; p = p->next)
		{
			if (p->data.getIdStudent() == username)
			{
				if (p->data.getPassword() == password) return 1;
				return -1;
			}
		}
	}
	return 0;
}
int login(ListClass& listClass)
{
	//return:	1 login as admin
	//			0 login as student
	//			-1 login failed

	//Username must be capitalized and exist in list student
	string username, password;
	cout << "Username: "; cin >> username;
	cout << "Password: "; cin >> password;

	string admin = "GV";
	if (username == admin && password == admin) return 1;

	if (checkAccount(listClass, username, password) == 1) return 0;
	return -1;
}

//Them lop duoi hinh thuc lop rong (chua co sinh vien)
int nhapLop(ListClass& listClass)
{
	string str_tmp;
	Class c_temp;
	//Doc ma lop
	cout << "Nhap ma lop moi: ";
	getline(cin >> ws, str_tmp); c_temp.setId(str_tmp);

	//Doc ten lop
	cout << "Nhap ten lop moi: ";
	getline(cin >> ws, str_tmp); c_temp.setName(str_tmp);

	//Them lop vao danh sach cac lop
	listClass.AddClass(c_temp);
	return 1;
}


int inDanhSachLop(ListClass& listClass)
{
	int size = listClass.GetSize();
	Class* c_ptr;
	for (int i = 0; i < size; i++)
	{
		c_ptr = listClass.GetNode(i);
		cout << c_ptr->getId() << " " << c_ptr->getName() << '\n';
	}
	return 1;
}

//Test chuong trinh
int main()
{
	//Initialize list subject & list class
	ListSubject listSub; ListClass listClass;
	
	//Read file 
	FILE_MANAGER f_mng;
	f_mng.readFileSubject(listSub);
	f_mng.readFileClass(listClass, listSub);

	int check_login;
	do {
		system("cls");
		check_login = login(listClass);
	} while (check_login == -1);

	cout << "\nDang nhap thanh cong\n";
	nhapLop(listClass);
	system("cls");
	inDanhSachLop(listClass);

	return 0;
}