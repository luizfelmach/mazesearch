#include <deque.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void **block;

struct _deque {
    block *data;
    int    allocated_block;
    int    block_size;
    int    block_up, block_down;
    int    begin, end;
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
    for (i = d->block_down; i >= d->block_up; i--) {
        d->data[i + shift] = d->data[i];
        d->data[i]         = NULL;
    }
    d->block_up += shift;
    d->block_down += shift;
}

void _deque_center_blocks(Deque d) {
    int current_middle = (d->block_down + d->block_up) / 2;
    int shift          = (d->allocated_block / 2) - current_middle;

    if (shift > 0) {
        _deque_shift_blocks_down(d, shift);
    } else if (shift < 0) {
        _deque_shift_blocks_up(d, -shift);
    }
}

int _deque_has_block_up(Deque d) {
    return d->block_up != 0;
}

int _deque_has_block_down(Deque d) {
    return d->block_down != (d->allocated_block - 1);
}

int _deque_is_centralizable(Deque d) {
    return (d->allocated_block - d->block_down - 1) + (d->block_up) > 1;
}

void _deque_ensure_blocks_up(Deque d) {
    if (!_deque_has_block_up(d)) {
        if (_deque_is_centralizable(d)) {
            _deque_center_blocks(d);
        } else {
            int size = d->allocated_block;
            d->allocated_block *= 3;
            block *b = calloc(d->allocated_block, sizeof(block));
            memcpy(b, d->data, size * sizeof(block));
            d->data = b;
            _deque_center_blocks(d);
        }
    }
}

void _deque_ensure_blocks_down(Deque d) {
    if (!_deque_has_block_down(d)) {
        if (_deque_is_centralizable(d)) {
            _deque_center_blocks(d);
        } else {
            int size = d->allocated_block;
            d->allocated_block *= 3;
            block *b = calloc(d->allocated_block, sizeof(block));
            memcpy(b, d->data, size * sizeof(block));
            d->data = b;
            _deque_center_blocks(d);
        }
    }
}

Deque deque() {
    Deque d            = calloc(1, sizeof(struct _deque));
    d->allocated_block = 10;
    d->block_size      = 10;
    d->block_up = d->block_down = (d->allocated_block) / 2;
    d->begin = d->end = 0;
    d->data           = calloc(d->allocated_block, sizeof(block));
    return d;
}

void deque_push_back(Deque d, void *data) {
    _deque_ensure_blocks_down(d);
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
    _deque_ensure_blocks_up(d);
    d->begin -= 1;
    if (d->begin == -1) {
        d->block_up -= 1;
        d->begin = d->block_size - 1;
    }
    _deque_ensure_blocks_up(d);
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
    if (d->end == -1) {
        d->end = d->block_size - 1;
        free(d->data[d->block_down]);
        d->data[d->block_down] = NULL;
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
}
