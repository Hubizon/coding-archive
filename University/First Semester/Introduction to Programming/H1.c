// Hubert Jastrzębski | Satori H1 (Akcja meduza) | 2024-10-31
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9422773

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef unsigned long long ull;
typedef long long ll;

ull baseToDec(char x[], int n, int base) {
    ull res = 0;
    for (int i = 0; i < n; i++) {
        if (x[i] == 0) break;
        int d = (x[i] >= 'A' ? x[i] + 10 - 'A' : x[i] - '0');
        res *= base;
        res += d;
    }
    return res;
}

int decToBase(ull x, int base, char res[]) {
    if (x == 0) {
        res[0] = '0';
        return 1;
    }

    char rres[100];
    int pos = 0;
    while (x) {
        int d = x % base;
        rres[pos++] = (d >= 10 ? d - 10 + 'A' : d + '0');
        x /= base;
    }

    for (int i = 0; i < pos; i++)
        res[pos - i - 1] = rres[i];

    return pos;
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int A[200];
        char B[200];
        memset(A, 0, sizeof A);
        memset(B, 0, sizeof B);
        for (int i = 0; i < 26; i++) {
            int x;
            scanf("%d", &x);
            A['A' + i] = x;
            B[x] = 'A' + i;
        }
        scanf("%d", &A['.']);
        B[A['.']] = '.';

        int zz;
        scanf("%d", &zz);
        while (zz--) {
            char s[20];
            scanf("%s", s);
            if (s[0] == 'K') {
                int p, q;
                char s[3010];
                memset(s, 0, sizeof s);
                scanf("%s", s);

                int V[1000];
                memset(V, 0, sizeof V);
                int vpos = 0, scnt = 0;

                unsigned int res = 0, freeBits = 32;
                for (int i = 0; s[i] != 0; i++, scnt++) {
                    int x = A[s[i]];
                    res += (x << (freeBits - 5));
                    freeBits -= 5;
                    if (freeBits <= 16) {
                        V[vpos++] = res >> 16;
                        res = res << 16;
                        freeBits += 16;
                    }
                }

                if (freeBits != 32)
                    V[vpos++] = res >> 16;

                int bitCnt = 0;
                for (int i = 0; i < vpos; i++)
                    for (int j = 0; j < 16; j++)
                        bitCnt += ((V[i] >> j) & 1);

                printf("%d %d ", scnt, bitCnt);
                for (int i = 0; i < vpos; i++)
                    printf("%d ", V[i]);
                printf("\n");
            }
            else if (s[0] == 'D') {
                int n, control;
                scanf("%d %d", &n, &control);

                int cnt = (n * 5 + 1) / 16;
                for (int i = 0; i < cnt; i++) {
                    int x;
                    scanf("%d", &x);

                }
            }
            else
                return -1;
        }
    }
}