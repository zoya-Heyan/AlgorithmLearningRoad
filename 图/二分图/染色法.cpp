#include <iostream>
#include <cstring>
using namespace std;

const int N = 200005;

int h[N], e[N], ne[N], idx;
int color[N];   // 0 未染色，1 和 2 表示两种颜色
int n, m;

// 加边（无向图）
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool dfs(int u, int c) {
    color[u] = c;

    // 遍历所有邻点
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];

        if (!color[v]) {
            if (!dfs(v, 3 - c)) return false;
        }
        else if (color[v] == color[u])
            return false;
    }
    return true;
}

int main() {
    cin >> n >> m;

    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            if (!dfs(i, 1)) {
                cout << "NO\n";
                return 0;
            }
        }
    }

    cout << "YES\n";
    return 0;
}

//判断是不是二分图