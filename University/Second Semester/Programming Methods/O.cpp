// Hubert Jastrzębski | Satori O (Śniegowy kryzys) | 2025-05-01
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9880324

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Refs {
  vector<vector<pair<int, int>>> &G;
  vector<int> &S, &R, &offset;
  vector<bool> &vis, &visE;
} *refs;

void DFS(int u) {
    while (refs->G[u].size()) {
        auto [v, ve] = refs->G[u].back(); refs->G[u].pop_back();
        if (refs->visE[ve])
            continue;
        refs->visE[ve] = true;
        refs->vis[u] = true;
        refs->S.push_back(u);
        if (refs->vis[v]) {
            refs->offset.push_back(refs->R.size());
            refs->R.push_back(v);
            while (refs->S.back() != v) {
                auto w = refs->S.back(); refs->S.pop_back();
                refs->vis[w] = false;
                refs->R.push_back(w);
            }
            refs->S.pop_back();
            refs->R.push_back(v);
        }
        DFS(v);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, m;
        cin >> n >> m;
        vector<vector<pair<int, int>>> G(n);
        for (int i = 0; i < m; i++) {
            int a, b, s, t;
            cin >> a >> b >> s >> t;
            if (s != t) {
                --a, --b;
                G[a].push_back({ b, i });
                G[b].push_back({ a, i });
            }
        }

        bool is_ok = true;
        for (int i = 0; i < n; i++) {
            if (G[i].size() % 2 == 1) {
                is_ok = false;
                break;
            }
        }
        if (!is_ok) {
            cout << "NIE\n";
            continue;
        }

        vector<int> S, R, offset;
        vector<bool> vis(n), visE(m);
        Refs refs_ = { G, S, R, offset, vis, visE };
        refs = &refs_;

        for (int u = 0; u < n; u++)
            DFS(u);

        cout << offset.size() << '\n';
        offset.push_back(R.size());
        for (int i = 0; i < offset.size() - 1; i++) {
            cout << offset[i + 1] - offset[i] - 1 << ' ';
            for (int j = offset[i]; j < offset[i + 1]; j++) {
                auto r = R[j];
                cout << r + 1 << ' ';
            }
            cout << '\n';
        }
    }
}