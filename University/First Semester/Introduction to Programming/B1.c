// Hubert Jastrzębski | Satori B1 (Sito Eratostenesa) | 2024-10-07
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9419762

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 10000010;

// obliczanie najmniejszego
int minD(int *IsP, int *P, int sizeP, int x) {
    if (IsP[x] == 1)
        return x;
    if (x <= 1)
        return 1;
    for (int i = 0; i < sizeP; i++)
        if (x % P[i] == 0)
            return P[i];
    return 1;
}

int main() {
    // sito
    int *IsP = (int *)malloc(SIZE * sizeof(int));
    IsP[0] = IsP[1] = 0;
    for (int i = 2; i < SIZE; i++)
        IsP[i] = 1;

    for (int i = 2; i * i < SIZE; i++)
        if (IsP[i] == 1)
            for (int j = i * i; j < SIZE; j += i)
                IsP[j] = 0;

    // sumy prefiksowe zliczające ilosc liczb pierwszych
    int *sumP = (int *)malloc(SIZE * sizeof(int));
    memset(sumP, 0, sizeof(sumP));
    for (int i = 1; i < SIZE; i++)
        sumP[i] = sumP[i - 1] + IsP[i];

    // tablica z liczbami pierwszymi
    int sizeP = 0, capacityP = 2;
    int *P = (int *)malloc(capacityP * sizeof(int));
    for (int i = 2; i < SIZE; i++) {
        if (IsP[i] == 1) {
            if (sizeP == capacityP)
                P = (int *)realloc(P, (capacityP *= 2) * sizeof(int));
            P[sizeP++] = i;
        }
    }

    // program
    int z;
    scanf("%d", &z);
    while (z--) {
        int a, b;
        scanf("%d %d", &a, &b);

        int primeCnt = sumP[b] - sumP[a - 1];
        int divA = minD(IsP, P, sizeP, a);
        int divB = minD(IsP, P, sizeP, b);
        printf("%d %d %d\n", primeCnt, divA, divB);
    }
}