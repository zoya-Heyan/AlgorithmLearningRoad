#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int N = 10005;

ll r[N];
int n, m;
ll d[N], s[N], t[N];

struct Node {
    ll minv, lazy;
} tr[N * 4];

void push_up(int u) {
    tr[u].minv = min(tr[u << 1].minv, tr[u << 1 | 1].minv);
}

void push_down(int u) {
    if(~tr[u].lazy) {
        ll tag = tr[u].lazy;
        tr[u << 1].minv += tag;
        tr[u << 1 | 1].minv += tag;
        tr[u << 1].lazy += tag;
        tr[u << 1 | 1].lazy += tag;
        tr[u].lazy = 0;
    }
}

void build(int u, int l, int rr) {
    tr[u].lazy = 0;
    if (l == rr) {
        tr[u].minv = r[l];
        return;
    }
    int mid = (l + rr) >> 1;
    build(u >> 1, l, mid);
    build(u >> 1 | 1, mid, rr);
    push_up(u);
}

void modify(int u, int l, int r, int L, int R, ll v) {
    if (L <= l && r <= R) {
        tr[u].minv += v;
        tr[u].lazy += v;
        return;
    }
    push_down(u);
    int mid = (l + r) >> 1;
    if (L <= mid) modify(u << 1, l, mid, L, R, v);
    if (R > mid) modify(u << 1 | 1, mid + 1, r, L, R, v);
    push_up(u);
}

bool check(int k) {
    build(1, 1, n);
    for (int i = 1; i <= k; i++) {
        modify(1, 1, n, s[i], t[i], -d[i]);
        if (tr[1].minv < 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> r[i];
    for (int i = 1; i <= m; i++) {
        cin >> d[i] >> s[i] >> t[i];
    }

    int l = 1, r = m, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid + 1;
        } else {
            ans = mid;
            r = mid - 1;
        }
    }

    if (ans == -1) {
        cout << 0 << '\n';
    } else {
        cout << -1 << '\n';
        cout << ans << '\n';
    }

    return 0;
}