// Hubert Jastrzębski | Satori Z2 (Złodzieje samochodów) | 2025-04-24
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9819534

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, k;
        cin >> n >> k;

        vector<vector<int>> G(n);
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            while (a--) {
                int ai;
                cin >> ai;
                G[i].push_back(ai);
            }
        }

        vector<bool> V(n);
        bool is_impossible = false;
        for (int i = 0; i < k; i++) {
            int v;
            cin >> v;
            V[v] = true;
            if (G[v].empty())
                is_impossible = true;
        }

        if (is_impossible) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        vector<int> R;
        function<int(int)> DFS = [&](int u) -> int { // 0 - unblocked, 1 - blocked, 2 - unblocked thief
          if (V[u]) {
              for (auto &v : G[u])
                  if (DFS(v) == 0)
                      R.push_back(v);
              return 2;
          }

          bool is_unblocked_thief = false, is_unblocked_v = G[u].empty();
          for (auto &v : G[u]) {
              int d = DFS(v);
              if (d == 2)
                  is_unblocked_thief = true;
              if (d == 0)
                  is_unblocked_v = true;
          }

          if (is_unblocked_thief && is_unblocked_v) {
              R.push_back(u);
              return 1;
          }

          if (is_unblocked_thief)
              return 2;

          return !is_unblocked_v;
        };

        DFS(0);
        cout << R.size() << ' ';
        for (auto& r : R)
            cout << r << ' ';
        cout << '\n';
    }
}