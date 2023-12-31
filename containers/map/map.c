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

map_pair *_map_get_pair(Map m, void *key) {
    int index = m->hash(m->allocated, key) % m->allocated;
    if (!m->data[index]) {
        return NULL;
    }
    map_pair *target = NULL;
    NodeList  n      = m->data[index]->head;
    while (n) {
        map_pair *mp = n->value;
        if (!m->cmp(key, mp->key)) {
            target = mp;
            break;
        }
        n = n->next;
    }

    return target;
}

void map_set(Map m, void *key, void *data) {
    int index = m->hash(m->allocated, key) % m->allocated;
    if (!m->data[index]) {
        m->data[index] = list(NULL);
    }

    map_pair *mp = _map_get_pair(m, key);
    if (!mp) {
        list_push_front(m->data[index], map_pair_new(key, data));
        m->size += 1;
    } else {
        if (m->free_data) {
            m->free_data(mp->data);
        }
        if (m->free_key) {
            m->free_key(key);
        }
        mp->data = data;
    }
}

void *map_get(Map m, void *key) {
    map_pair *mp = _map_get_pair(m, key);
    if (!mp) {
        return NULL;
    }
    if (m->free_key) {
        m->free_key(key);
    }
    return mp->data;
}

void map_force_key(Map m, void *key) {
    map_pair *mp = _map_get_pair(m, key);
    if (mp) {
        mp->key = key;
    }
}

void map_del(Map m, void *key) {
    int index = m->hash(m->allocated, key) % m->allocated;
    if (!m->data[index]) {
        return;
    }

    NodeList cur  = m->data[index]->head;
    NodeList prev = NULL;

    while (cur) {
        map_pair *mp = cur->value;
        if (!m->cmp(key, mp->key)) {
            if (prev == NULL) {
                m->data[index]->head = cur->next;
            } else {
                prev->next = cur->next;
            }
            if (m->free_key) {
                m->free_key(mp->key);
            }
            if (m->free_data) {
                m->free_data(mp->data);
            }
            free(cur);
            free(mp);
            m->data[index]->size -= 1;
            break;
        }
        prev = cur;
        cur  = cur->next;
    }
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
                n = n->next;
            }
            list_destroy(m->data[i]);
        }
    }
    free(m->data);
    free(m);
}