// Hubert Jastrzębski | Satori N2 (Binarny Algorytm Euklidesa) | 2024-12-07
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9422647

#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    if (!(a & 1) && !(b & 1))
        return gcd(a >> 1, b >> 1) << 1;
    if ((a & 1) && !(b & 1))
        return gcd(a, b >> 1);
    if (a <= b)
        return gcd(a, b - a);
    return gcd(b, a - b);
}

int gcd2(int a, int b) {
    int gcd = 1;
    while (b != 0) {
        if (!(a & 1) && !(b & 1))
            gcd <<= 1, a >>= 1, b >>= 1;
        else if ((a & 1) && !(b & 1))
            b >>= 1;
        else {
            if (a > b)
                a ^= (b ^= (a ^= b));
            b -= a;
        }
    }
    return gcd;
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int a, b;
        scanf("%d %d", &a, &b);

        printf("%d\n", gcd(a, b));
    }
}