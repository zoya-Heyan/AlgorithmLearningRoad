#include <iostream>
#include <cstring>
using namespace std;

const int N = 505;  // 顶点数上限（左右部最大节点数）

int n1, n2, m;       // n1: 左部点数, n2: 右部点数, m: 边数
int h[N], e[N * N], ne[N * N], idx;
int match[N];        // match[y] = x，表示右部点 y 当前匹配到的左部点 x
bool st[N];          // 右部点是否访问过（防止重复搜索）

//x -> y （x 属于左部，y 属于右部）
void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx++;
}

// 尝试让左部点 x 匹配上一个右部点
bool find(int x) {
    for (int i = h[x]; ~i; i = ne[i]) {
        int y = e[i];
        if (st[y]) continue;  // 右部点已访问过
        st[y] = true;
        // 如果 y 未匹配 或 y 的匹配对象能让出位置
        if (match[y] == 0 || find(match[y]))    {
            match[y] = x;  // 匹配成功
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n1 >> n2 >> m;

    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;  // a 属于左部，b 属于右部
        add(a, b);
    }

    int res = 0;
    for (int x = 1; x <= n1; x++) {
        memset(st, 0, sizeof st);  // 每次尝试前重置访问标记
        if (find(x)) res++;
    }

    cout << res << "\n";  // 输出最大匹配数
    return 0;
}