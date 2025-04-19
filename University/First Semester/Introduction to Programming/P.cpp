// Hubert Jastrzębski | Satori P (Zdezelowany radar) | 2024-12-14
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9424816

#include <bits/stdc++.h>

using namespace std;

int main() {
    int z;
    cin >> z;
    while (z--) {
        int n, s;
        cin >> n >> s;

        bitset<225> tab;
        for (int i = 0; i < n * n; i++) {
            int t;
            cin >> t;
            tab[i] = t;
        }

        vector<bitset<225>> rows(n), columns(n), d1s(2 * n - 1), d2s(2 * n - 1);
        for (int x = 0, pos = 0; x < n; x++) {
            for (int y = 0; y < n; y++, pos++) {
                rows[x][pos] = 1;
                columns[y][pos] = 1;
                d1s[x + y][pos] = 1;
                d2s[x - y + n - 1][pos] = 1;
            }
        }

        vector<bool> row(n), column(n);
        vector<int> d1(2 * n - 1), d2(2 * n - 1);
        vector<pair<int, int>> R, tempR;
        int res = 0;

        function<bool(int, int)> fun = [&](int x, int s) {
            if (s == 0) {
                bitset<225> bres;
                for (int i = 0; i < n; i++) {
                    if (row[i]) bres |= rows[i];
                    if (column[i]) bres |= columns[i];
                }
                for (int i = 0; i < 2 * n - 1; i++) {
                    if (d1[i]) bres |= d1s[i];
                    if (d2[i]) bres |= d2s[i];
                }

                int tempRes = bres.count();
                if (res < tempRes) {
                    res = tempRes;
                    R = vector<pair<int, int>>(tempR);
                    if (res == n * n)
                        return 1;
                }
                return 0;
            }
            if (n - x < s || x >= n)
                return 0;

            for (int y = 0; y < n; y++) {
                if (!tab[n * x + y] && !column[y]) {
                    row[x] = true;
                    column[y] = true;
                    d1[x + y]++;
                    d2[x - y + n - 1]++;
                    tempR.push_back({ x, y });

                    if (fun(x + 1, s - 1))
                        return 1;

                    row[x] = false;
                    column[y] = false;
                    d1[x + y]--;
                    d2[x - y + n - 1]--;
                    tempR.pop_back();
                }
            }
            if (fun(x + 1, s))
                return 1;

            return 0;
        };

        if (fun(0, s))
            cout << "TAK\n";
        else
            cout << "NIE " << n * n - res << '\n';
        for (auto& [a, b] : R)
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
}