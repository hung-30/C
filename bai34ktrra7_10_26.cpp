#include <iostream>
#include <string>

using namespace std;


struct NhanVien {
    string maNV;
    string hoTen;
    string ngaySinh;
    double luong;
};


void nhapDanhSach(NhanVien a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\n--- Nhap thong tin nhan vien thu " << i + 1 << " ---\n";
        
        cout << "Ma nhan vien: ";
        cin >> a[i].maNV;
        cin.ignore(); 
        
        cout << "Ho ten: ";
        getline(cin, a[i].hoTen);
        
        cout << "Ngay sinh: ";
        getline(cin, a[i].ngaySinh);
        
        cout << "Luong (trieu dong): ";
        cin >> a[i].luong;
    }
}


void xuatDanhSach(NhanVien a[], int n) {
    cout << "\n-------------------------------------------------------------------------\n";
    cout << "Ma NV\t| Ho ten\t\t| Ngay sinh\t| Luong (Trieu VNĐ)\n";
    cout << "-------------------------------------------------------------------------\n";
    
    for (int i = 0; i < n; i++) {
        cout << a[i].maNV << "\t| " 
             << a[i].hoTen << "\t\t| " 
             << a[i].ngaySinh << "\t| " 
             << a[i].luong << "\n";
    }
    cout << "-------------------------------------------------------------------------\n";
}


void sapXepNoiBot(NhanVien a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            if (a[j].luong > a[j + 1].luong) {
                NhanVien temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}


void timKiemNhiPhan(NhanVien a[], int n, double x) {
    int left = 0, right = n - 1;
    int viTriTimThay = -1;


    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (a[mid].luong == x) {
            viTriTimThay = mid; 
            break; 
        }
        else if (a[mid].luong < x) {
            left = mid + 1; 
        }
        else {
            right = mid - 1; 
        }
    }


    if (viTriTimThay == -1) {
        cout << "Khong tim thay nhan vien nao co muc luong bang " << x << " trieu dong!\n";
        return;
    }


    int start = viTriTimThay;
    int end = viTriTimThay;
    
    while (start > 0 && a[start - 1].luong == x) start--;
    while (end < n - 1 && a[end + 1].luong == x) end++;

    cout << "\n--- Danh sach nhan vien co muc luong = " << x << " trieu dong ---\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << "Ma NV\t| Ho ten\t\t| Ngay sinh\t| Luong (Trieu VNĐ)\n";
    cout << "-------------------------------------------------------------------------\n";
    
    for (int i = start; i <= end; i++) {
        cout << a[i].maNV << "\t| " 
             << a[i].hoTen << "\t\t| " 
             << a[i].ngaySinh << "\t| " 
             << a[i].luong << "\n";
    }
    cout << "-------------------------------------------------------------------------\n";
}


int main() {
    int n;

    do {
        cout << "Nhap so luong nhan vien (n > 0): ";
        cin >> n;
    } while (n <= 0);


    NhanVien* dsNV = new NhanVien[n];


    cout << "\n=== NHAP DANH SACH NHAN VIEN ===";
    nhapDanhSach(dsNV, n);

    cout << "\n=== DANH SACH NHAN VIEN VUA NHAP ===";
    xuatDanhSach(dsNV, n);

    sapXepNoiBot(dsNV, n);
    cout << "\n=== DANH SACH SAU KHI SAP XEP (LUONG TANG DAN) ===";
    xuatDanhSach(dsNV, n);


    double X;
    cout << "\nNhap muc luong X can tim (trieu dong): ";
    cin >> X;
    
    timKiemNhiPhan(dsNV, n, X);


    delete[] dsNV;

    return 0;
}