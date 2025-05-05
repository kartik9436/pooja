#include <bits/stdc++.h>
using namespace std;

class DSU
{
	int *parent;
	int *rank;

public:
	DSU(int n)
	{
		parent = new int[n];
		rank = new int[n];

		for (int i = 0; i < n; i++)
		{
			parent[i] = -1;
			rank[i] = 1;
		}
	}

	// Find function
	int find(int i)
	{
		if (parent[i] == -1)
			return i;

		return parent[i] = find(parent[i]);
	}
	// union function
	void unite(int x, int y)
	{
		int s1 = find(x);
		int s2 = find(y);

		if (s1 != s2)
		{
			if (rank[s1] < rank[s2])
			{
				parent[s1] = s2;
				rank[s2] += rank[s1];
			}
			else
			{
				parent[s2] = s1;
				rank[s1] += rank[s2];
			}
		}
	}
};

class Graph
{
	vector<vector<int>> edgelist;
	int V;

public:
	Graph(int V) { this->V = V; }

	void addEdge(int x, int y, int w)
	{
		edgelist.push_back({w, x, y});
	}

	void kruskals_mst()
	{
		// 1. Sort all edges
		sort(edgelist.begin(), edgelist.end());

		// Initialize the DSU
		DSU s(V);
		int ans = 0;
		cout << "Following are the edges in the "
				"constructed MST"
			 << endl;
		for (auto edge : edgelist)
		{
			int w = edge[0];
			int x = edge[1];
			int y = edge[2];

			// take that edge in MST if it does form a cycle
			if (s.find(x) != s.find(y))
			{
				s.unite(x, y);
				ans += w;
				cout << x << " -- " << y << " == " << w
					 << endl;
			}
		}
		cout << "Minimum Cost Spanning Tree: " << ans << endl;
	}
};
int main()
{

	Graph g(4);
	g.addEdge(0, 1, 10);
	g.addEdge(1, 3, 15);
	g.addEdge(2, 3, 4);
	g.addEdge(2, 0, 6);
	g.addEdge(0, 3, 5);

	int n, m;
	cin >> n >> m;

	Graph g(n);
	for (int i = 0; i < m; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		g.addEdge(x, y, w);
	}

	g.kruskals_mst();
	return 0;
}

/*This C++ code implements Kruskal’s Algorithm to find the Minimum Spanning Tree (MST) of a weighted undirected graph using the Disjoint Set Union (DSU) data structure. The DSU class manages connected components to prevent cycles when adding edges. The Graph class stores all edges with their weights and runs Kruskal’s algorithm by first sorting all edges by weight and then selecting the smallest edge that connects two different components (using DSU's find and unite methods). The final MST is printed along with its total weight. In main(), the user inputs the number of vertices (n) and edges (m), followed by m lines of edge data. Note: the initial calls to g.addEdge() before user input are redundant and should be removed for clarity.

How to give input in terminal (after running the program):

5 6
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4
1 2 8
Here, 5 is the number of vertices, 6 is the number of edges, and each line after that represents an edge in the format: source destination weight */