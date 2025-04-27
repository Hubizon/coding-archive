// Hubert Jastrzębski | Satori Z3 (Mutacje) | 2025-04-27
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9880402

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main()  {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, k;
        cin >> n >> k;

        const ull PRIME1 = 101;
        const ull MOD = 1e9 + 100501;

        vector<ull> P1(k);
        for (ull i = 0, x1 = 1; i < k; i++)
            P1[i] = ((x1 *= PRIME1) %= MOD);

        auto calculateHPre = [&](const string& S) {
          vector<ull> HPre1(k + 1);
          for (int i = 0; i < k; i++)
              (HPre1[i + 1] = HPre1[i] + (S[i] * P1[i])) %= MOD;
          return HPre1;
        };

        auto subHash = [&](vector<ull>& HPre, int l, int r) { // [l, r]
          ull ssHash = (HPre[r] - HPre[l] + MOD) % MOD;
          (ssHash *= P1[k - r]) %= MOD;
          return ssHash;
        };

        vector<vector<ull>> HPres;
        while (n--) {
            string S;
            cin >> S;
            HPres.push_back(calculateHPre(S));
        }

        int m;
        cin >> m;
        while (m--) {
            string S;
            cin >> S;

            auto HPre1 = calculateHPre(S);
            int res0 = 0, res1 = 0, res2 = 0;
            for (auto& HPre2 : HPres) {
                if (HPre1.back() == HPre2.back())
                    res0++;
                else {
                    int a = 0, b = k;
                    while (a < b) {
                        int mid = (a + b) / 2;
                        if (HPre1[mid] == HPre2[mid])
                            a = mid + 1;
                        else
                            b = mid;
                    }
                    int firstDiff = a;

                    a = 0, b = k;
                    while (a < b) {
                        int mid = (a + b) / 2;
                        if ((HPre1.back() - HPre1[mid] + MOD) % MOD != (HPre2.back() - HPre2[mid] + MOD) % MOD)
                            a = mid + 1;
                        else
                            b = mid;
                    }
                    int lastDiff = a;

                    if (firstDiff == lastDiff)
                        res1++;
                    else if (firstDiff + 1 == lastDiff ||
                            subHash(HPre1, firstDiff, lastDiff - 1) == subHash(HPre2, firstDiff, lastDiff - 1))
                        res2++;
                }
            }


            if (res0 + res1 + res2 == 0)
                HPres.push_back(HPre1);
            cout << res0 << ' ' << res1 << ' ' << res2 << '\n';
        }
    }
}