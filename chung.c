#include "chung.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

TaiKhoan dsTaiKhoan[MAX_USER];
int soTaiKhoan = 0;
int chiSoHienTai = -1;
DanhSach danhSach;

void saoChep(char dich[], const char nguon[], size_t size) {
    strncpy(dich, nguon, size - 1);
    dich[size - 1] = '\0';
}

int tachTruong(char *line, char *f[], int max) {
    int n = 0;
    line[strcspn(line, "\r\n")] = '\0';
    f[n++] = line;
    for (char *p = line; *p != '\0' && n < max; p++) {
        if (*p == '|') { *p = '\0'; f[n++] = p + 1; }
    }
    return n;
}

int chuaChuoi(const char *s, const char *tuKhoa) {
    size_t ls = strlen(s), lk = strlen(tuKhoa);
    if (lk == 0) return 1;
    if (lk > ls) return 0;
    for (size_t i = 0; i + lk <= ls; i++) {
        size_t j = 0;
        while (j < lk &&
               tolower((unsigned char)s[i + j]) ==
               tolower((unsigned char)tuKhoa[j])) j++;
        if (j == lk) return 1;
    }
    return 0;
}

void docDong(char s[], int size) {
    if (fgets(s, size, stdin) == NULL) {
        printf("\nKhong con du lieu nhap. Thoat chuong trinh.\n");
        exit(0);
    }
    if (strchr(s, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    s[strcspn(s, "\r\n")] = '\0';
}

int docInt(const char *thongBao) {
    char s[100], *end;
    long x;
    while (1) {
        printf("%s", thongBao);
        docDong(s, sizeof(s));
        errno = 0;
        x = strtol(s, &end, 10);
        int coSo = (end != s);
        while (*end == ' ') end++;
        if (coSo && *end == '\0' && errno == 0 &&
            x >= INT_MIN && x <= INT_MAX) return (int)x;
        printf("Du lieu khong hop le! Nhap lai.\n");
    }
}

double docDouble(const char *thongBao) {
    char s[100], *end;
    double x;
    while (1) {
        printf("%s", thongBao);
        docDong(s, sizeof(s));
        errno = 0;
        x = strtod(s, &end);
        int coSo = (end != s);
        while (*end == ' ') end++;
        if (coSo && *end == '\0' && errno == 0 &&
            isfinite(x) && x >= 0 && x <= MAX_TIEN) return x;
        printf("So tien khong hop le! Nhap lai.\n");
    }
}

void docChuoi(const char *thongBao, char s[], int size) {
    printf("%s", thongBao);
    docDong(s, size);
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] == '|') s[i] = ' ';
}

void docChuoiKhongRong(const char *thongBao, char s[], int size) {
    do {
        docChuoi(thongBao, s, size);
        if (strlen(s) == 0) printf("Khong duoc de trong!\n");
    } while (strlen(s) == 0);
}

int docCoKhong(const char *thongBao) {
    int x;
    do { x = docInt(thongBao); } while (x != 0 && x != 1);
    return x;
}

int namNhuan(int nam) {
    return nam % 400 == 0 || (nam % 4 == 0 && nam % 100 != 0);
}

int ngayTrongThang(int thang, int nam) {
    int ngay[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (thang == 2 && namNhuan(nam)) return 29;
    return ngay[thang - 1];
}

int ngayHopLe(Ngay d) {
    if (d.nam < 1 || d.thang < 1 || d.thang > 12) return 0;
    if (d.ngay < 1 || d.ngay > ngayTrongThang(d.thang, d.nam)) return 0;
    return 1;
}

Ngay nhapNgay() {
    Ngay d;
    do {
        d.ngay = docInt("Nhap ngay: ");
        d.thang = docInt("Nhap thang: ");
        d.nam = docInt("Nhap nam: ");
        if (!ngayHopLe(d)) printf("Ngay thang khong hop le! Nhap lai.\n");
    } while (!ngayHopLe(d));
    return d;
}

Ngay ngayHomNay() {
    Ngay d = {1, 1, 2000};
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if (tm != NULL) {
        d.ngay = tm->tm_mday;
        d.thang = tm->tm_mon + 1;
        d.nam = tm->tm_year + 1900;
    }
    return d;
}

long khoaNgay(Ngay d) {
    return (long)d.nam * 10000L + d.thang * 100L + d.ngay;
}
