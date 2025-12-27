#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005;

int v[N], w[N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    for(int i = 0; i < n; i ++) cin >> v[i] >> w[i];
    cin >> m;

    memset(f, 0xcf, sizeof f);
    f[0][0] = 0;

    for(int i = 1; i <= n; i ++) {
        for(int j = 0; j <= m; j ++) 
            f[i][j] = f[i - 1][j];
        for(int j = v[j]; j <= m; j ++)
            f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
    }

    int ans = 0;
    for(int i = 0; i <= m; i ++)
        ans = max(ans, f[n][i]);
        
    return 0;
}