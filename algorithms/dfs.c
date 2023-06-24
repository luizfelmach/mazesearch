#include <deque.h>
#include <g_node.h>
#include <graph.h>
#include <graph_search.h>
#include <stack.h>
#include <stdio.h>
#include <stdlib.h>

void dfs(Graph g, Point start, Point end, Deque path, int *expanded, double *cost) {
    int   i, result = 0;
    GNode initial = graph_node_get(g, start.x, start.y);
    if (!initial) {
        return;
    }
    Stack nodes = stack(NULL);
    g_node_set_state(initial, VISITED);
    g_node_cost_set(initial, 0);
    stack_push(nodes, initial);
    *cost     = 0;
    *expanded = 1;
    while (!stack_empty(nodes)) {
        GNode top = stack_pop(nodes);
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
                stack_push(nodes, a);
                *expanded += 1;
            }
        }
        if (point_cmp(p, end)) {
            result = 1;
            *cost  = g_node_cost_get(top);
            break;
        }
    }
    stack_destroy(nodes);
    if (result) {
        Point k = end;
        while (1) {
            if (point_cmp(start, k)) {
                deque_push_front(path, point_alloc(start));
                break;
            }
            deque_push_front(path, point_alloc(k));
            GNode a = graph_node_get(g, k.x, k.y);
            k       = g_node_prev_get(a);
        }
    }
}