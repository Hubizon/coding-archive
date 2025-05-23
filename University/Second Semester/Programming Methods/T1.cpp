// Hubert Jastrzębski | Satori T1 (Przygody Owena) | 2025-05-24
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/10015364

#include <iostream>
#include <vector>
#include <numeric>

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

        vector<bool> R(n);
        for (auto& [v, i] : V) {
            if (R[i]) continue;
            R[i] = true;
            cout << v << ' ';
        }
        cout << '\n';
    }
}