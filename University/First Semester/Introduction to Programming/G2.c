// Hubert Jastrzębski | Satori G2 (Leniwy Jaś) | 2024-10-31
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9420927

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
        char s[20];
        scanf("%s", s);
        if (s[0] == 'C') {
            int p, q;
            char x[80];
            memset(x, 0, sizeof x);
            scanf("%d %d %s", &p, &q, x);

            ull y = baseToDec(x, 80, p);
            int n = decToBase(y, q, x);
            for (int i = 0; i < n; i++)
                printf("%c", x[i]);
            printf("\n");
        }
        else if (s[0] == 'W') {
            int r;
            ll x;
            scanf("%d %lld", &r, &x);

            if (r != 64 && (x < -(1LL << (r - 1)) || (x >= (1LL << (r - 1)))))
                printf("ERROR\n");
            else {
                char res[r];
                memset(res, '0', sizeof res);
                if (x < 0) {
                    res[0] = '1';
                    x += (1LL << (r - 1));
                }

                char tores[80];
                int n = decToBase(x, 2, tores);
                for (int i = 0; i < n; i++)
                    res[i + r - n] = tores[i];

                for (int i = 0; i < r; i++)
                    printf("%c", res[i]);
                printf("\n");
            }
        }
        else if (s[0] == 'R') {
            char x[80];
            scanf("%s", x);

            char c = x[0];
            x[0] = '0';
            int pos = 0;
            for (; x[pos] != 0; pos++);

            ull y = baseToDec(x, 80, 2);
            if (c == '1')
                printf("%lld\n", ((long long)y) - (1LL << (pos - 1)));
            else
                printf("%llu\n", y);
        }
        else
            return -1;
    }
}