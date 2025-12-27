#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int N = 505;

int n, m;
int dis[N][N];

int main() {
    cin >> n >> m;

    // 初始化距离
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            dis[i][j] = (i == j ? 0 : INF);

    // 输入 m 条边
    for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        dis[a][b] = min(dis[a][b], w);
    }

    // Floyd
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

    // 查询
    int q;
    cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;

        if(dis[x][y] > INF / 2) cout << "impossible\n";
        else cout << dis[x][y] << "\n";
    }
}