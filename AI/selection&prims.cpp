#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

// Selection Sort
void selectionSort(vector<int>& a) {
    for (size_t i = 0; i + 1 < a.size(); ++i) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < a.size(); ++j)
            if (a[j] < a[minIdx])
                minIdx = j;
        swap(a[i], a[minIdx]);
    }
    cout << "\nSorted array: ";
    for (int x : a) cout << x << ' ';
    cout << "\n";
}

// Prim’s MST (adjacency‐matrix, 0 = no edge)
void primMST(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> key(n, numeric_limits<int>::max()), parent(n, -1);
    vector<bool> inMST(n, false);
    key[0] = 0;

    cout << "\nMST edges (u - v : w):\n";
    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int v = 0; v < n; ++v)
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        if (u < 0) {
            cout << "Graph not connected.\n";
            return;
        }
        inMST[u] = true;
        if (parent[u] != -1)
            cout << parent[u] << " - " << u
                 << " : " << g[parent[u]][u] << "\n";

        for (int v = 0; v < n; ++v) {
            int w = g[u][v];
            if (w > 0 && !inMST[v] && w < key[v]) {
                key[v]    = w;
                parent[v] = u;
            }
        }
    }
}

int main() {
    cout << "Choose operation:\n"
         << "  1) Selection Sort\n"
         << "  2) Prim's MST\n"
         << "Enter 1 or 2: ";
    int choice;
    if (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice.\n";
        return 1;
    }

    cout << "Enter n (number of elements or vertices): ";
    int n;
    if (!(cin >> n) || n <= 0) {
        cout << "n must be a positive integer.\n";
        return 1;
    }

    if (choice == 1) {
        vector<int> a(n);
        cout << "Enter " << n << " integers separated by spaces:\n";
        for (int &x : a)
            cin >> x;
        selectionSort(a);
    } 
    else {
        vector<vector<int>> g(n, vector<int>(n));
        cout << "Enter adjacency matrix (" << n << "x" << n << "):\n"
             << "(0 = no edge, positive weight otherwise)\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> g[i][j];
        primMST(g);
    }

    return 0;
}
