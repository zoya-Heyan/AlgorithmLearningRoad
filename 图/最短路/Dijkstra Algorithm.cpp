#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 100005;   // 点数
const int M = 200005;   // 边数
const int INF = 0x3f3f3f3f;

int head[N], to[M], w[M], nxt[M], idx;
int dis[N];
bool vis[N];

// 加边：u -> v 权重为 w
void add(int u, int v, int weight) {
    to[idx] = v;
    w[idx] = weight;
    nxt[idx] = head[u];
    head[u] = idx++;
}

void dijkstra(int start) {
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[start] = 0;

    // 小根堆：first=距离, second=节点编号
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (vis[u]) continue;
        vis[u] = true;

        for (int i = head[u]; i != -1; i = nxt[i]) {
            int v = to[i];
            int ww = w[i];
            if (dis[v] > dis[u] + ww) {
                dis[v] = dis[u] + ww;
                pq.push({dis[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    memset(head, -1, sizeof head);
    idx = 0;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);     // 有向图
        // add(b, a, c);  // 无向图需要加这一句
    }

    int start = 1;
    dijkstra(start);

    for (int i = 1; i <= n; i++) {
        cout << "dis[" << i << "] = " << dis[i] << "\n";
    }
}