#ifndef DEQUE_H
#define DEQUE_H

typedef struct _deque *Deque;
typedef void (*free_deque)(void *);

Deque deque(free_deque free);
void  deque_push_back(Deque d, void *data);
void  deque_push_front(Deque d, void *data);
void *deque_pop_back(Deque d);
void *deque_pop_front(Deque d);
void *deque_at(Deque d, int index);
int   deque_size(Deque d);
void  deque_destroy(Deque d);

#endif