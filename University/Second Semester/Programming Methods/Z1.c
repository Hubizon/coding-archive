// Hubert Jastrzębski | Satori Z1 (k-ty element) | 2025-04-05
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9786550

#include <stdio.h>

typedef long long ll;

#define SWAP(a, b) (a ^= b ^= a ^=b)

ll f(int a, int b, ll x) { // wartość funkcji y = ax + b w x
    return a * x + b;
}

ll lower(int a, int b, ll y, int n) { // ile jest mniejszych lub równych y
    if (a == 0) {
        if (b <= y)
            return n;
        return 0;
    }

    ll res = (y + a - b) / a;
    if (res < 0) res = 0;
    if (res > n) res = n;
    return res;
}

int search(int a, int b, int c, int d, int n, int m, int k) {
    int start = 0, end = n;
    while (start < end) {
        int mid = (start + end) / 2;
        int f1 = lower(a, b, f(a, b, mid), n);
        int f2 = lower(c, d, f(a, b, mid), m);
        if (f1 + f2 < k)
            start = mid + 1;
        else
            end = mid;
    }
    return start;
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n, a, b, m, c, d, k;
        scanf("%d %d %d %d %d %d %d", &n, &a, &b, &m, &c, &d, &k);

        if (a == 0 && c == 0) {
            if ((b <= d && n >= k) || (b >= d && m < k))
                printf("%d\n", b);
            else
                printf("%d\n", d);
            continue;
        }
        if (a == 0) {
            SWAP(a, c);
            SWAP(b, d);
            SWAP(n, m);
        }

        int s1 = search(a, b, c, d, n, m, k);
        int f1 = lower(a, b, f(a, b, s1), n);
        int f2 = lower(c, d, f(a, b, s1), m);
        if (s1 < n && f1 + f2 == k) {
            printf("%lld\n", f(a, b, s1));
        }
        else {
            int s2 = search(c, d, a, b, m, n, k);
            f2 = lower(c, d, f(a, b, s2), m);
            printf("%lld\n", f(c, d, s2));
        }
    }
}