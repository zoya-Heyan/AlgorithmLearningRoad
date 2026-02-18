#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10005;
const int M = 20005;

int n, m;
int head[N], nex[N], to[N], idx;
int low[N], dfn[N], stk[N], in_stk[N];
int tim, top;
int scc_cnt;
int id[N];

inline void add(int a, int b) {
    to[idx] = b, nex[idx] = head[a], head[a] = idx ++;
}

int tarjan(int u) {
    dfn[u] = low[u] = ++ tim;
    stk[++ top] = u;
    in_stk[u] = true;

    for(int i = head[u]; ~i; i ++) {
        int v = to[i];
        if(!dfn[v]) {
            tarjan(v);
            low[v] = min(low[v], low[u]);
        } else if(in_stk[v]) {
            low[v] = min(low[u], dfn[v]);
        }
    }

    if(low[u] == dfn[u]) {
        ++ scc_cnt;
        while(1) {
            int x = stk[top --];
            in_stk[x] = 0;
            id[x] = scc_cnt;
            if(x == u) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(head, -1, sizeof head);

    cin >> n >> m;
    while(m --) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    for(int i = 0; i < n; i ++) {
        if(!dfn[i])
            tarjan(i);
    }

    cout << scc_cnt << endl;
    return 0;
}
//找到所有强连通分量(极大的连通分量)并进行缩图操作