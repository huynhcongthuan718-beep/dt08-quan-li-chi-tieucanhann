#include "ngansach.h"
#include "taikhoan.h"
#include <stdio.h>
#include <string.h>

double tongChiThang(const char *nguoiDung, int thang, int nam) {
    double tong = 0;
    for (int i = 0; i < danhSach.soLuong; i++) {
        GiaoDich gd = danhSach.ds[i];
        if (strcmp(gd.nguoiDung, nguoiDung) == 0 && gd.loai == 0 &&
            gd.ngay.thang == thang && gd.ngay.nam == nam) tong += gd.soTien;
    }
    return tong;
}

void canhBaoNganSach(Ngay d) {
    TaiKhoan *tk = &dsTaiKhoan[chiSoHienTai];
    if (tk->nganSach <= 0) return;
    double tong = tongChiThang(tk->tenDangNhap, d.thang, d.nam);
    if (tong > tk->nganSach)
        printf("!!! CANH BAO: Chi tieu thang %02d/%04d (%.2lf) da VUOT ngan sach (%.2lf)!\n",
               d.thang, d.nam, tong, tk->nganSach);
    else if (tong >= tk->nganSach * 0.8)
        printf("Luu y: Chi tieu thang %02d/%04d da dat %.0lf%% ngan sach.\n",
               d.thang, d.nam, tong / tk->nganSach * 100);
}

void datNganSach() {
    printf("\n========== DAT NGAN SACH THANG ==========\n");
    printf("Ngan sach hien tai: %.2lf\n", dsTaiKhoan[chiSoHienTai].nganSach);
    dsTaiKhoan[chiSoHienTai].nganSach = docDouble("Nhap ngan sach thang moi (0 de tat canh bao): ");
    luuTaiKhoan();
    printf("Da cap nhat ngan sach!\n");
}
