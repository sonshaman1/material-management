#include "HoaDon.cpp"
bool KiemTraRong(DanhSachNhanVien ds)
{
	if (ds.n == 0) return true;
	return false;
}
bool KiemTraDay(DanhSachNhanVien ds) 
{
	if (ds.n == MAX_NHAN_VIEN) return true;
	return false;
}
//tim kiem NV theo ma, co thi tra ve vitri, khong thi return -1
int TimKiemNhanVien(DanhSachNhanVien ds, string manv) 
{
	for (int i = 0; i < ds.n; i++)
	{
		if (ds.nodes[i]->manv == manv) return i;
	}
	return -1;
}
int TimViTriThichHop(DanhSachNhanVien ds, string ho, string ten) 
{
	string t1 = ten + ho;
	string t2;
	for (int i = 0; i < ds.n; i++)
	{
		t2 = ds.nodes[i]->ten + ds.nodes[i]->ho;
		if (t2 >= t1) return i;// chi lay vi tri, chua lam gi
	}	
	return ds.n;
}
bool ThemNhanVienVaoViTriX(DanhSachNhanVien &ds, NHANVIEN nv, int idx) 
{
	if (idx < 0 || idx > ds.n || KiemTraDay(ds)) return false;
	ds.nodes[ds.n] = new NHANVIEN; 
	for (int i = ds.n; i > idx; i--)
	{
		*ds.nodes[i] = *ds.nodes[i - 1];
	}
	*ds.nodes[idx] = nv;
	ds.n++;
	return true;
}
bool ThemNhanVienSapXepTheoTen(DanhSachNhanVien &ds, NHANVIEN nv) 
{
	ChuanHoaChuoi(nv.ten); ChuanHoaChuoi(nv.ho);
	int idx = TimViTriThichHop(ds, nv.ho, nv.ten);
	bool kq = ThemNhanVienVaoViTriX(ds, nv, idx);
	return kq;
}
bool XoaNhanVienTheoViTri(DanhSachNhanVien &ds, int idx) 
{
	if (idx < 0 || idx > ds.n || KiemTraRong(ds)) return false;
	
	for (int i = idx;  i < ds.n - 1; i++ )
	{
		*ds.nodes[i] = *ds.nodes[i + 1];
	}
	delete ds.nodes[ds.n - 1];
	ds.n--;
	return true;	
}
void DocFile(DanhSachNhanVien &ds)
{
	ifstream filein(FILE_NHAN_VIEN);
	if(!filein)
	{
		return;
		ofstream fileout(FILE_NHAN_VIEN);
		fileout.close();
		filein.open(FILE_NHAN_VIEN);
	}
	NHANVIEN nv;
	HOADON hd;
	CTHD cthd;
	string s;
	int dem = 0;
	
	getline(filein, s);
	if(s == "=") return;//ket thuc file bang dau = ay ma
	getline(filein, nv.manv);//doc hang dau tien va bo vao manv
	bool check = false;
	if(nv.manv == "") return;
	else
	{
		check = true;
	}
	while(!filein.eof())//trong khi chua ket thuc file
	{
LoadNhanVien:
		if(!check)
		{
			getline(filein, nv.manv);//doc manv 
		}
		getline(filein, nv.ho);
		getline(filein, nv.ten);
		
		getline(filein, s);//gioi tinh
		check = false;
		stringstream(s) >> nv.phai;
		nv.dshd = NULL;
		getline(filein, s);	
		if(s == "+")
		{
			ThemNhanVienSapXepTheoTen(ds, nv);
			goto LoadNhanVien;
		}
		if(s == "=")
		{
			ThemNhanVienSapXepTheoTen(ds, nv);
			return;
		}
LoadHD:
		getline(filein, hd.sohd);
		getline(filein, s);
		stringstream(s) >> hd.ngaylap.ngay;//doc ngay
		getline(filein, s);
		stringstream(s) >> hd.ngaylap.thang;
		getline(filein, s);
		stringstream(s) >> hd.ngaylap.nam;
		hd.dscthd = NULL;
		getline(filein, s);
		hd.loai = s[0];
		getline(filein, s);
		if (s == "-")
		{
			ThemVaoCuoiDanhSach(nv.dshd, hd);//them hoa don vao sau cac hoa don truoc
			goto LoadHD;
		}
		if (s == "+")
		{	
			ThemVaoCuoiDanhSach(nv.dshd, hd);
			ThemNhanVienSapXepTheoTen(ds, nv);// rui them nhan vien
			goto LoadNhanVien;//den load nv de doc tiep file
		}
		if (s == "=")
		{
			ThemVaoCuoiDanhSach(nv.dshd, hd);
			ThemNhanVienSapXepTheoTen(ds, nv);
			return;
		}
	
LoadCTHD:
		getline(filein, cthd.mavt);
		getline(filein, s);
		stringstream(s) >> cthd.soluong;
		getline(filein, s);
		stringstream(s) >> cthd.dongia;
		getline(filein, s);
		stringstream(s) >> cthd.vat;
		getline(filein, s);
		ThemVaoCuoiDanhSach(hd.dscthd, cthd);
		if (s == "*")goto LoadCTHD;
	
		if (s == "-")
		{
			ThemVaoCuoiDanhSach(nv.dshd, hd);
			goto LoadHD;
		}
		if (s == "=")
		{
			ThemVaoCuoiDanhSach(nv.dshd, hd);
			ThemNhanVienSapXepTheoTen(ds, nv);
			return;
		}
		if (s == "+")
		{
			ThemVaoCuoiDanhSach(nv.dshd, hd);
			ThemNhanVienSapXepTheoTen(ds, nv);
			goto LoadNhanVien;
		}
	}
	filein.close();
	return;
}
void GhiFile(DanhSachNhanVien ds)
{
	ofstream fileout(FILE_NHAN_VIEN);		
	NHANVIEN temp;
	LISTHD dshd = NULL;
	LISTCTHD dscthd = NULL;
		
	for(int i = 0; i < ds.n; i++)// duyet het danh sach
	{	
		temp = *ds.nodes[i];
		fileout << "+" << endl;
		fileout << temp.manv << endl;
		fileout << temp.ho << endl;
		fileout << temp.ten << endl;
		fileout << temp.phai << endl;
		dshd = temp.dshd;
		while(dshd != NULL)   // dau tru ("-") ki hieu bat dau hoa don
		{
			fileout << "-" << endl;
			fileout << dshd->infohd.sohd << endl;
			fileout << dshd->infohd.ngaylap.ngay << endl;
			fileout << dshd->infohd.ngaylap.thang << endl;
			fileout << dshd->infohd.ngaylap.nam << endl;
			fileout << dshd->infohd.loai << endl;
			dscthd = dshd->infohd.dscthd;
			while(dscthd != NULL) // dau nhan ("*") ki hieu chi tiet hoa don
				{
				fileout << "*" << endl;	
				fileout << dscthd->infocthd.mavt << endl;
				fileout << dscthd->infocthd.soluong << endl;
				fileout << dscthd->infocthd.dongia << endl;
				fileout << dscthd->infocthd.vat << endl;
				dscthd = dscthd->next;
				}
			dshd = dshd->next;
		}
	}
	fileout << "=";   // ki hieu den cuoi file
	fileout.close();
	return;
}
void XoaDanhSach(DanhSachNhanVien &ds)
{
	NHANVIEN temp;
	LISTHD dshd = NULL;
	LISTCTHD dscthd = NULL;
	LISTHD hd; 
	LISTCTHD cthd;
	for(int i = 0; i < ds.n; i++)
	{
		temp = *ds.nodes[i];//lay noi dung cua nhan vien thu i
		dshd = temp.dshd;// lay danh sach hoa don cua nhan vien do ra
		while(dshd != NULL)
		{
			dscthd = dshd->infohd.dscthd;
			while(dscthd != NULL)//xoa tung nut cthd
			{
				cthd = dscthd;	
				dscthd = dscthd->next;
				delete cthd;
			}
			hd = dshd;//xoa tung hd
			dshd = dshd->next;
			delete hd;
		}
		delete ds.nodes[i];//xoa node
	}
}
void FormThemNhanVien(string s, string t)
{
	XoaManHinh();
	SetColor(CYAN);
	SetBGColor(BLACK);
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1);
	cout << s;
	VeFooter(t);

	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 15;
	int yinput = ylabel - 1;
	
	for (int i = 0; i < 4; i++) 
	{
		gotoxy(xlabel, ylabel + 3 * i);
		if(i != 3)
		{
			cout << lableNhanVien[i];
			VeInputText(xinput, yinput + 3 * i, 0);
		}
		else
		{
			cout << lableNhanVien[i];
			VeInputLuaChon(xinput + 12, yinput + 3 * i);
			SetBGColor(BLACK);
			cout << " Nam";
			VeInputLuaChon(xinput + 25, yinput + 3 * i);
			SetBGColor(BLACK);
			cout << " Nu";
		}
	}
}
int CapNhapNhanVien(NHANVIEN &nv)
{
	int c;
	int index = 1;
	bool kq = false;
	string s = "CAP NHAT NHAN VIEN";
	string t = "Esc: Thoat\tInsert: Luu";
	FormThemNhanVien(s, t);//lay cai form them nhan vien len 
	SetBGColor(BLACK);
	SetColor(WHITE);
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 16;
	int yinput = ylabel;
	// khong cho cap nhat ma nhan vien
	SetColor(CYAN);
	gotoxy(xinput, yinput);
	cout << nv.manv;
	
	SetColor(WHITE);//ho va ten dc phep
	gotoxy(xinput, yinput + 3);
	cout << nv.ho;
	gotoxy(xinput, yinput + 6);
	cout << nv.ten;
	if(nv.phai== true)
	{
		SetBGColor(BLACK);
		SetColor(WHITE);
		gotoxy(xinput + 25, yinput + 9);
		cout << "   ";
		gotoxy(xinput + 12, yinput + 9);
		cout << " X";
	}
	else
	{
		SetBGColor(BLACK);
		SetColor(WHITE);
		gotoxy(xinput + 12, yinput + 9);
		cout << "   ";
		gotoxy(xinput + 25, yinput + 9);
		cout << " X";				
	}
	do
	{
		if(index == 1)
		{
			c = NhapChuoiKiTu(nv.ho, xinput , yinput + index * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}else if(index == 2){
			c = NhapChuoiKiTu(nv.ten, xinput , yinput + index * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}else{
			do
			{
				if(nv.phai== true)
				{
					SetBGColor(BLACK);
					SetColor(WHITE);
					gotoxy(xinput + 25, yinput + 9);
					cout << "   ";
					gotoxy(xinput + 12, yinput + 9);
					cout << " X";
				}
				else
				{
					SetBGColor(BLACK);
					SetColor(WHITE);
					gotoxy(xinput + 12, yinput + 9);
					cout << "   ";
					gotoxy(xinput + 25, yinput + 9);
					cout << " X";				
				}
				c = KeyPressed();
				if(c == KEY_RIGHT) nv.phai = false;
				if(c== KEY_LEFT) nv.phai = true;
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT);
		}
		//index++ => con tro xuong dong ten,gioi tinh, tuong tu khi index--
		if((c == KEY_DOWN || c == KEY_ENTER || c == KEY_TAB) && index < 3) index++;
		if(c == KEY_UP && index > 1) index--;
		if(c == KEY_INSERT)
		{
			if(nv.ho == "" || nv.ten == "")
			{
				ThongBao("Vui Long Khong De Trong Thong Tin");
			} 
			else
			{
				XoaKhoangTrang(nv.manv); ChuanHoaMa(nv.manv);
				ChuanHoaChuoi(nv.ho);
				ChuanHoaChuoi(nv.ten);
				ThongBao("Cap Nhat Nhan Vien Thanh Cong");
				return 1;
			}
			FormThemNhanVien(s, t);
			if(nv.phai== true)
			{
				SetBGColor(BLACK);
				SetColor(WHITE);
				gotoxy(xinput + 25, yinput + 9);
				cout << "   ";
				gotoxy(xinput + 12, yinput + 9);
				cout << " X";
			}
			else
			{
				SetBGColor(BLACK);
				SetColor(WHITE);
				gotoxy(xinput + 12, yinput + 9);
				cout << "   ";
				gotoxy(xinput + 25, yinput + 9);
				cout << " X";				
			}
			SetColor(CYAN);
			SetBGColor(BLACK);
			gotoxy(xinput, yinput);
			cout << nv.manv;
			SetColor(WHITE);
			gotoxy(xinput, yinput + 3);
			cout << nv.ho;
			gotoxy(xinput, yinput + 6);
			cout << nv.ten; 
		}
	}while(c != KEY_ESC);
	if(c == KEY_ESC) return -1;
}
int NhapNhanVien(DanhSachNhanVien &ds, string &manv)
{
	int c;
	int index = 0;
	bool kq = false;
	NHANVIEN nv;
	int idx = 0;
	string s = "NHAP NHAN VIEN";
	string t = "Esc: Thoat\tInsert: Them vao danh sach";
	FormThemNhanVien(s, t);
	SetColor(WHITE);
	SetBGColor(BLACK);
	
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 16;
	int yinput = ylabel;
	if(nv.phai== true)
	{
		SetBGColor(BLACK);
		SetColor(WHITE);
		gotoxy(xinput + 25, yinput + 9);
		cout << "   ";
		gotoxy(xinput + 12, yinput + 9);
		cout << " X";
	}
	else
	{
		SetBGColor(BLACK);
		SetColor(WHITE);
		gotoxy(xinput + 12, yinput + 9);
		cout << "   ";
		gotoxy(xinput + 25, yinput + 9);
		cout << " X";				
	}
	do
	{
		if(index == 0)
		{
			c = NhapChuoiKiTuVaSo(nv.manv, xinput , yinput + index * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}else if(index == 1){
			c = NhapChuoiKiTu(nv.ho, xinput , yinput + index * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}else if(index == 2){
			c = NhapChuoiKiTu(nv.ten, xinput , yinput + index * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}else
		{
			do
			{
				if(nv.phai== true)
				{
					SetBGColor(BLACK);
					SetColor(WHITE);
					gotoxy(xinput + 25, yinput + 9);
					cout << "   ";
					gotoxy(xinput + 12, yinput + 9);
					cout << " X";
				}
				else
				{
					SetBGColor(BLACK);
					SetColor(WHITE);
					gotoxy(xinput + 12, yinput + 9);
					cout << "   ";
					gotoxy(xinput + 25, yinput + 9);
					cout << " X";				
				}
				c = KeyPressed();
				if(c == KEY_RIGHT) nv.phai = false;
				if(c== KEY_LEFT) nv.phai = true;
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT);
		}
		if((c == KEY_DOWN || c == KEY_ENTER || c == KEY_TAB) && index < 3) index++;
		if(c == KEY_UP && index > 0) index--;
		if(c == KEY_INSERT)
		{
			if(nv.manv == "" || nv.ho == "" || nv.ten == "")
			{
				ThongBao("Vui Long Khong De Trong Thong Tin");
				if(nv.manv == "") index = 0;
				else if(nv.ho == "") index = 1;
				else if(nv.ten == "") index = 2;
			}
			else // dieu kien da hop le
			{
				XoaKhoangTrang(nv.manv); ChuanHoaMa(nv.manv);
			 	ChuanHoaChuoi(nv.ho);
			 	ChuanHoaChuoi(nv.ten);
				idx = TimKiemNhanVien(ds, nv.manv);//tra ve -1 neu k co
		 		if(idx == -1)  // chua ton tai trong danh sach
			 	{
				 	kq = ThemNhanVienSapXepTheoTen(ds, nv);
			 		if(kq == true)
					{
						ThongBao("Them Nhan Vien Thanh Cong");
						manv = nv.manv;
						break;
					}
				}
				else
				{	
					ThongBao("Ma Nhan Vien Da Ton Tai");
					index = 0;
				}
			}
		  	FormThemNhanVien(s, t);//quay lai form them nv
			if(nv.phai== true)
			{
				SetBGColor(BLACK);
				SetColor(WHITE);
				gotoxy(xinput + 25, yinput + 9);
				cout << "   ";
				gotoxy(xinput + 12, yinput + 9);
				cout << " X";
			}
			else
			{
				SetBGColor(BLACK);
				SetColor(WHITE);
				gotoxy(xinput + 12, yinput + 9);
				cout << "   ";
				gotoxy(xinput + 25, yinput + 9);
				cout << " X";				
			}
			SetColor(WHITE);
			SetBGColor(BLACK);
			gotoxy (xinput, yinput + 6);
			cout << nv.ten;
			gotoxy (xinput, yinput + 3);
			cout << nv.ho; 
			gotoxy (xinput, yinput);
			cout << nv.manv; 
		}  	
	}while(c != KEY_ESC);
	if(c == KEY_ESC)
	{
		return -1;
	}
}
void VeFormDanhSachNhanVien()
{
	SetColor(CYAN);
	SetBGColor(BLACK);
	string s = "                              ";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
	cout << s;
	s = "DANH SACH NHAN VIEN";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 2);
	cout << s;
	VeFooter("Esc: Thoat   Insert: Them   Delete: Xoa   F5: Sua   F4: Luu File   F2: Danh Sach hoa Don   <-Trang Truoc   Trang Sau->");
}
//in nha vien: in tieu de va trang
void InNhanVien(DanhSachNhanVien ds, int trang, int tongtrang, int socot, int sodong, int x, int y)
{
	XoaManHinh();
	SetColor(CYAN);
	if(ds.n == 0)
	{
		string s = "Danh Sach Nhan Vien Rong";
		gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 7);
		cout << s;
		return;
	}
	VeBangDanhSach(x, y, socot, sodong, 20);
	int xlabel;
	SetColor(CYAN);
	for (int i = 0; i < socot; i++)// tieu de
	{
		xlabel = x + i * (20 + 1) + 1 + (20 - tenCotBangNhanVien[i].length()) / 2;
		gotoxy(xlabel, y + 1);
		cout << tenCotBangNhanVien[i];
	}
	SetColor(WHITE);
	int xtro;
	int ytro;
	if(ds.n == 0) return;
	string str;
	int vtdau = (trang - 1) * 10;// de con tro o vi tri dau tien cua danh sach
	NHANVIEN nv;
	int tam = 0;
	SetColor(WHITE);
	for(int i = vtdau; i < ds.n && i < trang * 10; i++)//load nd
	{
		nv = *ds.nodes[i];
		ytro = y + 3 + 2 * tam;
		tam++;
		str = ChuyenSoThanhChuoi(i + 1);
		xtro = x + 0 * (20 + 1) + 1 + (20 - str.length()) / 2;
		gotoxy(xtro, ytro);
		
		cout << ChuyenSoThanhChuoi(i + 1);
		xtro = x + 1 * (20 + 1) + 1 + (20 - nv.manv.length()) / 2;
		gotoxy(xtro, ytro);
		cout << nv.manv;
		
		xtro = x + 2 * (20 + 1) + 1 + (20 - nv.ho.length()) / 2;
		gotoxy(xtro, ytro);
		cout << nv.ho;
		xtro = x + 3 * (20 + 1) + 1 + (20 - nv.ten.length()) / 2;
		gotoxy(xtro, ytro);
		cout << nv.ten;
		if(nv.phai) str = "Nam";
		else str = "Nu";
		xtro = x + 4 * (20 + 1) + 1 + (20 - str.length()) / 2;
		gotoxy(xtro, ytro);
		cout << str;
	}
	PhanTrang(trang, tongtrang, 0, 2);
}
void SapXepNhanVien(DanhSachNhanVien &ds)
{
	string t, v;
	NHANVIEN temp;
	for(int i = 0; i < ds.n - 1; i++)
	{
		t = ds.nodes[i]->ten + ds.nodes[i]->ho;
		for(int j = i + 1; j < ds.n; j++)
		{
			v = ds.nodes[j]->ten + ds.nodes[j]->ho;
			if(t > v)
			{
				temp = *ds.nodes[i];
				*ds.nodes[i] = *ds.nodes[j];
				*ds.nodes[j] = temp;
			}
		}
	}
}
void DuyetDanhSachNhanVien(DanhSachNhanVien &ds, VATTUTREE &root)
{
	int trang = 1;
	int n = ds.n;
	int tongtrang =  n / 10;
	if(n % 10 != 0) tongtrang++;
	int vtri = 1;
	int vtrisau;
	int c;
	string s;
	int kq;
	int socot = 5;
	int sodong = 10 + 1; 
	int x = 37, y = 11;
	InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
	if(ds.n != 0) VeConTro(x - 3, y + 3, vtri);
	VeFormDanhSachNhanVien();
	do 
	{
		SetColor(CYAN);
		SetBGColor(BLACK);
		c = KeyPressed();
		if(c == KEY_LEFT) 
		{
			if (trang > 1)
			{
				trang--;
				InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
				XoaConTro(x - 3, y + 3, vtri);
				vtri = 1;
				VeConTro(x - 3, y + 3, vtri);
				VeFormDanhSachNhanVien();
			}
		}
		if(c == KEY_RIGHT) 
		{
			if (trang < tongtrang)
			{
				trang++;
				InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
				XoaConTro(x - 3, y + 3, vtri);
				vtri = 1;
				VeConTro(x - 3, y + 3, vtri);
				VeFormDanhSachNhanVien();
			}
		}
		if (c == KEY_UP)
		{
			if (vtri > 1)
			{
				XoaConTro(x - 3, y + 3, vtri--);
				VeConTro(x - 3, y + 3, vtri);
			}
			else if(vtri == 1 && trang > 1)
			{
				trang--;
				InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
				XoaConTro(x - 3, y + 3, vtri);
				vtri = 10;
				VeConTro(x - 3, y + 3, vtri);
				VeFormDanhSachNhanVien();
			}
		}
		if (c == KEY_DOWN)
		{
			if (vtri < 10 && (vtri + (trang - 1) * 10) < ds.n) 
			{
				XoaConTro(x - 3, y + 3, vtri++);
				VeConTro(x - 3, y + 3, vtri);
			}
			else if(vtri == 10 && trang < tongtrang)
			{
				trang++;
				InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
				XoaConTro(x - 3, y + 3, vtri);
				vtri = 1;
				VeConTro(x - 3, y + 3, vtri);
				VeFormDanhSachNhanVien();
			}
		}
		if(c == KEY_INSERT)
		{
			string s = "                              ";
			gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
			cout << s;
			string manv = "";
			do
			{
				c = NhapNhanVien(ds, manv);
			}while(c != -1);
			if(manv != "")
			{
				vtrisau = TimKiemNhanVien(ds, manv);
				vtrisau++;
				trang = vtrisau / 10;
				if(vtrisau % 10 != 0) trang++;
				vtrisau--;
				vtri = vtrisau % 10;
				vtri++;
			}
			InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
			VeConTro(x - 3, y + 3, vtri);
			VeFormDanhSachNhanVien();
		}
		if(c == KEY_F5)
		{
			string s = "                              ";
			gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
			cout << s;
			NHANVIEN nv = *ds.nodes[(trang - 1) * 10 + vtri - 1];
			kq = CapNhapNhanVien(nv);
			if(kq != -1) 
			{
				*ds.nodes[(trang - 1) * 10 + vtri - 1] = nv;
				SapXepNhanVien(ds);
				vtrisau = TimKiemNhanVien(ds, nv.manv);
				vtrisau++;
				trang = vtrisau / 10;
				if(vtrisau % 10 != 0) trang++;
				vtrisau--;
				vtri = vtrisau % 10;
				vtri++;
			}
			SetBGColor(BLACK);
			SetColor(CYAN);
			InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
			VeConTro(x - 3, y + 3, vtri);
			VeFormDanhSachNhanVien();
		}
		if(c == KEY_DELETE)
		{
			NHANVIEN nv = *ds.nodes[(trang - 1) * 10 + vtri - 1];
			if(nv.dshd != NULL)
			{
				ThongBao("Nhan Vien Da Lap hoa Don");
				SetBGColor(BLACK);
				SetColor(CYAN);
				InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
				VeConTro(x - 3, y + 3, vtri);
			}
			else
			{
				kq = HopThoaiLuaChon("Ban Co Muon Xoa Nhan Vien "+ nv.manv + " Khong?", 
									  TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) / 2, (SCREEN_HEIGTH - 5) / 2, 50, 5);
				if(kq == 1)
				{
					XoaNhanVienTheoViTri(ds, (trang - 1) * 10 + vtri - 1);				
					ThongBao("Xoa Thanh Cong");
					SetBGColor(BLACK);
					SetColor(CYAN);
					n--;
					if(n < 0) n = 0; 
					tongtrang =  n / 10;
					if(n % 10 != 0) tongtrang++;
					if (trang > 1 && vtri == 1)
					{
						trang--;
						XoaConTro(x - 3, y + 3, vtri);
						vtri = 10;
					} else if (vtri > 1)
					{
						XoaConTro(x - 3, y + 3, vtri);
						vtri--;
					}		
					InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
					VeConTro(x - 3, y + 3, vtri);
				}
				else
				{
					InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
					VeConTro(x - 3, y + 3, vtri);
				}
			}
		}
		if(c == KEY_F2)
		{
			string s = "                              ";
			gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1 );
			cout << s;
			DanhSachHoaDonDaLapCuaNhanVien(root, *ds.nodes[(trang - 1) * 10 + vtri - 1]);
			InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
			VeConTro(x - 3, y + 3, vtri);	
			VeFormDanhSachNhanVien();	
		}	
		if(c == KEY_F4)
		{
			GhiFile(ds);
			ThongBao("Luu Du Lieu Thanh Cong");
			InNhanVien(ds, trang, tongtrang, socot, sodong, x, y);
			VeConTro(x - 3, y + 3, vtri);		
			VeFormDanhSachNhanVien();
		}		
	} while (c != KEY_ESC);
}





