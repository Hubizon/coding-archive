// Hubert Jastrzębski | Satori F (My name is Depth) | 2025-03-20
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9757795

#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        string s1, s2;
        unordered_map<int, int> MI;
        vector<int> V1(n), V2(n);
        cin >> s1;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            MI[x] = i + 1;
            V1[i] = i + 1;
        }
        cin >> s2;
        for (auto &v2 : V2) {
            int x;
            cin >> x;
            v2 = MI[x];
        }

        if (n == 1) {
            cout << 0 << '\n';
            cout << 'K' << '\n';
            continue;
        }

        if (s2 == "PREORDER" && s1 == "INORDER") {
            swap(s1, s2);
            swap(V1, V2);
        }

        if (s1 == "PREORDER" && s2 == "INORDER") {
            vector<char> R2(n);
            vector<int> R3(n);
            vector<int> M(n + 1);
            for (int i = 0; i < n; i++)
                M[V2[i]] = i;

            vector<int> R;
            function<void(int, int, int, char, int)> fun = [&](int l1, int l2, int size, char c, int d) {
              if (size <= 0)
                  return;

              int root_i = V1[l1] - 1;
              R2[root_i] = c;
              R3[root_i] = d;

              int root = M[V1[l1]];

              int size1 = root - l2;
              fun(l1 + 1, l2, size1, 'L', d + 1);
              fun(l1 + size1 + 1, l2 + size1 + 1, size - size1 - 1, 'R', d + 1);

              R.push_back(V2[root]);
            };

            fun(0, 0, n, 'K', 0);

            for (auto &r : R)
                cout << R3[r - 1] << ' ';
            cout << '\n';
            for (auto &r : R)
                cout << R2[r - 1] << ' ';
            cout << '\n';
            continue;
        }

        if (s2 == "INORDER" && s1 == "POSTORDER") {
            swap(s1, s2);
            swap(V1, V2);
        }

        if (s1 == "INORDER" && s2 == "POSTORDER") {
            vector<char> R2(n);
            vector<int> R3(n);
            vector<int> M(n + 1);
            for (int i = 0; i < n; i++)
                M[V1[i]] = i;

            vector<int> R;
            function<void(int, int, int, char, int)> fun = [&](int l1, int l2, int size, char c, int d) { // [l; r]
              if (size <= 0)
                  return;

              int root_i = V2[l2 + size - 1] - 1;
              R2[root_i] = c;
              R3[root_i] = d;

              int root = M[V2[l2 + size - 1]];
              R.push_back(V1[root]);

              int size1 = root - l1;
              fun(l1, l2, size1, 'L', d + 1);
              fun(l1 + size1 + 1, l2 + size1, size - size1 - 1, 'R', d + 1);
            };

            fun(0, 0, n, 'K', 0);

            for (auto &r : R)
                cout << R3[r - 1] << ' ';
            cout << '\n';
            for (auto &r : R)
                cout << R2[r - 1] << ' ';
            cout << '\n';
            continue;
        }

        if (s2 == "PREORDER" && s1 == "POSTORDER") {
            swap(s1, s2);
            swap(V1, V2);
        }

        if (s1 == "PREORDER" && s2 == "POSTORDER") {
            vector<char> R2(n);
            vector<int> R3(n);
            vector<int> M(n + 1);
            for (int i = 0; i < n; i++)
                M[V1[i]] = i;

            bool isFull = true;
            for (int i = 0; i < n - 1; i++) {
                if (M[V2[i]] == M[V2[i + 1]] + 1)
                    isFull = false;
            }

            if (isFull) {
                M = vector<int>(n + 1);
                for (int i = 0; i < n; i++)
                    M[V2[i]] = i;

                vector<int> R;
                function<void(int, int, int, char, int)> fun = [&](int l1, int l2, int size, char c, int d) {
                  if (size <= 0)
                      return;

                  int root_i = V1[l1] - 1;
                  R2[root_i] = c;
                  R3[root_i] = d;

                  if (size == 1) {
                      R.push_back(V1[l1]);
                      return;
                  }

                  int newSize = M[V1[l1 + 1]] - l2 + 1;
                  fun(l1 + 1, l2, newSize, 'L', d + 1);
                  R.push_back(V1[l1]);
                  fun(l1 + newSize + 1, l2 + newSize, size - newSize - 1, 'R', d + 1);
                };

                fun(0, 0, n, 'K', 0);

                for (auto &r : R)
                    cout << R3[r - 1] << ' ';
                cout << '\n';
                for (auto &r : R)
                    cout << R2[r - 1] << ' ';
                cout << '\n';
                continue;
            }
        }

        cout << "ERROR\n";
    }
}