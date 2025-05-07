#include <iostream>
#include <limits>
#include <algorithm> // for std::swap
using namespace std;

// Selection Sort on a plain array
void selectionSort(int a[], int n) {
    for (int i = 0; i + 1 < n; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[minIdx])
                minIdx = j;
        }
        swap(a[i], a[minIdx]);
    }
    cout << "\nSorted array: ";
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << "\n";
}

// Prim’s MST using a flat adjacency matrix (0 = no edge)
void primMST(int *g, int n) {
    int *key    = new int[n];
    int *parent = new int[n];
    bool *inMST = new bool[n];

    for (int i = 0; i < n; ++i) {
        key[i]    = numeric_limits<int>::max();
        parent[i] = -1;
        inMST[i]  = false;
    }
    key[0] = 0;

    cout << "\nMST edges (u - v : w):\n";
    for (int count = 0; count < n; ++count) {
        // pick the unused vertex u with smallest key[u]
        int u = -1;
        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }
        if (u < 0) {
            cout << "Graph not connected.\n";
            delete[] key; delete[] parent; delete[] inMST;
            return;
        }
        inMST[u] = true;

        if (parent[u] != -1) {
            int w = g[parent[u] * n + u];
            cout << parent[u] << " - " << u << " : " << w << "\n";
        }

        // relax edges from u
        for (int v = 0; v < n; ++v) {
            int w = g[u * n + v];
            if (w > 0 && !inMST[v] && w < key[v]) {
                key[v]    = w;
                parent[v] = u;
            }
        }
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;
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
        int *a = new int[n];
        cout << "Enter " << n << " integers separated by spaces:\n";
        for (int i = 0; i < n; ++i)
            cin >> a[i];

        selectionSort(a, n);
        delete[] a;
    }
    else {
        int *g = new int[n * n];
        cout << "Enter adjacency matrix (" << n << "x" << n << "):\n"
             << "(0 = no edge, positive weight otherwise)\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> g[i * n + j];

        primMST(g, n);
        delete[] g;
    }

    return 0;
}
