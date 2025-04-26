// Hubert Jastrzębski | Satori L (Zakłady cukiernicze) | 2025-04-27
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9880172

#include <bits/stdc++.h>

using namespace std;

int main()  {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, m;
        cin >> n >> m;

        vector<int> V(n);
        for (auto& v : V)
            cin >> v;

        vector<vector<int>> G(n);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            --a, --b;
            G[a].push_back(b);
            G[b].push_back(a);
        }

        vector<int> C(n, -1), T;
        function<bool(int)> DFS = [&](int u) {
            T.push_back(u);
            for (auto& v : G[u]) {
                if (C[v] == -1) {
                    C[v] = !C[u];
                    if (!DFS(v))
                        return false;
                }
                else if (C[v] == C[u])
                    return false;
            }
            return true;
        };

        bool is_error = false;
        vector<pair<int, int>> R(n);
        for (int u = 0; u < n; u++) {
            if (C[u] == -1) {
                C[u] = 0;
                T.clear();
                if (!DFS(u)) {
                    cout << "ERROR\n";
                    is_error = true;
                    break;
                }
                for (auto& t : T) {
                    if (C[t] == 0)
                        R[t] = { 0, V[t] };
                }

                for (auto& t : T) {
                    int res = 0;
                    for (auto& v : G[t])
                        res = max(res, R[v].second);
                    if (C[t] == 1)
                        R[t] = { res, res + V[t] };
                }
            }
        }

        if (is_error)
            continue;

        int res = 0;
        for (auto& [a, b] : R)
            res = max(res, b);
        cout << res << '\n';

        for (auto& [a, b] : R)
            cout << a << ' ' << b << '\n';
    }
}