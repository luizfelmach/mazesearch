#include <deque.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void **block;

struct _deque {
    block     *data;
    int        allocated_block;
    int        block_size;
    int        block_up, block_down;
    int        begin, end;
    free_deque free;
};

void _deque_shift_blocks_up(Deque d, int shift) {
    int i;
    for (i = d->block_up; i < d->block_down; i++) {
        d->data[i - shift] = d->data[i];
        d->data[i]         = NULL;
    }
    d->block_up -= shift;
    d->block_down -= shift;
}

void _deque_shift_blocks_down(Deque d, int shift) {
    int i;
    for (i = d->block_down; i > d->block_up; i--) {
        d->data[i + shift] = d->data[i];
        d->data[i]         = NULL;
    }
    d->block_up += shift;
    d->block_down += shift;
}

int _deque_unused_block_up(Deque d) {
    return d->block_up;
}

int _deque_unused_block_down(Deque d) {
    return d->allocated_block - d->block_down - 1;
}

void _deque_resolve_block_down(Deque d) {
    int unused_block_up = _deque_unused_block_up(d);
    if (unused_block_up > 5) {
        _deque_shift_blocks_up(d, unused_block_up / 2);
    } else {
        int size = d->allocated_block;
        d->allocated_block *= 2;
        block *b = calloc(d->allocated_block, sizeof(block));
        memcpy(b, d->data, size * sizeof(block));
        free(d->data);
        d->data = b;
    }
}

void _deque_resolve_block_up(Deque d) {
    int unused_block_down = _deque_unused_block_down(d);
    if (unused_block_down > 5) {
        _deque_shift_blocks_down(d, (unused_block_down / 2) + 1);
    } else {
        int size = d->allocated_block;
        d->allocated_block *= 2;
        block *b = calloc(d->allocated_block, sizeof(block));
        memcpy(b, d->data, size * sizeof(block));
        free(d->data);
        d->data           = b;
        unused_block_down = _deque_unused_block_down(d);
        _deque_shift_blocks_down(d, (unused_block_down / 2) + 1);
    }
}

Deque deque(free_deque free) {
    Deque d            = calloc(1, sizeof(struct _deque));
    d->allocated_block = 10;
    d->block_size      = 10;
    d->block_up = d->block_down = (d->allocated_block) / 2;
    d->begin = d->end = 0;
    d->data           = calloc(d->allocated_block, sizeof(block));
    d->free           = free;
    return d;
}

void deque_push_back(Deque d, void *data) {
    if (d->block_down == d->allocated_block) {
        _deque_resolve_block_down(d);
    }
    if (!d->data[d->block_down]) {
        d->data[d->block_down] = calloc(d->block_size, sizeof(void **));
    }
    d->data[d->block_down][d->end] = data;
    d->end += 1;
    if (d->end == d->block_size) {
        d->block_down += 1;
        d->end = 0;
    }
}

void deque_push_front(Deque d, void *data) {
    d->begin -= 1;
    if (d->begin == -1) {
        d->block_up -= 1;
        d->begin = d->block_size - 1;
    }
    if (d->block_up == -1) {
        _deque_resolve_block_up(d);
    }
    if (!d->data[d->block_up]) {
        d->data[d->block_up] = calloc(d->block_size, sizeof(void **));
    }
    d->data[d->block_up][d->begin] = data;
}

void *deque_pop_back(Deque d) {
    if (d->begin == d->end && d->block_up == d->block_down) {
        printf("error: pop with empty deque\n.");
        exit(1);
    }
    int   last = deque_size(d) - 1;
    void *data = deque_at(d, last);
    d->end -= 1;
    if (d->end == 0) {
        free(d->data[d->block_down]);
        d->data[d->block_down] = NULL;
    }
    if (d->end == -1) {
        d->end = d->block_size - 1;
        d->block_down -= 1;
    }
    return data;
}

void *deque_pop_front(Deque d) {
    if (d->begin == d->end && d->block_up == d->block_down) {
        printf("error: pop with empty deque\n.");
        exit(1);
    }
    void *data = deque_at(d, 0);
    d->begin += 1;
    if (d->begin == d->block_size) {
        d->begin = 0;
        free(d->data[d->block_up]);
        d->data[d->block_up] = NULL;
        d->block_up += 1;
    }
    return data;
}

void *deque_at(Deque d, int index) {
    int at    = (index + d->begin) % d->block_size;
    int block = (index + d->begin) / d->block_size;
    return d->data[d->block_up + block][at];
}

int deque_size(Deque d) {
    int size = d->end - d->begin + d->block_size * (d->block_down - d->block_up);
    return size;
}

void deque_destroy(Deque d) {
    int i;
    int size = deque_size(d);
    for (i = 0; i < size; i++) {
        void *data = deque_pop_back(d);
        if (d->free) {
            d->free(data);
        }
    }
    for (i = 0; i < d->allocated_block; i++) {
        free(d->data[i]);
    }
    free(d->data);
    free(d);
}
