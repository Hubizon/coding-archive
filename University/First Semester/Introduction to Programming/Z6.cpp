// Hubert Jastrzębski | Satori Z6 (Zamach) | 2024-12-27
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9423574

#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX_H = 100010;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        vector<int> L(MAX_H, 1e9), R(MAX_H, -1);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            L[x] = min(L[x], i);
            R[x] = max(R[x], i);
        }

        for (int i = 1; i < MAX_H; i++)
            L[i] = min(L[i], L[i - 1]);

        for (int i = MAX_H - 2; i >= 0; i--)
            R[i] = max(R[i], R[i + 1]);

        int res = 0, l = -1, r = -1;
        for (int i = 0; i < MAX_H - 1; i++) {
            int a = L[i], b = R[i + 1];
            int tres = b - a + 1;
            if (tres >= res) {
                res = tres;
                l = a;
                r = b;
            }
        }

        if (res == 0)
            cout << "NIE\n";
        else
            cout << l << ' ' << r  << '\n';
    }
}