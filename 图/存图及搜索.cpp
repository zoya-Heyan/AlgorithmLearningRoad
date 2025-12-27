#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000 + 5;

int e[N], h[N], ne[N], idx;
bool vis[N];

//from poinnt a to point b
inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u) {
    vis[u] = 1;

    for(int i = h[u]; i != -1; i ++) {
        int v = e[i];
        if(!vis[v]) dfs(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, n;
    cin >> n;
    while(n --) {
        cin >> a >> b;
        add(a, b);
    }

    dfs(1);
}