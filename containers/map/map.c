#include <list.h>
#include <map.h>
#include <stdlib.h>

typedef struct {
    void *key;
    void *data;
} map_pair;

map_pair *map_pair_new(void *key, void *data) {
    map_pair *mp = calloc(1, sizeof(map_pair));
    mp->key      = key;
    mp->data     = data;
    return mp;
}

struct _map {
    List    *data;
    int      allocated, size;
    map_free free_key;
    map_free free_data;
    map_hash hash;
    map_cmp  cmp;
};

Map map(map_hash hash, map_cmp cmp, map_free free_key, map_free free_data) {
    Map m        = calloc(1, sizeof(struct _map));
    m->cmp       = cmp;
    m->hash      = hash;
    m->free_key  = free_key;
    m->free_data = free_data;
    m->size      = 0;
    m->allocated = 3079;
    m->data      = calloc(m->allocated, sizeof(List *));
    return m;
}

void map_set(Map m, void *key, void *data) {
    int index = m->hash(m->allocated, key) % m->allocated;
    if (!m->data[index]) {
        m->data[index] = list(NULL);
    }
    map_pair *mp = map_pair_new(key, data);
    list_push_front(m->data[index], mp);
    m->size += 1;
}

void *map_get(Map m, void *key) {
    int index = m->hash(m->allocated, key) % m->allocated;
    if (!m->data[index]) {
        return NULL;
    }
    void    *target = NULL;
    NodeList n      = m->data[index]->head;
    while (n) {
        map_pair *mp = n->value;
        if (!m->cmp(key, mp->key)) {
            target = mp->data;
            break;
        }
        n = n->next;
    }
    if (m->free_key) {
        m->free_key(key);
    }
    return target;
}

int map_size(Map m) {
    return m->size;
}

void map_destroy(Map m) {
    int i;
    for (i = 0; i < m->allocated; i++) {
        if (m->data[i]) {
            NodeList n = m->data[i]->head;
            while (n) {
                map_pair *mp = n->value;
                if (m->free_key) {
                    m->free_key(mp->key);
                }
                if (m->free_data) {
                    m->free_data(mp->data);
                }
                free(mp);
                break;
                n = n->next;
            }   
            list_destroy(m->data[i]);
        }
    }
    free(m->data);
    free(m);
}
