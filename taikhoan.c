#include "taikhoan.h"
#include "giaodich.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void luuTaiKhoan() {
    FILE *f = fopen(FILE_USER, "w");
    if (f == NULL) { printf("Khong the luu file tai khoan!\n"); return; }
    for (int i = 0; i < soTaiKhoan; i++)
        fprintf(f, "%s|%s|%d|%d|%.2lf\n",
                dsTaiKhoan[i].tenDangNhap, dsTaiKhoan[i].matKhau,
                dsTaiKhoan[i].quyen, dsTaiKhoan[i].trangThai,
                dsTaiKhoan[i].nganSach);
    fclose(f);
}

void taoAdminMacDinh() {
    int vt = soTaiKhoan < MAX_USER ? soTaiKhoan++ : MAX_USER - 1;
    saoChep(dsTaiKhoan[vt].tenDangNhap, "admin", sizeof(dsTaiKhoan[vt].tenDangNhap));
    saoChep(dsTaiKhoan[vt].matKhau, "admin123", sizeof(dsTaiKhoan[vt].matKhau));
    dsTaiKhoan[vt].quyen = 1;
    dsTaiKhoan[vt].trangThai = 1;
    dsTaiKhoan[vt].nganSach = 0;
    luuTaiKhoan();
    printf("Da tao tai khoan Admin mac dinh: admin / admin123\n");
}

void docTaiKhoan() {
    FILE *f = fopen(FILE_USER, "r");
    soTaiKhoan = 0;
    if (f == NULL) { taoAdminMacDinh(); return; }
    char line[256];
    while (soTaiKhoan < MAX_USER && fgets(line, sizeof(line), f) != NULL) {
        char *f5[5];
        if (tachTruong(line, f5, 5) != 5) continue;
        if (strlen(f5[0]) == 0 || strlen(f5[0]) >= sizeof(dsTaiKhoan[0].tenDangNhap)) continue;
        if (strlen(f5[1]) == 0 || strlen(f5[1]) >= sizeof(dsTaiKhoan[0].matKhau)) continue;
        TaiKhoan tk;
        saoChep(tk.tenDangNhap, f5[0], sizeof(tk.tenDangNhap));
        saoChep(tk.matKhau, f5[1], sizeof(tk.matKhau));
        tk.quyen = atoi(f5[2]) == 1 ? 1 : 0;
        tk.trangThai = atoi(f5[3]) == 1 ? 1 : 0;
        tk.nganSach = atof(f5[4]);
        if (!isfinite(tk.nganSach) || tk.nganSach < 0) tk.nganSach = 0;
        dsTaiKhoan[soTaiKhoan++] = tk;
    }
    fclose(f);
    int coAdmin = 0;
    for (int i = 0; i < soTaiKhoan; i++)
        if (dsTaiKhoan[i].quyen == 1) coAdmin = 1;
    if (!coAdmin) taoAdminMacDinh();
}

int timTaiKhoan(const char ten[]) {
    for (int i = 0; i < soTaiKhoan; i++)
        if (strcmp(dsTaiKhoan[i].tenDangNhap, ten) == 0) return i;
    return -1;
}

int dangNhap() {
    char ten[30], matKhau[30];
    printf("\n========== DANG NHAP ==========\n");
    for (int lan = 1; lan <= 3; lan++) {
        docChuoi("Ten dang nhap: ", ten, sizeof(ten));
        docChuoi("Mat khau: ", matKhau, sizeof(matKhau));
        int index = timTaiKhoan(ten);
        if (index != -1 && strcmp(dsTaiKhoan[index].matKhau, matKhau) == 0) {
            if (dsTaiKhoan[index].trangThai == 1) {
                chiSoHienTai = index;
                printf("\nDang nhap thanh cong!\n");
                return 1;
            }
            printf("Tai khoan da bi khoa!\n");
        } else printf("Sai ten dang nhap hoac mat khau!\n");
        printf("Ban con %d lan thu.\n", 3 - lan);
    }
    printf("Dang nhap that bai!\n");
    return 0;
}

