#ifndef G_NODE_H
#define G_NODE_H

typedef struct _g_node *GNode;

GNode g_node(int i, int j);
void  g_node_edge(GNode gn, int i, int j);
void  g_node_show(GNode gn);
void  g_node_destroy(GNode gn);

#endif