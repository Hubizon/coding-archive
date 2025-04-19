// Hubert Jastrzębski | Satori Z1 (Magiczny ciąg) | 2024-10-15
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9423450

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 1500000;
const int SIZE2 = 300010;

int* create() {
    int* V = (int*)malloc(3 * sizeof(int));
    V[0] = 0;
    V[1] = 1;
    return V;
}

void push(int** V_ref, int x) {
    int* V = *V_ref;
    if (V[0] == V[1]) {
        V = (int*)realloc(V, ((V[1] *= 2) + 2) * sizeof(int));
        *V_ref = V;
    }
    V[2 + V[0]] = x;
    V[0]++;
}

int size(int* V) {
    return V[0];
}

int value(int* V, int i) {
    return V[i + 2];
}


int main() {
    // sito, a równocześnie najmniejsza niewykorzystana liczba dla p
    int* IsP = (int*)malloc(SIZE * sizeof(int));
    IsP[0] = IsP[1] = 0;
    for (int i = 2; i < SIZE; i++)
        IsP[i] = -1;

    int** Divs = (int**)malloc(SIZE * sizeof(int*));
    for (int i = 0; i < SIZE; i++)
        Divs[i] = create();

    for (int i = 2; i < SIZE; i++) {
        if (IsP[i] == -1) {
            IsP[i] = i;
            for (int j = i; j < SIZE; j += i) {
                push(&Divs[j], i);
                IsP[j] = 0;
            }
        }
    }

    // czy liczba jest wykorzystana
    int* IsUsed = (int*)malloc(SIZE * sizeof(int));
    IsUsed[0] = IsUsed[1] = IsUsed[2] = 1;
    for (int i = 3; i < SIZE; i++)
        IsUsed[i] = 0;

    // nasz ciąg
    int* V = (int*)malloc(SIZE2 * sizeof(int));
    V[0] = 0, V[1] = 1, V[2] = 2;

    int prevv = 2, vcnt = 3;
    for (int i = 3; vcnt < SIZE2; i++) {
        int prev = prevv;
        int minV = 1e9;
        for (int j = 0; j < size(Divs[prev]); j++) {
            int p = value(Divs[prev], j), k;
            for (k = IsP[p]; IsUsed[k]; k += p);
            IsP[p] = k;
            if (k < minV)
                minV = k;
        }

        IsUsed[minV] = 1;
        prevv = minV;
        if (minV < SIZE2) {
            V[minV] = i;
            vcnt++;
        }
    }

    // zapytania
    int z;
    scanf("%d", &z);
    while (z--) {
        int a;
        scanf("%d", &a);
        printf("%d\n", V[a]);
    }
}