// Hubert Jastrzębski | Satori T2 (Przygody Owena) | 2025-05-24
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/10015412

#include <iostream>
#include <numeric>
#include <climits>
#include <vector>

using namespace std;

void radixSort(vector<pair<int, int>>& V, int n, int p = 3) {
    auto getDigit = [n](int v, int pos) {
      for (int j = 0; j < pos; j++)
          v /= n;
      return v % n;
    };

    for (int i = 0; i < p; i++) {
        vector<int> C(n);
        for (auto [v, idx] : V) {
            C[getDigit(v, i)]++;
        }
        partial_sum(C.begin(), C.end(), C.begin());

        vector<pair<int, int>> R(V.size());
        for (int k = V.size() - 1; k >= 0; k--)
            R[--C[getDigit(V[k].first, i)]] = V[k];
        V = R;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        vector<pair<int, int>> V;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                int a;
                cin >> a;
                V.push_back({ a, i });
            }
        }

        radixSort(V, n);

        int l = 0, r = 0, res = INT_MAX;
        int i = 0, j = 0, cnt = 0;
        vector<int> Cnt(n);
        while (j < V.size()) {
            while (j < V.size() && cnt != n)
                if (Cnt[V[j++].second]++ == 0)
                    cnt++;
            while (cnt == n)
                if (--Cnt[V[i++].second] == 0)
                    cnt--;
            if (V[j - 1].first - V[i - 1].first < res) {
                res = V[j - 1].first - V[i - 1].first;
                l = i - 1, r = j;
            }
        }

        cout << res << '\n';
        vector<int> R(n);
        for (int k = l; k < r; k++)
            R[V[k].second] = V[k].first;
        for (auto& rres : R)
            cout << rres << ' ';
        cout << '\n';
    }
}