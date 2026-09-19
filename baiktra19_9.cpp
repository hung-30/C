#include <stdio.h>
#include <string.h>

// ================= CÂU 1 =================
// Định nghĩa kiểu ngày tháng
typedef struct {
    int ngay;
    int thang;
    int nam;
} Ngay;

// Định nghĩa cấu trúc Hàng hóa
typedef struct {
    char maHang[20];
    char tenHang[50];
    Ngay ngayXuat;
    float giaXuat; 
} HangHoa;

// ================= CÂU 2 =================
// Hàm nhập mảng n hàng hóa
void nhapMangHangHoa(HangHoa a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Nhap hang hoa thu %d ---\n", i + 1);
        
        printf("Nhap ma hang: ");
        scanf("%s", a[i].maHang);
        
        getchar(); 
        
        printf("Nhap ten hang: ");
        fgets(a[i].tenHang, sizeof(a[i].tenHang), stdin);
        a[i].tenHang[strcspn(a[i].tenHang, "\n")] = 0; 
        
        printf("Nhap ngay xuat: ");
        scanf("%d/%d/%d", &a[i].ngayXuat.ngay, &a[i].ngayXuat.thang, &a[i].ngayXuat.nam);
        
        printf("Nhap gia xuat (trieu dong): ");
        scanf("%f", &a[i].giaXuat);
    }
}

// ================= CÂU 3 =================
// Hàm xuất mảng n hàng hóa
void xuatMangHangHoa(HangHoa a[], int n) {
    printf("\n%-10s | %-25s | %-15s | %s\n", "Ma hang", "Ten hang", "Ngay xuat", "Gia xuat (Tr.d)");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10s | %-25s | %02d/%02d/%04d      | %.2f\n", 
               a[i].maHang, a[i].tenHang, 
               a[i].ngayXuat.ngay, a[i].ngayXuat.thang, a[i].ngayXuat.nam, 
               a[i].giaXuat);
    }
}

// ================= CÂU 4 =================
// Thuật toán sắp xếp chọn trực tiếp (Selection sort)
void selectionSort(HangHoa a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j].giaXuat < a[min_idx].giaXuat) {
                min_idx = j;
            }
        }
        // Hoán vị
        HangHoa temp = a[i];
        a[i] = a[min_idx];
        a[min_idx] = temp;
    }
}

// ================= CÂU 5 =================
// Thuật toán tìm kiếm nhị phân chia để trị 
void timKiemNhiPhan(HangHoa a[], int n, float X) {
    int bottom = 0, top = n - 1;
    int found_idx = -1;
    
    while (bottom <= top) {
        int mid = (bottom + top) / 2;
        if (a[mid].giaXuat == X) {
            found_idx = mid;
            break;
        } else if (a[mid].giaXuat < X) {
            bottom = mid + 1;
        } else {
            top = mid - 1;
        }
    }

    if (found_idx == -1) {
        printf("\n-> Khong tim thay hang hoa nao co gia xuat = %.2f trieu dong.\n", X);
    } else {
        // Tìm các mặt hàng lân cận có cùng giá X (vì mảng đã được sắp xếp)
        int start = found_idx, end = found_idx;
        while (start > 0 && a[start - 1].giaXuat == X) start--;
        while (end < n - 1 && a[end + 1].giaXuat == X) end++;
        
        printf("\n-> Cac hang hoa co gia xuat = %.2f trieu dong:\n", X);
        printf("\n%-10s | %-25s | %-15s | %s\n", "Ma hang", "Ten hang", "Ngay xuat", "Gia xuat (Tr.d)");
        printf("-----------------------------------------------------------------------\n");
        for (int i = start; i <= end; i++) {
            printf("%-10s | %-25s | %02d/%02d/%04d      | %.2f\n", 
                   a[i].maHang, a[i].tenHang, 
                   a[i].ngayXuat.ngay, a[i].ngayXuat.thang, a[i].ngayXuat.nam, 
                   a[i].giaXuat);
        }
    }
}

// ================= CÂU 6 =================
int main() {
    HangHoa danhSach[100];
    int n;

    printf("Nhap so luong hang hoa n = ");
    scanf("%d", &n);

    // 6.1 Nhập và hiển thị
    nhapMangHangHoa(danhSach, n);
    printf("\n============= DANH SACH HANG HOA VUA NHAP =============");
    xuatMangHangHoa(danhSach, n);

    // 6.2 Sắp xếp
    selectionSort(danhSach, n);
    printf("\n========== DANH SACH SAU KHI SAP XEP TANG DAN =========");
    xuatMangHangHoa(danhSach, n);

    // 6.3 Tìm kiếm
    float X;
    printf("\nNhap gia xuat X can tim (trieu dong): ");
    scanf("%f", &X);
    timKiemNhiPhan(danhSach, n, X);

    return 0;
}