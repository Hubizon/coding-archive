// Hubert Jastrzębski | Satori 0 (Największy wspólny dzielnik) | 2024-10-07
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9419710

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", gcd(a, b));
    }
}