#ifndef G_NODE_H
#define G_NODE_H

typedef struct _g_node *GNode;

typedef struct {
    int x, y;
} Point;

typedef enum {
    NOT_VISITED = 0,
    VISITED     = 1,
} NodeState;

GNode     g_node(int x, int y);
void      g_node_edge(GNode gn, int x, int y);
Point     g_node_get_point(GNode gn);
int       g_node_edge_size(GNode gn);
Point     g_node_edge_at(GNode gn, int index);
NodeState g_node_state(GNode gn);
void      g_node_set_state(GNode gn, NodeState s);
void      g_node_show(GNode gn);
void      g_node_destroy(GNode gn);
void      g_node_prev_set(GNode gn, Point p);
Point     g_node_prev_get(GNode gn);

void   g_node_cost_set(GNode gn, double cost);
double g_node_cost_get(GNode gn);

Point *point_alloc(Point a);
int    point_cmp(Point a, Point b);
double point_dist(Point a, Point b);

#endif