void taoTaiKhoan() {
    if (soTaiKhoan >= MAX_USER) { printf("Danh sach tai khoan da day!\n"); return; }
    TaiKhoan tk;
    printf("\n========== TAO TAI KHOAN ==========\n");
    docChuoi("Nhap ten dang nhap: ", tk.tenDangNhap, sizeof(tk.tenDangNhap));
    if (strlen(tk.tenDangNhap) == 0) { printf("Ten dang nhap khong duoc de trong!\n"); return; }
    if (timTaiKhoan(tk.tenDangNhap) != -1) { printf("Ten dang nhap da ton tai!\n"); return; }
    docChuoi("Nhap mat khau: ", tk.matKhau, sizeof(tk.matKhau));
    if (strlen(tk.matKhau) == 0) { printf("Mat khau khong duoc de trong!\n"); return; }
    tk.quyen = 0; tk.trangThai = 1; tk.nganSach = 0;
    dsTaiKhoan[soTaiKhoan++] = tk;
    luuTaiKhoan();
    printf("Tao tai khoan User thanh cong!\n");
}

void danhSachTaiKhoan() {
    printf("\n========== DANH SACH TAI KHOAN ==========\n");
    for (int i = 0; i < soTaiKhoan; i++) {
        printf("\nTen dang nhap: %s\n", dsTaiKhoan[i].tenDangNhap);
        printf("Quyen: %s\n", dsTaiKhoan[i].quyen == 1 ? "Admin" : "User");
        printf("Trang thai: %s\n", dsTaiKhoan[i].trangThai == 1 ? "Hoat dong" : "Bi khoa");
        printf("Ngan sach thang: %.2lf\n", dsTaiKhoan[i].nganSach);
    }
}

void khoaMoTaiKhoan() {
    char ten[30];
    docChuoi("Nhap ten tai khoan can khoa/mo: ", ten, sizeof(ten));
    int index = timTaiKhoan(ten);
    if (index == -1) { printf("Khong tim thay tai khoan!\n"); return; }
    if (dsTaiKhoan[index].quyen == 1) { printf("Khong the khoa tai khoan Admin!\n"); return; }
    dsTaiKhoan[index].trangThai = 1 - dsTaiKhoan[index].trangThai;
    luuTaiKhoan();
    printf("Da %s tai khoan %s!\n",
           dsTaiKhoan[index].trangThai == 1 ? "mo khoa" : "khoa",
           dsTaiKhoan[index].tenDangNhap);
}

void xoaTaiKhoan() {
    char ten[30];
    docChuoi("Nhap ten tai khoan can xoa: ", ten, sizeof(ten));
    int index = timTaiKhoan(ten);
    if (index == -1) { printf("Khong tim thay tai khoan!\n"); return; }
    if (dsTaiKhoan[index].quyen == 1) { printf("Khong the xoa tai khoan Admin!\n"); return; }
    if (!docCoKhong("Xoa tai khoan va TAT CA giao dich cua no? (1: Co, 0: Khong): ")) {
        printf("Da huy.\n"); return;
    }
    int j = 0;
    for (int i = 0; i < danhSach.soLuong; i++)
        if (strcmp(danhSach.ds[i].nguoiDung, ten) != 0)
            danhSach.ds[j++] = danhSach.ds[i];
    danhSach.soLuong = j;
    for (int i = index; i < soTaiKhoan - 1; i++) dsTaiKhoan[i] = dsTaiKhoan[i + 1];
    soTaiKhoan--;
    if (chiSoHienTai > index) chiSoHienTai--;
    luuTaiKhoan();
    luuGiaoDich();
    printf("Da xoa tai khoan va giao dich lien quan!\n");
}

void doiMatKhau() {
    char cu[30], moi[30], nhapLai[30];
    docChuoi("Nhap mat khau hien tai: ", cu, sizeof(cu));
    if (strcmp(cu, dsTaiKhoan[chiSoHienTai].matKhau) != 0) {
        printf("Mat khau hien tai khong dung!\n"); return;
    }
    docChuoi("Nhap mat khau moi: ", moi, sizeof(moi));
    if (strlen(moi) == 0) { printf("Mat khau khong duoc de trong!\n"); return; }
    docChuoi("Nhap lai mat khau moi: ", nhapLai, sizeof(nhapLai));
    if (strcmp(moi, nhapLai) != 0) { printf("Mat khau nhap lai khong khop!\n"); return; }
    saoChep(dsTaiKhoan[chiSoHienTai].matKhau, moi, sizeof(dsTaiKhoan[chiSoHienTai].matKhau));
    luuTaiKhoan();
    printf("Doi mat khau thanh cong!\n");
}
