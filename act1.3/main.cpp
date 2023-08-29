/**
 * @file main.cpp
 * @author Juan Daniel Muñoz Dueñas A01641792
 * @author Carlos David Amezcua Canales A01641742
 * @version 0.1
 * @date 2023-08-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;

const vector<int> DR = {1, 0, -1, 0};
const vector<int> DC = {0, 1, 0, -1};

/*
Description:
    Function to check if a cell is visitable.
Complexity, where n is the number of rows and m is the number of columns:
    Time: O(1)
    Space: O(1)
*/
bool isVisitable(int n, int m, vector<vector<bool>> &maze, int row, int col)
{
    return 0 <= row && row < n && 0 <= col && col < m && maze[row][col];
}

/*
Description:
    Recursive function to explore the maze using backtracking.
Complexity, where n is the number of rows and m is the number of columns:
    Time: O(3^(n*m))
    Space: O(n*m))
*/
bool exploreMaze(int n, int m, vector<vector<bool>> &maze, vector<vector<bool>> &isVisited, int row, int col)
{
    isVisited[row][col] = true;
    if (row == n - 1 && col == m - 1)
        return true;
    bool canReachEnd = false;
    for (int i = 0; i < 4; ++i)
    {
        if (!canReachEnd)
        {
            int newRow = row + DR[i];
            int newCol = col + DC[i];
            if (isVisitable(n, m, maze, newRow, newCol) && !isVisited[newRow][newCol])
                canReachEnd |= exploreMaze(n, m, maze, isVisited, newRow, newCol);
        }
    }
    if (!canReachEnd)
        isVisited[row][col] = false;
    return canReachEnd;
}

/*
Description:
    Function to solve the maze using backtracking.
Complexity, where n is the number of rows and m is the number of columns:
    Time: O(3^(n*m))
    Space: O(n*m)
*/
vector<vector<bool>> solveMazeWithBacktracking(vector<vector<bool>> &maze)
{
    int n = maze.size();
    int m = maze[0].size();
    vector<vector<bool>> path(n, vector<bool>(m, false));
    exploreMaze(n, m, maze, path, 0, 0);
    return path;
}

/*
Description:
    Function to solve the maze using branch and bound.
Complexity, where n is the number of rows and m is the number of columns:
    Time: O(n*m)
    Space: O(n*m)
*/

vector<vector<bool>> solveMazeWithBranchAndBound(vector<vector<bool>> &maze)
{
    int n = maze.size();
    int m = maze[0].size();
    vector<vector<int>> distance(n, vector<int>(m, inf<int>));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    queue<pair<int, int>> q;
    q.push({0, 0});
    distance[0][0] = 0;
    while (!q.empty())
    {
        auto [row, col] = q.front();
        q.pop();
        if (row == n - 1 && col == m - 1)
            while (!q.empty())
                q.pop();
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                int newRow = row + DR[i];
                int newCol = col + DC[i];
                if (isVisitable(n, m, maze, newRow, newCol) && distance[row][col] + 1 < distance[newRow][newCol])
                {
                    distance[newRow][newCol] = distance[row][col] + 1;
                    parent[newRow][newCol] = {row, col};
                    q.push({newRow, newCol});
                }
            }
        }
    }
    vector<vector<bool>> path(n, vector<bool>(m, false));
    if (distance[n - 1][m - 1] != inf<int>)
    {
        int row = n - 1;
        int col = m - 1;
        while (row != -1 && col != -1)
        {
            path[row][col] = true;
            auto [newRow, newCol] = parent[row][col];
            row = newRow;
            col = newCol;
        }
    }
    return path;
}

/*
Description:
    Main function.
Test Cases:
    1.
        Input:
            5 5
            1 0 1 1 1
            1 1 1 0 1
            0 1 1 0 1
            1 0 1 1 1
            1 1 1 1 1
        Output:
            1 0 0 0 0 
            1 1 1 0 0 
            0 0 1 0 0 
            0 0 1 1 1 
            0 0 0 0 1 
            ...
            1 0 0 0 0 
            1 1 1 0 0 
            0 0 1 0 0 
            0 0 1 1 1 
            0 0 0 0 1 
    2.
        Input:
            5 6
            1 1 1 1 1 1
            1 1 1 1 1 1
            1 1 1 1 1 1
            1 1 1 1 1 1
            1 1 1 1 1 1
        Output:
            1 0 0 0 0 0 
            1 0 0 0 0 0 
            1 0 0 0 0 0 
            1 0 0 0 0 0 
            1 1 1 1 1 1 

            1 0 0 0 0 0 
            1 0 0 0 0 0 
            1 0 0 0 0 0 
            1 0 0 0 0 0 
            1 1 1 1 1 1 
    3.
        Input:
            5 5
            1 0 1 1 1
            1 1 1 0 1
            0 0 0 0 0 
            0 0 0 0 0
            1 1 1 1 1
        Output:
            0 0 0 0 0 
            0 0 0 0 0 
            0 0 0 0 0 
            0 0 0 0 0 
            0 0 0 0 0 

            0 0 0 0 0 
            0 0 0 0 0 
            0 0 0 0 0 
            0 0 0 0 0 
            0 0 0 0 0 
    4. 
        Input:
            5 6
            1 1 1 1 1 1
            1 1 1 0 0 1
            1 0 1 1 1 1
            1 0 1 0 1 1
            1 1 1 1 0 1
        Output:
            1 0 0 0 0 0 
            1 0 0 0 0 0 
            1 0 1 1 1 0 
            1 0 1 0 1 1 
            1 1 1 0 0 1 

            1 0 0 0 0 0 
            1 1 1 0 0 0 
            0 0 1 1 1 0 
            0 0 0 0 1 1 
            0 0 0 0 0 1 
            
*/
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> maze(n, vector<bool>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            char aux;
            cin >> aux;
            maze[i][j] = aux == '1';
        }
    }
    vector<vector<bool>> path = solveMazeWithBacktracking(maze);
    for (auto row : path)
    {
        for (auto cell : row)
            cout << cell << " ";
        cout << endl;
    }
    cout << endl;
    path = solveMazeWithBranchAndBound(maze);
    for (auto row : path)
    {
        for (auto cell : row)
            cout << cell << " ";
        cout << endl;
    }

    return 0;
}
