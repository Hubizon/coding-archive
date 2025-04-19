// Hubert Jastrzębski | Satori D (Akwarium) | 2024-10-22
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9419858

#include <stdio.h>
#include <stdlib.h>

typedef long double ld;

ld fun(ld k) {
    return k * (k * (k - 1) + 1);
}

ld bisection(ld x) {
    ld epsilon = 1e-12;
    ld a = 0, b = 1000;
    while (b - a > epsilon) {
        ld mid = (a + b) / 2;
        if (fun(mid) < x)
            a = mid;
        else
            b = mid;
    }
    return (a + b) / 2;
}


int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        int x;
        scanf("%d", &x);
        ld res = bisection(x);
        int resFloor = (int)res;
        int resCeil = resFloor;
        if (res > resFloor)
            resCeil++;
        if (fun(resFloor) == x)
            resCeil = resFloor;
        if (fun(resCeil) == x)
            resFloor = resCeil;
        printf("%.10f %d %d\n", (double)res, resFloor, resCeil);
    }
}