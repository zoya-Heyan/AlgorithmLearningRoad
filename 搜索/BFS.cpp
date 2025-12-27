#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m;
    if (!(cin >> n >> m)) return 0; 

    vector<vector<int>> p(n, vector<int>(m));
    int maxp = 0; // 用来确定二分上界
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> p[i][j];
            maxp = max(maxp, p[i][j]);
        }
    }

    // 判定函数：检查是否存在一条路径，其上所有中间格子值 <= T
    auto check = [&](int T) -> bool {
        vector<vector<char>> vis(n, vector<char>(m, 0));
        queue<pair<int,int>> q;
      
        for (int j = 0; j < m; ++j) {
            vis[0][j] = 1;
            q.emplace(0, j);
        }
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
          
            if (x == n - 1) return true;
          
            for (int k = 0; k < 4; ++k) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; 
                if (vis[nx][ny]) continue; 
                
                if (nx == 0 || nx == n - 1 || p[nx][ny] <= T) {
                    vis[nx][ny] = 1;
                    q.emplace(nx, ny);
                }
            }
        }
        return false;
    };

    // 二分答案：最小 T 使 check(T) == true
    int l = 0, r = maxp;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << l << '\n';
    return 0;
}