#include "mylib.h"
#include "FileManager.h"
using namespace std;

void clearMemory(ListSubject& listSub, ListClass& listClass)
{
	//Xoa bo nho cho danh sach mon hoc
	listSub.ClearList();

	int c_size = listClass.GetSize();
	ListStudent* ptr_list_stu;
	ListMark* ptr_list_mark;
	for (int i = 0; i < c_size; i++)
	{
		ptr_list_stu = listClass.GetNode(i)->getListStudent();
		for (Node<Student>* p = ptr_list_stu->GetStudentHead(); p != nullptr; p = p->next)
		{
			ptr_list_mark = p->data.getListMark();
			ptr_list_mark->ClearList();
		}
		ptr_list_stu->ClearList();
	}
}

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

	//Tao vung nho danh sach sinh vien
	ListStudent* ptr = new ListStudent();
	c_temp.setList(ptr);

	//Them lop vao danh sach cac lop
	int status = listClass.AddClass(c_temp);
	if (status == 1) cout << "\nThem thanh cong\n\n";
	else if (status == 0) cout << "\nLop da ton tai trong danh sach\n\n";
	else cout << "\nMang danh sach lop da day\n\n";
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


int nhapSinhVienLop(ListClass& listClass)
{
	string id_class;
	cout << "Nhap ma lop: "; cin >> id_class;

	bool find = false;
	int size = listClass.GetSize();
	Class* c_ptr = nullptr;
	for (int i = 0; i < size; i++)
	{
		c_ptr = listClass.GetNode(i);
		if (c_ptr->getId() == id_class) {
			find = true; break;
		}
	}

	if (find == false)
	{
		cout << "\nKhong co lop " << id_class << " trong danh sach!\n";
		return 0;
	}

	ListStudent* ptr_list_stu = c_ptr->getListStudent();
	string str_tmp; char a_tmp;
	do {
		Student stu_tmp;
		//Doc id/ho va ten cua sinh vien
		cout << "\nNhap 0 de thoat nhap sinh vien\n";
		cout << "Nhap ma so sinh vien: ";
		getline(cin >> ws, str_tmp); stu_tmp.setIdStudent(str_tmp);
		if (str_tmp == "0") break;
		cout << "Nhap ho va ten dem cua sinh vien: ";
		getline(cin >> ws, str_tmp); stu_tmp.setLastName(str_tmp);
		cout << "Nhap ten sinh vien: ";
		getline(cin >> ws, str_tmp); stu_tmp.setFirstName(str_tmp);

		//Doc gioi tinh
		cout << "Nhap gioi tinh (Nam: M, Nu: F, Khong xac dinh: U): ";
		getline(cin >> ws, str_tmp);
		a_tmp = str_tmp[0]; stu_tmp.setGender(a_tmp);

		//Doc password
		cout << "Nhap password: ";
		getline(cin >> ws, str_tmp); stu_tmp.setPassword(str_tmp);

		//Luu thong tin sinh vien vao danh sach
		ptr_list_stu->AddStudent(stu_tmp);
	} while (true);

	return 1;
}

int inDSSV(ListClass& listClass)
{
	string id_class;
	cout << "Nhap ma lop muon in dssv: "; cin >> id_class;

	bool find = false;
	int size = listClass.GetSize();
	Class* c_ptr = nullptr;
	for (int i = 0; i < size; i++)
	{
		c_ptr = listClass.GetNode(i);
		if (c_ptr->getId() == id_class) {
			find = true; break;
		}
	}

	if (find == false)
	{
		cout << "Khong co lop " << id_class << " trong danh sach!" << endl;
		return 0;
	}

	int cnt_stu = 0;
	for (Node<Student>* p = c_ptr->getListStudent()->GetStudentHead(); p != nullptr; p = p->next)
	{
		cout << p->data.getIdStudent() << " " << p->data.getFirstName() << " " << endl;
		cnt_stu++;
	}
	if (cnt_stu == 0) cout << "Khong co sinh vien trong lop";
	return 1;
}


