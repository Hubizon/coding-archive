// Hubert Jastrzębski | Satori K (Izomorfizm drzew) | 2025-04-26
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9821826

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

pair<ull, int> DFS(const string& s, int pos, ull P) { // [hash, ending pos]
    vector<ull> hashes;
    pos++;
    while (s[pos] != ')') {
        auto [c_hash, end_pos] = DFS(s, pos, P);
        hashes.push_back(c_hash);
        pos = end_pos + 1;
    }

    ull hash = 1e6 + 151;
    for (auto& h : hashes)
        hash *= 1000100501 + h + (h << 5) + (h >> 3) + h * P + h * h * h * P + h * P * P;

    return { hash, pos };
}

array<ull, 2> hash_v(const string& s) {
    ull hash1 = DFS(s, 0, 1e15 + 100021).first;
    ull hash2 = DFS(s, 0, 1e5 + 2701).first;
    return { hash1, hash2 };
}

int main()  {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        vector<array<ull, 2>> V;
        while (n--) {
            string v;
            cin >> v;
            V.push_back(hash_v(v));
        }

        sort(V.begin(), V.end());
        auto it = unique(V.begin(), V.end());
        cout << it - V.begin() << '\n';
    }
}