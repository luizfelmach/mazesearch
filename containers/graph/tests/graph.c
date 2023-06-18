#include <mazesearch.h>
#include <stdio.h>

int main() {
    Graph g  = graph(100, 200);
    GNode gn = g_node(10, 10);
    g_node_edge(gn, 1, 10);
    g_node_edge(gn, 3, 50);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);
    graph_node_add(g, 0, 0, gn);
    graph_show(g);
    graph_destroy(g);
    return 0;
}