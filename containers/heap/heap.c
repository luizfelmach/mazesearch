#include <heap.h>
#include <map.h>
#include <stdio.h>
#include <stdlib.h>

struct _heap {
    void    **data;
    heap_free free;
    heap_prio prio;
    int       size, allocated;
    Map       indexes;
};

Heap heap(Map indexes, heap_prio prio, heap_free free) {
    Heap h       = calloc(1, sizeof(struct _heap));
    h->allocated = 100;
    h->size      = 0;
    h->free      = free;
    h->prio      = prio;
    h->indexes   = indexes;
    h->data      = calloc(h->allocated, sizeof(void *));
    return h;
}

void _heap_swap(Heap h, int i, int j) {
    int *i_map = map_get(h->indexes, h->data[i]);
    int *j_map = map_get(h->indexes, h->data[j]);
    *i_map     = j;
    *j_map     = i;
    void *aux  = h->data[i];
    h->data[i] = h->data[j];
    h->data[j] = aux;
}

int _heap_parent(int idx) {
    return (idx - 1) / 2;
}

int _heap_child1(int idx) {
    return 2 * idx + 1;
}

int _heap_child2(int idx) {
    return 2 * idx + 2;
}

void _heapify_up(Heap h, int a) {
    int last_idx   = a;
    int parent_idx = _heap_parent(last_idx);

    while (last_idx) {
        void *child  = h->data[last_idx];
        void *parent = h->data[parent_idx];

        if (h->prio(child) < h->prio(parent)) {
            _heap_swap(h, last_idx, parent_idx);
        }

        last_idx   = parent_idx;
        parent_idx = _heap_parent(parent_idx);
    }
}

void _heapify_down(Heap h, int a) {
    int last_idx = h->size - 1;
    _heap_swap(h, a, last_idx);
    int current_idx = a, i = a;
    while (1) {
        int child1_idx = _heap_child1(i);
        int child2_idx = _heap_child2(i);

        if (child1_idx < last_idx &&
            h->prio(h->data[current_idx]) > h->prio(h->data[child1_idx])) {
            current_idx = child1_idx;
        }

        if (child2_idx < last_idx &&
            h->prio(h->data[current_idx]) > h->prio(h->data[child2_idx])) {
            current_idx = child2_idx;
        }

        if (current_idx != i) {
            _heap_swap(h, i, current_idx);
            i = current_idx;
        } else {
            break;
        }
    }
}

void heap_insert(Heap h, void *data) {
    if (h->size == h->allocated) {
        h->allocated *= 2;
        h->data = realloc(h->data, h->allocated * sizeof(void *));
    }
    int *index = map_get(h->indexes, data);
    if (!index) {
        index  = calloc(1, sizeof(int));
        *index = h->size;
        map_set(h->indexes, data, index);
    } else {
        if (h->prio(data) < h->prio(h->data[*index])) {
            map_force_key(h->indexes, data);
            if (h->free) {
                h->free(h->data[*index]);
            }
            h->data[*index] = data;
            _heapify_up(h, *index);
        } else {
            if (h->free) {
                h->free(data);
            }
        }
        return;
    }
    h->data[h->size] = data;
    _heapify_up(h, h->size++);
}

void *heap_pop(Heap h) {
    if (h->size == 0) {
        printf("error\n");
        exit(1);
    }
    void *target = h->data[0];
    _heapify_down(h, 0);
    map_del(h->indexes, target);
    h->size -= 1;
    return target;
}

int heap_empty(Heap h) {
    return h->size == 0;
}

void heap_destroy(Heap h) {
    int i;
    if (h->free) {
        for (i = 0; i < h->size; i++) {
            h->free(h->data[i]);
        }
    }
    free(h->data);
    free(h);
}
