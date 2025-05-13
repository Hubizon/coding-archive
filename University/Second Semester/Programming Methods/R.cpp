// Hubert Jastrzębski | Satori R (Czek) | 2025-05-13
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/10015263

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Value {
  string value;

  bool operator<(const Value& other) const{
      return value + other.value > other.value + value;
  }

  bool operator==(const Value& other) const{
      return value == other.value;
  }

  friend istream& operator>>(istream& in, Value& v) {
      in >> v.value;
      return in;
  }
};

template<typename T>
void quickSort(vector<T>& V, int start, int end)
{
    while (start < end) {
        auto [p1, p2] = partition(V, start, end);

        if (p1 - start < end - p2) {
            quickSort(V, start, p1);
            start = p2;
        } else {
            quickSort(V, p2, end);
            end = p1;
        }
    }
}

template<typename T>
pair<int, int> partition(vector<T>& V, int start, int end)
{
    int pos = uniform_int_distribution<int>(start, end - 1)(rng);
    swap(V[start], V[pos]);
    T pivot = V[start];
    int i = start, j = start, k = start;
    while (k < end) {
        if (V[k] < pivot) {
            swap(V[i], V[k]);
            i++;
        }
        if (V[k] == pivot) {
            swap(V[j], V[k]);
            j++;
        }
        k++;
    }
    return { i, j };
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        vector<Value> V(n);
        for (auto& v : V)
            cin >> v;

        quickSort(V, 0, V.size());
        for (auto& v : V)
            cout << v.value;
        cout << '\n';
    }
}