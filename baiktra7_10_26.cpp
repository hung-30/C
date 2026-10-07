#include <iostream>
#include <string>

using namespace std;


struct KhachHang {
    int maKH;
    string tenKH;
    string sdt;
    double tongTien;
};


void nhapDanhSach(KhachHang a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\n--- Nhap thong tin khach hang thu " << i + 1 << " ---\n";
        cout << "Ma khach hang: ";
        cin >> a[i].maKH;
        cin.ignore(); 
        
        cout << "Ten khach hang: ";
        getline(cin, a[i].tenKH);
        
        cout << "So dien thoai: ";
        getline(cin, a[i].sdt);
        
        cout << "Tong tien thanh toan: ";
        cin >> a[i].tongTien;
    }
}


void xuatDanhSach(KhachHang a[], int n) {
    cout << "\n-------------------------------------------------------------------------\n";
    cout << "Ma KH\t| Ten khach hang\t\t| So dien thoai\t| Tong tien\n";
    cout << "-------------------------------------------------------------------------\n";
    
    for (int i = 0; i < n; i++) {
        cout << a[i].maKH << "\t| " 
             << a[i].tenKH << "\t\t| " 
             << a[i].sdt << "\t| " 
             << a[i].tongTien << "\n";
    }
    cout << "-------------------------------------------------------------------------\n";
}


void sapXepChen(KhachHang a[], int n) {
    for (int i = 1; i < n; i++) {
        KhachHang key = a[i];
        int j = i - 1;
        
        while (j >= 0 && a[j].tongTien > key.tongTien) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}


void timKiemNhiPhan(KhachHang a[], int n, double x) {
    int left = 0, right = n - 1;
    int viTriTimThay = -1;


    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (a[mid].tongTien == x) {
            viTriTimThay = mid;
            break; 
        }
        else if (a[mid].tongTien < x) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (viTriTimThay == -1) {
        cout << "Khong tim thay khach hang nao co tong tien thanh toan bang " << x << "!\n";
        return;
    }


    int start = viTriTimThay;
    int end = viTriTimThay;
    
    while (start > 0 && a[start - 1].tongTien == x) start--;
    while (end < n - 1 && a[end + 1].tongTien == x) end++;

    cout << "\n--- Danh sach khach hang co tong tien = " << x << " ---\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << "Ma KH\t| Ten khach hang\t\t| So dien thoai\t| Tong tien\n";
    cout << "-------------------------------------------------------------------------\n";
    
    for (int i = start; i <= end; i++) {
        cout << a[i].maKH << "\t| " 
             << a[i].tenKH << "\t\t| " 
             << a[i].sdt << "\t| " 
             << a[i].tongTien << "\n";
    }
    cout << "-------------------------------------------------------------------------\n";
}


int main() {
    int n;
    
    do {
        cout << "Nhap so luong khach hang (n > 0): ";
        cin >> n;
    } while (n <= 0);

    KhachHang* danhSachKH = new KhachHang[n];

    cout << "\n--- NHAP DANH SACH KHACH HANG ---";
    nhapDanhSach(danhSachKH, n);

    cout << "\n--- DANH SACH KHACH HANG VUA NHAP ---";
    xuatDanhSach(danhSachKH, n);

    sapXepChen(danhSachKH, n);
    cout << "\n--- DANH SACH KHACH HANG SAU KHI SAP XEP (TANG DAN) ---";
    xuatDanhSach(danhSachKH, n);

    double X;
    cout << "\nNhap tong tien X can tim: ";
    cin >> X;
    
    timKiemNhiPhan(danhSachKH, n, X);

    delete[] danhSachKH;

    return 0;
}