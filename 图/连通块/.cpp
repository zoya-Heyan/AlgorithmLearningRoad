#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100005;

int e[N], ne[N], h[N], idx;
bool vis[N];

void add(int a, int b) {
    e[idx] = a, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u) {
    int k0 = 2 * u, k1 = 2 * u + 1;
    vis[k0] = 1, vis[k1] = 1;

    for(int i = h[u]; ~i; i ++) {
        int v = e[i];
        if(!vis[k0] || !vis[k1])
            dfs(u);
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

    dfs(1);
}