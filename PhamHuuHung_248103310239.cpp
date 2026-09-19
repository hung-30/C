#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// ================= CÂU 1: ĐỊNH NGHĨA CẤU TRÚC =================
struct VeMayBay {
    int maVe;
    string khoiHanh;
    string den;
    float giaVe;
};

// Hàm phụ trợ để nhập 1 vé
void nhapMotVe(VeMayBay &v) {
    cout << "Nhap ma ve: ";
    cin >> v.maVe;
    cin.ignore(); // Xóa bộ nhớ đệm trước khi nhập chuỗi
    cout << "Nhap noi khoi hanh: ";
    getline(cin, v.khoiHanh);
    cout << "Nhap noi den: ";
    getline(cin, v.den);
    cout << "Nhap gia ve: ";
    cin >> v.giaVe;
}

// Hàm phụ trợ để xuất 1 vé
void xuatMotVe(VeMayBay v) {
    cout << "| " << setw(5) << v.maVe 
         << " | " << setw(15) << left << v.khoiHanh 
         << " | " << setw(15) << left << v.den 
         << " | " << setw(10) << right << v.giaVe << " |" << endl;
}

// ================= CÂU 2: HÀM NHẬP MẢNG =================
void nhapMangVe(VeMayBay a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\n--- Nhap thong tin ve may bay thu " << i + 1 << " ---" << endl;
        nhapMotVe(a[i]);
    }
}

// ================= CÂU 3: HÀM XUẤT MẢNG =================
void xuatMangVe(VeMayBay a[], int n) {
    cout << string(59, '-') << endl;
    cout << "| " << setw(5) << "Ma Ve" 
         << " | " << setw(15) << left << "Khoi Hanh" 
         << " | " << setw(15) << left << "Noi Den" 
         << " | " << setw(10) << right << "Gia Ve" << " |" << endl;
    cout << string(59, '-') << endl;
    for (int i = 0; i < n; i++) {
        xuatMotVe(a[i]);
    }
    cout << string(59, '-') << endl;
}

// ================= CÂU 4: QUICK SORT (TĂNG DẦN GIÁ VÊ) =================
void quickSort(VeMayBay a[], int left, int right) {
    if (left >= right) return;
    
    int i = left, j = right;
    // Chọn phần tử chốt (pivot) ở giữa
    float pivot = a[(left + right) / 2].giaVe; 
    
    // Phân hoạch mảng
    while (i <= j) {
        while (a[i].giaVe < pivot) i++;
        while (a[j].giaVe > pivot) j--;
        
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    
    // Gọi đệ quy sắp xếp 2 nửa
    quickSort(a, left, j);
    quickSort(a, i, right);
}

// ================= CÂU 5: TÌM KIẾM NHỊ PHÂN (CHIA ĐỂ TRỊ) =================
// Hàm đệ quy tìm và in ra tất cả các vé có giá bằng X
void binarySearch(VeMayBay a[], int left, int right, float X, bool &found) {
    if (left > right) return;
    
    int mid = left + (right - left) / 2;
    
    if (a[mid].giaVe == X) {
        found = true;
        xuatMotVe(a[mid]); // In ra vé tìm thấy
        
        // Vì có thể có nhiều vé cùng giá X nằm cạnh nhau, ta tiếp tục tìm kiếm ở 2 nửa
        binarySearch(a, left, mid - 1, X, found);
        binarySearch(a, mid + 1, right, X, found);
    } 
    else if (a[mid].giaVe > X) {
        // Nếu giá vé ở giữa lớn hơn X, tìm nửa trái
        binarySearch(a, left, mid - 1, X, found);
    } 
    else {
        // Nếu giá vé ở giữa nhỏ hơn X, tìm nửa phải
        binarySearch(a, mid + 1, right, X, found);
    }
}

// ================= CÂU 6: HÀM CHÍNH =================
int main() {
    int n;
    cout << "Nhap so luong ve may bay (n): ";
    cin >> n;
    
    // Cấp phát mảng động
    VeMayBay *danhSachVe = new VeMayBay[n];
    
    // 6.1 Nhập và hiển thị
    nhapMangVe(danhSachVe, n);
    cout << "\n>>> DANH SACH VE MAY BAY VUA NHAP <<<\n";
    xuatMangVe(danhSachVe, n);
    
    // 6.2 Sắp xếp và hiển thị
    quickSort(danhSachVe, 0, n - 1);
    cout << "\n>>> DANH SACH VE SAU KHI SAP XEP TANG DAN THEO GIA <<<\n";
    xuatMangVe(danhSachVe, n);
    
    // 6.3 Tìm kiếm theo giá X
    float X;
    cout << "\nNhap gia ve (X) can tim: ";
    cin >> X;
    
    cout << "\n>>> KET QUA TIM KIEM VE CO GIA " << X << " <<<\n";
    bool found = false;
    // In tiêu đề bảng
    cout << string(59, '-') << endl;
    cout << "| " << setw(5) << "Ma Ve" << " | " << setw(15) << left << "Khoi Hanh" 
         << " | " << setw(15) << left << "Noi Den" << " | " << setw(10) << right << "Gia Ve" << " |" << endl;
    cout << string(59, '-') << endl;
    
    // Thực thi tìm kiếm nhị phân
    binarySearch(danhSachVe, 0, n - 1, X, found);
    cout << string(59, '-') << endl;
    
    if (!found) {
        cout << "-> Khong tim thay ve may bay nao co gia bang " << X << ".\n";
    }
    
    // Giải phóng bộ nhớ
    delete[] danhSachVe;
    
    return 0;
}