// Hubert Jastrzębski | Satori N1 (Budowa (obgryzanie)) | 2025-04-29
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9880245

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()  {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, m;
        cin >> n >> m;

        vector<ll> V(n);
        for (auto& v : V)
            cin >> v;

        vector<vector<int>> G(n);
        vector<int> Degree(n);
        while (m--) {
            int a, b;
            char c;
            cin >> a >> c >> b;
            G[a - 1].push_back(b - 1);
            Degree[b - 1]++;
        }

        queue<int> Q;
        vector<ll> A(n, -1), B(n, -1);
        for (int u = 0; u < n; u++) {
            if (Degree[u] == 0) {
                Q.push(u);
                A[u] = 0;
            }
            if (G[u].empty())
                B[u] = V[u];
        }

        vector<int> T;
        function<void()> TopoSort1 = [&]() {
          while (Q.size()) {
              auto u = Q.front(); Q.pop();
              T.push_back(u);
              for (auto& v : G[u]) {
                  if (--Degree[v] == 0)
                      Q.push(v);
              }
          }
        };

        TopoSort1();

        for (auto u : T)
            for (auto v : G[u])
                A[v] = max(A[v], A[u] + V[u]);
        for (auto u = T.rbegin(); u != T.rend(); u++)
            for (auto v : G[*u])
                B[*u] = max(B[*u], B[v] + V[*u]);

        bool is_cycle = accumulate(Degree.begin(), Degree.end(), 0) != 0;
        ll res = *max_element(B.begin(), B.end());

        if (is_cycle)
            cout << "CYKL\n";
        else
            cout << "OK " << res << '\n';

        int q;
        cin >> q;
        while (q--) {
            int s, d;
            cin >> s >> d;
            s--;

            if (is_cycle)
                continue;

            if (A[s] + B[s] + d <= res)
                cout << "TAK\n";
            else
                cout << "NIE " << A[s] + B[s] + d - res << '\n';
        }
    }
}