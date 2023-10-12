
/**
 * @file main.cpp
 * @author Carlos David Amezcua Canales A01641742
 * @author Juan Daniel Muñoz Dueñas A01641792
 * @brief Traveling Salesman Problem
 * @version 0.1
 * @date 09-09-2023
 */
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef long long lli;
typedef pair<lli, lli> ii;
typedef vector<lli> vi;

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;

/*
Description:
    Function to calculate the approximate shortest path for the Traveling Salesman Problem.
    It utilizes a greedy approach, always selecting the nearest unvisited vertex.
Parameters:
    verticesPositions: vector containing positions (coordinates) of each vertex.
Return:
    Approximate minimal total distance required to visit each vertex exactly once and return to the starting vertex.
Complexity, where n is the number of vertices:
    Time: O(n ^ 2) due to nested loops in which the nearest unvisited vertex is determined.
    Space: O(n) mainly because of the visited array and the input vertices' positions.
*/

ld travelingSalesmanProblem(vector<ii> &verticesPositions) {
    lli n = verticesPositions.size();
    vector<bool> visited(n, false);
    ld ans = 0.0;
    lli u = 0;
    visited[u] = true;
    for (lli i = 0; i < n - 1; ++i) {
        lli v = -1;
        lli minSquareDistance = inf<lli>;
        for (lli j = 0; j < n; ++j) {
            if (!visited[j]) {
                lli dx = verticesPositions[u].first - verticesPositions[j].first;
                lli dy = verticesPositions[u].second - verticesPositions[j].second;
                lli squareDistance = dx * dx + dy * dy;
                if (squareDistance < minSquareDistance) {
                    minSquareDistance = squareDistance;
                    v = j;
                }
            }
        }
        u = v;
        visited[u] = true;
        ans += sqrt(minSquareDistance);
    }
    lli dx = verticesPositions[u].first - verticesPositions[0].first;
    lli dy = verticesPositions[u].second - verticesPositions[0].second;
    ans += sqrt(dx * dx + dy * dy);
    return ans;
}
/*
Description:
    Entry point of the program. Reads input vertex coordinates, calls the travelingSalesmanProblem function to calculate
    the approximate distance, and then outputs the result.
Parameters:
    None.
Return:
    Int value indicating program's success or failure (standard for main functions).
Complexity:
    Time: O(n^2) as it internally calls the travelingSalesmanProblem function.
    Space: O(n) for storing the vertex positions.
*/

/*
input:
3
1 0 0
2 1 0
3 0 1

output:
3.4142135624
*/

/*
input:
1
1 0 0

output:
0.0
*/

/*
input:
2
1 0 0
2 1 0

output:
2.0000000000
*/

/*
input:
4
1 0 0
2 1 0
3 1 1
4 0 1

output:
4.0000000000
*/

/*
input:
5
1 0 0
2 5 0
3 5 5
4 0 5
5 2.5 2.5

output:
20.0000000000
*/

int main() {
    lli n;
    cin >> n;
    lli index, x, y;
    vector<ii> vericesPositions;
    while (cin >> index >> x >> y) {
        vericesPositions.push_back({x, y});
    }
    cout << fixed << setprecision(10) << travelingSalesmanProblem(vericesPositions) << endl;

    return 0;
}
