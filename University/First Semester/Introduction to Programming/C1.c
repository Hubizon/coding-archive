// Hubert Jastrzębski | Satori C1 (Ulica kasztanowa) | 2024-10-08
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9419810

#include <stdio.h>
#include <stdlib.h>

int binSearch(int* K, int k, int x) {
    int a = 0, b = k;
    while (a < b) {
        int mid = a + (b - a) / 2;
        if (K[mid] <= x)
            a = mid + 1;
        else
            b = mid;
    }
    return a;
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int k;
        scanf("%d", &k);
        int* K = (int*)malloc(k * sizeof(int));
        scanf("%d", &K[0]);
        for (int i = 1; i < k; i++) {
            scanf("%d", &K[i]);
            K[i] += K[i - 1];
        }

        int q;
        scanf("%d", &q);
        while (q--) {
            int b;
            scanf("%d", &b);
            int res = binSearch(K, k, b);
            printf("%d\n", res);
        }

        free(K);
    }
}