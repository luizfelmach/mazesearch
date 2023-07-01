#ifndef MAP_H
#define MAP_H

typedef struct _map *Map;
typedef void (*map_free)(void *);
typedef int (*map_hash)(int, void *);
typedef int (*map_cmp)(void *, void *);

Map   map(map_hash hash, map_cmp cmp, map_free free_key, map_free free_data);
void  map_set(Map m, void *key, void *data);
void *map_get(Map m, void *key);
void  map_force_key(Map m, void *key);
int   map_size(Map m);
void  map_destroy(Map m);

#endif
