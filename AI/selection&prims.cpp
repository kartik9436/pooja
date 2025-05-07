#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>    // for std::swap

using namespace std;

// Selection Sort
void selectionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i + 1 < n; ++i) {
        int m = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[m]) 
                m = j;
        }
        swap(a[i], a[m]);
    }

    cout << "\nSorted array:\n";
    for (int x : a)
        cout << x << ' ';
    cout << "\n";
}

// Prim’s MST (array-based)
void primMST(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> key(n, numeric_limits<int>::max()), parent(n, -1);
    vector<bool> inMST(n, false);
    key[0] = 0;

    cout << "\nMST edges (u - v : weight):\n";
    for (int i = 0; i < n; ++i) {
        // pick the unused vertex with smallest key
        int u = -1;
        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }
        if (u == -1) {
            cerr << "Error: Graph not fully connected.\n";
            return;
        }

        inMST[u] = true;
        if (parent[u] != -1) {
            cout << parent[u] << " - " << u
                 << " : " << g[parent[u]][u] << "\n";
        }

        // update neighbors
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char choice;
    cout << "Choose operation:\n"
         << "  s) Selection Sort\n"
         << "  p) Prim's MST\n"
         << "Enter choice (s/p): ";
    if (!(cin >> choice)) {
        cerr << "Invalid input.\n";
        return 1;
    }

    int n;
    cout << "Enter n (number of elements or vertices): ";
    if (!(cin >> n) || n <= 0) {
        cerr << "n must be a positive integer.\n";
        return 1;
    }

    if (choice == 's' || choice == 'S') {
        vector<int> a(n);
        cout << "Enter " << n << " integer values:\n";
        for (int i = 0; i < n; ++i) {
            if (!(cin >> a[i])) {
                cerr << "Invalid number at position " << i << ".\n";
                return 1;
            }
        }
        selectionSort(a);
    }
    else if (choice == 'p' || choice == 'P') {
        vector<vector<int>> g(n, vector<int>(n));
        cout << "Enter adjacency matrix (" << n << " x " << n << "),\n"
             << "use 0 for no edge, positive weights otherwise:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!(cin >> g[i][j]) || g[i][j] < 0) {
                    cerr << "Invalid weight at [" << i << "][" << j << "].\n";
                    return 1;
                }
            }
        }
        primMST(g);
    }
    else {
        cerr << "Unknown choice: " << choice << "\n";
        return 1;
    }

    return 0;
}
