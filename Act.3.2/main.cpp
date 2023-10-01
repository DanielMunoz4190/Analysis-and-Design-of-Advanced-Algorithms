/**
 * @file main.cpp
 * @author Carlos David Amezcua Canales A01641742
 * @author Juan Daniel Muñoz Dueñas A01641792
 * @version 0.1
 * @date 2023-09-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <limits>
#include <queue>
#include <vector>


using namespace std;

typedef long double ld;

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;

template <typename T>
static constexpr T eps = numeric_limits<T>::epsilon();

/*
Description:
    Checks if two long double values are not approximately equal.
Parameters:
    a - First long double value.
    b - Second long double value.
Returns:
    True if the values are not approximately equal, false otherwise.
Complexity:
    Time: O(1)
    Space: O(1)
*/

bool neq(ld a, ld b)
{
    return abs(a - b) > eps<ld>;
}
/*
Description:
    Checks if the first long double value is less than the second long double value.
Parameters:
    a - First long double value.
    b - Second long double value.
Returns:
    True if the first value is less than the second value, false otherwise.
Complexity:
    Time: O(1)
    Space: O(1)
*/
bool le(ld a, ld b)
{
    return b - a > eps<ld>;
}

vector<ld> dijkstra(vector<vector<pair<int, ld>>> &adjList, int source)
{
    int n = adjList.size();
    vector<ld> d(n, inf<ld>);
    d[source] = 0.0;
    priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<pair<ld, int>>> pq;
    pq.push({0.0, source});
    while (!pq.empty())
    {
        int v = pq.top().second;
        ld distV = pq.top().first;
        pq.pop();
        if (neq(distV, d[v]))
        {
            continue;
        }
        for (auto edge : adjList[v])
        {
            int to = edge.first;
            ld len = edge.second;
            if (le(d[v] + len, d[to]))
            {
                d[to] = d[v] + len;
                pq.push({d[to], to});
            }
        }
    }
    return d;
}

vector<vector<ld>> floydWarshall(vector<vector<ld>> &adjMatrix)
{
    int n = adjMatrix.size();
    vector<vector<ld>> d = adjMatrix;
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (le(d[i][k], inf<ld>) && le(d[k][j], inf<ld>) && le(d[i][k] + d[k][j], d[i][j]))
                {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
    return d;
}

int main()
{
    int v, e;
    cin >> v >> e;
    vector<vector<pair<int, ld>>> adjList(v);
    vector<vector<ld>> adjMatrix(v, vector<ld>(v, inf<ld>));
    for (int i = 0; i < e; ++i)
    {
        int from, to;
        ld w;
        cin >> from >> to >> w;
        adjList[from].push_back({to, w});
        adjMatrix[from][to] = w;
    }
    cout << "Dijkstra :" << endl;
    for (int i = 0; i < v; ++i)
    {
        vector<ld> dist = dijkstra(adjList, i);
        for (int j = 0; j < v; ++j)
        {
            if (i != j)
            {
                cout << "node " << i << " to node " << j << " : " << (dist[j] == inf<ld> ? -1 : dist[j]) << endl;
            }
        }
    }
    cout << endl;
    vector<vector<ld>> dist = floydWarshall(adjMatrix);
    cout << "Floyd :" << endl;
    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
        {
            cout << (dist[i][j] == inf<ld> ? -1 : dist[i][j]) << " ";
        }
        cout << endl;
    }

    return 0;
}
