// Hubert Jastrzębski | Satori Z4 (Specjalizacje) | 2024-12-14
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9423538

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
constexpr int MOD = 1000;

unsigned int popcount64(unsigned long long x)
{
    x = (x & 0x5555555555555555ULL) + ((x >> 1) & 0x5555555555555555ULL);
    x = (x & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);
    x = (x & 0x0F0F0F0F0F0F0F0FULL) + ((x >> 4) & 0x0F0F0F0F0F0F0F0FULL);
    return (x * 0x0101010101010101ULL) >> 56;
}

int fast_pow(int a, int k) {
    int res = 1;
    while (k) {
        if (k % 2) (res *= a) %= MOD;
        (a *= a) %= MOD;
        k /= 2;
    }
    return res % MOD;
}

struct my_bitset {
  vector<ull> V;

  my_bitset() { }

  my_bitset(int size) {
      V = vector<ull>((size + 63) / 64);
  }

  void set(const string &s) {
      for (int i = 0; i < s.size(); i++)
          if (s[i] == '1')
              V[i / 64] |= (1ULL << (i % 64));
  }
};

int and_count(const my_bitset& A, const my_bitset& B) { // (A & B).count()
int res = 0;
for (int i = 0; i < A.V.size(); i++)
res += popcount64(A.V[i] & B.V[i]);
return res;
}

int main() {
    int z;
    cin >> z;
    while (z--) {
        int n, m, t, u, k;
        cin >> n >> m >> t >> u >> k;

        vector<my_bitset> V(n, my_bitset(m));
        for (auto& v : V) {
            string s;
            cin >> s;
            v.set(s);
        }

        int uni_res = 0;
        vector<int> cnts(n);
        for (int i = 0; i < n; i++) {
            int cnt = cnts[i];
            for (int j = i + 1; j < n; j++) {
                if (and_count(V[i], V[j]) >= t) {
                    cnts[j]++;
                    cnt++;
                }
            }

            if (cnt >= u)
                uni_res++;
        }

        cout << uni_res << ' ';
        cout << std::setw(3) << std::setfill('0')<< fast_pow(uni_res, k) << '\n';
    }
}