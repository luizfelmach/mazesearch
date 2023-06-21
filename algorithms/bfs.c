#include <deque.h>
#include <g_node.h>
#include <graph.h>
#include <graph_search.h>
#include <queue.h>
#include <stdio.h>
#include <stdlib.h>

int bfs(Graph g, Point start, Point end, Deque path, int *expanded) {
    int   i, result = 0;
    GNode initial = graph_node_get(g, start.x, start.y);
    if (!initial) {
        return result;
    }
    Queue nodes = queue(NULL);
    g_node_set_state(initial, VISITED);
    g_node_cost_set(initial, 0);
    queue_push(nodes, initial);
    *expanded = 1;
    while (!queue_empty(nodes)) {
        GNode top = queue_enqueue(nodes);
        Point p   = g_node_get_point(top);
        for (i = 0; i < g_node_edge_size(top); i++) {
            Point e = g_node_edge_at(top, i);
            GNode a = graph_node_get(g, e.x, e.y);
            if (g_node_state(a) == NOT_VISITED) {
                double cost = g_node_cost_get(top);
                double dist = point_dist(e, p);
                g_node_cost_set(a, cost + dist);
                g_node_set_state(a, VISITED);
                g_node_prev_set(a, p);
                queue_push(nodes, a);
                *expanded += 1;
            }
        }
        if (point_cmp(p, end)) {
            result = 1;
            printf("%lf\n", g_node_cost_get(top));
            break;
        }
    }
    queue_destroy(nodes);
    if (result) {
        Point k = end;
        while (1) {
            if (point_cmp(start, k)) {
                deque_push_front(path, point_alloc(start));
                break;
            }
            GNode a = graph_node_get(g, k.x, k.y);
            k       = g_node_prev_get(a);
        }
    }
    return result;
}