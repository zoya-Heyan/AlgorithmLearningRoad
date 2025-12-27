#include <iostream>
#include <cstring>
using namespace std;

const int N = 1005;

int f[N], a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for(int i = 0; i < t; i++) cin >> a[i];

    int ans = 0;

    for(int i = 0; i < t; i++) {
        f[i] = 1;  
        for(int j = 0; j < i; j++) {
            if(a[i] > a[j])
                f[i] = max(f[i], f[j] + 1);
        }
        ans = max(ans, f[i]);
    }

    cout << ans << endl;
    return 0;
}

//O(n^2)