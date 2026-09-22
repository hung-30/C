#include <iostream>
#include <string>

using namespace std;

// ==========================================
// CÂU 1: Định nghĩa cấu trúc SinhVien
// ==========================================
struct SinhVien {
    int maSV;
    string tenSV;
    string lop;
    float diemTK;
    string hanhKiem;
};

// ==========================================
// CÂU 2: Cấu trúc cây nhị phân và các thao tác
// ==========================================
struct Node {
    SinhVien data;
    Node* left;
    Node* right;
};

// 1. Khởi tạo cây
void khoiTaoCay(Node*& root) {
    root = nullptr;
}

// 2. Tạo mới một nút chứa dữ liệu
Node* taoNut(SinhVien sv) {
    Node* newNode = new Node;
    newNode->data = sv;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// 3. Chèn nút vào cây (chia để trị)
void chenNut(Node*& root, SinhVien sv) {
    if (root == nullptr) {
        root = taoNut(sv);
    } else {
        // So sánh theo Khóa (maSV) để chèn vào nhánh trái hoặc nhánh phải
        if (sv.maSV < root->data.maSV) {
            chenNut(root->left, sv);
        } else if (sv.maSV > root->data.maSV) {
            chenNut(root->right, sv);
        }
        // Bỏ qua nếu mã sinh viên đã tồn tại
    }
}

// 4. Tìm kiếm phần tử trong cây (chia để trị)
Node* timKiem(Node* root, int maSV) {
    if (root == nullptr) return nullptr;
    if (root->data.maSV == maSV) return root;

    // Phân nhỏ bài toán, tìm ở nửa trái hoặc nửa phải
    if (maSV < root->data.maSV) {
        return timKiem(root->left, maSV);
    } else {
        return timKiem(root->right, maSV);
    }
}

// Hàm phụ trợ in thông tin 1 sinh viên
void inThongTinSV(SinhVien sv) {
    cout << "Ma SV: " << sv.maSV 
         << " | Ten: " << sv.tenSV 
         << " | Lop: " << sv.lop 
         << " | Diem TK: " << sv.diemTK 
         << " | Hanh kiem: " << sv.hanhKiem << endl;
}

// 5. Duyệt cây (Duyệt LNR - Inorder: In ra danh sách tăng dần theo Mã SV)
void duyetCay(Node* root) {
    if (root != nullptr) {
        duyetCay(root->left);       // Duyệt cây con trái
        inThongTinSV(root->data);   // Thao tác trên nút gốc
        duyetCay(root->right);      // Duyệt cây con phải
    }
}

// ==========================================
// CHƯƠNG TRÌNH CHÍNH
// ==========================================
int main() {
    Node* root;
    khoiTaoCay(root);

    // CÂU 3: Nhập vào cây nhị phân gồm n Sinh viên
    int n;
    cout << "--- NHAP DANH SACH SINH VIEN ---" << endl;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        SinhVien sv;
        cout << "\nNhap thong tin sinh vien thu " << i + 1 << ":" << endl;
        cout << "Ma SV: ";
        cin >> sv.maSV;
        cin.ignore(); // Xóa bộ đệm bàn phím
        
        cout << "Ten SV: ";
        getline(cin, sv.tenSV);
        
        cout << "Lop: ";
        getline(cin, sv.lop);
        
        cout << "Diem tong ket: ";
        cin >> sv.diemTK;
        cin.ignore();
        
        cout << "Hanh kiem (Tot/Kha/TB/Yeu): ";
        getline(cin, sv.hanhKiem);

        chenNut(root, sv);
    }

    // CÂU 4: Liệt kê danh sách sinh viên có trong cây
    cout << "\n--- DANH SACH SINH VIEN (Sap xep theo Ma SV) ---" << endl;
    duyetCay(root);

    // CÂU 5: Tìm kiếm sinh viên theo mã số vừa nhập
    int maCanTim;
    cout << "\n--- TIM KIEM SINH VIEN ---" << endl;
    cout << "Nhap ma so sinh vien can tim: ";
    cin >> maCanTim;

    Node* ketQua = timKiem(root, maCanTim);
    if (ketQua != nullptr) {
        cout << "=> Da tim thay sinh vien:" << endl;
        inThongTinSV(ketQua->data);
    } else {
        cout << "=> Khong co sinh vien trong cay!" << endl;
    }

    return 0;
}