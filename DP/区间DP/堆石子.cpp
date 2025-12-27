#include <iostream>
using namespace std;
using ll = long long;

const int N = 105;
const ll INF = 4e18;

ll s[N];
ll f[N][N];
ll sum[N]; // 前缀和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> s[i];
        sum[i] = s[i] + (i > 0 ? sum[i-1] : 0);
    }

    // 初始化 f[i][j]
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            f[i][j] = (i == j ? 0 : INF);

    // 区间长度
    for(int len = 2; len <= n; len++) {
        for(int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            for(int k = i; k < j; k++) {
                int cost = sum[j] - (i > 0 ? sum[i-1] : 0); // 区间和
                f[i][j] = min(f[i][j], f[i][k] + f[k+1][j] + cost);
            }
        }
    }

    cout << f[0][n-1] << "\n";
    return 0;
}