int nhapMonHoc(ListSubject& listSubject)
{
	Subject sub_tmp;
	string str_tmp;

	//Doc ma lop
	cout << "Nhap ma mon hoc moi: ";
	getline(cin >> ws, str_tmp); sub_tmp.setId(str_tmp);

	//Doc ten lop
	cout << "Nhap ten mon hoc moi: ";
	getline(cin >> ws, str_tmp); sub_tmp.setName(str_tmp);

	int status = listSubject.AddSubject(sub_tmp);
	if (status == 1) cout << "\nThem thanh cong\n\n";
	else if (status == 0) cout << "\nMon hoc da ton tai trong danh sach\n\n";
	else cout << "\nMang danh sach mon hoc da day\n\n";
	return 1;
}

int xoaMonHoc(ListSubject& listSubject)
{
	//return 0: Xoa khong thanh cong
	//		 1: Xoa thanh cong

	string subId;
	//Doc ma lop
	cout << "Nhap ma mon hoc muon xoa: ";
	getline(cin >> ws, subId);

	int size = listSubject.GetSize();
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (listSubject.GetNode(i)->getId() == subId)
		{
			index = i;
			break;
		}
	}

	if (index == -1 || listSubject.GetNode(index)->getNumTested() != 0)
	{
		cout << "\nMon hoc khong ton tai trong danh sach\n\n";
		return 0;
	}

	int status = listSubject.DelSubjectAt(index);
	if (status == 1) cout << "\nXoa thanh cong\n\n";
	return 1;
}

int dieuChinhMonHoc(ListSubject& listSubject, int type = 0)
{
	//	type == 0: dieu chinh id mon hoc
	//			1: dieu chinh ten mon hoc

	string str_tmp;
	cout << "Nhap id mon hoc can dieu chinh: ";
	getline(cin, str_tmp);
	Subject* ptr = listSubject.SearchSubject(str_tmp, &listSubject, &ListSubject::SearchByID);

	if (ptr == nullptr)
	{
		cout << "Khong co mon hoc nao co id " << str_tmp << " trong danh sach";
		return 0;
	}
	
	if (type == 0)
	{
		cout << "Nhap id moi cua mon hoc: ";
		getline(cin, str_tmp);
		ptr->setId(str_tmp);
	}
	else
	{
		cout << "Nhap ten moi cua mon hoc: ";
		getline(cin, str_tmp);
		ptr->setName(str_tmp);
	}
	return 1;
}

int inDanhSachMonHoc(ListSubject& listSubject)
{
	int size = listSubject.GetSize();
	Subject* ptr;
	for (int i = 0; i < size; i++)
	{
		ptr = listSubject.GetNode(i);
		cout << ptr->getId() << " " << ptr->getName() << "\n";
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

	//a.Login
	/*int check_login;
	do {
		system("cls");
		check_login = login(listClass);
	} while (check_login == -1);
	cout << "\nDang nhap thanh cong\n";*/

	//b.Nhap them lop moi, c.In danh sach lop
	/*nhapLop(listClass);
	cout << "\n\n";
	inDanhSachLop(listClass);*/

	//d.Nhap them sinh vien vao lop
	//Nhap them sinh vien trong lop
	/*nhapSinhVienLop(listClass);
	cout << "\n\n";
	inDSSV(listClass);*/

	//e1.Nhap them mon hoc moi
	/*nhapMonHoc(listSub);
	cout << "\n\n";
	inDanhSachMonHoc(listSub);*/

	//e2.Xoa mon hoc: Chi xoa khi khong co sinh vien nao da thi mon hoc do
	/*inDanhSachMonHoc(listSub);
	cout << "\n\n";
	xoaMonHoc(listSub);
	cout << "\n\n";
	inDanhSachMonHoc(listSub);*/

	//e3.Dieu chinh mon hoc (hieu chinh id/ten mon hoc)
	/*dieuChinhMonHoc(listSub, 0);
	cout << "\n\n";
	inDanhSachMonHoc(listSub);*/
	

	//f_mng.saveFileClass(listClass);
	//f_mng.saveFileSubject(listSub);
	clearMemory(listSub, listClass);	//Clear data
	return 0;
}