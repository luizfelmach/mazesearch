#include <g_node.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct _g_node {
    int       size_edge;
    double    cost;
    NodeState state;
    Point     point;
    Point     edges[8];
    Point     prev;
};

GNode g_node(int x, int y) {
    GNode gn      = calloc(1, sizeof(struct _g_node));
    gn->size_edge = 0;
    gn->cost      = 0;
    gn->point     = (Point){.x = x, .y = y};
    gn->state     = NOT_VISITED;
    return gn;
}

void g_node_edge(GNode gn, int x, int y) {
    Point p                    = {.x = x, .y = y};
    gn->edges[gn->size_edge++] = p;
}

Point g_node_get_point(GNode gn) {
    return gn->point;
}

NodeState g_node_state(GNode gn) {
    return gn->state;
}

void g_node_set_state(GNode gn, NodeState s) {
    gn->state = s;
}

int g_node_edge_size(GNode gn) {
    return gn->size_edge;
}

Point g_node_edge_at(GNode gn, int index) {
    return gn->edges[index];
}

void g_node_show(GNode gn) {
    printf("(%d, %d) -> ", gn->point.x, gn->point.y);
    int i;
    for (i = 0; i < gn->size_edge; i++) {
        printf("(%d, %d) ", gn->edges[i].x, gn->edges[i].y);
    }
}

void g_node_destroy(GNode gn) {
    free(gn);
}

void g_node_prev_set(GNode gn, Point p) {
    gn->prev = p;
}

Point g_node_prev_get(GNode gn) {
    return gn->prev;
}

void g_node_cost_set(GNode gn, double cost) {
    gn->cost = cost;
}

double g_node_cost_get(GNode gn) {
    return gn->cost;
}

Point *point_alloc(Point a) {
    Point *p = calloc(1, sizeof(Point));
    p->x     = a.x;
    p->y     = a.y;
    return p;
}

int point_cmp(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

double point_dist(Point a, Point b) {
    int x2 = pow(a.x - b.x, 2);
    int y2 = pow(a.y - b.y, 2);
    return sqrt(x2 + y2);
}