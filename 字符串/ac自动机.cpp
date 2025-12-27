#include <queue>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1000005;

int tr[N][26];
int cnt[N];
int fail[N];
int idx;

// 插入模式串
void insert_str(const string &s) {
    int p = 0;
    for(char c : s) {
        int t = c - 'a';
        if(!tr[p][t]) tr[p][t] = ++ idx;
        p = tr[p][t];
    }
    cnt[p] ++;
}

// 构建fail（BFS）
void build() {
    queue<int> q;
    for(int i = 0; i < 26; i ++) {
        int v = tr[0][i];
        if(v) q.push(v);
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = 0; i < 26; i ++) {
            int v = tr[u][i];
            if (v) {
                fail[v] = tr[fail[u]][i];
                q.push(v);
            } else {
                tr[u][i] = tr[fail[u]][i]; // 自动跳转优化（AC 自动机核心）
            }
        }
    }
}

// 匹配文本
int query(const string &t) {
    int p = 0, res = 0;
    for (char c : t) {
        int x = c - 'a';
        p = tr[p][x];
        int tmp = p;
        while (tmp) {
            res += cnt[tmp];   // 统计匹配
            tmp = fail[tmp];
        }
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    memset(tr, 0, sizeof tr);
    memset(cnt, 0, sizeof cnt);
    memset(fail, 0, sizeof fail);
    idx = 0;

    // 读入模式串
    while (n--) {
        string s;
        cin >> s;
        insert_str(s);
    }

    // 构建自动机
    build();

    // 匹配文本
    string text;
    cin >> text;
    cout << query(text) << "\n";

    return 0;
}


// Aho-corasick Automation 用于多模式串匹配问题 (Multiple Pattern Matching)
//O (N + M + P)