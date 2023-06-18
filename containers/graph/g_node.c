#include <g_node.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int i, j;
} edge;

struct _g_node {
    int  i, j, size_edge;
    edge edges[8];
};

GNode g_node(int i, int j) {
    GNode gn      = calloc(1, sizeof(struct _g_node));
    gn->i         = i;
    gn->j         = j;
    gn->size_edge = 0;
    return gn;
}

void g_node_edge(GNode gn, int i, int j) {
    edge e                     = {.i = i, .j = j};
    gn->edges[gn->size_edge++] = e;
}

void g_node_show(GNode gn) {
    printf("(%d, %d) -> ", gn->i, gn->j);
    int i;
    for (i = 0; i < gn->size_edge; i++) {
        printf("(%d, %d) ", gn->edges[i].i, gn->edges[i].j);
    }
}

void g_node_destroy(GNode gn) {
    free(gn);
}