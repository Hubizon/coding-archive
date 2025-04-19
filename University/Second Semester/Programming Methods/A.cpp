// Hubert Jastrzębski | Satori A (Sieć wifi) | 2025-03-09
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9757496

#include <bits/stdc++.h>

using namespace std;

int check(vector<int> &V, int x) {
    int pos = 0, cnt = 0;
    while (pos < V.size()) {
        cnt++;
        int y = V[pos] + x;

        int b = V.size();
        while (pos < b) {
            int mid = (pos + b) / 2;
            if (V[mid] <= y + x)
                pos = mid + 1;
            else
                b = mid;
        }
    }
    return cnt;
};

int main()  {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        vector<int> V(n);
        for (auto& v : V)
            cin >> v;
        partial_sum(V.begin(), V.end(), V.begin());

        int m;
        cin >> m;
        while (m--) {
            int k;
            cin >> k;

            int a = 0, b = 1e7 + 10;
            while (a < b) {
                int x = (a + b) / 2;
                if (check(V, x) > k)
                    a = x + 1;
                else
                    b = x;
            }

            cout << a << '\n';
        }
    }
}