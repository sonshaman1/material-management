#include "NhanVien.cpp"
void VeGiaoDienChinh(string title)
{
	// cot tieu de
	VeHinhChuNhat(TOADOX + 20, TOADOY, SCREEN_WIDTH - 25, 3, CYAN);
	gotoxy(TOADOX + (150 + WIDTH_MENU_BAR - title.length()) / 2, TOADOY + 1);
	SetColor(WHITE);
	SetBGColor(CYAN);
	cout << title;
	// cot chuc nang
	VeHinhChuNhat(TOADOX, TOADOY + 3, WIDTH_MENU_BAR, SCREEN_HEIGTH, CYAN);
	SetColor(WHITE);
	SetBGColor(CYAN);
	for(int i = 0; i < 5; i++)
	{
		gotoxy(TOADOX + (WIDTH_MENU_BAR - menu[i].length()) / 2, TOADOY + 10 + i * 6);
		cout << menu[i];
		for(int j = 0; j < WIDTH_MENU_BAR; j++)
		{
			gotoxy(TOADOX + j, TOADOY + 9 + i * 6);
			cout << char(196);
			gotoxy(TOADOX + j, TOADOY + 11 + i * 6);	
			cout << char(196);
		}
	}	
}
void Menu(VATTUTREE &root, DanhSachNhanVien &ds, string title)
{
	VeGiaoDienChinh(title);
	int c;
	int chon = 0;
	VeFooter("Esc: Thoat");
	do
	{
		gotoxy(TOADOX, TOADOY + 9 + chon * 6);
		VeHinhChuNhat(TOADOX,TOADOY + 9 + chon * 6, WIDTH_MENU_BAR, 3, BLACK);
		gotoxy(TOADOX + (WIDTH_MENU_BAR - menu[chon].length()) / 2, TOADOY + 10 + chon * 6);
		SetColor(CYAN);
		SetBGColor(BLACK);
		cout << menu[chon];
		c = KeyPressed();
		if(c == KEY_DOWN)
		{
			VeHinhChuNhat(TOADOX,TOADOY + 9 + chon * 6, WIDTH_MENU_BAR, 3, CYAN);
			SetColor(WHITE);
			SetBGColor(CYAN);
			gotoxy(TOADOX + (WIDTH_MENU_BAR - menu[chon].length()) / 2 , TOADOY + 10 + chon * 6);
			cout << menu[chon];
			for(int i = 0; i < WIDTH_MENU_BAR; i++)
			{
				gotoxy(TOADOX + i, TOADOY + 9 + chon * 6);
				cout << char(196);
				gotoxy(TOADOX + i, TOADOY + 11 + chon * 6);	
				cout << char(196);
			}
			if(chon <= 4)
			{
				chon++;
				if(chon == 5) chon = 0;
			}
		}
		if(c == KEY_UP)
		{
			VeHinhChuNhat(TOADOX,TOADOY + 9 + chon * 6, WIDTH_MENU_BAR, 3, CYAN);
			SetColor(WHITE);
			SetBGColor(CYAN);
			gotoxy(TOADOX + (WIDTH_MENU_BAR - menu[chon].length()) / 2 , TOADOY + 10 + chon * 6);
			cout << menu[chon];
			for(int i = 0; i < WIDTH_MENU_BAR; i++)
			{
				gotoxy(TOADOX + i, TOADOY + 9 + chon * 6);
				cout << char(196);
				gotoxy(TOADOX + i, TOADOY + 11 + chon * 6);	
				cout << char(196);
			}
			if(chon >= 0) 
			{
				chon--;
				if(chon == -1) chon = 4;
			}
		}
		if(c == KEY_ENTER)
		{	
			switch(chon)
			{
				case 0:
					DuyetDanhSachVatTu(ds, root);
					XoaManHinh();
					VeFooter("Esc: Thoat");
					break;
				case 1:
					DuyetDanhSachNhanVien(ds, root);
					XoaManHinh();
					VeFooter("Esc: Thoat");
					break;
				case 2:
					InHoaDon(ds, root);
					XoaManHinh();
					VeFooter("Esc: Thoat");
					break;
				case 3:
					ModuleThongKeHoaDon(ds);
					XoaManHinh();
					VeFooter("Esc: Thoat");
					break;
				case 4:
					ModuleThongKeVatTu(ds, root);
					XoaManHinh();
					VeFooter("Esc: Thoat");
					break;	
			}
		}
	}while(c != KEY_ESC);
	if(c == KEY_ESC) 
	{
		GhiFile(ds);
		GhiFile(root);
		XoaCay(root);
		XoaDanhSach(ds);
		system("cls");
		exit(1);
	}
}
DanhSachNhanVien ds;
VATTUTREE root = NULL;
static volatile bool g_exit = false;
static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType)
{
    g_exit = true; 
	GhiFile(ds);
	GhiFile(root);
	XoaCay(root);
	XoaDanhSach(ds);
  return TRUE;
}
int main()
{
	SetConsoleCtrlHandler(console_ctrl_handler, TRUE);
	DocFile(root);
	DocFile(ds);
	ResizeConsole(1360, 730);
	Menu(root, ds, "QUAN LI VAT TU");
	return 0;
}


