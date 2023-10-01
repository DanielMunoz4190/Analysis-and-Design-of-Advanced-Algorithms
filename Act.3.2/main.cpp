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

bool neq(ld a, ld b) {
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
bool le(ld a, ld b) {
    return b - a > eps<ld>;
}
/*
Description:
    Computes the shortest path from a source node to all other nodes in a graph using Dijkstra's algorithm.
Parameters:
    adjList - Adjacency list representation of the graph.
    source - Source node from which shortest paths are to be computed.
Returns:
    A vector containing the shortest path distances from the source to all other nodes.
Complexity:
    Time: O(|E| log|E|) - where V is the number of vertices and E is the number of edges.
*/

vector<ld> dijkstra(vector<vector<pair<int, ld>>> &adjList, int source) {
    int n = adjList.size();
    vector<ld> d(n, inf<ld>);
    d[source] = 0.0;
    priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<pair<ld, int>>> pq;
    pq.push({0.0, source});
    while (!pq.empty()) {
        int v = pq.top().second;
        ld distV = pq.top().first;
        pq.pop();
        if (neq(distV, d[v])) {
            continue;
        }
        for (auto edge : adjList[v]) {
            int to = edge.first;
            ld len = edge.second;
            if (le(d[v] + len, d[to])) {
                d[to] = d[v] + len;
                pq.push({d[to], to});
            }
        }
    }
    return d;
}
/*
Description:
    Computes the shortest paths between all pairs of nodes in a graph using the Floyd-Warshall algorithm.
Parameters:
    adjMatrix - Adjacency matrix representation of the graph.
Returns:
    A matrix containing the shortest path distances between all pairs of nodes.
Complexity:
    Time: O(V^3) - where V is the number of vertices.
    Space: O(V^2)
*/
vector<vector<ld>> floydWarshall(vector<vector<ld>> &adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<ld>> d = adjMatrix;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (le(d[i][k], inf<ld>) && le(d[k][j], inf<ld>) && le(d[i][k] + d[k][j], d[i][j])) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
    return d;
}
/*
Description:
    Main function that reads input for a graph, computes shortest paths using Dijkstra's and Floyd-Warshall algorithms,
and prints the results. Parameters: None. Returns: 0 on successful execution. Complexity: Time: Depends on the input
size and the algorithms used. Space: Depends on the input size.
*/

/*
    Test cases:
        1.
        Input:
            1 0
        Output:
            Dijkstra :

            Floyd :
                0

        2.
        Input:
            0 0
        Output:
            Dijkstra :

            Floyd :

        3.
        Input:
            4 2
            0 1 1
            2 3 2
        Output:
            Dijkstra :
            node 0 to node 1 : 1
            node 0 to node 2 : -1
            node 0 to node 3 : -1
            node 1 to node 0 : -1
            node 1 to node 2 : -1
            node 1 to node 3 : -1
            node 2 to node 0 : -1
            node 2 to node 1 : -1
            node 2 to node 3 : 2
            node 3 to node 0 : -1
            node 3 to node 1 : -1
            node 3 to node 2 : -1

            Floyd :
                0 1 -1 -1
                -1 0 -1 -1
                -1 -1 0 2
                -1 -1 -1 0

        4.
        Input:
            4 5
            0 1 2
            1 2 3
            2 3 1
            3 0 4
            0 2 5
        Dijkstra :
            node 0 to node 1 : 2
            node 0 to node 2 : 5
            node 0 to node 3 : 6
            node 1 to node 0 : 8
            node 1 to node 2 : 3
            node 1 to node 3 : 4
            node 2 to node 0 : 5
            node 2 to node 1 : 7
            node 2 to node 3 : 1
            node 3 to node 0 : 4
            node 3 to node 1 : 6
            node 3 to node 2 : 9
        Floyd :
            0 2 5 6
            8 0 3 4
            5 7 0 1
            4 6 9 0
*/
int main() {
    int v, e;
    cin >> v >> e;
    vector<vector<pair<int, ld>>> adjList(v);
    vector<vector<ld>> adjMatrix(v, vector<ld>(v, inf<ld>));
    for (int i = 0; i < v; ++i) {
        adjMatrix[i][i] = 0.0;
    }
    for (int i = 0; i < e; ++i) {
        int from, to;
        ld w;
        cin >> from >> to >> w;
        adjList[from].push_back({to, w});
        adjMatrix[from][to] = w;
    }
    cout << "Dijkstra :" << endl;
    for (int i = 0; i < v; ++i) {
        vector<ld> dist = dijkstra(adjList, i);
        for (int j = 0; j < v; ++j) {
            if (i != j) {
                cout << "node " << i << " to node " << j << " : " << (dist[j] == inf<ld> ? -1 : dist[j]) << endl;
            }
        }
    }
    cout << endl;
    vector<vector<ld>> dist = floydWarshall(adjMatrix);
    cout << "Floyd :" << endl;
    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
            cout << (dist[i][j] == inf<ld> ? -1 : dist[i][j]) << " ";
        }
        cout << endl;
    }

    return 0;
}
