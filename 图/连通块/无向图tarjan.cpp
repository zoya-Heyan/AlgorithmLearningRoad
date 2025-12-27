#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100005;
const int M = 200005;

int e[N], ne[N], h[N], idx;
int stk[N], in_stk[N], low[N], dfn[N];
int scc_cnt, top, ts;

void add(int a, int b) {
    e[idx] = a, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ts ++;
    stk[++ top] = u;
    in_stk[u] = 1;

    for(int i = h[u]; ~i; i ++) {
        int k0 = 2 * i, k1 = 2 * i + 1;
        int v = e[i];
        if(!dfn[v]) {
            low[v] = min(low[u], low[v]);
            tarjan(v);
        } else if(in_stk[v]) {
            low[v] = min(low[u], dfn[v]);
        }
    }

    if(low[u] = dfn[u]) {
        ++ scc_cnt;
        while(1) {
            int x = stk[top --];
            in_stk[x] = 0;
            if(x == u) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    while(m --) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    for(int i = 1; i <= n; i ++) {
        if(!dfn[i]) 
            tarjan(i);
    }

    int ans = 0;

}

//边双连通分量 e_DCC 桥
//点双连通分量 v_DCC 割点

//vis[i] = true;
//k = 2i or 2i + 1(不同方向)
//vis[k] = vis[i];