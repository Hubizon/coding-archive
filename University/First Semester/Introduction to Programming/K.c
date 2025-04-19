// Hubert Jastrzębski | Satori K (Stacje benzynowe) | 2024-11-18
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9420987

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n;
        scanf("%d", &n);

        int* V = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            scanf("%d", V + i);

        if (n == 1) {
            printf("1\n0\n");
            free(V);
            continue;
        }

        int prev = *V;
        *V = (*V < *(V + 1));
        for (int i = 1; i < n - 1; i++) {
            int tprev = *(V + i);
            *(V + i) = (*(V + i) < prev && *(V + i) < *(V + (i + 1)));
            prev = tprev;
        }
        *(V + (n - 1)) = prev > *(V + (n - 1));

        *(V + (n - 1)) = (*(V + (n - 1)) == 1 ? n - 1 : n);
        for (int i = n - 2; i >= 0; i--)
            *(V + i) = (*(V + i) == 1 ? i : *(V + i + 1));

        int a = 0, b = min(n, sqrt(n) + 3);
        while (a < b) {
            int k = (b - a) / 2 + a;

            int pos = -k, tk = 0;
            while (pos + k < n) {
                pos = *(V + pos + k);
                if (pos >= n || ++tk >= k) break;
            }

            if (tk >= k) a = k + 1;
            else b = k;
        }

        printf("%d\n", --a);
        int pos = -a;
        for (int i = 0; i < a; i++) {
            pos = *(V + pos + a);
            printf("%d ", pos);
        }
        printf("\n");

        free(V);
    }
}