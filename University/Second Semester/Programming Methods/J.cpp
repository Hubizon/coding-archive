// Hubert Jastrzębski | Satori J (Domeny) | 2025-04-26
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9821618

#include <bits/stdc++.h>

using namespace std;

template<typename T1, typename T2>
class HashMap {
 private:
  enum Type { EMPTY=0, FILLED=1, DELETED=2 };
  struct Node {
    T1 key;
    T2 value;
    Type t;
  };

  constexpr const static size_t P[] = {
      5, 23, 29, 37, 47, 59, 73, 89, 107, 131, 163,
      197, 239, 293, 353, 431, 521, 631, 761, 919, 1103,
      1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839,
      7013, 8419, 10103, 12143, 14591, 17519, 21023, 25229,
      30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631,
      130363, 156437, 187751, 225307, 270371, 324449, 389357,
      467237, 560689, 672827, 807403, 968897, 1162687, 1395263,
      1674319, 2009191, 2411033, 2893249, 3471899, 4166287,
      4999559, 5999471, 7199369
  };
  const float resize_factor = 0.9;
  int p_size = 0, size = 0;
  vector<Node> V;

  void insert_(vector<Node>& A, T1 key, T2 value) {
      size_t pos = hash<T1>{}(key) % A.size();
      while (A[pos].t != EMPTY) {
          if (A[pos].t == FILLED && A[pos].key == key) {
              A[pos] = { key, value, FILLED };
              return;
          }
          (pos += 1) %= A.size();
      }
      A[pos] = { key, value, FILLED };
      size++;
  }

  void resize_() {
      if (size >= P[p_size] * resize_factor) {
          vector<Node> T(P[++p_size]);
          size = 0;
          for (auto& [key, value, t] : V)
              if (t == FILLED)
                  insert_(T, key, value);
          V = T;
      }
  }

 public:
  HashMap() {
      V.resize(P[0]);
  }

  void insert(T1 key, T2 value) {
      insert_(V, key, value);
      resize_();
  }

  void delete_key(T1 key) {
      size_t pos = hash<T1>{}(key) % V.size();
      while (V[pos].t != EMPTY) {
          if (V[pos].t == FILLED && V[pos].key == key) {
              V[pos].t = DELETED;
              return;
          }
          (pos += 1) %= V.size();
      }
  }

  pair<bool, T2> find(T1 key) {
      size_t pos = hash<T1>{}(key) % V.size();
      while (V[pos].t != EMPTY) {
          if (V[pos].t == FILLED && V[pos].key == key)
              return { true, V[pos].value };
          (pos += 1) %= V.size();
      }
      return { false, T2() };
  }
};

int main()  {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        HashMap<string, string> M;
        while (n--) {
            string s;
            cin >> s;
            if (s == "INSERT") {
                string nazwa, adres;
                cin >> nazwa >> adres;
                M.insert(nazwa, adres);
            }
            else {
                string nazwa;
                cin >> nazwa;
                auto [is_ok, adres] = M.find(nazwa);
                cout << (is_ok ? adres : "ERROR") << '\n';
                if (s == "DELETE")
                    M.delete_key(nazwa);
            }
        }
    }
}