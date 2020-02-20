#include "VatTu.cpp"
bool KiemTraRong(LISTCTHD dscthd)
{
	if(dscthd == NULL) return true;
	return false;
}
bool ThemVaoCuoiDanhSach(LISTCTHD &dscthd, CTHD cthd)
{
	LISTCTHD p = new NodeCTHD;
	if(p == NULL) return false;
	p->infocthd = cthd;
	p->next = NULL;
	
	if(dscthd == NULL)
	{
		dscthd = p;
	}
	else
	{
		LISTCTHD q;
		for(q = dscthd; q->next != NULL; q = q->next);
		q->next = p;
	}
	return true;
}
int DemSoCTHD(LISTCTHD dscthd)
{
	LISTCTHD p = dscthd;
	int dem = 0;
	while(p != NULL)
	{
		dem++;
		p = p->next;
	}
	return dem;
}
void FormXuatCTHD(NHANVIEN nv, HOADON hd)
{
	XoaManHinh();
	int x = 37, y = 11;
	SetBGColor(BLACK);
	SetColor(CYAN);
	string s = "BANG CHI TIET HOA DON";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 2);
	cout << s;
	gotoxy(x,y - 4);
	cout << "Nhan vien: " << nv.ho << " " << nv.ten;
	gotoxy(x,y - 3);
	cout << "So HD    : " << hd.sohd;
	gotoxy(x,y - 2);
	cout << "Loai HD  :";
	if(hd.loai == 'X') cout << " Xuat";
	else cout << " Nhap";
	gotoxy(x,y - 1); 
	cout << "Ngay lap : " << ChuyenNgayThanhChuoi(hd.ngaylap);
	SetBGColor(BLACK);
	SetColor(WHITE);
	VeFooter("Esc: Thoat     <- Trang Truoc     -> Trang Sau");
}
long long TinhTongTienMotVatTu(CTHD cthd)
{
	long long tong = 0;
	tong = (cthd.dongia * cthd.soluong);
	
	return tong * double((100 + cthd.vat)/ 100.0);
}
long long TinhTongGiaTriHoaDon(LISTCTHD dscthd)
{
	long long tong = 0;
	LISTCTHD p = dscthd;
	if(p == NULL) return 0;
	while(p != NULL)
	{
		tong += TinhTongTienMotVatTu(p->infocthd);
		p = p->next;
	}
	return tong;
}
void InCTHD(LISTCTHD dscthd, int trang, int tongtrang, int x, int y)
{
	long long tien;
	LISTCTHD p = dscthd;
	int dem = 0;
	int vtri = (trang - 1) * 10;
	VeBangDanhSach(x, y, 6, 11, 17);
	while(p != NULL && dem < vtri)
	{
		p = p->next;
		dem++;
	}
	SetColor(CYAN);
	int xlabel;
	for(int i = 0; i < 6; i++)
	{
		xlabel = x + i * (17 + 1) + 1 + (17 - tenCotBangCTHoaDon2[i].length()) / 2;
		gotoxy(xlabel, y + 1);
		cout << tenCotBangCTHoaDon2[i];
	}
	SetBGColor(BLACK);
	SetColor(WHITE);
	string s;
	int tam = 0;
	int xtro;
	int ytro;
	while(p != NULL && vtri < trang * 10)
	{
		ytro = y + 3 + 2 * tam;
		tam++;
		
		s = ChuyenSoThanhChuoi(vtri + 1);
		xtro = x + 0 * (17 + 1) + 1 + (17 - s.length()) / 2;
		gotoxy(xtro, ytro);				
		cout << s;
		
		xtro = x + 1 * (17 + 1) + 1 + (17 - p->infocthd.mavt.length()) / 2;
		gotoxy(xtro, ytro);			
		cout << p->infocthd.mavt;
		
		s = ChuyenSoThanhChuoi(p->infocthd.soluong);
		xtro = x + 2 * (17 + 1) + 1 + (17 - s.length()) / 2;
		gotoxy(xtro, ytro);				
		cout << s;
		
		s = ChuyenSoThanhChuoi(p->infocthd.dongia);
		xtro = x + 3 * (17 + 1) + 1 + (17 - s.length()) / 2;
		gotoxy(xtro, ytro);				
		cout << s;
		
		s = ChuyenSoThanhChuoi(p->infocthd.vat);
		xtro = x + 4 * (17 + 1) + 1 + (17 - s.length()) / 2;
		gotoxy(xtro, ytro);				
		cout << s;
		tien = TinhTongTienMotVatTu(p->infocthd);
		s = ToString(tien);
		xtro = x + 5 * (17 + 1) + 1 + (17 - s.length()) / 2;
		gotoxy(xtro, ytro);				
		cout << s;
		
		vtri++;
		p = p->next;
	}
	PhanTrang(trang, tongtrang, 0, 2);
}
void VeGiaoDienThemCTHD()
{
	XoaManHinh();
	SetColor(CYAN);
	SetBGColor(BLACK);
	string s = "NHAP CHI TIET HOA DON";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1);
	cout << s;
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 15;
	int yinput = ylabel - 1;
	for (int i = 0; i < 4; i++) //tao ra 4 input
	{
		gotoxy(xlabel, ylabel + 3 * i);
		cout << tenCotBangCTHoaDon[i];
		VeInputText(xinput, yinput + 3 * i, 0);
	}
	VeFooter("Esc: Tro ve \t F5: Danh Sach Vat Tu   Insert: Them");
}
void CapNhapSoLuongTonKho(VATTUTREE &root, char loai, CTHD cthd)
{
	VATTUTREE p = root;
	while(p != NULL && p->vattu.mavt != cthd.mavt)
	{
		if(cthd.mavt < p->vattu.mavt)
		{
			p = p->left;
		}
		else if(cthd.mavt > p->vattu.mavt)
		{
			p = p->right;
		} 
	}
	if(loai == 'N')
	{
		p->vattu.soluongton += cthd.soluong;
		return;
	}
	else
	{
		p->vattu.soluongton -= cthd.soluong;
		return;
	}
}
int TonTaiMaHoaDonTrongDSCTHD(LISTCTHD &dscthd, CTHD cthd)
{
	if(dscthd == NULL) return 0;
	for(LISTCTHD p = dscthd; p != NULL; p = p->next)
	{
		if(p->infocthd.mavt == cthd.mavt) return 1;//neu tim thay manv
	}
	return 0;
}
void CongDonSoLuongNeuTrungMa(LISTCTHD &dscthd, CTHD cthd)
{
	LISTCTHD p = dscthd;
	for(p; p != NULL; p = p->next)
	{
		if(p->infocthd.mavt == cthd.mavt)
		{
			p->infocthd.soluong += cthd.soluong;
			return;
		}
	}
}
void NhapChiTietHoaDon(VATTUTREE &root, HOADON &hd)
{
NHAPCTHOADON:
	VeGiaoDienThemCTHD();
	CTHD ct;
	string dongia = "";
	string vat = "";
	string soluong = "";
	string errors[4] = {"", "", "", ""};
	int c;
	bool res;
	int soluongxuat;
	DanhSachVatTu ds;
	PreOrder(root, ds);
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 16;
	int yinput = ylabel;
	int idx = 0;
	do
	{
		switch(idx)
		{
			case 0:
				c = NhapChuoiKiTuVaSo(ct.mavt, xinput, yinput , WIDTH_INPUT_TEXT, BLACK, WHITE);
				gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
				for (int i = 0; i < errors[idx].length(); i++) cout << " ";
				XoaKhoangTrang(ct.mavt); ChuanHoaMa(ct.mavt);
				if(ct.mavt == "")
				{
					errors[idx] = "Khong Duoc De Trong";
					SetColor(WHITE);
					gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
					cout << errors[idx]; 
				}else if(TimKiemVatTu(root, ct.mavt) == NULL)
				{
					errors[idx] = "Vat Tu Khong Ton Tai";
					SetColor(WHITE);
					gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
					cout << errors[idx];
				}else errors[idx] = "";
				break;
			case 1:	
				c = NhapChuoiKiTuSo(soluong, xinput, yinput + idx * 3, 10 , BLACK, WHITE);
				gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
				for (int i = 0; i < errors[idx].length(); i++) cout << " ";
				stringstream(soluong) >> soluongxuat;
				if(hd.loai == 'X')
				{
					if (soluong.length() <= 0) 
					{	
						errors[idx] = "Khong Duoc De Trong";
						SetColor(15);
						gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
						cout << errors[idx];
					}
					else if(soluongxuat > SoLuongVatTuTonKhoCuaMaVT(root, ct.mavt))
					{
						errors[idx] = "SL Ton Cua " + ct.mavt + " : " + ChuyenSoThanhChuoi(SoLuongVatTuTonKhoCuaMaVT(root, ct.mavt));
						SetColor(15);
						gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
						cout << errors[idx];
					}
					else errors[idx] = "";
				}
				else
				{
					if (soluong.length() <= 0) 
					{	
						errors[idx] = "Khong Duoc De Trong";
						SetColor(15);
						gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
						cout << errors[idx];
					}else errors[idx] = "";
				}
				break;
			case 2:	
				c = NhapChuoiKiTuSo(dongia, xinput , yinput + idx * 3, 20, BLACK, WHITE);
				gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
				for (int i = 0; i < errors[idx].length(); i++) cout << " ";
				if (dongia.length() <= 0) 
				{
					errors[idx] = "Khong Duoc De Trong";
					SetColor(15);
					gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
					cout << errors[idx];

				} else errors[idx] = "";
				break;
			case 3:	
				c = NhapChuoiKiTuSo(vat, xinput , yinput + idx * 3, 2, BLACK, WHITE);
				gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
				for (int i = 0; i < errors[idx].length(); i++) cout << " ";
				
				if (vat.length() <= 0) 
				{
					errors[idx] = "Khong Duoc De Trong";
					SetColor(15);
					gotoxy(xinput + WIDTH_INPUT_TEXT + 1, yinput + idx * 3);
					cout << errors[idx];

				}else errors[idx] = "";
				break;
		}
		
		if((c == KEY_DOWN || c == KEY_ENTER) && idx < 3) idx++;
		if(c == KEY_UP && idx > 0) idx--;
		
		if(c == KEY_INSERT)
		{
			XoaKhoangTrang(ct.mavt); ChuanHoaMa(ct.mavt);
			if(ct.mavt.length() > 0 && soluong.length() > 0 && dongia.length() > 0 && vat.length() > 0)
			{
				if(TimKiemVatTu(root, ct.mavt) != NULL)  // vat tu co ton tai trong cay
				{
					if(hd.loai == 'X')
					{
						if (soluongxuat <= SoLuongVatTuTonKhoCuaMaVT(root, ct.mavt))
						{
							stringstream(soluong) >> ct.soluong;
							stringstream(dongia) >> ct.dongia;
							stringstream(vat) >> ct.vat;
							if(TonTaiMaHoaDonTrongDSCTHD(hd.dscthd, ct))
							{
								CongDonSoLuongNeuTrungMa(hd.dscthd, ct);
								ThongBao("Them Vat Tu Thanh Cong");
							}
							else 
							{
								res = ThemVaoCuoiDanhSach(hd.dscthd, ct);	
								if(res == true)
								{
									ThongBao("Them Vat Tu Thanh Cong");
								}else
									ThongBao("That Bai");
							}
							CapNhapSoLuongTonKho(root, hd.loai, ct);
							goto NHAPCTHOADON;
						}
					}
					else 
					{
						stringstream(soluong) >> ct.soluong;
						stringstream(dongia) >> ct.dongia;
						stringstream(vat) >> ct.vat;
						if(TonTaiMaHoaDonTrongDSCTHD(hd.dscthd, ct))
						{
							CongDonSoLuongNeuTrungMa(hd.dscthd, ct);
							ThongBao("Them Vat Tu Thanh Cong");
						}
						else 
						{
							res = ThemVaoCuoiDanhSach(hd.dscthd, ct);	
							if(res == true)
							{
								ThongBao("Them Vat Tu Thanh Cong");
							}else
								ThongBao("That Bai");
						}
						CapNhapSoLuongTonKho(root, hd.loai, ct);
						goto NHAPCTHOADON;						
					}
				}
			}
		}
		if(c == KEY_F5)
		{
			XoaManHinh();
			SetColor(CYAN);
			string s = "DANH SACH VAT TU";
			gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 2);
			cout << s;
			VeFooter("Esc: Tro ve\t <-Trang Truoc \t Trang Sau->");
			DanhSachVatTu ds; PreOrder(root, ds);
			if (ds.n == 0)
			{
				string t = "Danh Sach Vat Tu Rong";
				ThongBao(t);	
			} 
			else
			{
				int trang = 1;
				int tongtrang = TongSoTrangVatTu(root);
				int c;
				InVatTu(root, trang, tongtrang, 37, 11, 5, 11, 20);
				string t = "DANH SACH VAT TU";
				gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - t.length()) / 2, TOADOY + HEIGHT_HEADER + 2);
				cout << t;	
				do 
				{
					c = KeyPressed();
					if(c == KEY_LEFT) 
					{
						if (trang > 1)
						{
							trang--;	
							InVatTu(root, trang, tongtrang, 37, 11, 5, 11, 20);	
							string h = "DANH SACH VAT TU";
							gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - h.length()) / 2, TOADOY + HEIGHT_HEADER + 2);
							cout << h;	
						} 
					} else if(c == KEY_RIGHT)
					{
						if (trang < tongtrang)
						{
							trang++;
							InVatTu(root, trang, tongtrang, 37, 11, 5, 11, 20);
							string h = "DANH SACH VAT TU";
							gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - h.length()) / 2, TOADOY + HEIGHT_HEADER + 2);
							cout << h;	
						} 
					}  
				} while (c != KEY_ESC);
			}	
			goto NHAPCTHOADON;		
		}
		if(c == KEY_ESC)
		{
			XoaManHinh();
			break;
		}
	}while (c != KEY_ESC);
}
void XuatChiTietHoaDon(NHANVIEN &nv, HOADON &hd)
{
	if(hd.dscthd == NULL)
	{
		XoaManHinh();
		string s = "Hoa Don Chua Co Chi Tiet";
		gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 7);
		cout << s;
		Sleep(1000);
		return; 
	}
	FormXuatCTHD(nv, hd);
	int sohang = 10;
	int c;
	int trang = 1;
	int socthd = DemSoCTHD(hd.dscthd);
	int tongtrang = socthd / sohang;
	if(socthd % sohang != 0) tongtrang++;
	if(socthd == 0) trang = tongtrang = 1;
	int x = 37, y = 11;
	do
	{
		SetBGColor(BLACK);
		SetColor(CYAN);
		PhanTrang(trang, tongtrang, 0, 2);
		InCTHD(hd.dscthd, trang, tongtrang, x, y);
		c = KeyPressed();
		if(c == KEY_RIGHT && trang < tongtrang) trang++;
		if(c == KEY_LEFT && trang > 1) trang--;
	}while(c != KEY_ESC);
}



