#include <algorithm>
#include <iostream>
using namespace std;

const int N = 200010;

int n, m;
int p[N];

struct Edge {
    int a, b, w;
    bool operator<(const Edge &e) {
        return w < e.w;
    }
} Edge[N];

//并查集
int find(int x) {
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void merge(int x,int y){
    p[x]=find(p[y]);
    return;
}

int kruskal() {
    sort(Edge, Edge + m);

    for(int i = 0; i < n; i ++) p[i] = i;

    int res = 0;
    int cnt = 0;

    for(int i = 0; i < n; i ++) {
        int a = Edge[i].a;
        int b = Edge[i].b;
        int w = Edge[i].w;

        int pa = find(pa), pb = find(pb);

        if(pa != pb) {
            merge(a,b);
            res += w;
            cnt ++;

            if(cnt == n + 1) break;
        }
    }
    if(cnt < n - 1) return -1;

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for(int i = 0; i < m; i ++)
        cin >> Edge[i].a >> Edge[i].b >> Edge[i].w;

    int ans = kruskal();

    cout << ans << endl;
    return 0;
}

//时间复杂度为O(n log n)
//依赖并查集实现
//适合稀疏图