#include <g_node.h>
#include <graph.h>
#include <graph_search.h>
#include <stack.h>
#include <stdio.h>
#include <stdlib.h>

void dfs(Graph g, int start_x, int start_y, int dest_x, int dest_y) {
    GNode gn = graph_node_get(g, start_x, start_y);
    if (!gn) {
        printf("IMPOSSIBLE\n");
        return;
    }
    Stack nodes = stack(NULL);
    g_node_set_state(gn, VISITED);
    stack_push(nodes, gn);
    while (!stack_empty(nodes)) {
        GNode s = stack_pop(nodes);
        int   i;
        for (i = 0; i < g_node_edge_size(s); i++) {
            edge  e = g_node_edge_at(s, i);
            GNode a = graph_node_get(g, e.i, e.j);
            if (g_node_state(a) == NOT_VISITED) {
                g_node_set_state(a, VISITED);
                stack_push(nodes, a);
            }
        }
        edge e = g_node_get_edge(s);
        if (e.i == dest_x && e.j == dest_y) {
            printf("encontrou!!!!\n");
        }
    }
    stack_destroy(nodes);
}