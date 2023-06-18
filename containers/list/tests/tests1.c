#include <mazesearch.h>
#include <stdio.h>

int main() {
    List l = list(NULL);
    list_push_front(l, "machado");
    list_push_front(l, "felipe");
    list_push_front(l, "luiz");
    int i, size = list_size(l);
    for (i = 0; i < size; i++) {
        printf("%s ", (char *)list_pop_front(l));
    }
    list_destroy(l);
    return 0;
}