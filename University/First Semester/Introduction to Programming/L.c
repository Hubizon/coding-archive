// Hubert Jastrzębski | Satori L (Świąteczny łańcuch) | 2024-11-18
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9421023

#include <stdio.h>
#include <stdlib.h>

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n;
        scanf("%d", &n);

        int MAXB = 1;
        int* A = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", A + i);
            if (*(A + i) > MAXB)
                MAXB = *(A + i);
        }
        MAXB++;

        int* WystCnt = (int*)calloc(MAXB, sizeof(int));
        for (int i = 0; i < n; i++)
            *(WystCnt + *(A + i)) += 1;

        int** Wyst = (int**)malloc(MAXB * sizeof(int*));
        for (int i = 0; i < MAXB; i++)
            if (*(WystCnt + i) != 0)
                *(Wyst + i) = (int*)malloc(*(WystCnt + i) * sizeof(int));

        int* tCnt = (int*)calloc(MAXB, sizeof(int));
        for (int i = 0; i < n; i++)
            *(*(Wyst + *(A + i)) + (*(tCnt + *(A + i)))++) = i;
        free(tCnt);
        free(A);

        int m;
        scanf("%d", &m);

        for (int i = 0; i < m; i++) {
            int mi;
            scanf("%d", &mi);
            int* B = (int*)calloc(mi, sizeof(int));
            for (int j = 0; j < mi; j++)
                scanf("%d", B + j);

            int pos = -1;
            for (int j = 0; j < mi; j++) {
                int x = *(B + j);
                if (*(WystCnt + x) == 0 || *(*(Wyst + x) + (*(WystCnt + x) - 1)) <= pos) {
                    pos = -1;
                    break;
                }
                int a = 0, b = *(WystCnt + x);
                while (a < b) {
                    int mid = (a + b) / 2;
                    if (*(*(Wyst + x) + mid) <= pos)
                        a = mid + 1;
                    else
                        b = mid;
                }
                pos = *(*(Wyst + x) + a);
            }

            if (pos == -1)
                printf("NIE\n");
            else
                printf("TAK\n");
            free(B);
        }

        for (int i = 0; i < MAXB; i++)
            if (*(WystCnt + i) != 0)
                free(*(Wyst + i));
        free(Wyst);
        free(WystCnt);
    }
}