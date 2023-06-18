#include <mazesearch.h>
#include <stdio.h>

int main() {
    GNode gn = g_node(10, 10);

    g_node_edge(gn, 1, 10);
    g_node_edge(gn, 3, 50);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);
    g_node_edge(gn, 90, 10);

    g_node_show(gn);
    g_node_destroy(gn);
    return 0;
}