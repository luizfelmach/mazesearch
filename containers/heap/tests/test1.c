#include <mazesearch.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y, p;
} TPoint;

TPoint *tpoint(int x, int y, int p) {
    TPoint *tp = calloc(1, sizeof(TPoint));
    tp->x      = x;
    tp->y      = y;
    tp->p      = p;
    return tp;
}

void point_print(TPoint *p) {
    printf("%d %d %d\n", p->x, p->y, p->p);
}

int point_cmp1(void *p1, void *p2) {
    TPoint *a1 = p1;
    TPoint *a2 = p2;

    if (a1->x == a2->x && a1->y == a2->y) return 0;

    return -1;
}

int point_hash(int size, void *p) {
    TPoint *a   = p;
    int     res = (a->x * 523) ^ (a->y * 541);
    return res;
}

double prio(TPoint *p) {
    return p->p;
}

int point_priority(void *p1, void *p2) {
    TPoint *a1 = p1;
    TPoint *a2 = p2;
    return prio(a1) < prio(a2);
}

int main() {
    Map  m = map(point_hash, point_cmp1, NULL, free);
    Heap h = heap(m, point_priority, free);

    heap_insert(h, tpoint(13, 12123, 1999));
    heap_insert(h, tpoint(10, 12, 1));
    heap_insert(h, tpoint(11, 12, 1));
    heap_insert(h, tpoint(12, 12, 1));
    heap_insert(h, tpoint(13, 12, 1));
    heap_insert(h, tpoint(13, 12, 1));
    heap_insert(h, tpoint(13, 12, 1));
    heap_insert(h, tpoint(13, 12, 1));
    heap_insert(h, tpoint(13, 12, 1));
    heap_insert(h, tpoint(13, 12, 1));
    heap_insert(h, tpoint(13, 12, 1));

    while (!heap_empty(h)) {
        TPoint *p = heap_pop(h);
        point_print(p);
        printf("%lf", prio(p));
        printf("\n\n");
        free(p);
    }

    heap_destroy(h);
    map_destroy(m);
    return 0;
}