#include "DuLieu.cpp"
int TimViTriThichHop(DanhSachVatTu ds, string tenvt) 
{
	for (int i = 0; i < ds.n; i++)
	{
		// return vi tri thich hop	
		if (ds.nodes[i].tenvt >= tenvt) return i;
	}	
	return ds.n;
}
int TimViTriVatTu(DanhSachVatTu ds, string mavt)
{
	for(int i = 0; i < ds.n; i++)
	{
		if(ds.nodes[i].mavt == mavt) return i;
	}
	return -1; // khong ton tai trong danh sach
}
bool ThemVatTuVaoViTriX(DanhSachVatTu &ds, VATTU vt, int idx) 
{
	if (idx < 0 || idx > ds.n || ds.n == MAX_VAT_TU) return false;
	for (int i = ds.n; i > idx; i--)
	{
		ds.nodes[i] = ds.nodes[i - 1];
	}
	ds.nodes[idx] = vt;
	ds.n++;
	return true;
}
bool ThemVatTuSapXepTheoTen(DanhSachVatTu &ds, VATTU vt) 
{
	int idx = TimViTriThichHop(ds, vt.tenvt);
	bool kq = ThemVatTuVaoViTriX(ds, vt, idx);
	return kq;
}
void PreOrder(VATTUTREE root, DanhSachVatTu &ds)
{
	if(root != NULL)
	{
		ThemVatTuSapXepTheoTen(ds, root->vattu);
		PreOrder(root->left, ds);
		PreOrder(root->right, ds);	
	}
}
void DemSoLuongVatTu(VATTUTREE root, int &dem)
{
	if(root != NULL)
	{
		dem++;
		DemSoLuongVatTu(root->left, dem);
		DemSoLuongVatTu(root->right, dem);
	}
}
int Height(VATTUTREE root)
{
    if (root == NULL) return 0;
    return root->height;
}
int Max(int a, int b)
{
    return (a > b) ? a : b;
}
VATTUTREE NewNode(VATTU vt)
{
    VATTUTREE node = new NodeVatTuTree;
    node->vattu   = vt;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  
    return node;
}
VATTUTREE RightRotate(VATTUTREE y)
{
    VATTUTREE x = y->left;
    VATTUTREE T2 = x->right;
    x->right = y;
    y->left = T2;
    // cap nhat chieu cao cay
    y->height = Max(Height(y->left), Height(y->right)) + 1;
    x->height = Max(Height(x->left), Height(x->right)) + 1;
    return x;
}
VATTUTREE LeftRotate(VATTUTREE x)
{
    VATTUTREE y = x->right;
    VATTUTREE T2 = y->left;
    y->left = x;
    x->right = T2;
    // cap nhat chieu cao cay
    x->height = Max(Height(x->left), Height(x->right)) + 1;
    y->height = Max(Height(y->left), Height(y->right)) + 1;
    return y;
}
int GetBalance(VATTUTREE root)
{
    if (root == NULL) return 0;
    return Height(root->left) - Height(root->right);
}
VATTUTREE ThemVaoCay(VATTUTREE &node, VATTU vt)
{
    if (node == NULL) return(NewNode(vt));
 
    if (vt.mavt < node->vattu.mavt)
        node->left  = ThemVaoCay(node->left, vt);
    else if (vt.mavt > node->vattu.mavt)
        node->right = ThemVaoCay(node->right, vt);
    else return node;
    
    node->height = 1 + Max(Height(node->left), Height(node->right));
    
    int balance = GetBalance(node);
    // mat can bang trai-trai
    if (balance > 1 && vt.mavt < node->left->vattu.mavt)
        return RightRotate(node);
    // mat can bang phai-phai    
    if (balance < -1 && vt.mavt > node->right->vattu.mavt)
        return LeftRotate(node);
    // mat can bang trai-phai    
    if (balance > 1 && vt.mavt > node->left->vattu.mavt)
    {
        node->left =  LeftRotate(node->left);
        return RightRotate(node);
    }
    // mat can bang phai-trai
    if (balance < -1 && vt.mavt < node->right->vattu.mavt)
    {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }
    return node;
}
VATTUTREE MinValueNode(VATTUTREE node)
{
    VATTUTREE current = node;
    
    while (current->left != NULL)
        current = current->left;
    return current;
}
VATTUTREE XoaNodeCuaCay(VATTUTREE &root, string mavt)
{
    if (root == NULL)
        return root;
    
    if ( mavt < root->vattu.mavt)
        root->left = XoaNodeCuaCay(root->left, mavt);
    else if(mavt > root->vattu.mavt)
        root->right = XoaNodeCuaCay(root->right, mavt);
    else  // Found this vattu
    {
        if((root->left == NULL) || (root->right == NULL))   // No child and one child case
        {
            VATTUTREE temp = root->left ? root->left : root->right;
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            delete temp;
        }
        else // Two child case
        {
            VATTUTREE temp = MinValueNode(root->right);
            // Copy the inorder successor's data to this node
            root->vattu = temp->vattu;
            // Delete the inorder successor
            root->right = XoaNodeCuaCay(root->right, temp->vattu.mavt);
        }
    }
    // If the tree had only one node then return
    if (root == NULL) return root;
   
    root->height = 1 + Max(Height(root->left), Height(root->right));
    int balance = GetBalance(root);
    if (balance > 1 && GetBalance(root->left) >= 0)
        return RightRotate(root);
    if (balance > 1 && GetBalance(root->left) < 0)
    {
        root->left =  LeftRotate(root->left);
        return RightRotate(root);
    }
    if (balance < -1 && GetBalance(root->right) <= 0)
        return LeftRotate(root);
    if (balance < -1 && GetBalance(root->right) > 0)
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }
    return root;
}
VATTUTREE TimKiemVatTu(VATTUTREE root, VATTU vt)
{
	VATTUTREE p = root;
	while(p != NULL && p->vattu.mavt != vt.mavt)
	{
		if(vt.mavt < p->vattu.mavt)
		{
			p = p->left;
		}
		else if(vt.mavt > p->vattu.mavt)
		{
			p = p->right;
		} 
	}
	return p;
}
VATTUTREE TimKiemVatTu(VATTUTREE root, string mavt)
{
	VATTUTREE p = root;
	while(p != NULL && p->vattu.mavt != mavt)
	{
		if(mavt < p->vattu.mavt)
		{
			p = p->left;
		}
		else if(mavt > p->vattu.mavt)
		{
			p = p->right;
		} 
	}
	return p;
}
int TongSoTrangVatTu(VATTUTREE root)
{
	int n = 0; DemSoLuongVatTu(root, n);
	return n / 10 + (n % 10 == 0 ? 0 : 1);
}
void GhiFile(VATTUTREE root)
{
	ofstream fileout(FILE_VAT_TU);
	if(!fileout) return;
	DanhSachVatTu ds;
	ds.n = 0;
	PreOrder(root, ds);
	for(int i = 0; i < ds.n; i++)
	{
		if (i > 0) fileout << endl;
		fileout << ds.nodes[i].mavt << endl;
		fileout << ds.nodes[i].tenvt << endl;
		fileout << ds.nodes[i].dvt << endl;
		fileout << ds.nodes[i].soluongton;
	}			
	fileout.close();
}
void DocFile(VATTUTREE &root)
{
	fstream filein(FILE_VAT_TU);
	if (!filein) return;
	VATTU vt; 
	string str;
	getline(filein, vt.mavt);
	bool check = false;
	if(vt.mavt == "") return;
	else
	{
		check = true;
	}
	VATTUTREE p;
	while (!filein.eof())
	{	
		if(!check)
		{
			getline(filein, vt.mavt);
		}
		getline(filein, vt.tenvt);
		getline(filein, vt.dvt);
		getline(filein, str);
		stringstream(str) >> vt.soluongton;
		root = ThemVaoCay(root, vt);
		check = false;
	}
	filein.close();
}
void TraVeMangVatTuXuat(ThongKe a[], DanhSachNhanVien ds, VATTUTREE root, Date batdau, Date ketthuc)
{
	LISTHD dshd = NULL;
	LISTCTHD dsct = NULL;
	int vtvattu;
	DanhSachVatTu dsvt; PreOrder(root, dsvt);
	for(int i = 0; i < ds.n; i++)
	{
		dshd = ds.nodes[i]->dshd;
		while(dshd != NULL)
		{
			if(dshd->infohd.loai == 'X' && KiemTraThoiGian(batdau, ketthuc, dshd->infohd.ngaylap))
			{
				dsct = dshd->infohd.dscthd;
				while(dsct != NULL)
				{
					vtvattu = TimViTriVatTu(dsvt, dsct->infocthd.mavt);
					a[vtvattu].soluongxuat += dsct->infocthd.soluong;
					a[vtvattu].idx = vtvattu;
					dsct = dsct->next;
				}
			}
			dshd = dshd->next;
		}
	}
}
void XoaCay(VATTUTREE &root)
{
	if(root == NULL) return;
	XoaCay(root->left);
	XoaCay(root->right);
	delete root;
}
int SoLuongVatTuTonKhoCuaMaVT(VATTUTREE &root, string mavt)
{
	VATTUTREE p = root;
	while(p != NULL && p->vattu.mavt != mavt)
	{
		if(mavt < p->vattu.mavt)
		{
			p = p->left;
		}
		else if(mavt > p->vattu.mavt)
		{
			p = p->right;
		} 
	}
	return p->vattu.soluongton;
}
void InVatTu(VATTUTREE root, int trang, int tongtrang, int x, int y, int socot, int sodong, int kichthuoccot)
{
	XoaManHinh();
	DanhSachVatTu ds;
	PreOrder(root, ds);
	if(ds.n == 0) 
	{
		string s = "Danh Sach Vat Tu Rong";
		gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 7);
		cout << s;
		return; 
	}
	TaoBangDanhSachVatTu(x, y, socot, sodong, kichthuoccot);
	SetColor(WHITE);
	SetBGColor(BLACK);	
	int xtro;
	int ytro;
	string str;
	int vtdau = (trang - 1) * 10;// de con tro o vi tri dau tien cua danh sach
	VATTU vt;
	int tam = 0;
	
	for(int i = vtdau; i < ds.n && i < trang * 10; i++)
	{
		vt = ds.nodes[i];
		ytro = y + 3 + 2 * tam; 
		tam++;
		// stt
		str = ChuyenSoThanhChuoi(i + 1);
		xtro = x + 0 * (kichthuoccot + 1) + 1 + (kichthuoccot - str.length()) / 2;
		gotoxy(xtro, ytro);
		cout << ChuyenSoThanhChuoi(i + 1);
		// mavt
		xtro = x + 1 * (kichthuoccot + 1) + 1 + (kichthuoccot - vt.mavt.length()) / 2;
		gotoxy(xtro, ytro);
		cout << vt.mavt;
		// tenvt
		xtro = x + 2 * (kichthuoccot + 1) + 1 + (kichthuoccot - vt.tenvt.length()) / 2;
		gotoxy(xtro, ytro);
		cout << vt.tenvt;
		// dvt
		xtro = x + 3 * (kichthuoccot + 1) + 1 + (kichthuoccot - vt.dvt.length()) / 2;
		gotoxy(xtro, ytro);
		cout << vt.dvt;
		// soluongton
		str = ChuyenSoThanhChuoi(vt.soluongton);
		xtro = x + 4 * (kichthuoccot + 1) + 1 + (kichthuoccot - str.length()) / 2;
		gotoxy(xtro, ytro);
		cout << str;
	}
	PhanTrang(trang, tongtrang, 0, 2);
}

