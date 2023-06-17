#ifndef DEQUE_H
#define DEQUE_H

typedef struct _deque *Deque;

Deque deque();
void  deque_push_back(Deque d, void *data);
void  deque_push_front(Deque d, void *data);
void *deque_pop_back(Deque d);
void *deque_pop_front(Deque d);
void *deque_at(Deque d, int index);
int   deque_size(Deque d);
void  deque_destroy(Deque d);
void  deque_debug(Deque d);

#endif