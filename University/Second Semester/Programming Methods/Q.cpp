// Hubert Jastrzębski | Satori Q (Kapral) | 2025-05-13
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9880600

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

void merge(vector<int> &V, int start, int mid, int end, int k, ll &result) {
    int n1 = mid - start;
    int n2 = end - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = V[start + i];
    for (int j = 0; j < n2; j++)
        R[j] = V[start + n1 + j];

    int i = 0, j = 0, pos = start;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j])
            V[pos++] = L[i++];
        else
            V[pos++] = R[j++];
    }

    while (i < n1)
        V[pos++] = L[i++];
    while (j < n2)
        V[pos++] = R[j++];

    i = 0, j = 0;
    while (i < n1) {
        while (j < n2 && L[i] + k < R[j])
            j++;
        result += j;
        i++;
    }
}

void mergeSort(vector<int> &V, int start, int end, int k, ll &result) {
    if (end > start + 1) {
        int mid = (start + end) / 2;
        mergeSort(V, start, mid, k, result);
        mergeSort(V, mid, end, k, result);
        merge(V, start, mid, end, k, result);
    }
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

        ll result = 0;
        mergeSort(V, 0, n, k, result);
        for (auto &v : V)
            cout << v << " ";
        cout << '\n' << result << '\n';
    }
}