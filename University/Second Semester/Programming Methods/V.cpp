// Hubert Jastrzębski | Satori V (Promocja) | 2025-05-30
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/10024775

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class MinMaxHeap {
 private:
  vector<T> H;

  void push_down(int pos) {
      if (is_min_level(pos))
          push_down_min(pos);
      else
          push_down_max(pos);
  }

  void push_down_min(int pos) {
      if (2 * pos < H.size()) {
          int m = 2 * pos;
          if (2 * pos + 1 < H.size() && H[2 * pos + 1] < H[m])
              m = 2 * pos + 1;
          for (int i = 0; i < 4; i++)
              if (4 * pos + i < H.size() && H[4 * pos + i] < H[m])
                  m = 4 * pos + i;

          if (m >= 4 * pos) {
              if (H[m] < H[pos]) {
                  swap(H[m], H[pos]);
                  if (H[m / 2] < H[m])
                      swap(H[m / 2], H[m]);
                  push_down(m);
              }
          }
          else if (H[m] < H[pos])
              swap(H[m], H[pos]);
      }
  }

  void push_down_max(int pos) {
      if (2 * pos < H.size()) {
          int m = 2 * pos;
          if (2 * pos + 1 < H.size() && H[m] < H[2 * pos + 1])
              m = 2 * pos + 1;
          for (int i = 0; i < 4; i++)
              if (4 * pos + i < H.size() && H[m] < H[4 * pos + i])
                  m = 4 * pos + i;

          if (m >= 4 * pos) {
              if (H[pos] < H[m]) {
                  swap(H[m], H[pos]);
                  if (H[m] < H[m / 2])
                      swap(H[m / 2], H[m]);
                  push_down(m);
              }
          }
          else if (H[pos] < H[m])
              swap(H[m], H[pos]);
      }
  }

  void push_up_min(int pos) {
      if (pos >= 4 && H[pos] < H[pos / 4]) {
          swap(H[pos], H[pos / 4]);
          push_up_min(pos / 4);
      }
  }

  void push_up_max(int pos) {
      if (pos >= 4 && H[pos / 4] < H[pos]) {
          swap(H[pos], H[pos / 4]);
          push_up_max(pos / 4);
      }
  }

  bool is_min_level(int pos) {
      int l = __lg(pos);
      return l % 2 == 0;
  }

  int min_pos() {
      return 1;
  }

  int max_pos() {
      if (size() == 1)
          return 1;
      if (size() == 2)
          return 2;
      return H[2] < H[3] ? 3 : 2;
  }

 public:
  MinMaxHeap() {
      H = { { } };
  }

  MinMaxHeap(const vector<T>& V) {
      H = { { } };
      for (auto& v : V) H.push_back(v);
      for (int pos = V.size() / 2; pos >= 1; pos--)
          push_down(pos);
  }

  int size() {
      return H.size() - 1;
  }

  bool empty() {
      return size() <= 0;
  }

  void push(T x) {
      int pos = H.size();
      H.push_back(x);
      if (size() > 1) {
          if (is_min_level(H.size() - 1)) {
              if (H[pos / 2] < H[pos]) {
                  swap (H[pos], H[pos / 2]);
                  push_up_max(pos / 2);
              }
              else
                  push_up_min(pos);
          }
          else {
              if (H[pos] < H[pos / 2]) {
                  swap (H[pos], H[pos / 2]);
                  push_up_min(pos / 2);
              }
              else
                  push_up_max(pos);
          }
      }
  }

  void pop_min() {
      int pos = min_pos();
      H[pos] = H.back();
      H.pop_back();
      push_down(pos);
  }

  void pop_max() {
      int pos = max_pos();
      H[pos] = H.back();
      H.pop_back();
      push_down(pos);
  }

  T min() {
      return H[min_pos()];
  }

  T max() {
      return H[max_pos()];
  }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        long long res = 0;
        MinMaxHeap<int> H1, H2;
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            while (k--) {
                int x;
                cin >> x;
                if (H1.empty() && H2.empty())
                    H1.push(x);
                else if (H1.empty()) {
                    if (H2.min() > x)
                        H1.push(x);
                    else {
                        H1.push(H2.min());
                        H2.pop_min();
                        H2.push(x);
                    }
                }
                else if (H2.empty()) {
                    if (H1.max() < x)
                        H2.push(x);
                    else {
                        H2.push(H1.max());
                        H1.pop_max();
                        H1.push(x);
                    }
                }
                else {
                    if (H2.min() <= x)
                        H2.push(x);
                    else
                        H1.push(x);
                }
            }

            if (H2.empty()) {
                H2.push(H1.max());
                H1.pop_max();
            }

            if (H1.empty()) {
                H1.push(H2.min());
                H2.pop_min();
            }

            const int C = 5050;
            while (H1.size() >= C) {
                int x = H1.max();
                H1.pop_max();
                if (H2.size() < C)
                    H2.push(x);
            }

            while (H2.size() >= C) {
                int x = H2.min();
                H2.pop_min();
                if (H1.size() < C)
                    H1.push(x);
            }

            res += H2.max() - H1.min();
            H2.pop_max();
            H1.pop_min();
        }

        cout << res << '\n';
    }
}