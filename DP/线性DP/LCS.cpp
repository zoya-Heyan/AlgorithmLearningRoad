#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int LCS(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> f(n + 1, vector<int> (m + 1, 0));

    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= m; j ++) {
            if(a[i - 1] == b[i - 1])
                f[i][j] = f[i - 1][j - 1] + 1;
            else
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
        }
    }
    return f[n][m];
}

int main() {
    string a, b;
    cin >> a >> b;
    cout << LCS(a, b) << endl;
}

//O(nm)