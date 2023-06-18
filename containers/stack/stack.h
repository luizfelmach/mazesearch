#ifndef STACK_H
#define STACK_H

typedef struct _stack *Stack;
typedef void (*free_stack)(void *);

Stack stack(free_stack free);
void  stack_push(Stack s, void *data);
int   stack_empty(Stack s);
void *stack_pop(Stack s);
void  stack_destroy(Stack s);

#endif