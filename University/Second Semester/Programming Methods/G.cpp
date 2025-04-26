// Hubert Jastrzębski | Satori G (My name is Depth) | 2025-03-25
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9757839

#include <bits/stdc++.h>

using namespace std;

int main() {
    int z;
    cin >> z;
    while (z--) {
        int n, r;
        cin >> n >> r;

        vector<pair<int, int>> T(n);
        for (auto& [a, b] : T) {
            cin >> a >> b;
            a--, b--;
        }

        int v = r - 1, p = -2;
        while (v != -2) {
            int tv = v, tp = p;

            if (T[v].first != -1) {
                p = v;
                v = T[v].first;
                cout << tv + 1 << ' ';
            }

            T[tv].first = T[tv].second;
            T[tv].second = tp;
        }

        cout << '\n';
    }
}