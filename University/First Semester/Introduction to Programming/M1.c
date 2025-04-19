// Hubert Jastrzębski | Satori M1 (Odwiedziny) | 2024-11-19
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9424400

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x, y;
  char name[11];
} Domek;

int cmp(const void* a, const void* b) {
    return ((Domek*)a)->x > ((Domek*)b)->x;
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n;
        scanf("%d", &n);

        Domek V[n];
        for (int i = 0; i < n; i++) {
            scanf("%d %d %s", &(V[i].x), &(V[i].y), &(V[i].name));
            if (V[i].y < 0) V[i].y *= -1;
        }

        qsort(V, n, sizeof(Domek), &cmp);

        int res = 1e9, prevRes = 1e9;
        int res1, res2, prev;
        for (int i = 1; i < n; i++) {
            if (V[i - 1].y < prevRes) {
                prevRes = V[i].x - V[i - 1].x + V[i - 1].y;
                prev = i - 1;
            }
            else
                prevRes += V[i].x - V[i - 1].x;
            if (prevRes + V[i].y < res) {
                res = prevRes + V[i].y;
                res1 = prev;
                res2 = i;
            }
        }

        printf("%d\n%s %s\n", res, V[res1].name, V[res2].name);
    }
}