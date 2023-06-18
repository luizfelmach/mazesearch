#include <deque.h>
#include <queue.h>
#include <stdlib.h>

struct _queue {
    Deque data;
};

Queue queue(free_queue free) {
    Queue s = calloc(1, sizeof(struct _queue));
    s->data = deque(free);
    return s;
}

void queue_push(Queue s, void *data) {
    deque_push_back(s->data, data);
}

int queue_empty(Queue s) {
    return deque_size(s->data) == 0;
}

void *queue_enqueue(Queue s) {
    return deque_pop_front(s->data);
}

void queue_destroy(Queue s) {
    deque_destroy(s->data);
    free(s);
}
