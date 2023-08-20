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
Description:
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

/*
Description:
    Main function.
Test Cases:
    1.
        Input:
            0
        Output:
            0
    2.
        Input:
            1
            743
        Output:
            743
    3. 
        Input:
            6
            5 1 2 10 6 2
        Output:
            17
    4. 
        Input:
            6
            7 3 9 10 8 6
        Output:
            24
    5.
        Input:
            7
            7 9 10 9 3 5 2
        Output:
            23
*/
int main() {
    int n;
    cin >> n;
    vector<int> coins(n);
    for (int i = 0; i < n; ++i)
        cin >> coins[i];
    cout << maxMoney(coins) << endl;
}
