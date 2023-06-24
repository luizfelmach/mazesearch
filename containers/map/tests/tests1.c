#include <mazesearch.h>
#include <stdio.h>
#include <string.h>

int hash(int size, char *key) {
    return 10;
}

int main() {
    Map m = map(hash, strcmp, NULL, NULL);

    map_set(m, "luiz", "felipe");
    map_set(m, "nome", "pedro");

    printf("%s\n", map_get(m, "luiz"));
    // printf("%p", map_get(m, "nome"));

    map_destroy(m);
    return 0;
}