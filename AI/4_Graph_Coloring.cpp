#include <iostream>
#include <vector>
using namespace std;

void addEdge(int graph[5][5], int edge1, int edge2)
{
    graph[edge1][edge2] = 1;
    graph[edge2][edge1] = 1;
}

bool safeToAssign(int i, int colorToAssign, int graph[5][5], int v, const vector<int>& color)
{
    for (int k = 0; k < v; k++)
    {
        if (graph[i][k] == 1 && color[k] == colorToAssign)
        {
            return false;
        }
    }
    return true;
}

bool assignColors(int graph[5][5], int m, int v, int i, vector<int>& color)
{
    if (i == v)
    {
        // All vertices assigned
        return true;
    }

    for (int j = 1; j <= m; j++) // use colors 1 to m
    {
        if (safeToAssign(i, j, graph, v, color))
        {
            color[i] = j;
            if (assignColors(graph, m, v, i + 1, color))
                return true;
            color[i] = 0; // backtrack
        }
    }
    return false;
}

bool graphColoring(int graph[5][5], int m, int v)
{
    vector<int> color(v, 0); // initialized with 0 (no color)
    if (assignColors(graph, m, v, 0, color))
    {
        cout << "Coloring possible with " << m << " colors:\n";
        for (int i = 0; i < v; i++)
        {
            cout << "Vertex " << i << " ---> Color " << color[i] << "\n";
        }
        return true;
    }
    else
    {
        cout << "Coloring NOT possible with " << m << " colors.\n";
        return false;
    }
}

int main()
{
    int m = 3; // number of colors
    int v = 5; // number of vertices
    int graph[5][5] = {0};

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 2, 4);
    // Edge to vertex 5 removed because only 0–4 are valid
    addEdge(graph, 3, 4); // Use valid vertex

    graphColoring(graph, m, v);

    return 0;
}
