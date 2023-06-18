#include <g_node.h>
#include <graph.h>
#include <graph_search.h>
#include <queue.h>
#include <stdio.h>
#include <stdlib.h>

void bfs(Graph g, int start_x, int start_y, int dest_x, int dest_y,
         graph_search_routine routine) {
    GNode gn = graph_node_get(g, start_x, start_y);
    if (!gn) {
        printf("IMPOSSIBLE\n");
        return;
    }
    Queue nodes = queue(NULL);
    g_node_set_state(gn, VISITED);
    queue_push(nodes, gn);
    while (!queue_empty(nodes)) {
        routine(g);
        GNode q = queue_enqueue(nodes);
        int   i;
        for (i = 0; i < g_node_edge_size(q); i++) {
            edge  e = g_node_edge_at(q, i);
            GNode a = graph_node_get(g, e.i, e.j);
            if (g_node_state(a) == NOT_VISITED) {
                g_node_set_state(a, VISITED);
                queue_push(nodes, a);
            }
        }
        edge e = g_node_get_edge(q);
        if (e.i == dest_x && e.j == dest_y) {
            printf("Encontrou!!!");
        }
    }
    queue_destroy(nodes);
}