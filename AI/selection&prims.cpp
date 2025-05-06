#include <iostream>
#include <vector>
#include <limits> // for numeric_limits

using namespace std;

// Selection Sort: pick the smallest from the unsorted tail and swap it forward
void selectionSort(vector<int> &a)
{
    int n = a.size();
    for (int i = 0; i + 1 < n; ++i)
    {
        int m = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j] < a[m])
                m = j;
        swap(a[i], a[m]);
    }
    cout << "\nSorted array:\n";
    for (int x : a)
        cout << x << ' ';
    cout << "\n";
}

// Prim’s MST (array‐based): track best edge weights in key[], pick min by scan
void primMST(const vector<vector<int>> &g)
{
    int n = g.size();
    vector<int> key(n, numeric_limits<int>::max()), parent(n, -1);
    vector<bool> used(n, false);
    key[0] = 0; // start from vertex 0

    cout << "\nMST edges (u - v : weight):\n";
    for (int i = 0; i < n; ++i)
    {
        // find unused vertex u with smallest key[u]
        int u = -1;
        for (int j = 0; j < n; ++j)
            if (!used[j] && (u == -1 || key[j] < key[u]))
                u = j;
        used[u] = true;

        if (parent[u] != -1)
            cout << parent[u] << " - " << u
                 << " : " << g[parent[u]][u] << "\n";

        // relax all edges from u
        for (int v = 0; v < n; ++v)
        {
            int w = g[u][v];
            if (w > 0 && !used[v] && w < key[v])
            {
                key[v] = w;
                parent[v] = u;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char choice;
    cout << "Choose (s=Selection Sort, p=Prim's MST): ";
    cin >> choice;

    int n;
    cout << "Enter n (#elements or #vertices): ";
    cin >> n;

    if (choice == 's' || choice == 'S')
    {
        vector<int> a(n);
        cout << "Enter " << n << " numbers:\n";
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        selectionSort(a);
    }
    else if (choice == 'p' || choice == 'P')
    {
        vector<vector<int>> g(n, vector<int>(n));
        cout << "Enter " << n << "x" << n << " adjacency matrix (0=no edge):\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> g[i][j];
        primMST(g);
    }
    else
    {
        cout << "Invalid choice.\n";
    }

    return 0;
}
