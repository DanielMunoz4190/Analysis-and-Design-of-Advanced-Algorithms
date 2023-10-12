/**
 * @file main.cpp
 * @author Carlos David Amezcua Canales A01641742
 * @author Juan Daniel Muñoz Dueñas A01641792
 * @brief Traveling Salesman Problem
 * @version 0.1
 * @date 12-10-2023
 * @copyright Copyright (c) 2023
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/*
Description:
    Data structure to represent a Disjoint Set Union (DSU) or Union-Find.
*/
struct DSU {
    vector<int> parent, size;

    /*
    Description:
        Constructor for the DSU. Initializes the parent of each element to itself and the size of each set to 1.
    Parameters:
        n - Number of elements.
    Complexity:
        Time: O(n)
        Space: O(n)
    */
    DSU(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    /*
    Description:
        Finds the representative of the set to which the element 'u' belongs.
    Parameters:
        u - The element whose set representative is to be found.
    Returns:
        The representative of the set to which 'u' belongs.
    Complexity:
        Time: O(α(n)) - Amortized time, where α(n) is the inverse Ackermann function.
        Space: O(1)
    */
    int find(int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }

    /*
    Description:
        Unites the sets containing elements 'u' and 'v'. If they are already in the same set, it does nothing.
    Parameters:
        u, v - The elements whose sets are to be united.
    Returns:
        True if the sets were united, false if they were already in the same set.
    Complexity:
        Time: O(α(n)) - Amortized time, where α(n) is the inverse Ackermann function.
        Space: O(1)
    */
    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u != v) {
            if (size[u] < size[v]) swap(u, v);
            size[u] += size[v];
            parent[v] = u;
            return true;
        }
        return false;
    }
};

/*
Description:
    Computes the minimum spanning tree of a graph using Kruskal's algorithm.
Parameters:
    n - Number of vertices.
    edges - List of edges represented as {weight, {vertex1, vertex2}}.
Returns:
    Weight of the minimum spanning tree.
Complexity:
    Time: O(m log m) - where m is the number of edges.
    Space: O(n + m)
*/
long long minimumSpanningTree(int n, vector<pair<int, pair<int, int>>> edges) {
    sort(edges.begin(), edges.end());
    DSU disjointSetUnion(n);
    long long ans = 0;
    for (auto i : edges) {
        int w, a, b;
        w = i.first;
        a = i.second.first;
        b = i.second.second;
        if (disjointSetUnion.unite(a, b)) {
            ans += w;
        }
    }
    return ans;
}

/*
    Test cases:

    input:
    4 5
    1 2 7
    1 4 6
    4 2 9
    4 3 8
    2 3 6

    output:
    19

    input:
    1 0

    output:
    0
    
    Input:
    5 0

    Output:
    0

    Input:
    4 3
    1 2 5
    2 3 6
    3 4 7

    Output:
    18

    Input:
    4 6
    1 2 5
    1 3 5
    1 4 5
    2 3 5
    2 4 5
    3 4 5
    
    Output:
    15

    Input:
    5 2
    1 2 3
    4 5 4

    Output:
    7

    Input:
    3 4
    1 2 2
    2 3 3
    3 1 4
    1 1 5

    Output:
    5

*/
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> edges(m);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({w, {a - 1, b - 1}});
    }
    cout << minimumSpanningTree(n, edges) << endl;

    return 0;
}