#include <iostream>
#include <vector>
using namespace std;

void addEdge(int graph[5][5], int edge1, int edge2)
{
    for (int i = 0; i < 5; i++)
    {
        graph[edge1][edge2] = 1;
        graph[edge2][edge1] = 1;
    }
}

bool safeToAssign(int i, int j, int graph[5][5], int v, vector<int> color)
{
    for (int k = 0; k < v; k++)
    {
        if (graph[i][k] == 1 && color[k] == j)
        {
            return false;
        }
    }
    return true;
}

bool function(int graph[5][5], int m, int v, int i, vector<int> color)
{
    if (i == v)
    {
        return true;
    }
    for (int j = 0; j < m; j++)
    {
        if (safeToAssign(i, j, graph, v, color))
        {
            color[i] = j;
            if (function(graph, m, v, i + 1, color))
                return true;
            color[i] = -1;
        }
    }
    return false;
}

bool graphColoring(int graph[5][5], int m, int v)
{

    vector<int> color = {v, -1};
    int i = 0;
    return function(graph, m, v, i, color);
}

int main()
{
    int m = 3; // no. of colors
    int v = 5; // no. of vertices
    int graph[v][v] = {0};

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 3, 5);

    graphColoring(graph, m, v);
}
/*This C++ code solves the Graph Coloring Problem using backtracking, where the goal is to assign colors to graph vertices such that no two adjacent vertices share the same color, using at most m colors. The graph is represented using an adjacency matrix, and the function safeToAssign() ensures a color can be safely given to a vertex. The recursive function function() tries assigning each color to vertices one by one and backtracks if a conflict arises. The graphColoring() function initializes the color list and starts the coloring process. However, there are bugs: the addEdge() function unnecessarily loops, the color vector is incorrectly initialized, and some vertex indices are out of bounds (e.g., vertex 5 in a 5-vertex graph). Fixing these issues will make the code functional for checking if valid coloring exists for the given graph.*/