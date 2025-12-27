#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int lengthOfLIS(vector<int> &a) {
    vector<int> d;             
    for (int x : a) {
        auto it = lower_bound(d.begin(), d.end(), x);
        if (it == d.end()) d.push_back(x);
        else *it = x;
    }
    return d.size();
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << lengthOfLIS(a) << endl;
}

//单调队列优化后时间复杂度变为O(n log n)