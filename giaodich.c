#include "giaodich.h"
#include "ngansach.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void khoiTao() { danhSach.ds = NULL; danhSach.soLuong = 0; danhSach.sucChua = 0; }

void themGiaoDichVaoMang(GiaoDich gd) {
    if (danhSach.soLuong == danhSach.sucChua) {
        int sucChuaMoi = danhSach.sucChua == 0 ? 10 : danhSach.sucChua * 2;
        GiaoDich *p = realloc(danhSach.ds, sucChuaMoi * sizeof(GiaoDich));
        if (p == NULL) { printf("Khong du bo nho!\n"); exit(1); }
        danhSach.ds = p; danhSach.sucChua = sucChuaMoi;
    }
    danhSach.ds[danhSach.soLuong++] = gd;
}

void luuGiaoDich() {
    FILE *f = fopen(FILE_DATA, "w");
    if (f == NULL) { printf("Khong the luu file giao dich!\n"); return; }
    for (int i = 0; i < danhSach.soLuong; i++) {
        GiaoDich gd = danhSach.ds[i];
        fprintf(f, "%d|%d|%d|%d|%s|%.2lf|%s|%s\n",
                gd.ngay.ngay, gd.ngay.thang, gd.ngay.nam, gd.loai,
                gd.danhMuc, gd.soTien, gd.ghiChu, gd.nguoiDung);
    }
    fclose(f);
}

void docGiaoDich() {
    FILE *f = fopen(FILE_DATA, "r");
    if (f == NULL) return;
    char line[512];
    while (fgets(line, sizeof(line), f) != NULL) {
        char *f8[8];
        if (tachTruong(line, f8, 8) != 8) continue;
        GiaoDich gd;
        gd.ngay.ngay = atoi(f8[0]); gd.ngay.thang = atoi(f8[1]); gd.ngay.nam = atoi(f8[2]);
        gd.loai = atoi(f8[3]);
        if (!ngayHopLe(gd.ngay)) continue;
        if (gd.loai != 0 && gd.loai != 1) continue;
        saoChep(gd.danhMuc, f8[4], sizeof(gd.danhMuc));
        gd.soTien = atof(f8[5]);
        if (!isfinite(gd.soTien) || gd.soTien < 0) continue;
        saoChep(gd.ghiChu, f8[6], sizeof(gd.ghiChu));
        saoChep(gd.nguoiDung, f8[7], sizeof(gd.nguoiDung));
        if (strlen(gd.nguoiDung) == 0) continue;
        themGiaoDichVaoMang(gd);
    }
    fclose(f);
}

void inTieuDe(int hienNguoiDung) {
    printf("\n%-5s %-12s %-5s %-15s %16s ", "STT", "Ngay", "Loai", "Danh muc", "So tien");
    if (hienNguoiDung) printf("%-15s ", "Nguoi dung");
    printf("Ghi chu\n");
}

void inGiaoDich(int stt, GiaoDich gd, int hienNguoiDung) {
    char ngay[16];
    snprintf(ngay, sizeof(ngay), "%02d/%02d/%04d", gd.ngay.ngay, gd.ngay.thang, gd.ngay.nam);
    printf("%-5d %-12s %-5s %-15s %16.2lf ", stt, ngay,
           gd.loai == 1 ? "Thu" : "Chi", gd.danhMuc, gd.soTien);
    if (hienNguoiDung) printf("%-15s ", gd.nguoiDung);
    printf("%s\n", gd.ghiChu);
}

int laCuaToi(GiaoDich gd) {
    return strcmp(gd.nguoiDung, dsTaiKhoan[chiSoHienTai].tenDangNhap) == 0;
}

int viTriCuaToi(int stt) {
    int dem = 0;
    for (int i = 0; i < danhSach.soLuong; i++)
        if (laCuaToi(danhSach.ds[i])) {
            dem++;
            if (dem == stt) return i;
        }
    return -1;
}

int inGiaoDichCuaToi() {
    int dem = 0;
    for (int i = 0; i < danhSach.soLuong; i++)
        if (laCuaToi(danhSach.ds[i])) {
            if (dem == 0) inTieuDe(0);
            inGiaoDich(++dem, danhSach.ds[i], 0);
        }
    if (dem == 0) printf("Chua co giao dich nao!\n");
    return dem;
}

