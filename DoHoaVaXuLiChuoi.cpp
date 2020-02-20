#include <mylib.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;
#define KEY_BACKSPACE 8
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_TAB 9
#define KEY_ESC 27
#define KEY_DOWN 80 + 256
#define KEY_UP 72 + 256
#define KEY_LEFT 75 + 256
#define KEY_RIGHT 77 + 256
#define KEY_DELETE 83 + 256
#define KEY_INSERT 82 + 256
#define KEY_F2 60 + 256
#define KEY_F3 61 + 256
#define KEY_F4 62 + 256
#define KEY_F5 63 + 256
// color
#define CYAN 3
#define BLACK 0
#define WHITE 15

#define TOADOX 5
#define TOADOY 2
#define SCREEN_WIDTH 150
#define SCREEN_HEIGTH 36
#define HEIGHT_HEADER 3
#define HEIGHT_FOOTER 3
#define WIDTH_MENU_BAR 20
#define WIDTH_BODY SCREEN_WIDTH - WIDTH_MENU_BAR
#define HEIGHT_BODY SCREEN_HEIGTH - HEIGHT_HEADER - HEIGHT_FOOTER
#define WIDTH_MESSAGE 50
#define WIDTH_INPUT_NGAY 17
// kich thuoc mang
#define MAX_NHAN_VIEN 500
#define MAX_VAT_TU 300
#define WIDTH_INPUT_TEXT 42
#define SIZE_MENU 5
#define FILE_VAT_TU "vattu.txt"
#define FILE_NHAN_VIEN "nhanvien.txt"
string menu[]={"Vat Tu", "Nhan Vien", "In Hoa Don", "Thong Ke Hoa Don", "Danh Sach Ban Chay"};
string thuocTinhVatTu[4] = {"Ma Vat Tu", "Ten Vat Tu", "Don Vi Tinh", "So Luong Ton"};
string nhanCuaBangDanhSachVatTu[5] = {"STT", "Ma Vat Tu", "Ten Vat Tu", "Don Vi Tinh", "So Luong Ton"};
string lableNhanVien[4] = {"Ma nhan vien", "Ho", "Ten", "Phai"};
string tenCotBangNhanVien[] = {"STT", "Ma Nhan Vien", "Ho", "Ten", "Phai"};
string lable[3] = {"So Hoa Don", "Ngay Lap", "Loai"};
string tenCotHoaDon[5] = {"So HD", "Ngay Lap", "Loai HD", "Nhan Vien Lap", "Tri Gia HD"};
string tenCotHoaDon2[5] = {"STT", "So HD", "Ngay Lap", "Loai HD", "Tri Gia HD"};
string tenCotBangCTHoaDon[] = {"Ma Vat Tu", "So Luong" , "Don Gia", "VAT"};
string tenCotBangCTHoaDon2[] = {"STT", "Ma Vat Tu", "So Luong" , "Don Gia", "VAT", "Thanh Tien"};
string tenCotBangTop10[] = {"STT", "Ma Vat Tu", "Ten Vat Tu", "So Luong Xuat"};

