#ifndef CHUNG_H
#define CHUNG_H

#include <stddef.h>

#define MAX_USER 100
#define FILE_USER "taikhoan.txt"
#define FILE_DATA "chitieu.txt"
#define MAX_TIEN 1e12

typedef struct { int ngay, thang, nam; } Ngay;
typedef struct {
    Ngay ngay;
    int loai;                 /* 1 = Thu, 0 = Chi */
    char danhMuc[30];
    double soTien;
    char ghiChu[100];
    char nguoiDung[30];
} GiaoDich;
typedef struct {
    char tenDangNhap[30];
    char matKhau[30];
    int quyen;                /* 1 = Admin, 0 = User */
    int trangThai;            /* 1 = hoat dong, 0 = bi khoa */
    double nganSach;
} TaiKhoan;
typedef struct {
    GiaoDich *ds;
    int soLuong;
    int sucChua;
} DanhSach;

extern TaiKhoan dsTaiKhoan[MAX_USER];
extern int soTaiKhoan;
extern int chiSoHienTai;
extern DanhSach danhSach;

void saoChep(char dich[], const char nguon[], size_t size);
int tachTruong(char *line, char *f[], int max);
int chuaChuoi(const char *s, const char *tuKhoa);
void docDong(char s[], int size);
int docInt(const char *thongBao);
double docDouble(const char *thongBao);
void docChuoi(const char *thongBao, char s[], int size);
void docChuoiKhongRong(const char *thongBao, char s[], int size);
int docCoKhong(const char *thongBao);
int namNhuan(int nam);
int ngayTrongThang(int thang, int nam);
int ngayHopLe(Ngay d);
Ngay nhapNgay(void);
Ngay ngayHomNay(void);
long khoaNgay(Ngay d);

#endif
