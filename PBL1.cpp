#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
#include<stdio.h>
#include <sstream>

using namespace std;

class Product {
private:
	string  tensp, loaisp;
	int soluong, dongia;
	int id;
public:
	Product(string tensp = " ", string loaisp = " ", int soluong = 0, int dongia = 0) : tensp(tensp), loaisp(loaisp), soluong(soluong), dongia(dongia) {}
	friend istream& operator >> (istream& in, Product& product);
	friend ostream& operator << (ostream& out, Product product);

	string get_tensp();
	int get_soluong();
	void set_soluong(int);
	void set_tensp(string);
	string get_loaisp();
	int get_dongia();
	void set_dongia(int);
	void set_loaisp(string);
	void set_id(int);
	int get_id();
};
void Product::set_id(int id) {
	this->id = id;
}
int Product::get_id() {
	return id;
}
string Product::get_tensp()
{
	return tensp;
}

istream& operator >> (istream& in, Product& product) {
	cout << "Nhap ID san pham: ";
	in >> product.id;
	cin.ignore();
	cout << "Nhap loai san pham: ";
	getline(in, product.loaisp);
	cout << "Nhap ten san pham: ";
	getline(in, product.tensp);
	cout << "So Luong: ";
	in >> product.soluong;
	cout << "Don gia: ";
	in >> product.dongia;
	return in;
}
ostream& operator << (ostream& out, Product product) {
	out << product.id << ". " << "Loai san pham: " << product.loaisp << ", " << "Ten san pham: " << product.tensp << ", " << " So luong: " << product.soluong << ", " << "Don gia: " << product.dongia << endl;
	return out;
}
void Product::set_soluong(int _soluong) {
	soluong = _soluong;
}
int Product::get_soluong() {
	return soluong;
}
void Product::set_tensp(string tensp) {
	this->tensp = tensp;
}
void Product::set_loaisp(string loaisp) {
	this->loaisp = loaisp;
}
void Product::set_dongia(int dongia) {
	Product::dongia = dongia;
}
string Product::get_loaisp() {
	return loaisp;
}
int Product::get_dongia() {
	return dongia;
}

class Store {
private:
	vector<Product> v;
public:
	void show_menu(fstream& fin, fstream& fout);
	void show_products();
	void add_products(fstream& fout);
	void delete_products();
	void search_product();
	void bill_product(fstream& fout);
	void getInfo(fstream& fin);
	void new_ds();
};



int main()
{
	Store s;

	fstream foutbill;
	foutbill.open("bill.txt", ios::out);

	fstream fin;
	fin.open("dssp.csv", ios::in);
	fstream fout;
	fout.open("dssp.csv", ios::app);
	s.getInfo(fin);


	s.show_menu(fout, foutbill);

	return 0;
}

void Store::new_ds() {
	fstream new_fin;
	new_fin.open("dssp.csv", ios::out);
	new_fin << "ID" << "," << "LoaiSP" << "," << "TenSP" << "," << "SoLuong" << "," << "DonGia" << endl;
	for (int i = 0; i <= v.size() - 1; i++) {
		new_fin << v[i].get_id() << "," << v[i].get_loaisp() << "," << v[i].get_tensp() << "," << v[i].get_soluong() << "," << v[i].get_dongia() << endl;
	}
}
void Store::getInfo(fstream& fin)
{
	string line, str;
	int x;
	getline(fin, line);
	cout << line << endl;
	while (getline(fin, line))
	{
		stringstream ss(line);
		Product sp;
		getline(ss, str, ',');
		sp.set_id(stoi(str));
		getline(ss, str, ',');
		sp.set_loaisp(str);
		getline(ss, str, ',');
		sp.set_tensp(str);
		getline(ss, str, ',');
		x = stoi(str);
		sp.set_soluong(x);
		getline(ss, str, ',');
		x = stoi(str);
		sp.set_dongia(x);
		v.push_back(sp);
	}
}


void Store::show_menu(fstream& fin, fstream& fout) {
	int chose;

	while (true) {
		system("cls");

		cout << "====== MENU =====" << endl;
		cout << "1. Xem danh sach san pham" << endl;
		cout << "2. Them san pham moi" << endl;
		cout << "3. Xoa san pham" << endl;
		cout << "4. Tim san pham" << endl;
		cout << "5. Hoa don thanh toan" << endl;
		cout << "0. Thoat chuong trinh" << endl;

		cout << "Lua chon cua ban la: ";
		cin >> chose;


		system("cls");

		switch (chose) {
		case 1:
			show_products();
			break;
		case 2:
			add_products(fin);
			break;
		case 3:
			delete_products();
			break;
		case 4:
			search_product();
			break;
		case 5:
			bill_product(fout);
			break;
		case 0:
			cout << "Tam biet !!!" << endl;
			return;
		default:
			cout << "Lua chon khong hop le." << endl;

		}
		cout << "Ban co muon tiep tuc khong?" << endl;
		cout << "Chon 1 neu tiep tuc." << endl;
		cout << "Chon 0 de thoat chuong trinh." << endl;
		bool is_continue;
		cin >> is_continue;

		if (is_continue == 0) {
			cout << "Tam biet!!!";
			break;
		}
	}



}
void Store::show_products() {
	if (v.size() == 0) {
		cout << "Chua co san pham." << endl;
		cout << "Vui long nhap san pham." << endl;
	}
	else {
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << endl;
		}
	}

}

