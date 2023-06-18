#ifndef GRAPH_H
#define GRAPH_H

#include <g_node.h>

typedef struct _graph *Graph;
typedef void (*graph_free)(void *);

Graph graph(int row, int column, graph_free free);
void  graph_node_add(Graph g, int i, int j, GNode gn);
GNode graph_node_get(Graph g, int i, int j);
void  graph_show(Graph g);
void  graph_destroy(Graph g);

#endif