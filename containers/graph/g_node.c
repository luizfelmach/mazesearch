#include <g_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _g_node {
    int       size_edge;
    NodeState state;
    edge      edge;
    edge      edges[8];
    time_t    time_visited;
};

GNode g_node(int i, int j) {
    GNode gn      = calloc(1, sizeof(struct _g_node));
    gn->size_edge = 0;
    gn->edge      = (edge){.i = i, .j = j};
    gn->state     = NOT_VISITED;
    return gn;
}

void g_node_edge(GNode gn, int i, int j) {
    edge e                     = {.i = i, .j = j};
    gn->edges[gn->size_edge++] = e;
}

edge g_node_get_edge(GNode gn) {
    return gn->edge;
}

NodeState g_node_state(GNode gn) {
    return gn->state;
}

void g_node_set_state(GNode gn, NodeState s) {
    if (s == VISITED) {
        gn->time_visited = time(NULL);
    }
    gn->state = s;
}

int g_node_edge_size(GNode gn) {
    return gn->size_edge;
}

edge g_node_edge_at(GNode gn, int index) {
    return gn->edges[index];
}

void g_node_show(GNode gn) {
    printf("(%d, %d) -> ", gn->edge.i, gn->edge.j);
    int i;
    for (i = 0; i < gn->size_edge; i++) {
        printf("(%d, %d) ", gn->edges[i].i, gn->edges[i].j);
    }
}

void g_node_destroy(GNode gn) {
    free(gn);
}

time_t g_node_time_visited(GNode gn) {
    return gn->time_visited;
}