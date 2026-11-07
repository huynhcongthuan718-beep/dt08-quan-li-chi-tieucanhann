CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
TARGET = quanlychitieu
SOURCES = main.c chung.c taikhoan.c giaodich.c thongke.c ngansach.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
