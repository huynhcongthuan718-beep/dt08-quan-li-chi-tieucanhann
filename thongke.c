#include "thongke.h"
#include "giaodich.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int huongSapXep = 1;

void timKiemGiaoDich() {
    char tuKhoa[100];
    printf("\n========== TIM KIEM GIAO DICH ==========\n");
    docChuoi("Nhap tu khoa (danh muc hoac ghi chu): ", tuKhoa, sizeof(tuKhoa));
    int dem = 0;
    for (int i = 0; i < danhSach.soLuong; i++) {
        GiaoDich gd = danhSach.ds[i];
        if (laCuaToi(gd) && (chuaChuoi(gd.danhMuc, tuKhoa) || chuaChuoi(gd.ghiChu, tuKhoa))) {
            if (dem == 0) inTieuDe(0);
            inGiaoDich(++dem, gd, 0);
        }
    }
    if (dem == 0) printf("Khong tim thay giao dich phu hop!\n");
}

void thongKe() {
    int thang, nam;
    printf("\n========== THONG KE THU CHI ==========\n");
    do {
        thang = docInt("Nhap thang (0 = ca nam): ");
        if (thang < 0 || thang > 12) printf("Thang khong hop le!\n");
    } while (thang < 0 || thang > 12);
    nam = docInt("Nhap nam: ");
    double thu = 0, chi = 0;
    int dem = 0;
    for (int i = 0; i < danhSach.soLuong; i++) {
        GiaoDich gd = danhSach.ds[i];
        if (!laCuaToi(gd) || gd.ngay.nam != nam) continue;
        if (thang != 0 && gd.ngay.thang != thang) continue;
        dem++;
        if (gd.loai == 1) thu += gd.soTien; else chi += gd.soTien;
    }
    if (thang == 0) printf("\nNam %d:\n", nam);
    else printf("\nThang %02d/%d:\n", thang, nam);
    printf("So giao dich : %d\n", dem);
    printf("Tong thu     : %.2lf\n", thu);
    printf("Tong chi     : %.2lf\n", chi);
    printf("Chenh lech   : %.2lf\n", thu - chi);
    double nganSach = dsTaiKhoan[chiSoHienTai].nganSach;
    if (thang != 0 && nganSach > 0) {
        printf("Ngan sach    : %.2lf\n", nganSach);
        if (chi > nganSach) printf("=> Da VUOT ngan sach %.2lf\n", chi - nganSach);
        else printf("=> Con lai %.2lf\n", nganSach - chi);
    }
}

int soSanhNgay(const void *a, const void *b) {
    long x = khoaNgay(((const GiaoDich *)a)->ngay);
    long y = khoaNgay(((const GiaoDich *)b)->ngay);
    return huongSapXep * (x > y) - huongSapXep * (x < y);
}

int soSanhTien(const void *a, const void *b) {
    double x = ((const GiaoDich *)a)->soTien;
    double y = ((const GiaoDich *)b)->soTien;
    return huongSapXep * (x > y) - huongSapXep * (x < y);
}

void sapXepGiaoDich() {
    printf("\n========== SAP XEP GIAO DICH ==========\n");
    printf("1. Theo ngay (cu -> moi)\n2. Theo ngay (moi -> cu)\n");
    printf("3. Theo so tien (tang dan)\n4. Theo so tien (giam dan)\n");
    int c = docInt("Chon: ");
    if (c < 1 || c > 4) { printf("Lua chon khong hop le!\n"); return; }
    huongSapXep = (c == 1 || c == 3) ? 1 : -1;
    if (danhSach.soLuong > 1)
        qsort(danhSach.ds, danhSach.soLuong, sizeof(GiaoDich), c <= 2 ? soSanhNgay : soSanhTien);
    luuGiaoDich();
    inGiaoDichCuaToi();
}
