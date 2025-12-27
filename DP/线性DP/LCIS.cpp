#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LCIS(const vector<int> &a, const vector<int> &b) {
    int n = a.size(), m = b.size();
    vector<int> f(m, 0);
    
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int best = 0; 
        for (int j = 0; j < m; j++) {
            if (b[j] < a[i]) {
                best = max(best, f[j]);
            }
            else if (b[j] == a[i]) {
                f[j] = best + 1;
                ans = max(ans, f[j]);
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, g;
    cin >> t >> g;

    vector<int> A(t), B(g);

    for (int i = 0; i < t; i++) cin >> A[i];
    for (int i = 0; i < g; i++) cin >> B[i];

    cout << LCIS(A, B) << endl;
    return 0;
}