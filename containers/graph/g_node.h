#ifndef G_NODE_H
#define G_NODE_H

typedef struct _g_node *GNode;

typedef struct {
    int i, j;
} edge;

typedef enum {
    NOT_VISITED = 0,
    VISITED     = 1,
} NodeState;

GNode     g_node(int i, int j);
void      g_node_edge(GNode gn, int i, int j);
edge      g_node_get_edge(GNode gn);
int       g_node_edge_size(GNode gn);
edge      g_node_edge_at(GNode gn, int index);
NodeState g_node_state(GNode gn);
void      g_node_set_state(GNode gn, NodeState s);
void      g_node_show(GNode gn);
void      g_node_destroy(GNode gn);

#endif