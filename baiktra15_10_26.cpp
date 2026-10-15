#include <iostream>
#include <cstdio>

#define INF 1e9

using namespace std;


int** capPhatMaTran(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
    return matrix;
}


void giaiPhongMaTran(int** matrix, int n) {
    if (matrix != nullptr) {
        for (int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

int main() {

    if (freopen("D:/Documents/CDL&GTNC/matrix.txt", "r", stdin) == NULL) {
        cout << "Loi: Khong the mo file matrix.txt!" << endl;
        return 1;
    }

    int n = 0;
    if (!(cin >> n) || n <= 0) {
        cout << "Loi: Khong doc duoc n tu file!" << endl;
        return 1;
    }

    int** matrix = capPhatMaTran(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val;
            cin >> val;
            if (i != j && val == 0) {
                matrix[i][j] = INF;
            } else {
                matrix[i][j] = val;
            }
        }
    }


    cout << "=== MA TRAN TRONG SO (" << n << "x" << n << ") ===\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << matrix[i][j] << "\t";
            }
        }
        cout << "\n";
    }

    giaiPhongMaTran(matrix, n);
    return 0;
}