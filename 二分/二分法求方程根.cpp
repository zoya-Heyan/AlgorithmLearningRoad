#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

double a, b, c, d;

double f(double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

int main() {
    cin >> a >> b >> c >> d;
    vector<double> roots;

    for (double x = -100; x <= 100; x += 1) {
        double l = x, r = x + 1;
        double fl = f(l), fr = f(r);

        if (fl * fr <= 0) {
            while (r - l > 1e-7) {
                double mid = (l + r) / 2;
                double fm = f(mid);
                if (fl * fm <= 0)
                    r = mid;
                else
                    l = mid;
            }
            double root = (l + r) / 2;

            bool ok = true;
            for (double x0 : roots) {
                if (fabs(x0 - root) < 1.0)
                    ok = false;
            }
            if (ok)
                roots.push_back(root);
        }
    }

    sort(roots.begin(), roots.end());

    cout << fixed << setprecision(2);
    for (int i = 0; i < roots.size(); i++) {
        if (i) cout << " ";
        cout << roots[i];
    }
    cout << endl;

    return 0;
}