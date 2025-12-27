#include <iostream>
using namespace std;

const int N = 0xFFFFFFF;

int f[N], a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i ++) cin >> a[i];

    for(int i = 0; i <= n; i ++)
        for(int j = m; j >= a[i]; j ++)
            f[j] += f[j - a[i]];

    cout << f[m] << endl;

    return 0;
}