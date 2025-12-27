#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 1000 + 5;

vector<ll> a;

void quik_sort(vector<ll> &a, int l, int r) {
    if(l >= r) return;

    int pivot_index = l + rand() % (r - l + 1);
    int pivot = a[pivot_index]; // 随机选出来的数

    swap(a[l], a[pivot_index]); // 把这个数放到左区间的最右边 （该区间皆<=此数）

    int i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while (a[i] < pivot);
        do j--; while (a[j] > pivot);
        if (i < j) swap(a[i], a[j]);
    }

    quik_sort(a, l, j);
    quik_sort(a, j + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 0; i < n; i ++) cin >> a[i];

    quik_sort(a, 0, sizeof a);

    for(int i = 0; i < n; i ++) cout << a[i];
}