#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    cin >> t;
    for (int test = 0; test < t; test++) {
        int n, m, k;
        cin >> n >> k >> m;
        vector <ll> p(n), s(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i] >> s[i];
        }
        ll l = 0, r = (ll)1e15;
        while (r - l > 1) {
            ll mid = (l + r) / 2;
            vector <ll> a(n, 0);
            for (int i = 0; i < n; i++) {
                if (mid >= p[i]) {
                    a[i] = (mid - p[i]) / s[i];
                }
            }
            sort(a.begin(), a.end());
            reverse(a.begin(), a.end());
            ll res = 0;
            for (int i = 0; i < k; i++) {
                res += a[i];
            }
            if (res >= m) {
                r = mid;
            } else {
                l = mid;
            }
        }
        cout << "Case #" << test + 1 << ": " << r << "\n";
    }
    return 0;
}