#include <list.h>
#include <stdio.h>
#include <stdlib.h>

NodeList node_list_new(void *value, NodeList next) {
    NodeList node = calloc(1, sizeof(struct _node_list));
    node->value   = value;
    node->next    = next;
    return node;
}

void node_list_destroy(NodeList node) {
    free(node);
}

List list(free_list free) {
    List l  = calloc(1, sizeof(struct _list));
    l->size = 0;
    l->head = NULL;
    l->tail = NULL;
    l->free = free;
    return l;
}

void list_push_front(List l, void *data) {
    l->head = node_list_new(data, l->head);
    if (l->size == 0) {
        l->tail = l->head;
    }
    l->size += 1;
}

void *list_pop_front(List l) {
    if (!l->head) {
        printf("IndexError: pop from empty forward list.\n");
        exit(1);
    }
    void    *data = l->head->value;
    NodeList n    = l->head;
    l->head       = l->head->next;
    l->size -= 1;
    node_list_destroy(n);
    if (l->size == 0) {
        l->tail = l->head;
    }
    return data;
}

int list_size(List l) {
    return l->size;
}

void *list_find(List l, void *data, cmp_list cmp) {
    void    *target = NULL;
    NodeList n      = l->head;
    while (n) {
        if (!cmp(data, n->value)) {
            target = n->value;
            break;
        }
        n = n->next;
    }
    return target;
}

void list_destroy(List l) {
    int i, size = l->size;
    for (i = 0; i < size; i++) {
        void *data = list_pop_front(l);
        if (l->free) {
            l->free(data);
        }
    }
    free(l);
}
