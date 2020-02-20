#include"DoHoaVaXuLiChuoi.cpp"
struct VatTu
{
	string mavt = "", tenvt = "", dvt = "";
	int soluongton;
};
typedef struct VatTu VATTU;
struct NodeVatTuTree
{
	VATTU vattu;
	NodeVatTuTree* left;
	NodeVatTuTree* right;
	int height;
};
typedef struct NodeVatTuTree* VATTUTREE;
struct DanhSachVatTu
{
	int n = 0;
	VATTU nodes[MAX_VAT_TU];	
};
struct ThongKe
{
	int idx = 0;
	int soluongxuat = 0; 	
};
struct cthd
{
	string mavt = "";
	int soluong, dongia, vat;
};
typedef struct cthd CTHD;
struct NodeCTHD
{
	CTHD infocthd;
	NodeCTHD *next;
};
typedef struct NodeCTHD* LISTCTHD;
struct HoaDon
{
	string sohd;
	Date ngaylap = LayGioHeThong();
	char loai = 'N';
	LISTCTHD dscthd = NULL;
};
typedef struct HoaDon HOADON;
struct NodeHD
{
	HOADON infohd;
	NodeHD *next;
};
typedef struct NodeHD* LISTHD;
struct NhanVien
{
	string manv = "", ho = "", ten = "";
	bool phai = true;
	LISTHD dshd = NULL;
};
typedef struct NhanVien NHANVIEN;
struct DanhSachNhanVien
{
	int n = 0;
	NHANVIEN *nodes[MAX_NHAN_VIEN];
};


