// Hubert Jastrzębski | Satori U (Wybory) | 2025-05-27
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/10015446

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct Heap {
  vector<T> H = { { } };

  void push(T x) {
      H.push_back(x);
      int pos = H.size() - 1;
      while (pos != 1 && H[pos / 2] < H[pos]) {
          swap(H[pos / 2], H[pos]);
          pos /= 2;
      }
  }

  void pop() {
      H[1] = H.back();
      H.pop_back();
      int pos = 1;
      while (true) {
          int biggest = pos;
          if (2 * pos < H.size() && H[biggest] < H[2 * pos])
              biggest = 2 * pos;
          if (2 * pos + 1 < H.size() && H[biggest] < H[2 * pos + 1])
              biggest = 2 * pos + 1;
          if (!(H[biggest] < H[pos]) && !(H[pos] < H[biggest]))
              break;
          swap(H[biggest], H[pos]);
          pos = biggest;
      }
  }

  T top() {
      return H[1];
  }
};

struct Partia {
  long long g, s, id;

  bool operator<(const Partia &other) const {
      long long left = g * other.s;
      long long right = other.g * s;
      if (left != right)
          return left < right;
      if (g != other.g)
          return g < other.g;
      return id > other.id;
  }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, m;
        cin >> n >> m;

        vector<int> V(n);
        Heap<Partia> Q;
        for (int i = 0; i < n; i++) {
            int g;
            cin >> g;
            Q.push({ g, 1, i });
        }

        for (int i = 0; i < m; i++) {
            Partia p = Q.top();
            Q.pop();
            p.s++;
            Q.push(p);
            V[p.id]++;
        }

        for (auto v : V)
            cout << v << ' ';
        cout << '\n';
    }
}