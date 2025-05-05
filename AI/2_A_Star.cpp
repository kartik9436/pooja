#include <iostream>
#include <cmath>
#include <limits.h>

using namespace std;

int g = 0;

void Print(int puzzle[])
{
    cout << "State:";
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            cout << '\n';
        if (puzzle[i] == -1)
            cout << "_ ";
        else
            cout << puzzle[i] << " ";
    }
    cout << "\n\n";
}

void moveLeft(int start[], int position)
{
    swap(start[position], start[position - 1]);
}

void moveRight(int start[], int position)
{
    swap(start[position], start[position + 1]);
}

void moveUp(int start[], int position)
{
    swap(start[position], start[position - 3]);
}

void moveDown(int start[], int position)
{
    swap(start[position], start[position + 3]);
}

void Copy(int temp[], int real[])
{
    for (int i = 0; i < 9; i++)
        temp[i] = real[i];
}

int heuristic(int start[], int goal[])
{
    int h = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (start[i] == goal[j] && start[i] != -1)
            {
                h += abs((j - i) / 3) + abs((j - i) % 3);
            }
        }
    }
    return h + g;
}

void moveTile(int start[], int goal[])
{
    int emptyAt = 0;
    for (int i = 0; i < 9; i++)
    {
        if (start[i] == -1)
        {
            emptyAt = i;
            break;
        }
    }

    int t1[9], t2[9], t3[9], t4[9], f1 = INT_MAX, f2 = INT_MAX, f3 = INT_MAX, f4 = INT_MAX;
    Copy(t1, start);
    Copy(t2, start);
    Copy(t3, start);
    Copy(t4, start);

    int row = emptyAt / 3;
    int col = emptyAt % 3;

    if (col - 1 >= 0)
    {
        moveLeft(t1, emptyAt);
        f1 = heuristic(t1, goal);
    }

    if (col + 1 < 3)
    {
        moveRight(t2, emptyAt);
        f2 = heuristic(t2, goal);
    }

    if (row + 1 < 3)
    {
        moveDown(t3, emptyAt);
        f3 = heuristic(t3, goal);
    }

    if (row - 1 >= 0)
    {
        moveUp(t4, emptyAt);
        f4 = heuristic(t4, goal);
    }

    if (f1 <= f2 && f1 <= f3 && f1 <= f4)
    {
        moveLeft(start, emptyAt);
    }
    else if (f2 <= f1 && f2 <= f3 && f2 <= f4)
    {
        moveRight(start, emptyAt);
    }
    else if (f3 <= f1 && f3 <= f2 && f3 <= f4)
    {
        moveDown(start, emptyAt);
    }
    else
    {
        moveUp(start, emptyAt);
    }
}

void solveEight(int start[], int goal[])
{
    g++;
    moveTile(start, goal);
    Print(start);
    int f = heuristic(start, goal);
    if (f == g)
    {
        cout << "✅ Puzzle solved in " << f << " moves.\n";
        return;
    }
    solveEight(start, goal);
}

bool solvable(int start[])
{
    int invrs = 0;
    for (int i = 0; i < 9; i++)
    {
        if (start[i] <= 1)
            continue;
        for (int j = i + 1; j < 9; j++)
        {
            if (start[j] == -1)
                continue;
            if (start[i] > start[j])
                invrs++;
        }
    }
    return invrs % 2 == 0;
}

int main()
{
    int start[9], goal[9];
    cout << "8-Puzzle Solver using A* Algorithm\n";
    cout << "Instructions:\n";
    cout << "- Enter 9 values for the puzzle state.\n";
    cout << "- Use numbers 1 to 8 and -1 for the empty tile.\n";
    cout << "- Example input for start state: 1 2 3 -1 4 6 7 5 8\n\n";

    cout << "🔸 Enter the START state:\n";
    for (int i = 0; i < 9; i++)
    {
        cin >> start[i];
    }

    cout << "\n🔸 Enter the GOAL state:\n";
    for (int i = 0; i < 9; i++)
    {
        cin >> goal[i];
    }

    cout << "\nStart State:";
    Print(start);

    if (solvable(start))
    {
        solveEight(start, goal);
    }
    else
    {
        cout << "\n❌ This puzzle is impossible to solve.\n";
    }

    return 0;
}
// 🔸 Enter the START state:
// 1 2 3 -1 4 6 7 5 8

// 🔸 Enter the GOAL state:
// 1 2 3 4 5 6 7 8 -1
/*This C++ program solves the 8-puzzle problem using a simplified A* search algorithm with a Manhattan distance heuristic. The puzzle is represented as a 1D array where -1 denotes the empty tile. The solveEight function recursively moves the empty tile in the direction that results in the minimum heuristic value (estimated cost to reach the goal) until the goal state is reached. The heuristic function calculates the total Manhattan distance of all tiles from their goal positions. The solvable function checks if the initial state can be solved by counting tile inversions. If solvable, the puzzle is printed at each step as the algorithm progresses toward the solution.*/