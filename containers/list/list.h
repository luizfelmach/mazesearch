#ifndef LIST_H
#define LIST_H

typedef struct _list *List;
typedef void (*free_list)(void *);
typedef int (*cmp_list)(void *, void *);

List  list(free_list free);
void  list_push_front(List l, void *data);
void *list_pop_front(List l);
int   list_size(List l);
void *list_find(List l, void *data, cmp_list cmp);
void  list_destroy(List l);

#endif
