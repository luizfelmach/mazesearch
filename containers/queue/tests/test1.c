#include <mazesearch.h>
#include <stdio.h>

int main() {
    Queue s = queue(NULL);
    queue_push(s, "luiz");
    queue_push(s, "felipe");
    queue_push(s, "machado");
    while (!queue_empty(s)) {
        char *word = queue_enqueue(s);
        printf("%s ", word);
    }
    queue_destroy(s);
    return 0;
}