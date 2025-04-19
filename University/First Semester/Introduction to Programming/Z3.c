// Hubert Jastrzębski | Satori Z3 (Miss szkoły) | 2024-10-31
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9423510

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STRSIZE 1010

typedef struct {
  int score;
  int index;
} Miss;

int compareSTR(char a[], char b[]) { // a > b
    for (int i = 0; i < STRSIZE; i++) {
        if (b[i] == 0 || tolower(a[i]) > tolower(b[i]))
            return 1;
        if (a[i] == 0 || tolower(a[i]) < tolower(b[i]))
            return 0;
    }
    return 0;
}

void assign(char a[], char b[]) { // a = b
    for (int i = 0; i < STRSIZE; i++)
        a[i] = b[i];
}

void sortSTR(char V[][STRSIZE], int n, int start, int step) {
    for (int i = start + step; i < n; i += step) {
        char x[STRSIZE];
        memset(x, 0, sizeof x);
        strcpy(x, V[i]);
        int j = i;
        for (; j >= start + step && compareSTR(V[j - step], x); j -= step)
            strcpy(V[j], V[j - step]);
        strcpy(V[j], x);
    }
}

void shellSortSTR(char V[][STRSIZE], int n) {
    for (int step = n / 2; step > 0; step /= 2) {
        for (int start = 0; start < step; start++) {
            sortSTR(V, n, start, step);
        }
    }
}

int compareMISS(Miss a, Miss b, char V[][STRSIZE]) { // a < b
    if (a.score == b.score)
        return compareSTR(V[a.index], V[b.index]);
    return (a.score < b.score);
}

void sortMISS(Miss V[], int n, int start, int step, char VV[][STRSIZE]) {
    for (int i = start + step; i < n; i += step) {
        Miss x;
        x = V[i];
        int j = i;
        for (; j >= start + step && compareMISS(V[j - step], x, VV); j -= step)
            V[j] = V[j - step];
        V[j] = x;
    }
}

void shellSortMISS(Miss V[], int n, char VV[][STRSIZE]) {
    for (int step = n / 2; step > 0; step /= 2) {
        for (int start = 0; start < step; start++) {
            sortMISS(V, n, start, step, VV);
        }
    }
}

int equal(char a[], char b[]) { // a == b
    for (int i = 0; i < STRSIZE; i++) {
        if (a[i] == 0 && b[i] == 0)
            return 1;
        if (tolower(a[i]) != tolower(b[i]))
            return 0;
    }
    return 1;
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n;
        scanf("%d", &n);
        char V[n][STRSIZE];
        memset(V, 0, sizeof V);
        for (int i = 0; i < n; i++)
            scanf("%s", V[i]);

        shellSortSTR(V, n);

        Miss Scores[n];
        memset(Scores, 0, sizeof Scores);
        Scores[0].score = 1;
        Scores[0].index = 0;
        int pos = 0;
        for (int i = 1; i < n; i++) {
            if (!equal(V[Scores[pos].index], V[i])) {
                pos++;
                Scores[pos].score = 1;
                Scores[pos].index = i;
            }
            else
                Scores[pos].score++;
        }

        shellSortMISS(Scores, pos + 1, V);

        printf("%d\n", pos + 1);
        for (int i = 0; i <= pos; i++)
            printf("%s %d\n", V[Scores[i].index], Scores[i].score);
    }
}