// Hubert Jastrzębski | Satori J (Symulator Przykładowej Maszyny Cyfrowej) | 2024-11-05
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9420955

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef unsigned short ushort;

const ushort MEM_SIZE = 600;

ushort add (ushort a, ushort b) {
    int ax = a, bx = b;
    if ((a >> 15) & 1)
        ax = -(((ushort)(a << 1)) >> 1);
    if ((b >> 15) & 1)
        bx = -(((ushort)(b << 1)) >> 1);

    int res = ax + bx;
    if (res < 0) {
        res *= -1;
        res |= (1 << 15);
    }
    return (ushort)res;
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int n, k;
        scanf("%d%d", &n, &k);

        unsigned short V[MEM_SIZE];
        memset(V, 0, sizeof V);
        for (int i = 0; i < n; i++) {
            int p;
            char c;
            scanf("%d: %c", &p, &c);
            ungetc(c, stdin);
            if (isalpha(c)) {
                char rozkaz[10];
                char znak;
                int x;
                scanf("%s %c %d", rozkaz, &znak, &x);
                if (x < 0) {
                    x *= -1;
                    V[p] |= (1 << 15);
                }
                ushort IR = 0;
                if (!strcmp(rozkaz, "STOP"))
                    IR = 1;
                else if (!strcmp(rozkaz, "LOAD"))
                    IR = 2;
                else if (!strcmp(rozkaz, "STORE"))
                    IR = 3;
                else if (!strcmp(rozkaz, "JUMP"))
                    IR = 4;
                else if (!strcmp(rozkaz, "JNEG"))
                    IR = 5;
                else if (!strcmp(rozkaz, "JZERO"))
                    IR = 6;
                else if (!strcmp(rozkaz, "ADD"))
                    IR = 8;
                else if (!strcmp(rozkaz, "SUB"))
                    IR = 9;
                else if (!strcmp(rozkaz, "AND"))
                    IR = 12;
                else if (!strcmp(rozkaz, "OR"))
                    IR = 13;
                else if (!strcmp(rozkaz, "NOT"))
                    IR = 14;
                else if (!strcmp(rozkaz, "XOR"))
                    IR = 15;
                else if (!strcmp(rozkaz, "SHL"))
                    IR = 10;
                else if (!strcmp(rozkaz, "SHR"))
                    IR = 11;
                V[p] |= (IR << 11);

                ushort OZ = 0;
                if (znak == '@')
                    OZ = 1;
                else if (znak == '*')
                    OZ = 2;
                else if (znak == '+')
                    OZ = 3;
                V[p] |= (OZ << 9);
                V[p] |= x;
            }
            else {
                int x;
                scanf("%d", &x);
                if (x < 0) {
                    x *= -1;
                    V[p] = x;
                    V[p] |= (1 << 15);
                }
                else
                    V[p] = x;
            }

            char komentarz[500];
            fgets(komentarz, sizeof(komentarz), stdin);
        }

        ushort AC = 0, PC = 0;
        while (1) {
            ushort sign = V[PC] >> 15;
            ushort IR = ((ushort)(V[PC] << 1)) >> 12;
            ushort OZ = ((ushort)(V[PC] << 5)) >> 14;
            ushort x = V[PC] & ((1 << 9) - 1);

            ushort PCp = PC + 1;
            x |= (sign << 15);
            if (OZ == 1)
                x = V[x];
            else if (OZ == 2)
                x = V[V[x]];
            else if (OZ == 3)
                x = V[AC + x];

            if (IR == 1) // STOP
                break;
            else if (IR == 2) // LOAD
                AC = x;
            else if (IR == 3) // STORE
                V[x] = AC;
            else if (IR == 4) // JUMP
                PCp = x;
            else if (IR == 5) { // JNEG
                if (AC != 0 && ((AC >> 15) & 1)) PCp = x;
            }
            else if (IR == 6) { // JZERO
                if (AC == 0) PCp = x;
            }
            else if (IR == 8) // ADD
                AC = add(AC, x);
            else if (IR == 9) { // SUB
                x ^= (1 << 15);
                AC = add(AC, x);
            }
            else if (IR == 12) // AND
                AC = AC & x;
            else if (IR == 13) // OR
                AC = AC | x;
            else if (IR == 14) // NOT
                AC = ~AC;
            else if (IR == 15) // XOR
                AC = AC ^ x;
            else if (IR == 10) // SHL
                AC = AC << x;
            else if (IR == 11) // SHR
                AC = AC >> x;

            PC = PCp;
        }

        while (k--) {
            ushort p;
            scanf("%hu", &p);
            int x = V[p];
            if ((x >> 15) & 1) {
                x = (((ushort)(x << 1)) >> 1);
                x *= -1;
            }
            printf("%d ", x);
        }
        printf("\n");
    }
}