void VeFormThemVatTu(string s)
{
	XoaManHinh();
	SetColor(CYAN);
	SetBGColor(BLACK);
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1);
	cout << s;
	VeFooter("Esc: Tro ve \t Insert: Luu");
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 15;
	int yinput = ylabel - 1;
	
	for (int i = 0; i < 4; i++) 
	{
		gotoxy(xlabel, ylabel + 3 * i);
		cout << thuocTinhVatTu[i];
		VeInputText(xinput, yinput + 3 * i, 0);
	}
}
void CapNhatThongTinVatTu(VATTUTREE root, VATTU vt, VATTUTREE p, int &flag)
{
	string s = "CAP NHAT THONG TIN VAT TU";
	VeFormThemVatTu(s);
	int c;
	int idx = 1;
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 16;
	int yinput = ylabel;
	// khong cho cap nhat
	SetColor(CYAN);
	gotoxy(xinput, yinput + 0 * 3);
	cout << vt.mavt;
	gotoxy(xinput, yinput + 3 * 3);
	cout << vt.soluongton;
	// cho phep cap nhat
	SetColor(WHITE);
	gotoxy(xinput, yinput + 1 * 3);
	cout << vt.tenvt;
	gotoxy(xinput, yinput + 2 * 3);
	cout << vt.dvt;
	
	do 
	{
		if(idx == 1)
		{
			c = NhapChuoiKiTuVaSo(vt.tenvt, xinput , yinput + idx * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}else if(idx == 2)
		{
			c = NhapChuoiKiTuVaSo(vt.dvt, xinput , yinput + idx * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}
		if (c == KEY_DOWN) idx = 2;
		if (c == KEY_UP) idx = 1;
		
		if(c == KEY_INSERT)
		{
			if(vt.tenvt == "" || vt.dvt == "")
			{
				ThongBao("Vui Long Khong De Trong Thong Tin");
				VeFormThemVatTu(s);
				// khong cho cap nhat
				SetColor(CYAN);
				gotoxy(xinput, yinput + 0 * 3);
				cout << vt.mavt;
				gotoxy(xinput, yinput + 3 * 3);
				cout << vt.soluongton;
				// cho phep cap nhat
				SetColor(WHITE);
				gotoxy(xinput, yinput + 1 * 3);
				cout << vt.tenvt;
				gotoxy(xinput, yinput + 2 * 3);
				cout << vt.dvt;
			}
			else
			{
				if (p != NULL)
				{
					ChuanHoaChuoi(vt.tenvt); 
					ChuanHoaChuoi(vt.dvt);
					p->vattu.tenvt = vt.tenvt;
					p->vattu.dvt = vt.dvt;
					ThongBao("Cap Nhat Thanh Cong");
					flag = 1;
					break;
				}
			}	
		}
	} while (c != KEY_ESC);
	if(c == KEY_ESC) flag = 0;
}
int XoaVatTu(DanhSachNhanVien ds, VATTUTREE &root, string mavt)
{
	LISTHD dshd = NULL;
	LISTCTHD dscthd = NULL;
	NHANVIEN temp;
	for(int i = 0; i < ds.n; i++)
	{
		temp = *ds.nodes[i];
		dshd = temp.dshd;
		while(dshd != NULL)
		{
			dscthd = dshd->infohd.dscthd;
			while(dscthd != NULL)
			{
				if(dscthd->infocthd.mavt == mavt)
				{
					ThongBao("Khong Duoc Xoa Vat Tu");
					return 0;
				}
				dscthd = dscthd->next;
			}
			dshd = dshd->next;
		}
	}
	VATTUTREE p = TimKiemVatTu(root, mavt);
	if(p->vattu.soluongton > 0)
	{
		ThongBao("Khong Duoc Xoa Vat Tu");
		return 0;
	}
	string s = "Ban Co Muon Xoa " + mavt + " Khong?";
	int kq = HopThoaiLuaChon(s, TOADOX + WIDTH_MENU_BAR + (SCREEN_WIDTH- WIDTH_MENU_BAR - WIDTH_MESSAGE) / 2, (SCREEN_HEIGTH - 5) / 2,
					         50, 5);		
	if(kq == 1)
	{
		root = XoaNodeCuaCay(root, mavt);
		s = "Da Xoa Vat Tu: " + mavt;
		ThongBao(s);
		return 1; // bat tin hieu da xoa
	}
	return 0; // huy	
}
void ThemMoiVatTu(VATTUTREE &root, int &flag, string &mavt)
{
	VeFormThemVatTu("THEM MOI VAT TU");
	VATTU vt;
	int c;
	int idx = 0;
	VATTUTREE p = NULL;
	string soluongstr = "";
	VATTUTREE temp;
	int k = 0;
	int xlabel = TOADOX + WIDTH_MENU_BAR + 30;
	int ylabel = TOADOY + HEIGHT_HEADER + 5;
	int xinput = xlabel + 16;
	int yinput = ylabel;
	vt.soluongton = 0;
	do 
	{
		if(idx == 0)
		{
			c = NhapChuoiKiTuVaSo(vt.mavt, xinput , yinput + idx * 3, 10, BLACK, WHITE);
		}else if(idx == 1)
		{
			c = NhapChuoiKiTuVaSo(vt.tenvt, xinput , yinput + idx * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}else if(idx == 2)
		{
			c = NhapChuoiKiTu(vt.dvt, xinput , yinput + idx * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}else if(idx == 3)
		{
			c = NhapChuoiKiTuSo(soluongstr, xinput , yinput + idx * 3, WIDTH_INPUT_TEXT, BLACK, WHITE);
		}
		if (c == KEY_DOWN && idx < 5 - 1) idx++;
		if (c == KEY_UP && idx > 0) idx--;
		
		if(c == KEY_INSERT)
		{
			if(vt.mavt == "" || vt.tenvt == "" || vt.dvt == "" || soluongstr == "")
			{
				ThongBao("Vui Long Khong De Trong Thong Tin");
				if(vt.mavt == "") idx = 0;
				else if(vt.tenvt == "") idx = 1;
				else if(vt.dvt == "") idx = 2;
				else idx = 3;	     
			}
			else
			{
				XoaKhoangTrang(vt.mavt); ChuanHoaMa(vt.mavt);
				ChuanHoaChuoi(vt.tenvt); ChuanHoaChuoi(vt.dvt);
				stringstream(soluongstr) >> vt.soluongton;
				temp = TimKiemVatTu(root, vt.mavt);
				if(temp == NULL)
				{
					root = ThemVaoCay(root, vt);
					flag = 1;
					mavt = vt.mavt;
					ThongBao("Them Thanh Cong");
					break;	
				}
				else
				{
					ThongBao("Ma Vat Tu Da Ton Tai");
					idx = 0;
				}
			}
			VeFormThemVatTu("THEM MOI VAT TU");
			SetColor(WHITE);
			gotoxy(xinput, yinput + 0 * 3);
			cout << vt.mavt;
			gotoxy(xinput, yinput + 3 * 3);
			cout << soluongstr;
			gotoxy(xinput, yinput + 1 * 3);
			cout << vt.tenvt;
			gotoxy(xinput, yinput + 2 * 3);
			cout << vt.dvt;	
		}
		
	} while (c != KEY_ESC);
	if(c == KEY_ESC) flag = 0;
}
void VeFormDanhSachVatTu()
{
	SetColor(CYAN);
	SetBGColor(BLACK);
	string s = "                              ";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1);
	cout << s;
	s = "DANH SACH VAT TU";
	gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 2);
	cout << s;
	VeFooter("Esc: Thoat   Insert: Them   Delete: Xoa   F2: Sua   F4: Luu File   <-Trang truoc   Trang sau->");
}
void DuyetDanhSachVatTu(DanhSachNhanVien dsnv, VATTUTREE &root)
{	
	int trang = 1;
	int tongtrang = TongSoTrangVatTu(root);
	int flag = 1;
	int vtri = 1;
	int vtrisau;
	int c;
	string s;
	int socot = 5;
	int sodong = 11; // 10 + 1 = 11 dong (dong dau tien cho de muc cua cot)
	int chieudai = 20;
	int x = 37, y = 11;
	int n = 0; DemSoLuongVatTu(root, n);
	VATTU vt;
	InVatTu(root, trang, tongtrang, x, y, socot, sodong, chieudai);
	if(n != 0) VeConTro(x - 3, y + 3, vtri);
	VeFormDanhSachVatTu();
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
				InVatTu(root, trang, tongtrang, x, y, socot, sodong, chieudai);
				XoaConTro(x - 3, y + 3, vtri);
				vtri = 1;
				VeConTro(x - 3, y + 3, vtri);
				VeFormDanhSachVatTu();
			}
		}
		if(c == KEY_RIGHT) 
		{
			if (trang < tongtrang)
			{
				trang++;
				InVatTu(root, trang, tongtrang, x, y, socot, sodong, chieudai);
				XoaConTro(x - 3, y + 3, vtri);
				vtri = 1;
				VeConTro(x - 3, y + 3, vtri);
				VeFormDanhSachVatTu();
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
				InVatTu(root, trang, tongtrang, x, y, socot, sodong, chieudai);
				XoaConTro(x - 3, y + 3, vtri);
				vtri = 10;
				VeConTro(x - 3, y + 3, vtri);
				VeFormDanhSachVatTu();
			}
		}
		if (c == KEY_DOWN)
		{
			if(vtri == 10 && trang < tongtrang)
			{
				trang++;
				InVatTu(root, trang, tongtrang, x, y, socot, sodong, chieudai);
				XoaConTro(x - 3, y + 3, vtri);
				vtri = 1;
				VeConTro(x - 3, y + 3, vtri);
				VeFormDanhSachVatTu();
			}
			else if (vtri < 10 && (vtri + (trang - 1) * 10) < n) 
			{
				XoaConTro(x - 3, y + 3, vtri++);
				VeConTro(x - 3, y + 3, vtri);
			}
		}
		// them vat tu
		if(c == KEY_INSERT)
		{
			string s = "                              ";
			gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1);
			cout << s;
			string mavt = "";
			DanhSachVatTu ds; ds.n = 0;
			do
			{
				ThemMoiVatTu(root, flag, mavt);
			}while(flag == 1);
			tongtrang = TongSoTrangVatTu(root);
			if(mavt != "")
			{
				PreOrder(root, ds);
				vtrisau = TimViTriVatTu(ds, mavt);
				vtrisau++;
				trang = vtrisau / 10;
				if(vtrisau % 10 != 0) trang++;
				vtrisau--;
				vtri = vtrisau % 10;
				vtri++;
			}
			InVatTu(root, trang, tongtrang, x, y, socot, sodong, chieudai);
			n = 0; DemSoLuongVatTu(root, n);
			if(n != 0) VeConTro(x - 3, y + 3, vtri);
			VeFormDanhSachVatTu();
		}
		// cap nhat vat tu
		if (c == KEY_F2)
		{	
			string s = "                              ";
			gotoxy(TOADOX + WIDTH_MENU_BAR + (WIDTH_BODY - s.length()) / 2, TOADOY + HEIGHT_HEADER + 1);
			cout << s;
			int vtvattu = (trang - 1) * 10 + vtri - 1;
			DanhSachVatTu ds; PreOrder(root, ds);
			vt = ds.nodes[vtvattu];
			VATTUTREE p = TimKiemVatTu(root, vt);
			CapNhatThongTinVatTu(root, vt, p, flag);
			if(flag)
			{
				ds.n = 0;
				PreOrder(root, ds);
			}
			vtrisau = TimViTriVatTu(ds, p->vattu.mavt);
			vtrisau++;
			trang = vtrisau / 10;
			if(vtrisau % 10 != 0) trang++;
			vtrisau--;
			vtri = vtrisau % 10;
			vtri++;
			InVatTu(root, trang, tongtrang, x, y, socot, sodong, chieudai);
			VeConTro(x - 3, y + 3, vtri);
			VeFormDanhSachVatTu();
		}
		// xoa vat tu
		if (c == KEY_DELETE)
		{
			int vtvattu = (trang - 1) * 10 + vtri - 1;
			DanhSachVatTu ds; PreOrder(root, ds);
			vt = ds.nodes[vtvattu];
			int kq = XoaVatTu(dsnv, root, vt.mavt);			
			if(kq == 1)
			{
				tongtrang = TongSoTrangVatTu(root);
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
			}
			InVatTu(root, trang, tongtrang, x, y, socot, sodong, chieudai);
			n = 0; DemSoLuongVatTu(root, n);
			if(n != 0) VeConTro(x - 3, y + 3, vtri);
		}
		if(c == KEY_F4)
		{
			GhiFile(root);
			ThongBao("Luu Du Lieu Thanh Cong");
			InVatTu(root, trang, tongtrang, x, y, socot, sodong, chieudai);
			if(n != 0) VeConTro(x - 3, y + 3, vtri);
			VeFormDanhSachVatTu();
		}
	} while (c != KEY_ESC);
}





