#ifndef QUEUE_H
#define QUEUE_H

typedef struct _queue *Queue;
typedef void (*free_queue)(void *);

Queue queue(free_queue free);
void  queue_push(Queue s, void *data);
int   queue_empty(Queue s);
void *queue_enqueue(Queue s);
void  queue_destroy(Queue s);

#endif