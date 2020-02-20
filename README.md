# Quản lí vật tư

+ Đồ án học phần cấu trúc dữ liệu và giải thuật

+ Tổ chức cấu trúc dữ liệu của chương trình:
    + Danh sách VatTu : cây nhị phân tìm kiếm (MAVT, TENVT, Đơn vị tính, Số lượng tồn)
    + Danh sách NhanVien : danh sách tuyến tính là một mảng con trỏ (MANV, HO, TEN, PHAI, con trỏ dshd): con trỏ dshd sẽ trỏ đến danh sách các hóa đơn mà nhân viên đó đã
    lập. Danh sách nhân viên có tối đa 500 nhân viên
    + Danh sách HoaDon : danh sách liên kết đơn(SoHD, Ngày lập hóa đơn, Loai, con trỏ cthd). Lọai chỉ nhận ‘N’ (phiếu nhập) hoặc ‘X’ (phiếu xuất); con trỏ cthd sẻ trỏ
    đến danh sách chi tiết các vật tư của hóa đơn đó.
    + Danh sách CT_HoaDon : danh sách liên kết đơn ( MAVT, Soluong, Dongia, %VAT).

+ Chức năng của chương trình: 
    + a/ Nhập vật tư : cho phép cập nhật (thêm / xóa / hiệu chỉnh) thông tin của vật tư; riêng số lượng tồn chỉ cho phép nhập khi đó là vật tư mới.
    + b/ In danh sách vật tư tồn kho : liệt kê ds vật tư ra màn hình theo thứ tự tên vật tư tăng dần.
    + c/ Nhập nhân viên: Cập nhập các nhân viên dựa vào mã nhân viên, họ, tên không được rỗng.
    + d/ In danh sách nhân viên theo thứ tự tên nhân viên tăng dần, nếu trùng tên thì tăng dần theo họ ra màn hình, 1 nhân viên / dòng
    + e/ Lập hóa đơn nhập/Lập hóa đơn xuất: nhập vào số hóa đơn, ngày lập, loại (chỉ nhận ký tự N hoặc X). Sau đó, tiếp tục cho phép nhập các vật tư của hóa đơn đó; Căn cứ vào loại hóa đơn, chương trình sẽ tự động cập nhật số lượng tồn.
    + f/ In hóa đơn : In hóa đơn dựa vào số hóa đơn do ta nhập vào
    + g/ Thống kê các hóa đơn trong 1 khỏang thời gian: nhập vào 2 thời điểm từ ngày , đến ngày, chương trình sẽ in ra các hóa đơn được lập trong khoảng thời gian như trên. Kết xuất:
    BẢNG LIỆT KÊ CÁC HÓA ĐƠN TRONG KHOẢNG THỜI GIAN
    Từ ngày : ##/##/#### Đến ngày : ##/##/####
    Số HĐ Ngày lập Loại HĐ Họ tên NV lập Trị giá hóa đơn
    + h/ In 10 vật tư có doanh thu cao nhất trong 1 khoảng thời gian

    + Lưu ý: 
    + Nếu số lượng xuất không đủ hàng thì báo lỗi và in ra số lượng tồn hiện có trong kho;
    + Chỉ được phép xóa vật tư đang lập của hóa đơn hiện tại. Khi hóa đơn đã ghi thì không được xóa các vật tư trog hóa đơn
