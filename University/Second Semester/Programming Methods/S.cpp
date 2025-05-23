// Hubert Jastrzębski | Satori S (Konkurs) | 2025-05-23
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/10015317

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
pair<int, int> partition(vector<T>& V, int start, int end, T pivot) {
    int i = start, j = end, k = start;
    while (k < j) {
        if (V[k] < pivot)
            swap(V[i++], V[k++]);
        else if (V[k] > pivot)
            swap(V[--j], V[k]);
        else
            k++;
    }
    return { i, j };
}

template<typename T>
T MagicFive(vector<T>& V, int start, int end, int k) {
    int n = end - start;
    if (n <= 6) {
        sort(V.begin() + start, V.begin() + end);
        return V[start + k];
    }

    int pos = start;
    for (int i = start; i + 5 <= end; i += 5) {
        sort(V.begin() + i, V.begin() + i + 5);
        swap(V[pos++], V[i + 2]);
    }

    T med = MagicFive<T>(V, start, pos, (pos - start) / 2);
    auto [p1, p2] = partition(V, start, end, med);
    if (p1 - start > k)
        return MagicFive<T>(V, start, p1, k);
    if (p2 - start > k)
        return V[p1];
    return MagicFive<T>(V, p2, end, k - (p2 - start));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, k;
        cin >> n >> k;
        vector<int> V(n);
        for (auto &v : V)
            cin >> v;

        int result = MagicFive<int>(V, 0, n, k - 1);
        cout << result << '\n';
    }
}