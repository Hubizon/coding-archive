// Hubert Jastrzębski | Satori A (Liczby pierwsze) | 2024-10-07
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9419734

#include <stdio.h>
#include <stdlib.h>

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n;
        scanf("%d", &n);

        int isPrime = (n > 1);
        for (int i = 2; i * i <= n; i++)
            if (n % i == 0)
                isPrime = 0;

        if (isPrime == 1)
            printf("%d jest pierwsza\n", n);
        else
            printf("%d jest zlozona\n", n);
    }
}