#include <iostream>

using namespace std;

#define TRUE 1
#define FALSE 0
#define VOCUNG 10000000

// Cấu trúc đồ thị
struct Graph
{
    int N;   // Số lượng các đỉnh của đồ thị
    int **A; // Ma trận trọng số
};

// Cấu trúc Dijkstra
struct Dijkstra
{
    Graph graph;
    int start;  // Đỉnh đầu
    int end;    // Đỉnh cuối
    int *truoc; // Mảng đánh dấu đường đi
    int *dist;  // Mảng đánh dấu khoảng cách
    int *T;     // Mảng đánh dấu đỉnh đã được gán nhãn
};

// Câu 2: Hàm Nhập từ file Grap.txt
void Nhap(Dijkstra &d)
{
    FILE* f = freopen("Grap.txt", "r", stdin);
    cin >> d.graph.N;
    cout << "So dinh : " << d.graph.N << endl;
    cin >> d.start >> d.end;

    d.graph.A = new int*[d.graph.N];
    for (int i = 0; i < d.graph.N; i++)
    {
        d.graph.A[i] = new int[d.graph.N];
        for (int j = 0; j < d.graph.N; j++)
        {
            cin >> d.graph.A[i][j];
            if (d.graph.A[i][j] == 0) d.graph.A[i][j] = VOCUNG;
        }
    }
    if (f != NULL) fclose(f);
}

// Câu 3: Hàm Hiển thị đồ thị
void HienThi(Dijkstra d)
{
    cout << "Do thi vua nhap la:" << endl;
    cout << "- So dinh cua do thi: " << d.graph.N << endl;
    cout << "- Ma tran trong so cua do thi:" << endl;
    for (int i = 0; i < d.graph.N; i++)
    {
        for (int j = 0; j < d.graph.N; j++)
        {
            if (d.graph.A[i][j] == VOCUNG)
                cout << 0 << "\t";
            else 
                cout << d.graph.A[i][j] << "\t";
        }
        cout << endl;
    }
}

// Hàm đặt tên các đỉnh của đồ thị
string GetName(int v)
{
    switch (v)
    {
        case 0: return "V1";
        case 1: return "V2";
        case 2: return "V3";
        case 3: return "V4";
        case 4: return "V5";
        case 5: return "V6";
        default: return "Unknown";
    }
}

// Hàm hiển thị đường đi ngắn nhất
void HienThiDuongDiNganNhat(Dijkstra d)
{
    int dinhcuoi = d.end;
    cout << "Duong di ngan nhat tu " << GetName(d.start) 
         << " den " << GetName(dinhcuoi) << " la" << endl;
    cout << GetName(dinhcuoi) << "<=";

    int i = d.truoc[dinhcuoi];
    while (i != d.start)
    {
        cout << GetName(i) << "<=";
        i = d.truoc[i];
    }
    cout << GetName(d.start);
    cout << endl << "Do dai duong di la : " << d.dist[dinhcuoi] << endl;
}

// Kiểm tra tập T đã gán nhãn hết chưa
bool CheckFullT(Dijkstra d)
{
    for (int i = 0; i < d.graph.N; i++)
    {
        if (!d.T[i]) return 0;
    }
    return 1;
}

// Câu 4: Thuật toán Dijkstra
void RunDijkstra(Dijkstra &d)
{
    d.truoc = new int[d.graph.N];
    d.dist = new int[d.graph.N];
    d.T = new int[d.graph.N];

    int s = d.start;
    for (int v = 0; v < d.graph.N; v++)
    {
        d.dist[v] = VOCUNG;
        d.truoc[v] = -1;
        d.T[v] = FALSE;
    }
    d.dist[s] = 0;

    while (!CheckFullT(d))
    {
        int u = -1, minp = VOCUNG;
        for (int v = 0; v < d.graph.N; v++)
        {
            if (!d.T[v] && d.dist[v] < minp)
            {
                u = v;
                minp = d.dist[v];
            }
        }

        if (u == -1) break;

        d.T[u] = TRUE;

        for (int v = 0; v < d.graph.N; v++)
        {
            if (!d.T[v] && d.graph.A[u][v] != VOCUNG 
                && (d.dist[u] + d.graph.A[u][v] <= d.dist[v]))
            {
                d.dist[v] = d.dist[u] + d.graph.A[u][v];
                d.truoc[v] = u;
            }
        }
    }
}

// Câu 5: Hàm main
int main()
{
    Dijkstra d;
    Nhap(d);
    HienThi(d);
    RunDijkstra(d);
    HienThiDuongDiNganNhat(d);

    for (int i = 0; i < d.graph.N; ++i) {
        delete[] d.graph.A[i];
    }
    delete[] d.graph.A;
    delete[] d.truoc;
    delete[] d.dist;
    delete[] d.T;

    return 0;
}