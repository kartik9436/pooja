#include <iostream>
#include <list>
#include <map>
#include <queue>

using namespace std;

class Graph
{
public:
    map<int, list<int>> adjList;
    map<int, bool> visited;
    queue<int> q;

    void addEdge(int src, int dest)
    {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // Since it's undirected
    }

    void DFS(int node)
    {
        visited[node] = true;
        cout << node << " ";
        for (int i : adjList[node])
        {
            if (!visited[i])
                DFS(i);
        }
    }

    void BFS()
    {
        if (q.empty())
            return;

        int node = q.front();
        q.pop();
        cout << node << " ";
        for (int i : adjList[node])
        {
            if (!visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
        BFS();
    }
};

int main()
{
    Graph g;
    int n, e;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter " << e << " edges (u v):\n";
    for (int i = 0; i < e; ++i)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int ch, start;
    cout << "Enter 0 for DFS or 1 for BFS: ";
    cin >> ch;
    cout << "Enter starting node: ";
    cin >> start;

    if (ch == 0)
    {
        cout << "DFS on the graph: ";
        g.DFS(start);
    }
    else
    {
        g.q.push(start);
        g.visited[start] = true;
        cout << "BFS on the graph: ";
        g.BFS();
    }

    return 0;
}

// 7          ← number of nodes
// 7          ← number of edges
// 0 1        ← edge 1 (node 0 connected to node 1)
// 0 2        ← edge 2
// 0 3        ← edge 3
// 1 3        ← edge 4
// 3 4        ← edge 5
// 4 5        ← edge 6
// 2 6        ← edge 7
// 0          ← 0 for DFS, 1 for BFS
// 0          ← starting node for traversal
