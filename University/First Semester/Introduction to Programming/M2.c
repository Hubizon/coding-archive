// Hubert Jastrzębski | Satori M2 (Odwiedziny) | 2024-11-19
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9424420

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x, y;
  char name[11];
} Domek;

int cmp(const void* a, const void* b) {
    return ((Domek*)a)->x - ((Domek*)b)->x;
}

struct Heap {
  void* arr;
  int n, size;
  int (*cmp) (const void*, const void*);
};

void myswap(void* a, void* b, int size) {
    void *t = malloc(size);
    memcpy(t, a, size);
    memcpy(a, b, size);
    memcpy(b, t, size);
    free(t);
}

void* heap_index(struct Heap* heap, int idx) {
    return (char*)heap->arr + idx * heap->size;
}

void heap_push(struct Heap* heap, void* x) {
    int pos = heap->n++;
    memcpy(heap_index(heap, pos), x, heap->size);
    while (heap->cmp(heap_index(heap, (pos - 1) / 2), heap_index(heap, pos)) < 0) {
        myswap(heap_index(heap, (pos - 1) / 2), heap_index(heap, pos), heap->size);
        pos = (pos - 1) / 2;
    }
}

void heap_pop(struct Heap* heap) {
    myswap(heap_index(heap, 0), heap_index(heap, --(heap->n)), heap->size);
    int pos = 0;
    while (1) {
        int maxPos = pos;
        int l = 2 * pos + 1, r = 2 * pos + 2;
        if (l < heap->n && cmp(heap_index(heap, l), heap_index(heap, maxPos)) > 0)
            maxPos = l;
        if (r < heap->n && cmp(heap_index(heap, r), heap_index(heap, maxPos)) > 0)
            maxPos = r;
        if (maxPos == pos)
            return;
        myswap(heap_index(heap, pos), heap_index(heap, maxPos), heap->size);
        pos = maxPos;
    }
}

void heap_constructor(struct Heap* heap, void* arr, int n, int size, int (*cmp) (const void*, const void*)) {
    heap->arr = arr; // in place operations
    heap->n = 0;
    heap->size = size;
    heap->cmp = cmp;
    for (int i = 0; i < n; i++)
        heap_push(heap, heap_index(heap, i));
}

void heapsort(void* tab, int n, int size, int (*cmp) (const void*, const void*)) {
    struct Heap heap;
    heap_constructor(&heap, tab, n, size, cmp);
    for (int i = 0; i < n; i++)
        heap_pop(&heap);
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

        heapsort(V, n, sizeof(Domek), &cmp);

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