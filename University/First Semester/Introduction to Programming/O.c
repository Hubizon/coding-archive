// Hubert Jastrzębski | Satori O (Lodowy labirynt) | 2024-12-08
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9422683

#include <stdio.h>
#include <stdlib.h>

int R[5000];
int rsize = 0;
int fun(int x, int y, int xd, int yd, int rope, int move, int ** tab) {
    if (tab[x][y] == 3) { // res
        R[rsize++] = x;
        R[rsize++] = y;
        return 1;
    }

    tab[x][y] += 10; // visited

    if (tab[x + xd][y + yd] == 0 || tab[x + xd][y + yd] == 3) { // moze isc dalej
        if (fun(x + xd, y + yd, xd, yd, rope, 0, tab) == 1) {
            R[rsize++] = x;
            R[rsize++] = y;
            return 1;
        }
        tab[x][y] -= 10;
        return 0;
    }

    if (tab[x + xd][y + yd] == 2 && rope == 1) { // przepasc
        if (fun(x + xd, y + yd, xd, yd, 0, 0, tab) == 1) {
            R[rsize++] = x;
            R[rsize++] = y;
            return 1;
        }
        tab[x][y] -= 10;
        return 0;
    }

    if (move) { // jezeli musi sie ruszyc
        tab[x][y] -= 10;
        return 0;
    }

    int G[8] = { 1, 0, -1, 0, 0, -1, 0, 1 }; // zablokowane nastepne
    for (int i = 0; i < 8; i += 2)
        if (G[i] != xd || G[i + 1] != yd)
            if (fun(x, y, G[i], G[i + 1], rope, 1, tab) == 1)
                return 1;

    tab[x][y] -= 10;
    return 0;
}

int main() {
    int z;
    scanf("%d", & z);
    while (z--) {
        int n, m;
        scanf("%d %d", & n, & m);

        int x1, y1, x2, y2;
        scanf("%d %d %d %d", & x1, & y1, & x2, & y2);

        int ** tab = (int ** ) malloc((n + 2) * sizeof(int * ));
        for (int i = 0; i < n + 2; i++) {
            tab[i] = (int * ) malloc((m + 2) * sizeof(int));
            if (i != 0 && i != n + 1) {
                tab[i][0] = tab[i][m + 1] = 1;
                for (int j = 1; j <= m; j++)
                    scanf("%d", & tab[i][j]);
            } else {
                for (int j = 0; j <= m + 1; j++)
                    tab[i][j] = 1;
            }
        }

        rsize = 0;
        int rope = 1;
        tab[x2][y2] = 3;
        if (tab[x1][y1] == 1) {
            rope = 0;
            tab[x1][y1] = 0;
        }

        if (tab[x1][y1] == 2 || fun(x1, y1, -x1, -y1, rope, 0, tab) == 0)
            printf("NIE\n");
        else {
            printf("TAK %d\n%d %d", rsize / 2, R[rsize - 2], R[rsize - 1]);
            for (int i = rsize - 4; i >= 0; i -= 2)
                printf(", %d %d", R[i], R[i + 1]);
            printf("\n");
        }
    }
}