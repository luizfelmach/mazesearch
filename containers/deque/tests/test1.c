#include <mazesearch.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *i32(int x) {
    int *a = calloc(1, sizeof(int));
    *a     = x;
    return a;
}

int main() {
    srand(time(NULL));
    Deque d = deque(free);
    int   i;
    for (i = 0; i < 10000; i++) {
        if (rand() % 2) {
            deque_push_back(d, i32(i));
        } else {
            deque_push_front(d, i32(i));
        }
    }
    for (i = 0; i < deque_size(d); i++) {
        printf("%d ", *(int *)deque_at(d, i));
    }
    deque_destroy(d);
    return 0;
}
