#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int LCS_rolling(string a, string b) {
    int n = a.size(), m = b.size();

    if(m > n) return LCS_rolling(b, a);

    vector<int> prev(m + 1, 0), cur(n + 1, 0);

    for(int i = 1; i <= n; ++ i) {
        for(int j = 0; j <= m; ++ j) {
            if (a[i - 1] == b[j - 1]) cur[j] = prev[j - 1] + 1;
            else cur[j] = max(prev[j], cur[j - 1]);
        }
        swap(prev, cur);
        fill(cur.begin(), cur.end(), 0);
    }

    return prev[m];
}

int main() {
    string a, b;
    cin >> a >> b;
    cout << LCS_rolling(a, b) << endl;
}

//O(min(n, m))
//滚动数组难以直接用于恢复 LCS 序列（路径），因为丢失了完整的表格信息；
//若需要输出序列，要么保留完整 f，要么使用 Hirschberg 算法（分治 + 两边滚动）在 O(nm) 时间下把空间降到 O(min(n,m)) 并可递归恢复序列