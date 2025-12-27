#include <iostream>
#include <algorithm>
using namespace std;

const int N = 505;
const int INF = 1e9;

int n, m;
int g[N][N];  //邻接矩阵
int dist[N];  //点到集合最小距离
bool st[N];

int prim() {
    memset(dist, 0x3f, sizeof dist);

    dist[1] = 0;

    int res = 0;

    for(int i = 1; i <= n; i ++) {
        int u = -1;

        for(int j = 1; j <= n; j ++) {
            if(!st[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }

        if(i > 1 && dist[u] == INF) return -1;

        st[u] = true;
        if(i > 1) res += dist[u];

        for(int v = 1; v <= n; v ++) 
            dist[v] = min(dist[v], g[u][v]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int a, b, w;

    while(m --) {
        cin >> a >> b >> w;
        g[a][b] = g[b][a] = min(g[a][b], w);
    }

    int ans = prim();
    cout << ans << endl;

    return 0;
}
//适用于无向图，连通图
//更适合绸密图