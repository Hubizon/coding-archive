// Hubert Jastrzębski | Satori M (Taksówki) | 2025-04-27
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9880206

#include <bits/stdc++.h>

using namespace std;

constexpr int INF = 1e9;

int main()  {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<vector<int>> G(n);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            --a, --b;
            G[a].push_back(b);
            G[b].push_back(a);
        }

        vector<array<int, 2>> dist(n, { INF, INF });
        auto BFS = [&](int src) {
          dist = vector<array<int, 2>>(n, { INF, INF });
          queue<pair<int, bool>> Q;
          dist[src][0] = 0;
          Q.push({ src, 0 });
          while (Q.size()) {
              auto [u, p] = Q.front(); Q.pop();
              for (auto& v : G[u]) {
                  if (dist[v][!p] == INF) {
                      dist[v][!p] = dist[u][p] + 1;
                      Q.push({ v, !p });
                  }
              }
          }
        };

        vector<array<int, 4>> K(k);
        for (int i = 0; i < k; i++) {
            int s, t, d;
            cin >> s >> t >> d;
            --s, --t;
            K[i] = { s, t, d, i };
        }

        sort(K.begin(), K.end());
        int prev = K[0][0];
        BFS(prev);

        vector<bool> R(k);
        for (auto [s, t, d, i] : K) {
            if (s != prev) {
                prev = s;
                BFS(prev);
            }
            R[i] = dist[t][d % 2] <= d;
        }

        for (auto r : R)
            cout << (r ? "TAK" : "NIE") << '\n';
    }
}