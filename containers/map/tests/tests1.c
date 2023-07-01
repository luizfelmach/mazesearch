#include <mazesearch.h>
#include <stdio.h>
#include <string.h>

int hash(int size, void *key) {
    return 10;
}

int cmp(void *key1, void *key2) {
    return strcmp((char *)key1, (char *)key2);
}

int main() {
    Map m = map(hash, cmp, NULL, NULL);

    map_set(m, "luiz", "felipe");
    map_set(m, "nome", "pedro");

    printf("%s\n", (char *)map_get(m, "luiz"));
    // printf("%p", map_get(m, "nome"));

    map_destroy(m);
    return 0;
}