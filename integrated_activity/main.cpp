/**
 * @file main.cpp
 * @author Carlos David Amezcua Canales A01641742
 * @author Juan Daniel Muñoz Dueñas A01641792
 * @author Diego Curiel Castellanos A01640372
 * @brief
 * @author Diego Curiel Castellanos A01640372
 * @brief
 * @version 0.1
 * @date 09-09-2023
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;


/*
Description:
    Reads the content of a file and returns it as a string.
Parameters:
    fileName - Name of the file to be read.
Returns:
    Content of the file as a string.
Complexity:
    Time: O(n) - where n is the number of characters in the file.
    Space: O(n)
*/

string readFile(const string &fileName) {
    ifstream archivo(fileName);

    if (!archivo.is_open()) throw runtime_error("Error opening file " + fileName);
    if (!archivo.is_open()) throw runtime_error("Error opening file " + fileName);

    stringstream buffer;
    buffer << archivo.rdbuf();
    archivo.close();

    return buffer.str();
}

/*
Description:
    Sorts characters in a string based on their ranks.
Parameters:
    sa - Suffix array.
    r  - Rank array.
    k  - Offset for ranking.
Complexity:
    Time: O(n) - where n is the length of the string.
    Space: O(n)
*/

#define RB(x) (x < n ? r[x] : 0)
void csort(vector<int> &sa, vector<int> &r, int k) {
    int n = sa.size();
    vector<int> f(max(255, n), 0), t(n);
    for (int i = 0; i < n; ++i) f[RB(i + k)]++;
    int sum = 0;
    for (int i = 0; i < max(255, n); ++i) f[i] = (sum += f[i]) - f[i];
    for (int i = 0; i < n; ++i) t[f[RB(sa[i] + k)]++] = sa[i];
    sa = t;
}
/*
Description:
    Constructs the suffix array of a string.
Parameters:
    s - Input string.
Returns:
    Suffix array of the string.
Complexity:
    Time: O(n log n) - where n is the length of the string.
    Space: O(n)
*/
vector<int> constructSA(string &s) {
    int n = s.size(), rank;
    vector<int> sa(n), r(n), t(n);
    for (int i = 0; i < n; ++i) sa[i] = i, r[i] = s[i];
    for (int k = 1; k < n; k *= 2) {
        csort(sa, r, k);
        csort(sa, r, 0);
        t[sa[0]] = rank = 0;
        for (int i = 1; i < n; ++i) {
            if (r[sa[i]] != r[sa[i - 1]] || RB(sa[i] + k) != RB(sa[i - 1] + k)) rank++;
            t[sa[i]] = rank;
        }
        r = t;
        if (r[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

/*
Description:
    Computes the Longest Common Prefix (LCP) array.
Parameters:
    s  - Input string.
    sa - Suffix array.
Returns:
    LCP array.
Complexity:
    Time: O(n) - where n is the length of the string.
    Space: O(n)
*/

vector<int> computeLCP(string &s, vector<int> &sa) {
    int n = (int)s.size(), L = 0;
    vector<int> lcp(n), plcp(n), phi(n);
    phi[sa[0]] = -1;
    for (int i = 1; i < n; ++i) phi[sa[i]] = sa[i - 1];
    for (int i = 0; i < n; ++i) {
        if (phi[i] < 0) {
            plcp[i] = 0;
            continue;
        }
        while (s[i + L] == s[phi[i] + L]) L++;
        plcp[i] = L;
        L = max(L - 1, 0);
    }
    for (int i = 0; i < n; ++i) lcp[i] = plcp[sa[i]];
    return lcp;
}

const int MAXN = 1e6;
int d1[MAXN];
int d2[MAXN];
/*
Description:
    Implements Manacher's algorithm to find the longest palindromic substring.
Parameters:
    s - Input string.
Complexity:
    Time: O(n) - where n is the length of the string.
    Space: O(n)
*/
void manacher(string &s) {
    int l = 0, r = -1, n = s.size();
    for (int i = 0; i < n; ++i) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i);
        while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    l = 0;
    r = -1;
    for (int i = 0; i < n; ++i) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
        k++;
        while (i + k <= n && i - k >= 0 && s[i + k - 1] == s[i - k]) k++;
        d2[i] = --k;
        if (i + k - 1 > r) l = i - k, r = i + k - 1;
    }
}

/*
Description:
    Finds the largest palindrome in a string.
Returns:
    Pair of indices representing the start and end of the palindrome.
Complexity:
    Time: O(n) - where n is the length of the string.
    Space: O(1)
*/

pair<int, int> findLargestPalindrome() {
    int n = MAXN;
    int maxLenOdd = 0;
    int centerOdd = 0;

    for (int i = 0; i < n; ++i) {
        if (d1[i] > maxLenOdd) {
            maxLenOdd = d1[i];
            centerOdd = i;
        }
    }

    int maxLenEven = 0;
    int centerEven = 0;
    for (int i = 0; i < n; ++i) {
        if (d2[i] > maxLenEven) {
            maxLenEven = d2[i];
            centerEven = i;
        }
    }

    if (maxLenOdd > maxLenEven) {
        int start = centerOdd - maxLenOdd + 1;
        int end = centerOdd + maxLenOdd;
        return {start, end};
    } else {
        int start = centerEven - maxLenEven + 1;
        int end = centerEven + maxLenEven;
        return {start, end};
    }
}

int main() {
    vector<string> transmissions(2), maliciousCodes(3);
    for (int i = 0; i < transmissions.size(); ++i) {
        transmissions[i] = readFile("transmission" + to_string(i + 1) + ".txt");
    }
    for (int i = 0; i < maliciousCodes.size(); ++i) {
        maliciousCodes[i] = readFile("mcode" + to_string(i + 1) + ".txt");
    }
    /*
    Description:
        Checks if each malicious code is a subsequence of each transmission.
    Complexity:
        Total Complexity: O(|M| * max(|T|, sum(T)))
    */
    for (int i = 0; i < transmissions.size(); ++i) {
        for (int j = 0; j < maliciousCodes.size(); ++j) {
            int arrow = 0, start = 0;
            for (int k = 0; k < transmissions[i].size(); ++k) {
                if (arrow < maliciousCodes[j].size() && transmissions[i][k] == maliciousCodes[j][arrow]) {
                    if (start == 0) {
                        start = k + 1;
                    }
                    ++arrow;
                }
            }
            if (arrow >= maliciousCodes[j].size()) {
                cout << "true " << start << endl;
            } else {
                cout << "false" << endl;
            }
        }
    }
    /*
    Description:
        Finds the largest palindrome in each transmission using Manacher's algorithm.
    Complexity:
        O(n) 
    */
    for (int i = 0; i < transmissions.size(); ++i) {
        manacher(transmissions[i]);
        pair<int, int> ans = findLargestPalindrome();
        cout << ans.first << " " << ans.second << endl;
    }
    /*
    Description:
        Finds the longest common substring between pairs of transmissions using a suffix array and an LCP array.
    Complexity:
        O(sum(T) * log(sum(T))) 
    */

    for (int i = 0; i < transmissions.size(); ++i) {
        for (int j = i + 1; j < transmissions.size(); ++j) {
            string s = transmissions[i] + '$' + transmissions[j] + '#';
            vector<int> suffixArray = constructSA(s);
            vector<int> LCPArray = computeLCP(s, suffixArray);
            int longestCommonSubstringLength = 0, start = 0, end = -1;
            for (int k = 1; k < LCPArray.size(); ++k) {
                if (LCPArray[k] > longestCommonSubstringLength) {
                    if (min(suffixArray[k - 1], suffixArray[k]) < transmissions[i].size() &&
                        transmissions[i].size() < max(suffixArray[k - 1], suffixArray[k])) {
                        longestCommonSubstringLength = LCPArray[k];
                        start = min(suffixArray[k - 1], suffixArray[k]) + 1;
                        end = start + longestCommonSubstringLength - 1;
                    }
                }
            }
            cout << start << " " << end << endl;
        }
    }

    return 0;

}