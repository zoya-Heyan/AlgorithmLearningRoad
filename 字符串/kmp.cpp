#include <iostream>
using namespace std;

const int N = 10010, M = 100010;

int n, m;
int p[N], s[N];
int ne[N];
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < m; i++) cin >> s[i];

    // Preprocess the pattern to create the 'ne' array
    for (int i = 1, j = 0; i < n; i++) {
        while (j && p[i] != p[j]) j = ne[j - 1];
        if (p[i] == p[j]) j++;
        ne[i] = j;
    }

    // KMP Search
    for (int i = 0, j = 0; i < m; i++) {
        while (j && s[i] != p[j]) j = ne[j - 1];
        if (s[i] == p[j]) j++;
        if (j == n) {
            cout << i - n + 1 << endl; // Match found at index (i - n + 1)
            j = ne[j - 1]; // Continue searching for next match
        }
    }

    return 0;

}