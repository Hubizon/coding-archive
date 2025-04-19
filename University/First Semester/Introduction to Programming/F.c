// Hubert Jastrzębski | Satori F (Księgarnia) | 2024-10-30
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9420867

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int SIZE = 230;

int compare(char a[], char b[], int A[]) { // czy A > B
    for (int i = 0; i < SIZE; i++) {
        if (A[a[i]] > A[b[i]])
            return 1;
        if (A[a[i]] < A[b[i]])
            return 0;
    }
    return 0;
}

void sort(char V[][SIZE], int Ids[], int n, int A[]) {
    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0 && compare(V[Ids[j]], V[Ids[j + 1]], A); j--) {
            int t = Ids[j];
            Ids[j] = Ids[j + 1];
            Ids[j + 1] = t;
        }
    }
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n, k;
        scanf("%d%d", &n, &k);

        char V[n][SIZE];
        memset(V, 0, sizeof V);
        getchar();

        for (int i = 0; i < n; i++)
            fgets(V[i], sizeof(V[i]), stdin);

        while (k--) {
            int A[300];
            memset(A, 0, sizeof A);

            char D[300];
            memset(D, 0, sizeof D);
            fgets(D, sizeof(D), stdin);
            for (int i = 0; i < 300; i++) {
                A[tolower(D[i])] = i + 1;
                A[toupper(D[i])] = i + 1;
            }
            A[' '] = A['\n'] = A[0] = -1;

            int Ids[n];
            for (int i = 0; i < n; i++)
                Ids[i] = i;

            sort(V, Ids, n, A);
            for (int i = 0; i < n; i++)
                printf("%s", V[Ids[i]]);
        }
    }
}