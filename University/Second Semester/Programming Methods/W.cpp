// Hubert Jastrzębski | Satori W (Rezerwacje) | 2025-06-12
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/10024799

#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

struct Value {
  int size = 0, sum = 0, pref = 0, suf = 0, res = 0;

  Value() { }

  Value(int x) : size(1), sum(x), pref(x), suf(x), res(x) { };
};

Value operator+(const Value& lhs, const Value& rhs) {
    Value res;
    res.size = lhs.size + rhs.size;
    res.sum = lhs.sum + rhs.sum;
    res.pref = (lhs.sum == lhs.size) ? lhs.sum + rhs.pref : lhs.pref;
    res.suf = (rhs.sum == rhs.size) ? rhs.sum + lhs.suf : rhs.suf;
    res.res = max({ lhs.res, rhs.res, lhs.suf + rhs.pref });
    return res;
}

Value operator*(const Value& lhs, const Value& rhs) {
    return rhs;
}

template <typename Value>
struct Tree {
  int L = 1;
  vector<Value> T;

  Tree(const int n) {
      while (L <= n) L *= 2;
      T = vector<Value>(2 * L);
      for (int i = 0; i < n; i++)
          T[i + L] = Value(1);
      for (int i = L - 1; i > 0; i--)
          T[i] = T[2 * i] + T[2 * i + 1];
  }

  void update(int i, const Value& x) {
      i += L;
      T[i] = T[i] * x;
      while (i /= 2)
          T[i] = T[2 * i] + T[2 * i + 1];
  }

  Value query(int p, int q) { // [p, q)
      if ((p += L) >= (q += L)) return { };
      Value resL = T[p], resR = { };
      while (p / 2 != q / 2) {
          if (p % 2 == 0) resL = resL + T[p + 1];
          if (q % 2 == 1) resR = T[q - 1] + resR;
          p /= 2, q /= 2;
      }
      return resL + resR;
  }

  int nxt(int i) {
      int tleft = query(0, i).sum;
      int pos = 1;
      while (pos < L) {
          if (T[2 * pos].sum > tleft)
              pos = 2 * pos;
          else {
              tleft -= T[2 * pos].sum;
              pos = 2 * pos + 1;
          }
      }
      return pos - L;
  }
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, k;
        cin >> n >> k;

        Tree<Value> T(n);
        while (k--) {
            string s;
            cin >> s;
            if (s == "RESERVE") {
                int a;
                cin >> a;
                if (T.query(a - 1, a).sum == 0)
                    cout << "ERROR\n";
                else
                    T.update(a - 1, Value(0));
            }
            else if (s == "CANCEL") {
                int a;
                cin >> a;
                if (T.query(a - 1, a).sum == 1)
                    cout << "ERROR\n";
                else
                    T.update(a - 1, Value(1));
            }
            else if (s == "SUM") {
                int a, b;
                cin >> a >> b;
                Value v = T.query(a - 1, b);
                cout << v.size - v.sum << '\n';
            }
            else if (s == "MAX") {
                int a, b;
                cin >> a >> b;
                cout << T.query(a - 1, b).res << '\n';
            }
            else if (s == "NXT") {
                int i;
                cin >> i;
                if (T.query(i, n).sum == 0)
                    cout << "ERROR\n";
                else
                    cout << T.nxt(i) + 1 << '\n';
            }
        }
    }
}