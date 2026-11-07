#include "chung.h"
#include "taikhoan.h"
#include "giaodich.h"
#include "thongke.h"
#include "ngansach.h"
#include <stdio.h>
#include <stdlib.h>

void menuUser(void) {
    int chon;
    do {
        printf("\n========== MENU NGUOI DUNG (%s) ==========\n", dsTaiKhoan[chiSoHienTai].tenDangNhap);
        printf("1. Them giao dich\n2. Xem giao dich cua toi\n3. Sua giao dich\n");
        printf("4. Xoa giao dich\n5. Tim kiem giao dich\n6. Sap xep giao dich\n");
        printf("7. Thong ke thu chi\n8. Dat ngan sach thang\n9. Doi mat khau\n0. Thoat\n");
        chon = docInt("Chon: ");
        switch (chon) {
            case 1: themGiaoDichMoi(); break;
            case 2: printf("\n========== GIAO DICH CUA TOI ==========\n"); inGiaoDichCuaToi(); break;
            case 3: suaGiaoDich(); break;
            case 4: xoaGiaoDich(); break;
            case 5: timKiemGiaoDich(); break;
            case 6: sapXepGiaoDich(); break;
            case 7: thongKe(); break;
            case 8: datNganSach(); break;
            case 9: doiMatKhau(); break;
            case 0: printf("Tam biet!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (chon != 0);
}

void menuAdmin(void) {
    int chon;
    do {
        printf("\n========== MENU ADMIN (%s) ==========\n", dsTaiKhoan[chiSoHienTai].tenDangNhap);
        printf("1. Tao tai khoan User\n2. Danh sach tai khoan\n3. Khoa/Mo tai khoan\n");
        printf("4. Xoa tai khoan\n5. Xem tat ca giao dich\n6. Doi mat khau\n0. Thoat\n");
        chon = docInt("Chon: ");
        switch (chon) {
            case 1: taoTaiKhoan(); break;
            case 2: danhSachTaiKhoan(); break;
            case 3: khoaMoTaiKhoan(); break;
            case 4: xoaTaiKhoan(); break;
            case 5: inTatCaGiaoDich(); break;
            case 6: doiMatKhau(); break;
            case 0: printf("Tam biet!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (chon != 0);
}

int main(void) {
    khoiTao();
    docTaiKhoan();
    docGiaoDich();
    if (dangNhap()) {
        if (dsTaiKhoan[chiSoHienTai].quyen == 1) menuAdmin();
        else menuUser();
        luuTaiKhoan();
        luuGiaoDich();
    }
    free(danhSach.ds);
    return 0;
}
