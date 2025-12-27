#include <iostream>
using namespace std;

long long fastpow(long long a, long long b, long long p) {
    long long res = 1 % p;
    a %= p;
    while (b > 0) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main() {
    
    return 0;
}