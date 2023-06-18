#include <deque.h>
#include <stack.h>
#include <stdlib.h>

struct _stack {
    Deque data;
};

Stack stack(free_stack free) {
    Stack s = calloc(1, sizeof(struct _stack));
    s->data = deque(free);
    return s;
}

void stack_push(Stack s, void *data) {
    deque_push_back(s->data, data);
}

int stack_empty(Stack s) {
    return deque_size(s->data) == 0;
}

void *stack_pop(Stack s) {
    return deque_pop_back(s->data);
}

void stack_destroy(Stack s) {
    deque_destroy(s->data);
    free(s);
}
