#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 100005;
const int M = 200005;     // 边数，按需调整
const int INF = 0x3f3f3f3f;

int head[N], to[M], w[M], nxt[M], idx;
int dis[N];
bool inq[N];      // 是否在队列中

void add(int u, int v, int weight) {
    to[idx] = v;
    w[idx] = weight;
    nxt[idx] = head[u];
    head[u] = idx++;
}

void spfa(int start) {
    memset(dis, 0x3f, sizeof dis);
    memset(inq, 0, sizeof inq);
    dis[start] = 0;

    queue<int> q;
    q.push(start);
    inq[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;

        for (int i = head[u]; i != -1; i = nxt[i]) {
            int v = to[i];
            int ww = w[i];
            if (dis[v] > dis[u] + ww) {
                dis[v] = dis[u] + ww;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
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
        add(a, b, c);         // 有向图
        // add(b, a, c);      // 无向图要加这行
    }

    int start = 1;
    spfa(start);

    for (int i = 1; i <= n; i++) {
        cout << "dis[" << i << "] = " << dis[i] << "\n";
    }
}