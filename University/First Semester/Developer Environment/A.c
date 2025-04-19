// Hubert Jastrzębski | Satori A (Prosty program strumieniowy) | 2024-10-14
// https://satori.tcs.uj.edu.pl/contest/9427987/problems/9444907

#include <stdio.h>
#include <stdlib.h>

int string_to_int(char* arg) {
    int x = 0;
    for (int i = 0; arg[i]; i++)
        x = x * 10 + (arg[i] - '0');
    return x;
}

int main(int argc, char** argv) {
    int sum = 0;
    for (int i = 1; i < argc; i++)
        sum += string_to_int(argv[i]);

    int x;
    while(scanf("%d", &x) == 1)
        sum += x;

    printf("%d\n", sum);
}