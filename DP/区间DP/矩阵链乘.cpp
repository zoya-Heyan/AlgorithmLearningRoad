#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const long long INF = (long long)1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
   
    vector<long long> p(n + 1);
    for (int i = 0; i <= n; i++) cin >> p[i];

    vector<vector<long long>> f(n + 1, vector<long long>(n + 1, INF));

    for (int i = 1; i <= n; i++)
        f[i][i] = 0;

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                long long cost = f[i][k] + f[k + 1][j] + p[i - 1] * p[k] * p[j];
                f[i][j] = min(f[i][j], cost);
            }
        }
    }

    cout << f[1][n] << '\n';
    return 0;
}