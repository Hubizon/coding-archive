// Hubert Jastrzębski | Satori B2 (Suma dzielników) | 2024-10-08
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9419782

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 10000010;

int main() {
    // sito
    int* IsP = (int*)malloc(SIZE * sizeof(int));
    IsP[0] = IsP[1] = 0;
    for (int i = 2; i < SIZE; i++)
        IsP[i] = 1;

    for (int i = 2; i * i < SIZE; i++)
        if (IsP[i] == 1)
            for (int j = i * i; j < SIZE; j += i)
                IsP[j] = 0;

    // tablica z liczbami pierwszymi
    int sizeP = 0, capacityP = 2;
    int* P = (int*)malloc(capacityP * sizeof(int));
    for (int i = 2; i < SIZE; i++) {
        if (IsP[i] == 1) {
            if (sizeP == capacityP)
                P = (int*)realloc(P, (capacityP *= 2) * sizeof(int));
            P[sizeP++] = i;
        }
    }

    // program
    int z;
    scanf("%d", &z);
    while (z--) {
        int x;
        scanf("%d", &x);

        long long res = 1;
        for (int i = 0; i < sizeP; i++) {
            if (x < P[i]) break;
            if (IsP[x] == 1) {
                res *= ((((long long)x) * x - 1) / (x - 1));
                break;
            }

            long long k = 0, pk = P[i];
            while (x % P[i] == 0) {
                x /= P[i];
                pk *= P[i];
                k++;
            }
            if (k > 0)
                res *= ((pk - 1) / (P[i] - 1));
        }

        printf("%d\n", res);
    }
}