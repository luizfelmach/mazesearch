#ifndef MAP_H
#define MAP_H

typedef struct _map *Map;
typedef void (*map_free)(void *);
typedef int (*map_hash)(void *);

Map   map(map_free free, map_hash hash);
void  map_set(Map m, void *key, void *data);
void *map_get(Map m, void *key);
void  map_del(Map m, void *key);
int   map_size(Map m);
void  map_destroy(Map m);

#endif
