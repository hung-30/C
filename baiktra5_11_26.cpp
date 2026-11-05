#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct NgayThang {
    int ngay;
    int thang;
    int nam;
};

struct HangHoa {
    string maHang;
    string tenHang;
    NgayThang ngayXuat;
    double giaXuat;
};

struct Node {
    HangHoa data;
    Node* left;
    Node* right;
};

void initTree(Node* &root) {
    root = NULL;
}

Node* createNode(HangHoa x) {
    Node* p = new Node();
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

Node* insertNode(Node* root, HangHoa x) {
    if (root == NULL) {
        return createNode(x);
    }
    
    if (x.maHang < root->data.maHang) {
        root->left = insertNode(root->left, x);
    } else if (x.maHang > root->data.maHang) {
        root->right = insertNode(root->right, x);
    } else {
        cout << "Loi: Ma hang hoa '" << x.maHang << "' da ton tai!\n";
    }
    
    return root;
}

Node* searchNode(Node* root, string maTim) {
    if (root == NULL || root->data.maHang == maTim) {
        return root;
    }
    
    if (maTim < root->data.maHang) {
        return searchNode(root->left, maTim);
    } else {
        return searchNode(root->right, maTim);
    }
}

void inHangHoa(HangHoa x) {
    cout << left << setw(12) << x.maHang
         << setw(25) << x.tenHang
         << right << setfill('0') << setw(2) << x.ngayXuat.ngay << "/"
         << setw(2) << x.ngayXuat.thang << "/"
         << setw(4) << x.ngayXuat.nam << setfill(' ')
         << setw(18) << fixed << setprecision(2) << x.giaXuat << endl;
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        inHangHoa(root->data);
        inorderTraversal(root->right);
    }
}

HangHoa nhapHangHoa() {
    HangHoa hh;
    cout << "  - Nhap ma hang hoa: ";
    cin >> hh.maHang;
    
    cin.ignore();
    cout << "  - Nhap ten hang hoa: ";
    getline(cin, hh.tenHang);
    
    cout << "  - Nhap ngay xuat: ";
    char slash1, slash2;
    cin >> hh.ngayXuat.ngay >> slash1 >> hh.ngayXuat.thang >> slash2 >> hh.ngayXuat.nam;
    
    cout << "  - Nhap gia xuat: ";
    cin >> hh.giaXuat;
    
    return hh;
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

int main() {
    Node* root;
    initTree(root);

    int n;
    cout << "================ NHAP DANH SACH HANG HOA ================\n";
    cout << "Nhap so luong hang hoa: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nNhap thong tin hang hoa thu " << i + 1 << ":\n";
        HangHoa hh = nhapHangHoa();
        root = insertNode(root, hh);
    }

    cout << "\n================ DANH SACH HANG HOA TRONG CAY ================\n";
    if (root == NULL) {
        cout << "Cay rong!\n";
    } else {
        cout << left << setw(12) << "Ma HH"
             << setw(25) << "Ten Hang Hoa"
             << setw(14) << "Ngay Xuat"
             << setw(18) << "Gia Xuat" << endl;
        cout << string(69, '-') << endl;
        inorderTraversal(root);
    }

    cout << "\n================ TIM KIEM HANG HOA ================\n";
    string maTim;
    cout << "Nhap ma hang hoa can tim: ";
    cin >> maTim;

    Node* result = searchNode(root, maTim);
    if (result != NULL) {
        cout << "\n-> Da tim thay hang hoa!\n";
        cout << left << setw(12) << "Ma HH"
             << setw(25) << "Ten Hang Hoa"
             << setw(14) << "Ngay Xuat"
             << setw(18) << "Gia Xuat" << endl;
        cout << string(69, '-') << endl;
        inHangHoa(result->data);
    } else {
        cout << "\n-> Thong bao: Khong co hang hoa trong cay mang ma '" << maTim << "'!\n";
    }

    freeTree(root);

    return 0;
}