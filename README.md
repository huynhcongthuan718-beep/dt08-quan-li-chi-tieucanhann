# QUẢN LÝ CHI TIÊU CÁ NHÂN & KẾ HOẠCH TÀI CHÍNH

Chương trình quản lý tài khoản và giao dịch thu/chi cá nhân, viết bằng ngôn ngữ C.

## 1. Chức năng

- Đăng nhập với tài khoản Admin hoặc User.
- Admin: tạo tài khoản, xem danh sách, khóa/mở khóa, xóa tài khoản, xem toàn bộ giao dịch.
- User: thêm, xem, sửa, xóa giao dịch; tìm kiếm; sắp xếp; thống kê thu chi; đặt ngân sách tháng; đổi mật khẩu.
- Lưu dữ liệu vào `taikhoan.txt` và `chitieu.txt`.
- Cảnh báo khi chi tiêu đạt từ 80% ngân sách hoặc vượt ngân sách.

## 2. Cấu trúc mã nguồn

| File | Vai trò |
|---|---|
| `main.c` | Hàm main và menu Admin/User |
| `chung.h`, `chung.c` | Struct, biến toàn cục, nhập liệu, kiểm tra ngày và hàm tiện ích |
| `taikhoan.h`, `taikhoan.c` | Đăng nhập và quản lý tài khoản |
| `giaodich.h`, `giaodich.c` | Đọc/ghi và thêm/sửa/xóa/hiển thị giao dịch |
| `thongke.h`, `thongke.c` | Tìm kiếm, thống kê và sắp xếp |
| `ngansach.h`, `ngansach.c` | Tính chi tiêu tháng, cảnh báo và đặt ngân sách |

## 3. Yêu cầu môi trường

- GCC (MinGW-w64 trên Windows hoặc GCC trên Linux/macOS).
- Trình soạn thảo bất kỳ: VS Code, Code::Blocks, Dev-C++...

## 4. Biên dịch

Mở Terminal/CMD tại thư mục dự án và chạy:

```bash
gcc -std=c11 -Wall -Wextra main.c chung.c taikhoan.c giaodich.c thongke.c ngansach.c -o quanlychitieu
```

Trên Windows chạy:

```bash
quanlychitieu.exe
```

Trên Linux/macOS chạy:

```bash
./quanlychitieu
```

Nếu môi trường GCC yêu cầu liên kết thư viện toán học, thêm `-lm` ở cuối lệnh.

Hoặc dùng Makefile:

```bash
make
```

## 5. Tài khoản mặc định

Nếu chưa có `taikhoan.txt`, chương trình tự tạo tài khoản Admin:

- Tên đăng nhập: `admin`
- Mật khẩu: `admin123`

Nên đổi mật khẩu sau lần đăng nhập đầu tiên. Đây là chương trình học tập; mật khẩu hiện được lưu dạng văn bản thuần trong file dữ liệu, không dùng cho hệ thống thực tế.

## 6. File dữ liệu

- `taikhoan.txt`: mỗi dòng lưu thông tin tài khoản, phân cách bằng dấu `|`.
- `chitieu.txt`: mỗi dòng lưu một giao dịch, phân cách bằng dấu `|`.

Hai file dữ liệu được chương trình tự tạo/cập nhật khi cần. Không chỉnh sửa thủ công nếu không hiểu định dạng.

## 7. Phân chia công việc nhóm 5 thành viên

| Thành viên | File | Nhiệm vụ |
|---|---|---|
| A | `taikhoan.h`, `taikhoan.c` | Đăng nhập, tạo/quản lý tài khoản, khóa/mở khóa, xóa tài khoản, đổi mật khẩu |
| B | `giaodich.h`, `giaodich.c` | Quản lý danh sách giao dịch, đọc/ghi file, thêm/sửa/xóa/hiển thị giao dịch |
| C | `thongke.h`, `thongke.c` | Tìm kiếm, thống kê thu chi, sắp xếp giao dịch |
| D | `chung.h`, `chung.c` | Kiểu dữ liệu dùng chung, biến toàn cục, nhập liệu, xử lý ngày tháng |
| E | `ngansach.h`, `ngansach.c`, `main.c` | Ngân sách, cảnh báo, menu, tích hợp và kiểm thử |

Thành viên D cần thống nhất `chung.h` sớm để những người khác dùng cùng kiểu dữ liệu và nguyên mẫu hàm. Thành viên E chịu trách nhiệm ghép và kiểm thử cuối cùng.

## 8. Quy trình GitHub đề xuất

1. Trưởng nhóm tạo Repository và mời 4 thành viên bằng tài khoản GitHub riêng.
2. Mỗi thành viên Clone Repository về máy.
3. Mỗi người tạo branch riêng, ví dụ `feature/taikhoan`, `feature/giaodich`, `feature/thongke`, `feature/chung`, `feature/integration`.
4. Chỉ chỉnh sửa file thuộc phần được phân công; nếu cần sửa header dùng chung, trao đổi với nhóm.
5. Biên dịch và chạy thử trước khi Commit.
6. Commit với mô tả cụ thể, Push branch và tạo Pull Request để kiểm tra trước khi nhập vào `main`.

## 9. Kiểm thử cơ bản

- Đăng nhập Admin mặc định.
- Tạo User, đăng xuất/đăng nhập bằng User.
- Thêm giao dịch Thu và Chi; xem, sửa, xóa giao dịch.
- Tìm kiếm theo danh mục hoặc ghi chú; thử sắp xếp theo ngày/số tiền.
- Xem thống kê theo tháng và cả năm.
- Đặt ngân sách, kiểm tra cảnh báo ở ngưỡng 80% và khi vượt ngân sách.
- Thoát chương trình, chạy lại để xác nhận dữ liệu được lưu.