struct Date
{
	int ngay, thang, nam;
};
Date LayGioHeThong()
{
	time_t t = time(0);
	struct tm * now = localtime(&t);
	Date date;
	date.ngay = now->tm_mday;
	date.thang = now->tm_mon + 1;
	date.nam = now->tm_year + 1900;
	return date;
}
void ResizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
int KeyPressed()
{
	int a = getch();
	if(a == 0 || a == 224)
	{
		a = 256 + getch();
	}
	return a;
}
void ChuanHoaChuoi(string &s)
{
	for(int i = 0; i < s.length() - 1; i++)
	{
		if(s[i] == ' ' && s[i + 1] == ' ')
		{
			s.erase(i, 1);
			i--;	
		}
	}
	if(s[0] == ' ') s.erase(0, 1);
	if(s[s.length() - 1] == ' ') s.erase(s.length() - 1, 1);
	
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] >= 'A' && s[i] <= 'Z')
		{
			s[i] += 32;
			i--;
		}
	}
	if(s[0] >= 'a' && s[0] <= 'z') s[0] -= 32;
	for(int i = 0; i < s.length() - 1; i++)
	{
		if(s[i] == ' ' && s[i + 1] != ' ')
		{
			if(s[i + 1] >= 'a' && s[i + 1] <= 'z') s[i + 1] -= 32;
		}
	}
}
void XoaKhoangTrang(string &s)
{
	int n = s.length();
	for(int i = 0; i < n; i++)
	{
		if(s[i] == ' ')
		{
			s.erase(i, 1);
			i--;
		}
	}
}
void ChuanHoaMa(string &s)
{
	int n = s.length();
	for(int i = 0; i < n; i++)
	{
		if(s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] -= 32;
		}
	}
}
template <typename T>
string ToString(T val)
{
    stringstream stream;
    stream << val;
    return stream.str();
}
string ChuyenSoThanhChuoi(int number)
{
	if(number == 0) return "0";
    string s = "";
	while (number!= 0)
	{
		s = char((number % 10) + 48) + s;
		number = number / 10;
	}
	return s;
}
string ChuyenNgayThanhChuoi(Date date)
{
	string s = "";
	string temp = "";
	temp = ChuyenSoThanhChuoi(date.ngay);
	s += temp + "/";
	temp = ChuyenSoThanhChuoi(date.thang);
	s += temp + "/";
	temp = ChuyenSoThanhChuoi(date.nam);
	s += temp;
	return s;
}
int NhapChuoiKiTuVaSo(string &s, int x, int y, int dodaichuoi, int maunen, int mauchu)
{
	SetBGColor(maunen);
	SetColor(mauchu);
	int n = s.length();
	int contro = s.length();
	gotoxy(x, y);
	cout << s;
	int c;
	char a;
	do
	{
		c = KeyPressed();
		if((c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0'&& c <= '9' || c == KEY_SPACE) && n < dodaichuoi)
		{
			a = char(c); 
			s.insert(contro, 1, a);
			for(int i = contro; i < s.length(); i++)
			{
				cout << s[i];
			}
			contro++;
			n++;
			gotoxy(x + contro, y);
		}else if(c == KEY_BACKSPACE && n != 0 && contro > 0) 
		{	
			s.erase(--contro, 1);
			gotoxy(x + contro, y);
			for(int i = contro; i <= n; i++)
			{
				cout << " ";
			}
			gotoxy(x + contro, y);
			for(int i = contro; i < n; i++)
			{
				cout << s[i];
			}
			n--;
			gotoxy(x + contro, y);
		}else if(c == KEY_DELETE && n != 0)
		{
			s.erase(contro, 1);
			gotoxy(x + contro, y);
			for(int i = contro; i <= n; i++)
			{
				cout << " ";
			}
			gotoxy(x + contro, y);
			for(int i = contro; i < n; i++)
			{
				cout << s[i];
			}
			n--;
			gotoxy(x + contro, y);	
		}else if(c == KEY_LEFT)
		{
			if(contro > 0)
			{
				contro--;
				gotoxy(x + contro, y);
			}
		}else if(c == KEY_RIGHT)
		{
			if(contro < n)
			{
				contro++;
				gotoxy(x + contro, y);
			}
		}
	}while(c != KEY_ENTER && c != KEY_UP && c != KEY_DOWN && c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F5);
	return c;
}

int NhapChuoiKiTu(string &s, int x, int y, int dodaichuoi, int maunen, int mauchu)
{
	SetBGColor(maunen);
	SetColor(mauchu);
	int n = s.length();
	int c;
	gotoxy(x, y);
	cout << s;
	int contro = s.length();
	char a;
	do
	{
		c = KeyPressed();
		if((c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'|| c == KEY_SPACE)&& n < dodaichuoi)
		{
			a = char(c); 
			s.insert(contro, 1, a);
			for(int i = contro; i < s.length(); i++)
			{
				cout << s[i];
			}
			contro++;
			n++;
			gotoxy(x + contro, y);
		}else if(c == KEY_BACKSPACE && n != 0 && contro > 0) 
		{	
			s.erase(--contro, 1);
			gotoxy(x + contro, y);
			for(int i = contro; i <= n; i++)
			{
				cout << " ";
			}
			gotoxy(x + contro, y);
			for(int i = contro; i < n; i++)
			{
				cout << s[i];
			}
			n--;
			gotoxy(x + contro, y);
		}else if(c == KEY_DELETE && n != 0)
		{
			s.erase(contro, 1);
			gotoxy(x + contro, y);
			for(int i = contro; i <= n; i++)
			{
				cout << " ";
			}
			gotoxy(x + contro, y);
			for(int i = contro; i < n; i++)
			{
				cout << s[i];
			}
			n--;
			gotoxy(x + contro, y);	
		}else if(c == KEY_LEFT)
		{
			if(contro > 0)
			{
				contro--;
				gotoxy(x + contro, y);
			}
		}else if(c == KEY_RIGHT)
		{
			if(contro < n)
			{
				contro++;
				gotoxy(x + contro, y);
			}
		}
	}while(c != KEY_ENTER && c != KEY_UP && c != KEY_DOWN && c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F5);
	return c;
}
int NhapChuoiKiTuSo(string &s, int x, int y, int dodaichuoi, int maunen, int mauchu)
{
	SetBGColor(maunen);
	SetColor(mauchu);
	int n = s.length();
	int c;
	gotoxy(x, y);
	cout << s;
	int contro = s.length();
	char a;
	do
	{
		c = KeyPressed();
		if(c >= '0'&& c <= '9' && n < dodaichuoi)
		{
			a = char(c); 
			s.insert(contro, 1, a);
			for(int i = contro; i < s.length(); i++)
			{
				cout << s[i];
			}
			contro++;
			n++;
			gotoxy(x + contro, y);
		}else if(c == KEY_BACKSPACE && n != 0 && contro > 0) 
		{	
			s.erase(--contro, 1);
			gotoxy(x + contro, y);
			for(int i = contro; i <= n; i++)
			{
				cout << " ";
			}
			gotoxy(x + contro, y);
			for(int i = contro; i < n; i++)
			{
				cout << s[i];
			}
			n--;
			gotoxy(x + contro, y);
		}else if(c == KEY_DELETE && n != 0)
		{
			s.erase(contro, 1);
			gotoxy(x + contro, y);
			for(int i = contro; i <= n; i++)
			{
				cout << " ";
			}
			gotoxy(x + contro, y);
			for(int i = contro; i < n; i++)
			{
				cout << s[i];
			}
			n--;
			gotoxy(x + contro, y);	
		}else if(c == KEY_LEFT)
		{
			if(contro > 0)
			{
				contro--;
				gotoxy(x + contro, y);
			}
		}else if(c == KEY_RIGHT)
		{
			if(contro < n)
			{
				contro++;
				gotoxy(x + contro, y);
			}
		}
	}while(c != KEY_ENTER && c != KEY_UP && c != KEY_DOWN && c != KEY_TAB && c!= KEY_INSERT && c!= KEY_ESC && c != KEY_F5);
	return c;
}
void VeHinhChuNhat(int x, int y, int chieudai, int chieurong, int color)
{
	SetBGColor(color);
	for(int i = 0; i < chieurong; i++)
	{
		gotoxy(x, y + i);
		for(int j = 0; j < chieudai; j++)
		{
			cout <<" ";
		}
	}
	SetBGColor(BLACK);	
}
void ThongBao(string noidung)
{
	VeHinhChuNhat(TOADOX + WIDTH_MENU_BAR +  (SCREEN_WIDTH - WIDTH_MENU_BAR - WIDTH_MESSAGE) / 2, (SCREEN_HEIGTH - 5) / 2, WIDTH_MESSAGE, 5, CYAN);
	gotoxy(TOADOX + WIDTH_MENU_BAR +  (SCREEN_WIDTH - WIDTH_MENU_BAR - WIDTH_MESSAGE) / 2 + (WIDTH_MESSAGE - noidung.length())/2, 
		   (SCREEN_HEIGTH - 5) / 2 + 5 / 2);
	SetBGColor(CYAN);
	SetColor(WHITE);
	cout << noidung;
	getch();
}

int HopThoaiLuaChon(string noidung, int x, int y, int chieudai, int chieurong)
{
	VeHinhChuNhat(x, y, chieudai, chieurong, CYAN);
	gotoxy(x + (chieudai - noidung.length()) / 2, y + chieurong / 2 - 1);
	SetBGColor(CYAN);
	SetColor(WHITE);
	cout << noidung;
	gotoxy(x + chieudai / 4 - 2, y + chieurong / 2 + 1);
	cout << "Co";
	gotoxy(x +(chieudai / 4) * 3 - chieudai / 8, y + chieurong / 2 + 1);
	cout << "Khong";
	int c;
	int luachon = 0;
	do
	{
		if(luachon == 0)
		{
			VeHinhChuNhat(x + chieudai / 4 - 2, y + chieurong / 2 + 1, 7, 1, CYAN);
			gotoxy(x + chieudai / 4, y + chieurong / 2 + 1);
			SetBGColor(CYAN);
			SetColor(WHITE);
			cout << "Co";
			
			VeHinhChuNhat(x +(chieudai / 4) * 3 - chieudai / 8 - 1, y + chieurong / 2 + 1, 7, 1, BLACK);
			gotoxy(x +(chieudai / 4) * 3 - chieudai / 8, y + chieurong / 2 + 1);
			SetBGColor(BLACK);
			SetColor(WHITE);
			cout << "Khong";
		}
		else
		{
			VeHinhChuNhat(x + (chieudai / 4) * 3 - chieudai / 8 - 1, y + chieurong / 2 + 1, 7, 1, CYAN);
			gotoxy(x + (chieudai / 4) * 3 - chieudai / 8, y + chieurong / 2 + 1);
			SetBGColor(CYAN);
			SetColor(WHITE);
			cout << "Khong";
			
			VeHinhChuNhat(x + chieudai / 4 - 2, y + chieurong / 2 + 1, 6, 1, BLACK);
			gotoxy(x + chieudai / 4, y + chieurong / 2 + 1);
			SetBGColor(BLACK);
			SetColor(WHITE);
			cout << "Co";
			
		}
		c = KeyPressed();
		if(c == KEY_LEFT) luachon = 1;
		if(c == KEY_RIGHT) luachon = 0;
	}while(c != KEY_ENTER && c != KEY_ESC);
	if(c == KEY_ESC) return 0;
	return luachon;
}
void VeDuongVien(int x, int y, int chieudai, int maunen, int mauchu)
{
	gotoxy(x, y);
	SetBGColor(maunen);
	SetColor(mauchu);
	for (int i = 0; i < chieudai; i++)
	{
		cout << char(196);
	}
}

void VeInputText(int x, int y, int temp)
{
	SetColor(CYAN);
	SetBGColor(BLACK);
	
	gotoxy(x, y);
	cout << char (218);
	for (int i = 1; i < WIDTH_INPUT_TEXT - temp; i++) cout << char (196);
	cout << char (191);
	
	gotoxy(x, y + 1);
	cout << char (179);
	gotoxy(x + WIDTH_INPUT_TEXT - temp, y + 1);
	cout << char (179);
	
	gotoxy(x, y + 2);
	cout << char (192);
	for (int i = 1; i < WIDTH_INPUT_TEXT - temp; i++) cout << char (196);
	cout << char (217);
}
void VeInputLuaChon(int x, int y)
{
	SetColor(CYAN);
	SetBGColor(BLACK);
	
	gotoxy(x, y);
	cout << char (218);
	for (int i = 1; i < 4; i++) cout << char (196);
	cout << char (191);
	
	gotoxy(x, y + 1);
	cout << char (179);
	gotoxy(x + 4, y + 1);
	cout << char (179);
	
	gotoxy(x, y + 2);
	cout << char (192);
	for (int i = 1; i < 4; i++) cout << char (196);
	cout << char (217);
}
void VeInputNhapNgay(int x, int y)
{
	SetColor(CYAN);
	SetBGColor(BLACK);
	gotoxy(x, y);
	cout << char (218);
	for (int i = 1; i < WIDTH_INPUT_NGAY; i++) cout << char (196);
	cout << char (191);
	gotoxy(x, y + 1);
	cout << char (179);
	gotoxy(x + WIDTH_INPUT_NGAY, y + 1);
	cout << char (179);
	gotoxy(x, y + 2);
	cout << char (192);
	for (int i = 1; i < WIDTH_INPUT_NGAY; i++) cout << char (196);
	cout << char (217);
	gotoxy(x + 5, y + 1);
	cout << "/";
	gotoxy(x + 10, y + 1);
	cout << "/";
}
void VeBangDanhSach(int x, int y, int socot, int sodong, int kichthuoccot)
{
	SetColor(WHITE);
	SetBGColor(BLACK);
	// Tao bang
	// 218 --- 196 --- 194 --- 196 --- 191
	// 179             179             179
	// 195 --- 196 --- 197 --- 196 --- 180
	// 179             179             179
	// 192 --- 196 --- 193 --- 196 --- 217
	for (int i = 0; i < sodong * 2 + 1; i++)
	{
		gotoxy(x, y + i);
		for (int j = 0; j < socot * 2 + 1; j++) 
		{
			// Dong dau
			if (i == 0)
			{
				if (j == 0) cout << char (218); // dau dong
				else if (j == socot * 2) cout << char (191); // cuoi dong
			 	else if (j % 2 == 0) cout << char (194); // phan chia cac cot
				else for (int k = 0; k < kichthuoccot; k++) cout << char (196);
			}		
			// Dong cuoi
			else if (i == sodong * 2)
			{
				if (j == 0) cout << char (192);
				else if (j == socot * 2) cout << char (217);
				else if (j % 2 == 0) cout << char (193);
				else for (int k = 0; k < kichthuoccot; k++) cout << char (196);
			}
			// Dong Giua
			else 
			{
				if (i % 2 == 0) 
				{
					if (j == 0) cout << char (195);
					else if (j == socot * 2) cout << char (180);
					else if (j == 0 || j == socot * 2) cout << char (179);
					else if (j % 2 == 0) cout << char (197);
					else for (int k = 0; k < kichthuoccot; k++) cout << char (196);
				}
				else if (j % 2 == 0) cout << char (179);
				else for (int k = 0; k < kichthuoccot; k++) cout << " ";
			}
				
		}	
	}
}
void TaoBangDanhSachVatTu(int x, int y, int socot, int sodong, int kichthuoccot)
{
	VeBangDanhSach(x, y, socot, sodong, kichthuoccot);
	SetColor(CYAN);
	SetBGColor(BLACK);
	// tieu de cho moi cot
	int toaDoXNhan;
	for (int i = 0; i < 5; i++)
	{
		toaDoXNhan = x + i * (kichthuoccot + 1) + 1 + (kichthuoccot - nhanCuaBangDanhSachVatTu[i].length()) / 2;
		gotoxy(toaDoXNhan, y + 1);
		cout << nhanCuaBangDanhSachVatTu[i];
	}
}
void PhanTrang(int trang, int tongtrang, int x, int y)
{
	SetColor(CYAN);
	SetBGColor(BLACK);
	string str = "Trang: " + ChuyenSoThanhChuoi(trang) + "/" + ChuyenSoThanhChuoi(tongtrang);
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - str.length()) / 2 + x, TOADOY + HEIGHT_HEADER + HEIGHT_BODY - 3 + y);
	cout << str;
}
void VeConTro(int x, int y, int vitri)
{
	SetColor(CYAN);
	SetBGColor(BLACK);
	vitri--;
	gotoxy(x, y + vitri * 2);
	cout << "->";
}
void XoaConTro(int x, int y, int vitri)
{
	SetColor(CYAN);
	SetBGColor(BLACK);
	vitri--;
	gotoxy(x, y + vitri * 2);
	cout << "  ";
}
void XoaManHinh()
{
	SetBGColor(BLACK);
	for (int i = 0; i < HEIGHT_BODY; i ++)
	{
		for (int j = 0; j < WIDTH_BODY; j++)
		{
			gotoxy(TOADOX + WIDTH_MENU_BAR + j, TOADOY + HEIGHT_HEADER + i);
			cout << " ";
		}
	}
}
void VeFooter(string noidung)    
{
	VeDuongVien(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY , SCREEN_WIDTH-WIDTH_MENU_BAR, BLACK, CYAN);
	for (int i = 0; i < HEIGHT_FOOTER - 1; i++)
	{
		gotoxy(TOADOX + WIDTH_MENU_BAR, TOADOY + HEIGHT_HEADER + HEIGHT_BODY + i + 1);
		for (int j = 0; j < WIDTH_BODY; j++)
		{
			SetBGColor(BLACK);
			SetColor(WHITE);
			cout << " ";
		}
	}
	SetColor(CYAN);
	SetBGColor(BLACK);
	gotoxy(TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH - WIDTH_MENU_BAR - noidung.length()) / 2, SCREEN_HEIGTH);
	cout << noidung;
}
int KiemTraThoiGian(Date batdau, Date ketthuc, Date kiemtra)
{
	// nam kiem tra nam ngoai batdau, ketthuc
	if(kiemtra.nam < batdau.nam || kiemtra.nam > ketthuc.nam) return 0;
	
	if(kiemtra.nam == batdau.nam)
	{
		// thang kiem tra nam ngoai batdau
		if(kiemtra.thang < batdau.thang) return 0;
		// ngay kiem tra nam ngoai batdau
		if(kiemtra.thang == batdau.thang && kiemtra.ngay < batdau.ngay) return 0;		
	}
	
	if(kiemtra.nam == ketthuc.nam)
	{
		if(kiemtra.thang > ketthuc.thang) return 0;
		if(kiemtra.thang == batdau.thang && kiemtra.ngay > ketthuc.ngay) return 0;
	}
	// thoi gian hop le, nam giua ngay bat dau va ngay ket thuc
	return 1;
}
// kiem Tra ngay thang nam hop le: Hop le: 1, Ko Hop Le: 0
int KiemTraThoiGian(int ngay, int thang, int nam, int &vtkhonghople)
{
	// vtkhonghople: ngay = 0, thang = 1, nam = 2
	Date hientai;
	hientai = LayGioHeThong();
	if (nam > hientai.nam)
	{
		vtkhonghople = 2;
		return 0;
	} else if (thang <= 0 || thang > 12 || (nam == hientai.nam && thang > hientai.thang)) 
	{
		vtkhonghople = 1;
		return 0;
	} else if (nam == hientai.nam && thang == hientai.thang && ngay > hientai.ngay) 
	{
		vtkhonghople = 0;
		return 0;
	}
	switch(thang)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(ngay <= 0 || ngay > 31) 
			{
				vtkhonghople = 0;
				return 0;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if(ngay <= 0 || ngay > 30) 
			{
				vtkhonghople = 0;
				return 0;
			}
			break;
		case 2:
			if((nam % 4 == 0 && (ngay <= 0 || ngay > 29)) || (nam % 4 != 0 && (ngay <= 0 || ngay > 28))) 
			{
				vtkhonghople = 0;
				return 0;
			}
			break;	
	}
	return 1;
}
// so sanh hai moc thoi gian a va b, neu a > b return 1, a = b return 0, a < b return -1
int SoSanhThoiGian(Date a, Date b)
{
	if (a.nam > b.nam) return 1;
	else if (a.nam < b.nam) return -1;
	else 
	{
		if (a.thang > b.thang) return 1;
		else if (a.thang < b.thang) return -1;
		else 
		{
			if (a.ngay > b.ngay) return 1;
			else if (a.ngay < b.ngay) return -1;
			else return 0;
		}
	}
}  
