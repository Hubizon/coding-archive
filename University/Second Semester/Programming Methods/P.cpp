// Hubert Jastrzębski | Satori P (Rozbudowa kolei) | 2025-05-06
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9880363

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> G(n), rG(n);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            G[a].push_back(b);
            rG[b].push_back(a);
        }

        vector<bool> vis(n);
        stack<int> S;
        function<void(int)> DFS = [&](int u) {
          if (vis[u]) return;
          vis[u] = true;
          for (auto v : G[u])
              DFS(v);
          S.push(u);
        };

        for (int u = 0; u < n; u++)
            DFS(u);

        vector<int> SCC(n, -1);
        int c = 0;

        function<void(int)> rDFS = [&](int u) {
          SCC[u] = c;
          for (auto& v : rG[u])
              if (SCC[v] == -1)
                  rDFS(v);
        };

        while (S.size()) {
            auto u = S.top(); S.pop();
            if (SCC[u] == -1)
                rDFS(u), c++;
        }

        if (c == 1) {
            cout << "0\n";
            continue;
        }

        vector<pair<bool, bool>> SCCIO(c);
        for (int u = 0; u < n; u++) {
            for (auto& v : G[u]) {
                if (SCC[u] != SCC[v]) {
                    SCCIO[SCC[u]].second = true;
                    SCCIO[SCC[v]].first = true;
                }
            }
        }

        int zIn = 0, zOut = 0;
        for (auto &[si, so] : SCCIO) {
            zIn += !si;
            zOut += !so;
        }

        cout << max(zIn, zOut) << '\n';
    }
}