void inTatCaGiaoDich() {
    printf("\n========== TAT CA GIAO DICH ==========\n");
    if (danhSach.soLuong == 0) { printf("Chua co giao dich nao!\n"); return; }
    inTieuDe(1);
    for (int i = 0; i < danhSach.soLuong; i++) inGiaoDich(i + 1, danhSach.ds[i], 1);
}

void themGiaoDichMoi() {
    GiaoDich gd;
    printf("\n========== THEM GIAO DICH ==========\n");
    do { gd.loai = docInt("Loai giao dich (1: Thu, 0: Chi): "); }
    while (gd.loai != 0 && gd.loai != 1);
    if (docCoKhong("Dung ngay hom nay? (1: Co, 0: Khong): ")) gd.ngay = ngayHomNay();
    else gd.ngay = nhapNgay();
    docChuoiKhongRong("Nhap danh muc: ", gd.danhMuc, sizeof(gd.danhMuc));
    do {
        gd.soTien = docDouble("Nhap so tien: ");
        if (gd.soTien <= 0) printf("So tien phai lon hon 0!\n");
    } while (gd.soTien <= 0);
    docChuoi("Nhap ghi chu (co the de trong): ", gd.ghiChu, sizeof(gd.ghiChu));
    saoChep(gd.nguoiDung, dsTaiKhoan[chiSoHienTai].tenDangNhap, sizeof(gd.nguoiDung));
    themGiaoDichVaoMang(gd);
    luuGiaoDich();
    printf("Them giao dich thanh cong!\n");
    if (gd.loai == 0) canhBaoNganSach(gd.ngay);
}

void suaGiaoDich() {
    printf("\n========== SUA GIAO DICH ==========\n");
    if (inGiaoDichCuaToi() == 0) return;
    int stt = docInt("Nhap STT can sua (0 de huy): ");
    if (stt == 0) return;
    int vt = viTriCuaToi(stt);
    if (vt == -1) { printf("STT khong hop le!\n"); return; }
    GiaoDich *gd = &danhSach.ds[vt];
    char buf[100];
    if (docCoKhong("Sua loai Thu/Chi? (1: Co, 0: Khong): "))
        do { gd->loai = docInt("Loai giao dich (1: Thu, 0: Chi): "); }
        while (gd->loai != 0 && gd->loai != 1);
    if (docCoKhong("Sua ngay? (1: Co, 0: Khong): ")) gd->ngay = nhapNgay();
    docChuoi("Danh muc moi (Enter de giu nguyen): ", buf, sizeof(gd->danhMuc));
    if (strlen(buf) > 0) saoChep(gd->danhMuc, buf, sizeof(gd->danhMuc));
    if (docCoKhong("Sua so tien? (1: Co, 0: Khong): ")) {
        double tien;
        do {
            tien = docDouble("Nhap so tien moi: ");
            if (tien <= 0) printf("So tien phai lon hon 0!\n");
        } while (tien <= 0);
        gd->soTien = tien;
    }
    docChuoi("Ghi chu moi (Enter de giu nguyen, nhap - de xoa ghi chu): ", buf, sizeof(gd->ghiChu));
    if (strcmp(buf, "-") == 0) gd->ghiChu[0] = '\0';
    else if (strlen(buf) > 0) saoChep(gd->ghiChu, buf, sizeof(gd->ghiChu));
    luuGiaoDich();
    printf("Da cap nhat giao dich!\n");
    if (gd->loai == 0) canhBaoNganSach(gd->ngay);
}

void xoaGiaoDich() {
    printf("\n========== XOA GIAO DICH ==========\n");
    if (inGiaoDichCuaToi() == 0) return;
    int stt = docInt("Nhap STT can xoa (0 de huy): ");
    if (stt == 0) return;
    int vt = viTriCuaToi(stt);
    if (vt == -1) { printf("STT khong hop le!\n"); return; }
    if (!docCoKhong("Ban chac chan xoa? (1: Co, 0: Khong): ")) { printf("Da huy.\n"); return; }
    for (int i = vt; i < danhSach.soLuong - 1; i++) danhSach.ds[i] = danhSach.ds[i + 1];
    danhSach.soLuong--;
    luuGiaoDich();
    printf("Da xoa giao dich!\n");
}
