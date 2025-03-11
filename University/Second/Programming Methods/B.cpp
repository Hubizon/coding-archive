// Hubert Jastrzębski | Satori B (Cyklon) | 2025-03-04
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9757550

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int main()  {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        vector<array<int, 4>> V(n);
        for (auto& [a, b, c, d] : V)
            cin >> a >> b >> c >> d;

        auto calculate = [&](ld t) {
          ld left = HUGE_VALL, right = -HUGE_VALL, top = HUGE_VALL, bot = -HUGE_VALL;
          for (auto& [a, b, c, d] : V) {
              ld ap = a + t * c, bp = b + t * d;
              left = min(left, ap);
              right = max(right, ap);
              top = min(top, bp);
              bot = max(bot, bp);
          }
          return max(right - left, bot - top);
        };

        ld a = 0, b = 1;
        ld prevc = calculate(a), nowc = calculate(b);
        while (prevc > nowc) {
            prevc = nowc;
            nowc = calculate(b *= 2);
        }

        ld w = HUGE_VALL;
        while (2 * w >= 1e-4) {
            ld r = (b - a) / 3;
            auto ca = calculate(a + r), cb = calculate(b - r);
            if (ca > cb) {
                w = calculate(a) - ca;
                a = a + r;
            } else {
                w = calculate(b) - cb;
                b = b - r;
            }
        }

        ld res = (a + b) / 2;
        cout << std::fixed << std::setprecision(10) << calculate(res) << ' ' << res << '\n';
    }
}