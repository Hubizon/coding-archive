// Hubert Jastrzębski | Satori Z2 (Zabawka) | 2024-10-14
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9423478

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>  // for malloc and free

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n, m;
        scanf("%d %d", &n, &m);

        int *V = (int *)malloc(n * sizeof(int));

        int smallest = INT_MAX;
        for (int i = 0; i < n; i++) {
            scanf("%d", &V[i]);
            if (V[i] < smallest) {
                smallest = V[i];
            }
            V[i] = smallest;
        }

        int prev = n;
        while (m--) {
            int k;
            scanf("%d", &k);

            prev--;
            while (prev >= 0 && k > V[prev])
                prev--;
        }

        printf("%d\n", prev + 1 > 0 ? prev + 1 : 0);

        free(V);
    }
}