#ifndef GRAPH_H
#define GRAPH_H

#include <g_node.h>

typedef struct _graph *Graph;

Graph graph(int row, int column);
void  graph_node_add(Graph g, int x, int y, GNode gn);
GNode graph_node_get(Graph g, int x, int y);
void  graph_show(Graph g);
void  graph_destroy(Graph g);

#endif