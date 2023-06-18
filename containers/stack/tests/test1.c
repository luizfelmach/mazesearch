#include <mazesearch.h>
#include <stdio.h>

int main() {
    Stack s = stack(NULL);
    stack_push(s, "machado");
    stack_push(s, "felipe");
    stack_push(s, "luiz");
    while (!stack_empty(s)) {
        char *word = stack_pop(s);
        printf("%s ", word);
    }
    stack_destroy(s);
    return 0;
}