#ifndef HEAP_H
#define HEAP_H

#include <map.h>

typedef void (*heap_free)(void *);
typedef double (*heap_prio)(void *);

typedef struct _heap *Heap;

Heap  heap(Map indexes, heap_prio prio, heap_free free);
void  heap_insert(Heap h, void *data);
void *heap_pop(Heap h);
int   heap_empty(Heap h);
void  heap_destroy(Heap h);

#endif