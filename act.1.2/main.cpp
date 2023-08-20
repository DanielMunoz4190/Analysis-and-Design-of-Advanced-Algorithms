/**
 * @file main.cpp
 * @author Juan Daniel Muñoz Dueñas A01641792 / Carlos David Amezcua Canalez A01641742
 * @brief
 * @version 0.1
 * @date 2023-08-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Function to find the maximum money that can be grabbed of a row of coins without
grabbing adjacent coins.
Complexity, where n is the number of coins:
    Time: O(n)
    Space: O(1)
*/
int maxMoney(vector<int> &coins) {
    const int N = 2; // Recurrence relation degree
    vector<int> dp(N + 1, 0);
    for (int i = 0; i < coins.size(); ++i) {
        rotate(dp.begin(), dp.begin() + 1, dp.end());
        dp[N] = max(dp[N - 2] + coins[i], dp[N - 1]);
    }
    return dp[N];
}

int main() {
    // We have 4 test cases
    // The fist is an empty row
    // The second is a row with the following coins: 5, 1, 2, 10, 6, 2
    // The third is a row with the following coins: 7, 3, 9, 10, 8, 6
    // The fourth is a row with the following coins: 7, 9, 10, 9, 3, 5, 2
    int cases = 4;
    for (int i = 0; i < cases; i++) {
        int n;
        cin >> n;
        vector<int> coins(n);
        for (int j = 0; j < n; j++) {
            cin >> coins[j];
        }
        cout << maxMoney(coins) << endl;
    }
}
