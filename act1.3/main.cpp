/**
 * @file main.cpp
 * @author Juan Daniel Muñoz Dueñas A01641792 / Carlos David Amezcua Canalez A01641742
 * @brief
 * @version 0.1
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Cell {
    int x, y;
    Cell(int _x, int _y) : x(_x), y(_y) {}
};

bool isSafe(const vector<vector<int>>& maze, int x, int y, const vector<vector<bool>>& visited) {
    int M = maze.size();
    int N = maze[0].size();
    return (x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 1 && !visited[x][y]);
}

bool solveMaze(const vector<vector<int>>& maze) {
    int M = maze.size();
    int N = maze[0].size();

    vector<vector<bool>> visited(M, vector<bool>(N, false));
    stack<Cell> s;
    s.push(Cell(0, 0));

    while (!s.empty()) {
        Cell cell = s.top();
        s.pop();

        int x = cell.x;
        int y = cell.y;

        if (x == M - 1 && y == N - 1) {
            visited[x][y] = true;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    cout << visited[i][j] << " ";
                }
                cout << endl;
            }
            return true;
        }

        if (isSafe(maze, x, y, visited)) {
            visited[x][y] = true;

            if (isSafe(maze, x - 1, y, visited)) {
                s.push(Cell(x - 1, y));
            }
            if (isSafe(maze, x + 1, y, visited)) {
                s.push(Cell(x + 1, y));
            }
            if (isSafe(maze, x, y - 1, visited)) {
                s.push(Cell(x, y - 1));
            }
            if (isSafe(maze, x, y + 1, visited)) {
                s.push(Cell(x, y + 1));
            }
        }
    }

    cout << "No hay solución" << endl;
    return false;
}

int main() {
    int M, N;
    cin >> M >> N;

    vector<vector<int>> maze(M, vector<int>(N));

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
        }
    }

    solveMaze(maze);

    return 0;
}


