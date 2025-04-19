// Hubert Jastrzębski | Satori E3 (Liczby) | 2024-10-22
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9420775

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void sort(int* V, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0 && V[j] > V[j + 1]; j--)
            V[j] ^= (V[j + 1] ^= (V[j] ^= V[j + 1]));
    }
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n;
        scanf("%d", &n);
        int* V = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            scanf("%d", &V[i]);

        sort(V, n);

        for (int i = 0; i < n; i++)
            printf("%d ", V[i]);
        printf("\n");

        int is_ok = 0;
        for (int k = 0; k < n; k++) {
            int i = 0, j = n - 1;
            while (i <= j) {
                int v = V[i] + V[j] + V[k];
                if (v == 0) break;
                if (v < 0) i++;
                else j--;
            }
            if (V[i] + V[j] + V[k] == 0) {
                printf("TAK %d %d %d\n", k, i, j);
                is_ok = 1;
                break;
            }
        }

        if (is_ok == 0)
            printf("NIE\n");
    }
}