void Store::add_products(fstream& fout) {
	Product add_product;
	cout << "Nhap thong tin san pham muon them. " << endl;
	cin >> add_product;
	v.push_back(add_product);
	cout << "Them san pham thanh cong." << endl;
	fout << add_product.get_id() << "," << add_product.get_loaisp() << "," << add_product.get_tensp() << "," << add_product.get_soluong() << "," << add_product.get_dongia() << endl; ;
}

void Store::delete_products() {
	string delete_pr;
	cout << "Nhap san pham muon xoa: ";
	cin.ignore();
	getline(cin, delete_pr);

	int delete_index = -1;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].get_tensp() == delete_pr) {
			v.erase(v.begin() + i);
			delete_index = i;
			break;
		}
	}

	if (delete_index == -1) {
		cout << "Khong tim thay san pham." << endl;
		return;
	}

	cout << "Xoa san pham thanh cong." << endl;
	new_ds();

}

void Store::search_product() {
	string search_name;
	cout << "Nhap ten san pham muon tim kiem: ";
	cin.ignore();
	getline(cin, search_name);
	int search_index = -1;

	for (int i = 0; i < v.size(); i++) {
		if (search_name == v[i].get_tensp()) {
			cout << v[i];
			search_index = i;
			break;
		}
	}
	if (search_index == -1) {
		cout << "Khong tim thay san pham." << endl;

	}

}

void Store::bill_product(fstream& fout) {
	time_t now = time(nullptr);
	struct tm local_time;

	int sl;
	int tongtien = 0;
	int num_Products;
	cout << "Nhap so luong san pham trong hoa don: ";
	cin >> num_Products;
	int* sell_id = new int[num_Products];
	int* sell_sl = new int[num_Products];
	for (int i = 0; i < num_Products; ++i) {

		bool validInput = false;


		cout << "Nhap ma san pham: ";
		cin >> sell_id[i];
		cout << "Nhap so luong: ";
		cin >> sell_sl[i];

		for (Product& product : v) {
			if (product.get_id() == sell_id[i]) {
				validInput = true;
				if (sell_sl[i] > product.get_soluong()) {
					cout << "Loi: So luong vuot qua ton kho. Vui long nhap lai so luong hop le." << endl;
					--i;
				}
				else {

					product.set_soluong(product.get_soluong() - sell_sl[i]);


				}
				break;
			}
		}

		if (!validInput) {
			cout << "Loi: Ma san pham k ton tai. Vui long nhap lai so luong hop le." << endl;
			--i;
		}

	}
	new_ds();
	cout << "==========BILL==========" << endl;
	fout << "==========BILL==========" << endl;



	for (int i = 0; i < num_Products; ++i) {
		bool validInput = false;
		for (Product& product : v) {
			if (product.get_id() == sell_id[i]) {
				validInput = true;
				cout << "Ma san pham: " << sell_id[i] << endl;
				fout << "Ma san pham: " << sell_id[i] << endl;
				cout << "Ten san pham: " << product.get_tensp() << endl;
				fout << "Ten san pham: " << product.get_tensp() << endl;
				cout << "So luong: " << sell_sl[i] << endl;
				fout << "So luong: " << sell_sl[i] << endl;
				cout << "So tien: " << product.get_dongia() << " " << "Thanh tien: " << product.get_dongia() * sell_sl[i] << endl;
				fout << "So tien: " << product.get_dongia() << " " << "Thanh tien: " << product.get_dongia() * sell_sl[i] << endl;
				tongtien += product.get_dongia() * sell_sl[i];
			}
		}

	}

	cout << "Tong tien thanh toan: " << tongtien << endl;
	fout << "Tong tien thanh toan: " << tongtien << endl;


	if (localtime_s(&local_time, &now) == 0) {

		cout << local_time.tm_hour << ":" << local_time.tm_min << ":" << local_time.tm_sec << endl;
		fout << local_time.tm_hour << ":" << local_time.tm_min << ":" << local_time.tm_sec << endl;
		cout << "Ngay " << local_time.tm_mday << "/" << local_time.tm_mon + 1 << "/" << local_time.tm_year + 1900 << endl;
		fout << "Ngay " << local_time.tm_mday << "/" << local_time.tm_mon + 1 << "/" << local_time.tm_year + 1900 << endl;

	}

	else {
		cerr << "Loi khi chuyen doi thoi gian." << endl;
		fout << "Loi khi chuyen doi thoi gian." << endl;
	}

}



