/**
 * @file main.cpp
 * @author Carlos David Amezcua Canales A01641742
 * @author Juan Daniel Muñoz Dueñas A01641792
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

string readFile(const string &fileName) {
    ifstream archivo(fileName);

    if (!archivo.is_open()) throw runtime_error("Error opening file " + fileName);

    stringstream buffer;
    buffer << archivo.rdbuf();
    archivo.close();

    return buffer.str();
}

vector<int> zFunction(string &s) {
    int l = 0, r = 0, n = s.size();
    vector<int> z(s.size(), 0);
    for (int i = 1; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

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

    vector<vector<int>> part1Ans(transmissions.size(), vector<int>(maliciousCodes.size(), false));
    for (int i = 0; i < maliciousCodes.size(); ++i) {
        string s = maliciousCodes[i] + '$';
        for (string &j : transmissions) {
            s += j;
        }
        vector<int> zArray = zFunction(s);
        int arrow = maliciousCodes[i].size();
        for (int j = 0; j < transmissions.size(); ++j) {
            for (int k = 0; k < transmissions[j].size(); ++k) {
                if (zArray[++arrow] >= maliciousCodes[i].size()) {
                    part1Ans[j][i] = k + 1;
                }
            }
        }
    }
    for (int i = 0; i < transmissions.size(); ++i) {
        for (int j = 0; j < maliciousCodes.size(); ++j) {
            if (!part1Ans[i][j]) {
                cout << "false" << endl;
            } else {
                cout << "true " << part1Ans[i][j] << endl;
            }
        }
    }
    for (int i = 0; i < transmissions.size(); ++i) {
        manacher(transmissions[i]);
        pair<int, int> ans = findLargestPalindrome();
        cout << ans.first << " " << ans.second << endl;
    }
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
