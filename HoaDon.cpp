#include "ChiTietHoaDon.cpp"
bool KiemTraRong(LISTHD first)
{
	if(first == NULL) return true;
	return false;
}
bool ThemVaoCuoiDanhSach(LISTHD &first, HOADON hd)
{
	LISTHD p = new NodeHD; //cap phat 1 node con tro 
	if(p == NULL) return false;
	
	p->infohd = hd;
	p->next = NULL;
	if(first == NULL)
	{
		first = p;
	}
	else
	{
		LISTHD q;
		for(q = first; q->next != NULL; q=q->next);
		q->next = p;
	}
	return true;
}
bool XoaNodeDauDanhSach(LISTHD &first)
{
	if(KiemTraRong(first))
	{
		return false;
	}
	LISTHD p = first;
	first = p->next;
	delete p;
	return true;
}
bool XoaSauNode(LISTHD &first, LISTHD p)// xoa node q sau node p
{
	if(p == NULL || p->next == NULL)//khi p la node cuoi cung
	{
		return false;
	}
	LISTHD q = p->next;
	p->next = q->next;
	delete q;
	return true;
	
}
//ham duoc them
LISTHD TimKiemInfo(LISTHD first, HOADON hd)
{
	for(LISTHD p= first;p!=NULL;p=p->next)
	{
		if(p->infohd.sohd == hd.sohd) { return p;
		}
	}
	return NULL;
}
//ham duoc sua
bool XoaNode_info(LISTHD &first, HOADON hd)
{
	LISTHD q,p;
	p=TimKiemInfo(first,hd);
	if(p==NULL) return false;
	if(p=first)
	{
		XoaNodeDauDanhSach(first);
	}
	else
	{
		q=first;
		while(q->next!=p)
		{
			q=q->next;
		}
		XoaSauNode(first,q);
	}
	return true;
//###########################	
//	LISTHD p = first;
//	if(p == NULL)
//	{
//		return false;
//	}
//	if(p->infohd.sohd == hd.sohd)
//	{
//		return	XoaNodeDauDanhSach(first);
//	}
//	p = first;
//	for(p; p->next != NULL && p->next->infohd.sohd != hd.sohd; p = p->next);
//	if(p->next != NULL)
//	{
//		return	XoaSauNode(first, p);
//	}
//	else return false;
}
int DemSoHoaDon(LISTHD dshd)
{
	LISTHD p = dshd;
	int dem = 0;
	while(p != NULL)
	{
	
		dem++;
		p = p->next;
	}
	return dem;
}
//tim kiem hoa don theo sohd, tra ve node p
LISTHD TimKiemHoaDon(LISTHD dshd, string sohd)
{
	LISTHD p = dshd;
	if(dshd == NULL) return NULL;
	while(p != NULL)
	{
		if(p->infohd.sohd == sohd)
		{
			break;
		}
		p = p->next;
	}
	return p;
}
int TimKiemViTriHoaDon(LISTHD dshd, string sohd)
{
	LISTHD p = dshd;
	int dem = 0;
	if(dshd == NULL) return -1;
	while(p != NULL)
	{
		if(p->infohd.sohd == sohd)
		{
			break;
		}
		dem++;
		p = p->next;
	}
	return dem;
}
//tra ve node
LISTHD TimKiemHoaDonThuN(LISTHD dshd, int idx)
{
	LISTHD p = dshd;
	if(dshd == NULL) return NULL;
	int dem = 0;
	while(p != NULL)//khi khong rong nua
	{
		if(dem == idx)
		{
			break;
		}
		dem++;
		p = p->next;
	}
	return p;
}
//cai nay la xuat form de nhap
void FormNhapHoaDon(NHANVIEN &nv, HOADON hd)
{
	XoaManHinh();
	SetBGColor(BLACK);
	SetColor(CYAN);
	string s = "NHAP HOA DON";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 2);
	cout << s;
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 15;
	int yinput = ylabel - 1;
	
	// so hoa don
	gotoxy(xlabel, ylabel + 3);
	cout << lable[0];
	VeInputText(xinput, yinput + 3, 0);
	// ngay nhap
	gotoxy(xlabel, ylabel);
	cout << lable[1];
	VeInputText(xinput + 10, yinput, 22);
	gotoxy(xinput + 16, yinput + 1);
	cout << " / ";
	gotoxy(xinput + 21, yinput + 1);
	cout << " / ";
	// loai
	gotoxy(xlabel, ylabel + 6);
	cout << lable[2];
	VeInputLuaChon(xinput + 10, yinput + 6);
	cout << " Nhap";
	VeInputLuaChon(xinput + 25, yinput + 6);
	cout << " Xuat";
	VeFooter("ESC: Thoat   Insert: Them vao danh sach    F5: Nhap danh sach vat tu");
}
//xuat noi dung len form
void XuatHoaDonLenForm(HOADON hd, string ngaystr, string thangstr, string namstr)
{
	SetBGColor(BLACK);
	SetColor(WHITE);
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 15;
	int yinput = ylabel - 1;
	SetColor(CYAN);
	gotoxy(xinput + 1, yinput + 4);
	cout << hd.sohd;
	SetColor(WHITE);
	gotoxy(xinput + 13, yinput + 1);
	cout << ngaystr;
	gotoxy(xinput + 19, yinput + 1);
	cout << thangstr;
	gotoxy(xinput + 24, yinput + 1);
	cout << namstr;
	
	if(hd.loai == 'N')
	{
		gotoxy(xinput + 26, yinput + 7);
		cout << "  ";
		gotoxy(xinput + 11, yinput + 7);
		cout << " X";
	}
	else
	{
		gotoxy(xinput + 11, yinput + 7);
		cout << "  ";
		gotoxy(xinput + 26, yinput + 7);
		cout << " X";
	}
}
//show form chinh
void FormInHD(NHANVIEN nv, int socot, int sohang, int  x, int y)
{
	XoaManHinh();
	SetBGColor(BLACK);
	SetColor(CYAN);
	string s = "BANG THONG TIN HOA DON DA LAP";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 2);
	cout << s;
	SetBGColor(BLACK);
	SetColor(CYAN);
	gotoxy(38, 10);
	cout << "Nhan Vien: " << nv.ho << " " << nv.ten;
	SetBGColor(BLACK);
	SetColor(WHITE);
	//VeBangDanhSach(x, y, socot, sohang, 20);
	VeFooter("Esc: Thoat     Delete: Xoa    F5: Sua     F2: Chi Tiet     Insert: Them     <-Trang Truoc     Trang Sau->");
}
//show noi dung hd len man hinh
void InHD(LISTHD first, int trang, int tongtrang, int x, int y)
{
	int vt = (trang - 1) * 10;//lay vitri dau tien cho con tro
	LISTHD p = first;
	int dem = 0;
	int tam = 0;
	int xtro = 0;
	int ytro = 0;
	string s;
	while(p != NULL && dem < vt)//lay so luong hay vi tri tu bien dem
	{
		p = p->next;
		dem++;
	}
	SetBGColor(BLACK);
	VeBangDanhSach(x, y, 5, 11, 20);
	int xlabel;
	SetColor(CYAN);
	for(int i = 0; i < 5; i ++)
	{
		xlabel = x + i * (20 + 1) + 1 + (20 - tenCotHoaDon2[i].length()) / 2;
		gotoxy(xlabel, y + 1);
		cout << tenCotHoaDon2[i];
	}
	SetColor(WHITE);
	while(p != NULL && vt < trang * 10)
	{
		ytro = y + 3 + 2 * tam;
		tam++;
		s = ChuyenSoThanhChuoi(vt + 1);
		xtro = x + 0 * (20 + 1) + 1 + (20 - s.length()) / 2;
		gotoxy(xtro, ytro);
		cout << s;//stt
		xtro = x + 1 * (20 + 1) + 1 + (20 - p->infohd.sohd.length()) / 2;
		gotoxy(xtro, ytro);				
		cout << p->infohd.sohd;
		
		s = ChuyenNgayThanhChuoi(p->infohd.ngaylap);
		xtro = x + 2 * (20 + 1) + 1 + (20 - s.length()) / 2;
		gotoxy(xtro, ytro);				
		cout << s;
		
		if(p->infohd.loai == 'X') s = "Xuat";
		else s = "Nhap";
		xtro = x + 3 * (20 + 1) + 1 + (20 - s.length()) / 2;
		gotoxy(xtro, ytro);				
		cout << s;				

		s = ToString(TinhTongGiaTriHoaDon(p->infohd.dscthd));
		xtro = x + 4 * (20 + 1) + 1 + (20 - s.length()) / 2;
		gotoxy(xtro, ytro);				
		cout << s;	//show ra tong tien
		
		vt++;//vt tang len de show ra node tiep theo
		p = p->next;
	}
	PhanTrang(trang, tongtrang, 1, 2);//show cai so trang/tong trang
}
int NhapHoaDon(VATTUTREE &root, NHANVIEN &nv, int &idxs)
{
	XoaManHinh();
	int c;
	int idx = 0;//chay tu ngay, sohd,...
	int temp = 0;//chay tu ngay thang nam
	// viTri con tro hien tai cua bang CT hoa don
	HoaDon hd;
	bool kq = false;
	FormNhapHoaDon(nv, hd);
	// ngay, thang, nam mac dinh la thoi gian hien tai layGioHeThong()
	string  ngaystr = "", thangstr = "", namstr = "";
	ngaystr = ChuyenSoThanhChuoi(hd.ngaylap.ngay);
	thangstr = ChuyenSoThanhChuoi(hd.ngaylap.thang);
	namstr = ChuyenSoThanhChuoi(hd.ngaylap.nam);
	XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);
	//hien tai da co form  va noi dung tren form nhap hd
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 15;
	int yinput = ylabel - 1;
	do
	{
		if(idx == 0)
		{
			// ngay, thang, nam
			do
			{
				if(temp == 0)
				{
					c = NhapChuoiKiTuSo(ngaystr,xinput + 13, yinput + 1, 2, BLACK, WHITE);
				}else if(temp == 1)
				{
					c = NhapChuoiKiTuSo(thangstr,xinput + 19, yinput + 1, 2, BLACK, WHITE);
				}
				else if(temp == 2)
				{
					c = NhapChuoiKiTuSo(namstr,xinput + 24, yinput + 1, 4, BLACK, WHITE);
				}
				if(c == KEY_ENTER)//neu c la phim enter thi chuyen qua chuyen lai giua ngay thang nam
				{
					switch(temp)
					{
						case 0: temp++;
							break;
						case 1: temp++;
							break;
						case 2: temp = 0;// day chinh la cho dua con tro ve ngay ne
							break;
					}
				}
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5 && c != KEY_TAB);
		}else if(idx == 1)
		{
			// so hoa don
			c = NhapChuoiKiTuVaSo(hd.sohd, xinput + 1, yinput + 4, 20, BLACK, WHITE);	
		}else //xuat hay nhap
		{
			do
			{
				if(hd.loai == 'N')
				{
					gotoxy(xinput + 26, yinput + 7);
					cout << "  ";
					gotoxy(xinput + 11, yinput + 7);
					cout << " X";
				}
				else
				{
					gotoxy(xinput + 11, yinput + 7);
					cout << "  ";
					gotoxy(xinput + 26, yinput + 7);
					cout << " X";
				}
				c = KeyPressed();//bat phim again
				if(c == KEY_RIGHT) hd.loai = 'X';
				if(c== KEY_LEFT) hd.loai = 'N';
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5);
		}
		//lenh khac
		if(c == KEY_DOWN && idx < 2)
		{
			idx++;
			if(idx == 1) temp = 0;
		} 
		if(c == KEY_UP && idx > 0)
		{
			idx--;
			if(idx == 1) temp = 0;
		}
		// xac nhan va them thong tin hoa don
		if(c == KEY_INSERT)
		{
			if(hd.sohd == "" || ngaystr == "" || thangstr == "" || namstr == "")
			{
				ThongBao("Vui Long Khong De Trong Thong Tin");
				if(hd.sohd == "") idx = 1;
				else if(ngaystr == "") 
				{
					idx = 0; temp = 0;
				}
				else if(thangstr == "") 
				{
					idx = 0; temp = 1;
				}
				else if(namstr == "") 
				{
					idx = 0; temp = 2;
				}
			}
			else //thong tin ok r nek. chuan bi them thong tin hd
			{
				XoaKhoangTrang(hd.sohd); ChuanHoaMa(hd.sohd);
				stringstream(ngaystr) >> hd.ngaylap.ngay;
				stringstream(thangstr) >> hd.ngaylap.thang;
				stringstream(namstr) >> hd.ngaylap.nam;
				kq = KiemTraThoiGian(hd.ngaylap.ngay, hd.ngaylap.thang, hd.ngaylap.nam, temp);
				if(kq == 0)//khong hop le
				{
					ThongBao("Ngay Nhap Vao Khong Hop Le");
					idx = 0;
					FormNhapHoaDon(nv, hd);
					XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);
				}
				else
				{
					LISTHD p = TimKiemHoaDon(nv.dshd, hd.sohd);
					if(p == NULL)//khong tim thay hd nao giong
					{
						kq = ThemVaoCuoiDanhSach(nv.dshd, hd);
						if(kq)
						{
							idxs = TimKiemViTriHoaDon(nv.dshd, hd.sohd);
							ThongBao("Them Hoa Don Thanh Cong");
							break;
						}
						else// neu kq=null
						{
							ThongBao("Them Hoa Don That Bai");
							FormNhapHoaDon(nv, hd);
							XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);
						}
					}
					else
					{
						ThongBao("So Hoa Don Da Ton Tai");
					}
				}
			}//ve form va xuat nd len do
			FormNhapHoaDon(nv, hd);
			XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);
		}
		// cho phep nhap danh sach vat tu
		if(c == KEY_F5)
		{
			if(hd.sohd == "" || ngaystr == "" || thangstr == "" || namstr == "")
			{
				ThongBao("Vui Long Khong De Trong Thong Tin");
				if(hd.sohd == "") idx = 1;
				else if(ngaystr == "") 
				{
					idx = 0; temp = 0;
				}
				else if(thangstr == "") 
				{
					idx = 0; temp = 1;
				}
				else if(namstr == "") 
				{
					idx = 0; temp = 2;
				}
			}
			else
			{
				XoaKhoangTrang(hd.sohd); ChuanHoaMa(hd.sohd);
				stringstream(ngaystr) >> hd.ngaylap.ngay;
				stringstream(thangstr) >> hd.ngaylap.thang;
				stringstream(namstr) >> hd.ngaylap.nam;
				kq = KiemTraThoiGian(hd.ngaylap.ngay, hd.ngaylap.thang, hd.ngaylap.nam, temp);
				if(kq == 0)
				{
					ThongBao("Ngay Nhap Vao Khong Hop Le");
					idx = 0;
					FormNhapHoaDon(nv, hd);
					XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);
				}
				else
				{
					LISTHD p = TimKiemHoaDon(nv.dshd, hd.sohd);
					if(p == NULL)
					{
						NhapChiTietHoaDon(root, hd);
						kq = ThemVaoCuoiDanhSach(nv.dshd, hd);
						if(kq)
						{
							idxs = TimKiemViTriHoaDon(nv.dshd, hd.sohd);
							ThongBao("Them Hoa Don Thanh Cong");
							break;
						}
						else
						{
							ThongBao("Them Hoa Don That Bai");
							FormNhapHoaDon(nv, hd);
							XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);
						}
					}
				}
			}
			FormNhapHoaDon(nv, hd);
			XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);
		}
	}while(c != KEY_ESC );
		
	if(c == KEY_ESC) return -1;
	return c;
}
int CapNhatHoaDon(VATTUTREE &root, NHANVIEN &nv, HOADON &hd, int &idxs)
{
	int c;
	int idx = 1;
	int temp = 0;
	bool kq = false;
	//VeHinhChuNhat(TOADOX + WIDTH_MENU_BAR, TOADOY + 3, SCREEN_WIDTH - WIDTH_MENU_BAR, SCREEN_HEIGTH - 3, BLACK);
	FormNhapHoaDon(nv, hd);
	
	string ngaystr = "", thangstr = "", namstr = "";
	ngaystr = ChuyenSoThanhChuoi(hd.ngaylap.ngay);
	thangstr = ChuyenSoThanhChuoi(hd.ngaylap.thang);
	namstr = ChuyenSoThanhChuoi(hd.ngaylap.nam);
	XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);//xuat nd
	
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 15;
	int yinput = ylabel - 1;
	do//begin lam y nhu o tren, bat chuoi+ di chuyen len xuong,...
	{
		if(idx == 1)
		{
			do
			{	
				if(temp == 0)
				{
					c = NhapChuoiKiTuSo(ngaystr,xinput + 13, yinput + 1, 2, BLACK, WHITE);
				}else if(temp == 1)
				{
					c = NhapChuoiKiTuSo(thangstr,xinput + 19, yinput + 1, 2, BLACK, WHITE);
				}
				else
				{
					c = NhapChuoiKiTuSo(namstr,xinput + 24, yinput + 1, 2, BLACK, WHITE);
				}
				if(c == KEY_ENTER)
				{
					switch(temp)
					{
						case 0: temp++;
							break;
						case 1: temp++;
							break;
						case 2: temp = 0;
							break;
					}
				}
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5 && c != KEY_TAB);
		}//end
		else 
		{		
			do
			{
				if(hd.loai == 'N')
				{
					gotoxy(xinput + 26, yinput + 7);
					cout << "  ";
					gotoxy(xinput + 11, yinput + 7);
					cout << " X";
				}
				else
				{
					gotoxy(xinput + 11, yinput + 7);
					cout << "  ";
					gotoxy(xinput + 26, yinput + 7);
					cout << " X";
				}
			c = KeyPressed();
			if(c == KEY_RIGHT) hd.loai = 'X';
			if(c== KEY_LEFT) hd.loai = 'N';				
			}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5);
		}
		
		if((c == KEY_DOWN || c == KEY_ENTER || c == KEY_TAB) && idx < 2)
		{
			idx++;
			if(idx == 1) temp = 0;
		} 
		if(c == KEY_UP && idx > 1)
		{
			idx--;
			if(idx == 1) temp = 0;
		}
		if(c == KEY_INSERT)//them hd vao
		{			
			if(ngaystr == "" || thangstr == "" || namstr == "")
			{
				ThongBao("Vui Long Khong De Trong Thong Tin");
				if(ngaystr == "")
				{
					idx = 1;
					temp = 0;	
				}else if(thangstr == "")
				{
					idx = 1;
					temp = 1;
				}
				else if(namstr == "")
				{
					idx = 1;
					temp = 2;
				}
			}
			else//kiem tra ngay thang nam
			{
				kq = KiemTraThoiGian(hd.ngaylap.ngay, hd.ngaylap.ngay, hd.ngaylap.nam, temp);
				if(kq == 0)
				{
					ThongBao("Ngay Nhap Vao Khong Hop Le");
					idx = 1;
					FormNhapHoaDon(nv, hd);
					XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);
				}
				else
				{				
					stringstream(ngaystr) >> hd.ngaylap.ngay;
					stringstream(thangstr) >> hd.ngaylap.thang;
					stringstream(namstr) >> hd.ngaylap.nam;
					idxs = TimKiemViTriHoaDon(nv.dshd, hd.sohd);
					ThongBao("Cap Nhat Hoa Don Thanh Cong");
					break;			
				}
			}
			FormNhapHoaDon(nv, hd);
			XuatHoaDonLenForm(hd, ngaystr, thangstr, namstr);
		}	
	
		if(c == KEY_F5)
		{
			NhapChiTietHoaDon(root, hd);
			break;
		}
	}while(c != KEY_ESC );
	if(c == KEY_ESC) return -1;
	return c;
}
//tra -1 hay phim nao do
int DanhSachHoaDonDaLapCuaNhanVien(VATTUTREE &root, NHANVIEN &nv)
{
	int x = 37, y = 11;
	int n = DemSoHoaDon(nv.dshd);//tim so luong hd
	int trang = 1, tongtrang=1, vt = 0;
	tongtrang = n / 10;
	if(n % 10 != 0) tongtrang++;
	if(n ==0) trang = tongtrang = 1;
	int c, kq;
	int idxs;
	FormInHD(nv, 5, 10 + 1, x, y);//tao form trc
	do
	{
		InHD(nv.dshd, trang, tongtrang, x, y);
		// thuc hien cac chuc nang them, xoa, sua va in CTHD cua mot hoadon
		do
		{
			VeConTro(x - 3, y + 3, vt + 1);
			c = KeyPressed();
			if(c == KEY_DOWN)
			{
				if(vt == 10 - 1 && trang < tongtrang && n > 0)
				{
					trang++;
					XoaConTro(x - 3, y + 3, vt + 1);
					vt = 0;
					break;
				}
				if(vt < 10 - 1 && (vt + ((trang - 1) * 10))< n - 1 && n > 0)
				{
					XoaConTro(x - 3, y + 3, vt + 1);
					vt++;
				}	
			}
			if(c == KEY_UP)
			{
				if(vt == 0 && trang > 1 && n > 0)
				{
					trang--;
					XoaConTro(x - 3, y + 3, vt + 1);	
					vt = 10 - 1;
					break;
				}
				if(vt > 0 && n > 0)
				{
					XoaConTro(x - 3, y + 3, vt + 1);
					vt--;
				}
			}
			if(c == KEY_INSERT)
			{
				c = NhapHoaDon(root, nv, idxs);
				n = DemSoHoaDon(nv.dshd);
				tongtrang =  n / 10;
				if(n % 10 != 0) tongtrang++;
				// tim trang ma nhan vien moi duoc them vao
				trang = idxs / 10;
				if(idxs % 10 != 0) trang++;
				if(idxs == 0) trang = 1;
				XoaConTro(x - 3, y + 3, vt + 1);
				// tim vi tri trong trang cua nhan vien
				vt = idxs % 10; 
				FormInHD(nv, 5, 10 + 1, x, y);
				break;
			}
			if(c == KEY_F5)
			{
				LISTHD p = TimKiemHoaDonThuN(nv.dshd, (trang- 1) * 10 + vt);
				if(p != NULL)
				{
					if(p->infohd.dscthd != NULL)
					{
						ThongBao("Hoa Don Da Co Chi Tiet Hoa Hon, Khong The Sua");
						FormInHD(nv, 5, 10 + 1, x, y);
						break;
					}
					else
					{
						HOADON hd = p->infohd;
						kq = CapNhatHoaDon(root, nv, p->infohd, idxs);
						if(kq == -1) p->infohd = hd;
						SetBGColor(BLACK);
						SetColor(CYAN);
						FormInHD(nv, 5, 10 + 1, x, y);
						break;	
					}
				}
			}
			if(c == KEY_DELETE)
			{
				LISTHD p = TimKiemHoaDonThuN(nv.dshd, (trang- 1) * 10 + vt);		
				if(p != NULL)
				{
					if(p->infohd.dscthd != NULL)
					{
						ThongBao("Hoa Don Da Co Chi Tiet Hoa Hon, Khong The Xoa");
					}
					else
					{
						kq = HopThoaiLuaChon("Ban Co Muon Xoa Hoa Don "+ p->infohd.sohd + " Khong?", TOADOX + WIDTH_MENU_BAR+  (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) /2, (SCREEN_HEIGTH - 5) / 2, 50,5 );
						if(kq == 1)
						{
							XoaNode_info(nv.dshd, p->infohd);
							ThongBao("Xoa Thanh Cong");
							SetBGColor(BLACK);
							SetColor(CYAN);
							n--;
							if(n < 0) n = 0; 
							tongtrang =  n / 10;
							if(n % 10 != 0) tongtrang++;	
							// neu la vi tri dau tien
							// chua phai la trang dau tien				
							if(vt == 0 && trang > 1)
							{
							 	trang--;
								XoaConTro(x - 3, y + 3, vt + 1);
								vt = 10 - 1;
							}
							//con tro dang dung o vi tri co STT lon hon soHoaDon				
							if((trang - 1) * 10 + vt >= n && n > 0)
							{
								XoaConTro(x - 3, y + 3, vt + 1);
								vt = n % 10 - 1;
							} 
							if(n == 0) trang = tongtrang = 1;
						}							
					}
					FormInHD(nv, 5, 10 + 1, x, y);
					break;
				}
			}	
			if(c == KEY_F2)
			{
				LISTHD p = TimKiemHoaDonThuN(nv.dshd, (trang - 1) * 10 + vt);
				if(p != NULL)
				{
					XuatChiTietHoaDon(nv, p->infohd);
					FormInHD(nv, 5, 10 + 1, x, y);
				}		
				break;
			}	
		}while(c!= KEY_ESC && c!= KEY_LEFT && c != KEY_RIGHT && c != KEY_F2);
		// chuyen trang qua phai
		if(c == KEY_RIGHT)
		{
			if(trang < tongtrang ) trang++;
			if(trang == tongtrang && (trang - 1) * 10 + vt >= n)
			{
				XoaConTro(x - 3, y + 3, vt + 1);
				if(n > 0)
				vt = (n - 1) % 10;
				else vt = 0;
			}	
		}
		// chuyen trang qua trai
		if(c == KEY_LEFT)
		{
			if(trang > 1 ) trang--;	
		}
	// thoat khi nhan ESC	
	}while(c != KEY_ESC);
	if(c == KEY_ESC) return -1; // tra ve tin hieu cho biet viec duyet da ket thuc
	return c;
}
// cac ham dung de xu li module in hoa don theo soHD do ta nhap vao
void FormInHoaDon()
{
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 15;
	int yinput = ylabel - 1;
	gotoxy(xlabel, ylabel);
	cout << "So Hoa Don:";
	VeInputText(xinput, yinput, 0);
	VeFooter("Esc: Thoat   Enter: Ok");
}
void InHoaDon(DanhSachNhanVien ds, VATTUTREE root)
{
	if(ds.n == 0)
	{
		ThongBao("Danh Sanh Nhan Vien Rong");
		return;
	}
	int c;
	string sohd;
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 16;
	int yinput = ylabel;
	LISTHD temp = NULL, dshd = NULL;
	HOADON hd;
	NHANVIEN nv;
	int trang = 1, tongtrang;
	int n;
	string loai;
	string nguoilap;
	long long tongtien;
	int x = 37, y = 11;
	do
	{
NhapLai:
		XoaManHinh();
		SetColor(CYAN);
		FormInHoaDon();
		c = NhapChuoiKiTuVaSo(sohd, xinput, yinput, 20, BLACK, WHITE);
		if(c == KEY_ENTER)
		{
			if(sohd == "")
			{
				goto NhapLai;
			}
			else
			{
				XoaKhoangTrang(sohd); ChuanHoaMa(sohd);
				if(ds.n == 0)
				{
					ThongBao("Danh Sanh Nhan Vien Rong");
				}
				else
				{
					XoaManHinh();
					for(int i = 0; i < ds.n; i++)
					{
						nv = *ds.nodes[i];
						dshd = nv.dshd;
						if(dshd != NULL)
						{
							temp = TimKiemHoaDon(dshd, sohd);
							if(temp != NULL) 
							{
								nguoilap = nv.ho + " " + nv.ten;
								break;
							}
						}
					}
					if(temp != NULL)
					{
						if(temp->infohd.dscthd == NULL)
						{
							string s = "Hoa Don Chua Co Chi Tiet";
							gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 7);
							cout << s;
							Sleep(1000);
							sohd = "";
							goto NhapLai; 
						}
					
						VeFooter("Esc: Thoat \t <-Trang Truoc \t Trang Sau->");
						hd = temp->infohd;
						n = DemSoCTHD(hd.dscthd);
						tongtien = TinhTongGiaTriHoaDon(hd.dscthd);
						tongtrang = n / 10 + (n % 10 == 0 ? 0 : 1);
						if(hd.loai = 'N') loai = "Hoa Don Nhap";
						else loai = "Hoa Don Xuat";
						SetColor(CYAN);
						gotoxy(x, y - 4); cout << "Nhan Vien Lap: " << nguoilap;
						gotoxy(x, y - 3); cout << "So HD: " << hd.sohd;
						gotoxy(x, y - 2); cout << "Ngay Lap: " << hd.ngaylap.ngay << "/" << hd.ngaylap.thang << "/" << hd.ngaylap.nam;
						gotoxy(x, y - 1); cout << "Loai HD: " << loai;
						gotoxy(x, y + 23); cout << "Tri Gia HD: " << tongtien;
						InCTHD(hd.dscthd, trang, tongtrang, x, y);
						do
						{
							c = KeyPressed();
							if(c == KEY_LEFT) 
								if (trang > 1)
								{
									trang--;
									InCTHD(hd.dscthd, trang, tongtrang, x, y);
								} 
							if(c == KEY_RIGHT) 
								if (trang < tongtrang)
								{
									trang++;
									InCTHD(hd.dscthd, trang, tongtrang, x, y);
								}
						}while(c != KEY_ESC);
						sohd = "";
						goto NhapLai;
					}
					else
					{
						ThongBao("So Hoa Don Khong Ton Tai");
						sohd = "";
						goto NhapLai;
					}
				}
			}
		}
	}while(c != KEY_ESC);
}
string TenDayDuCuaNhanVien(NHANVIEN nv)
{
	return nv.ho + " " + nv.ten;
}
void TaoBangDanhSachHoaDon(int x, int y, int socot, int sodong, int kichthuoccot)
{
	VeBangDanhSach(x, y, socot, sodong, kichthuoccot);	
	SetColor(CYAN);
	SetBGColor(BLACK);
	int xlabel;
	for (int i = 0; i < 5; i++)
	{
		xlabel = x + i * (kichthuoccot + 1) + 1 + (kichthuoccot - tenCotHoaDon[i].length()) / 2;
		gotoxy(xlabel, y + 1);
		cout << tenCotHoaDon[i];
	}	
}
//hao
int DemSoHoaDonTrongKhoangThoiGian(DanhSachNhanVien ds, Date batdau, Date ketthuc)
{
	int dem = 0;
	int kiemTra;
	Date ngaylap;
	LISTHD hd = NULL;
	
	for(int i = 0; i < ds.n; i++)
	{
		hd = ds.nodes[i]->dshd;					
		while(hd != NULL)
		{
			ngaylap = hd->infohd.ngaylap;
			if(KiemTraThoiGian(batdau, ketthuc, ngaylap)) dem++;
			hd = hd->next;
		}
	}
	return dem;
}
void TraVeMangHoaDon(string **a, DanhSachNhanVien ds, Date batdau, Date ketthuc)
{
	LISTHD hd = NULL;
	HOADON temp;
	NHANVIEN nv;
	int kt;
	Date ngaylap;
	int j = 0;
	long long tien;
	string s;
	for(int i = 0; i < ds.n; i++)
	{
		nv = *ds.nodes[i];
		hd = nv.dshd;	
		while(hd != NULL)
		{
			temp = hd->infohd;
			ngaylap = temp.ngaylap;
			if(KiemTraThoiGian(batdau, ketthuc, ngaylap))
			{
				tien = TinhTongGiaTriHoaDon(temp.dscthd);
				s = ToString(tien);
				a[j][0] = temp.sohd;						// So HD
				a[j][1] = ChuyenNgayThanhChuoi(ngaylap);		// Ngay lap		
				if (temp.loai == 'X') a[j][2] = "Xuat";	// Loai hd
				else a[j][2] = "Nhap";		
				a[j][3] = TenDayDuCuaNhanVien(nv);				// nv lap
				a[j][4] = s;							// Tri gia hoa don
				j++;
			}				
			hd = hd->next;
		}
	}
}
void VeFormThongKeHoaDon(Date batdau, Date ketthuc)
{
	XoaManHinh();
	SetColor(CYAN);
	SetBGColor(BLACK);
	string s = "BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1);
	cout << s;
	s = "Tu Ngay: " + ChuyenNgayThanhChuoi(batdau) + " Den Ngay: " + ChuyenNgayThanhChuoi(ketthuc);
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 3);
	cout << s;
	VeFooter("Esc: Thoat \t <- Trang Truoc   Trang Sau ->");
}
void InThongKeHoaDon(string **a, int n, int trang, int tongtrang, Date batdau, Date ketthuc)
{
	TaoBangDanhSachHoaDon(37, 11, 5, 11, 20);
	int vtDau = (trang - 1) * 10;
	int xtro;
	int ytro;
	int tam = 0;
	SetColor(WHITE);
	for(int i = vtDau; i < trang * 10 && i < n; i++)
	{
		ytro = 11 + 3 + 2 * tam;
		tam++;
		// so hoa don
		xtro = 37 + 0 * (20 + 1) + 1 + (20 - a[i][0].length()) / 2;
		gotoxy(xtro, ytro);
		cout << a[i][0];
		// ngay lap
		xtro = 37 + 1 * (20 + 1) + 1 + (20 - a[i][1].length()) / 2;
		gotoxy(xtro, ytro);
		cout << a[i][1];
		// loai hoa don
		xtro = 37 + 2 * (20 + 1) + 1 + (20 - a[i][2].length()) / 2;
		gotoxy(xtro, ytro);
		cout << a[i][2];
		// nhan vien lap
		xtro = 37 + 3 * (20 + 1) + 1 + (20 - a[i][3].length()) / 2;
		gotoxy(xtro, ytro);
		cout << a[i][3];
		// tri gia hoa don
		xtro = 37 + 4 * (20 + 1) + 1 + (20 - a[i][4].length()) / 2;
		gotoxy(xtro, ytro);
		cout << a[i][4];
	}
	PhanTrang(trang, tongtrang, 1, 2);
}
void ModuleThongKeHoaDon(DanhSachNhanVien ds)
{
	if(ds.n == 0)
	{
		ThongBao("Danh Sach Rong");	
		return;
	}
	Date batdau, ketthuc;	
	string ngbd, thbd, nambd, ngkt, thkt, namkt;
	int a, b;
	int idx = 0;
	int idxerror = 0;
	int c;
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 16;
	int yinput = ylabel;
	int n;
	int trang = 1, tongtrang;
	int kq;
	string **arr;
NhapLai:
	XoaManHinh();
	VeFooter("Esc: Thoat   Enter: Ok   Insert: Di Chuyen Con Tro Nhap Lieu");
	SetColor(CYAN);
	gotoxy(xlabel, ylabel); 
	cout << "Tu Ngay: ";
	VeInputNhapNgay(xinput - 2, yinput - 1); 
	SetColor(CYAN);
	gotoxy(xlabel + 40, ylabel); 
	cout << "Den Ngay: ";
	VeInputNhapNgay(xinput + 38, yinput - 1); 
	SetColor(WHITE);
	gotoxy(xinput - 1, yinput); cout << ngbd;
	gotoxy(xinput + 4, yinput); cout << thbd;
	gotoxy(xinput + 9, yinput); cout << nambd;
	gotoxy(xinput + 39, yinput); cout << ngkt;
	gotoxy(xinput + 44, yinput); cout << thkt;
	gotoxy(xinput + 49, yinput); cout << namkt;
	do
	{
		switch (idx)
		{
			// thoi gian batdau
			case 0:
				c = NhapChuoiKiTuSo(ngbd,xinput - 1, yinput, 2, BLACK, WHITE);
				break;
			case 1:
				c = NhapChuoiKiTuSo(thbd,xinput + 4, yinput, 2, BLACK, WHITE);
				break;
			case 2:
				c = NhapChuoiKiTuSo(nambd,xinput + 9, yinput, 4, BLACK, WHITE);
				break;
			// thoi gian ketthuc
			case 3:
				c = NhapChuoiKiTuSo(ngkt,xinput + 39, yinput, 2, BLACK, WHITE);
				break;
			case 4:
				c = NhapChuoiKiTuSo(thkt,xinput + 44, yinput, 2, BLACK, WHITE);
				break;
			case 5:
				c = NhapChuoiKiTuSo(namkt, xinput + 49, yinput, 4, BLACK, WHITE);
				break;
		}
				
		if (c == KEY_INSERT && idx < 6) 
		{
			idx++;
			if(idx == 6) idx = 0;
		}
		if (c == KEY_ENTER)
		{
			stringstream(ngbd) >> batdau.ngay;
			stringstream(thbd) >> batdau.thang;
			stringstream(nambd) >> batdau.nam;			
			stringstream(ngkt) >> ketthuc.ngay;
			stringstream(thkt) >> ketthuc.thang;
			stringstream(namkt) >> ketthuc.nam;
			a = KiemTraThoiGian(batdau.ngay, batdau.thang, batdau.nam, idxerror);
			b = KiemTraThoiGian(ketthuc.ngay, ketthuc.thang, ketthuc.nam, idxerror);
					
			if(a == 0 || b == 0)
			{
				if (a == 0) idx = idxerror;
				else if (b == 0) idx = idxerror + 3;
				ThongBao("Thoi Gian Nhap Vao Khong Hop Le");
				goto NhapLai;
			} 
			else 
			{
				kq = SoSanhThoiGian(ketthuc, batdau);
				if (kq == -1)
				{ 
					ThongBao("Thoi Gian Nhap Vao Khong Hop Le");
					idx = 2; 
					goto NhapLai;
				} 
				else
				{	
					n = DemSoHoaDonTrongKhoangThoiGian(ds, batdau, ketthuc);
					if(n == 0)
					{
						ThongBao("Danh Sach Rong");
						ngbd = thbd = nambd = "";
						ngkt = thkt = namkt = "";
						idx = 0;
						goto NhapLai;
					}
					arr = new string* [n];
					for(int i = 0; i < n; i++) 
					{
						arr[i] = new string[5]{""};
					}
					TraVeMangHoaDon(arr, ds, batdau, ketthuc);
					tongtrang = n / 10;
					if(n % 10 != 0) tongtrang++;
					VeFormThongKeHoaDon(batdau, ketthuc);
					InThongKeHoaDon(arr, n, trang, tongtrang, batdau, ketthuc);
					do
					{
						c = KeyPressed();
						if(c == KEY_RIGHT && trang < tongtrang) 
						{
							trang++;
							InThongKeHoaDon(arr, n, trang, tongtrang, batdau, ketthuc);
						}
						if(c == KEY_LEFT && trang > 1)
						{
							trang--;
							InThongKeHoaDon(arr, n, trang, tongtrang, batdau, ketthuc);
						}
					}while(c != KEY_ESC);
					for(int i = 0; i < n; i++)
					{
						delete[] arr[i];
					}
					delete[] arr;
					break;
				}
			}
		}
	}while(c != KEY_ESC);
}
void TaoBangThongKeVatTu(int x, int y, int socot, int sodong, int kichthuoccot)
{
	VeBangDanhSach(x, y, socot, sodong, kichthuoccot);	
	SetColor(CYAN);
	SetBGColor(BLACK);
	int xlabel;
	for (int i = 0; i < 4; i++)
	{
		xlabel = x + i * (kichthuoccot + 1) + 1 + (kichthuoccot - tenCotBangTop10[i].length()) / 2;
		gotoxy(xlabel, y + 1);
		cout << tenCotBangTop10[i];
	}	
}
void VeFormThongKeVatTu(Date batdau, Date ketthuc)
{	
	XoaManHinh();
	string s = "THONG KE DANH SACH TOP 10 VAT TU XUAT";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1);
	SetColor(CYAN);
	cout << s;
	s = "Tu ngay: " + ChuyenNgayThanhChuoi(batdau) + " Den Ngay: " + ChuyenNgayThanhChuoi(ketthuc);
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 3);
	cout << s;
	VeFooter("Esc: Tro ve");
}
void InThongKeVatTu(ThongKe a[], int soluongvt, VATTUTREE &root, int trang, int tongtrang)
{
	int x = 47, y = 11;
	TaoBangThongKeVatTu(x, y, 4, 11, 20);
	int vtri = (trang - 1) * 10;
	DanhSachVatTu ds; PreOrder(root, ds);
	int tam = 0;
	int xtro;
	int ytro;
	string str = "";
	VatTu vt;
	SetColor(WHITE);
	for(int i = vtri; i < trang * 10 && i < soluongvt; i++)
	{										
		vt = ds.nodes[a[i].idx];
		ytro = y + 3 + 2 * tam;
		tam++;
		// stt
		str = ChuyenSoThanhChuoi(i + 1);
		xtro = x + 0 * (20 + 1) + 1 + (20 - str.length()) / 2;
		gotoxy(xtro, ytro);
		cout << str;
		// ma vat tu
		xtro = x + 1 * (20 + 1) + 1 + (20 - vt.mavt.length()) / 2;
		gotoxy(xtro, ytro);
		cout << vt.mavt;
		// ten vat tu
		xtro = x + 2 * (20 + 1) + 1 + (20 - vt.tenvt.length()) / 2;
		gotoxy(xtro, ytro);
		cout << vt.tenvt;				
		// so luong
		xtro = x + 3 * (20 + 1) + 1 + (20 - ChuyenSoThanhChuoi(a[i].soluongxuat).length()) / 2;
		gotoxy(xtro, ytro);
		cout << a[i].soluongxuat;
	}
	PhanTrang(trang, tongtrang, 0, 2);	
}
// module thong ke top 10 vat tu
void ModuleThongKeVatTu(DanhSachNhanVien ds, VATTUTREE root)
{
	if(ds.n == 0)
	{
		ThongBao("Danh Sach Rong");	
		return;
	}
	Date batdau, ketthuc;	
	string ngbd, thbd, nambd, ngkt, thkt, namkt;
	int a, b;
	int idx = 0;
	int idxerror = 0;
	int c;
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 16;
	int yinput = ylabel;
	int trang = 1, tongtrang;
	int kq;
	int n = 0; DemSoLuongVatTu(root, n);
	struct ThongKe arr[n];
NhapLai2:
	XoaManHinh();
	VeFooter("Esc: Thoat   Enter: Ok   Insert: Di Chuyen Con Tro Nhap Lieu");
	SetColor(CYAN);
	gotoxy(xlabel, ylabel); 
	cout << "Tu Ngay: ";
	VeInputNhapNgay(xinput - 2, yinput - 1); 
	SetColor(CYAN);
	gotoxy(xlabel + 40, ylabel); 
	cout << "Den Ngay: ";
	VeInputNhapNgay(xinput + 38, yinput - 1); 
	SetColor(WHITE);
	gotoxy(xinput - 1, yinput); cout << ngbd;
	gotoxy(xinput + 4, yinput); cout << thbd;
	gotoxy(xinput + 9, yinput); cout << nambd;
	gotoxy(xinput + 39, yinput); cout << ngkt;
	gotoxy(xinput + 44, yinput); cout << thkt;
	gotoxy(xinput + 49, yinput); cout << namkt;
	do
	{
		switch (idx)
		{
			// thoi gian batdau
			case 0:
				c = NhapChuoiKiTuSo(ngbd, xinput - 1, yinput, 2, BLACK, WHITE);
				break;
			case 1:
				c = NhapChuoiKiTuSo(thbd, xinput + 4, yinput, 2, BLACK, WHITE);
				break;
			case 2:
				c = NhapChuoiKiTuSo(nambd, xinput + 9, yinput, 4, BLACK, WHITE);
				break;
			// thoi gian ketthuc
			case 3:
				c = NhapChuoiKiTuSo(ngkt, xinput + 39, yinput, 2, BLACK, WHITE);
				break;
			case 4:
				c = NhapChuoiKiTuSo(thkt, xinput + 44, yinput, 2, BLACK, WHITE);
				break;
			case 5:
				c = NhapChuoiKiTuSo(namkt, xinput + 49, yinput, 4, BLACK, WHITE);
				break;
		}
				
		if (c == KEY_INSERT && idx < 6) 
		{
			idx++;
			if(idx == 6) idx = 0;
		}
		if (c == KEY_ENTER)
		{
			stringstream(ngbd) >> batdau.ngay;
			stringstream(thbd) >> batdau.thang;
			stringstream(nambd) >> batdau.nam;			
			stringstream(ngkt) >> ketthuc.ngay;
			stringstream(thkt) >> ketthuc.thang;
			stringstream(namkt) >> ketthuc.nam;
			a = KiemTraThoiGian(batdau.ngay, batdau.thang, batdau.nam, idxerror);
			b = KiemTraThoiGian(ketthuc.ngay, ketthuc.thang, ketthuc.nam, idxerror);
					
			if(a == 0 || b == 0)
			{
				if (a == 0) idx = idxerror;
				else if (b == 0) idx = idxerror + 3;
				ThongBao("Thoi Gian Nhap Vao Khong Hop Le");
				goto NhapLai2;
			} 
			else 
			{
				kq = SoSanhThoiGian(ketthuc, batdau);
				if (kq == -1)
				{ 
					ThongBao("Thoi Gian Nhap Vao Khong Hop Le");
					idx = 2; 
					goto NhapLai2;
				} 
				else
				{				
					TraVeMangVatTuXuat(arr, ds, root, batdau, ketthuc);
					for(int i = 0; i < n - 1; i++)
					{
						for(int j = i + 1; j < n; j++)
						{
							if(arr[i].soluongxuat < arr[j].soluongxuat)
							{
								ThongKe temp = arr[i];
								arr[i] = arr[j];
								arr[j] = temp;
							}
						}
					}
					int soluongvt = 0;
					for(int i = 0; i < 10 && i < n; i++)
					{
						if(arr[i].soluongxuat != 0)
						{
							soluongvt++;
						}
						if(arr[i].soluongxuat == 0) break;
					}
					for(int i = 10; i < n && soluongvt > 9; i++)
					{
						if(arr[i].soluongxuat == arr[i - 1].soluongxuat && arr[i - 1].soluongxuat != 0)
						{
							soluongvt++;
						}
						else break;
					}
					if(arr[0].soluongxuat == 0)
					{
						ThongBao("Danh Sach Rong");
						ngbd = thbd = nambd = "";
						ngkt = thkt = namkt = "";
						idx = 0;
						goto NhapLai2;	
					}
					else
					{
						int trang = 1;
						int tongtrang = soluongvt / 10 + (soluongvt % 10 == 0 ? 0 : 1);					 
						VeFormThongKeVatTu(batdau, ketthuc);
						InThongKeVatTu(arr, soluongvt, root, trang, tongtrang);
						do 
						{
							c = KeyPressed();				
							if(c == KEY_RIGHT)
							{
								if(trang < tongtrang) 
								{
									trang++;
									InThongKeVatTu(arr, soluongvt, root, trang, tongtrang);
								}							
							}else if(c == KEY_LEFT)
							{
								if(trang > 1) 
								{
									trang--;
									InThongKeVatTu(arr, soluongvt, root, trang, tongtrang);
								}
							}
							if(c == KEY_ESC) break;		
						}while(true);
					}
				}
			}
		}
	}while(c != KEY_ESC);
}

