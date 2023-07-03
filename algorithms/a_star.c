#include <deque.h>
#include <g_node.h>
#include <graph.h>
#include <graph_search.h>
#include <heap.h>
#include <map.h>
#include <stdio.h>
#include <stdlib.h>

int g_node_hash(int size, void *ptr) {
    GNode g = ptr;
    Point p = g_node_get_point(g);
    return (p.x * 523) ^ (p.y * 541);
}

int g_node_cmp(void *a1, void *a2) {
    GNode g1 = a1;
    GNode g2 = a2;
    Point p1 = g_node_get_point(g1);
    Point p2 = g_node_get_point(g2);
    return !point_cmp(p1, p2);
}

double g_node_prio(void *ptr) {
    GNode g = ptr;
    return g_node_prio_get(g);
}

void a_star(Graph g, Point start, Point end, Deque path, int *expanded, double *cost) {
    int   i, result = 0;
    GNode initial = graph_node_get(g, start.x, start.y);
    if (!initial) {
        return;
    }
    Map  indexes = map(g_node_hash, g_node_cmp, NULL, free);
    Heap nodes   = heap(indexes, g_node_prio, NULL);
    g_node_set_state(initial, VISITED);
    g_node_cost_set(initial, 0);
    g_node_prio_set(initial, 0 + point_dist(start, end));
    heap_insert(nodes, initial);
    *cost     = 0;
    *expanded = 0;
    while (!heap_empty(nodes)) {
        GNode top = heap_pop(nodes);
        Point p   = g_node_get_point(top);
        for (i = 0; i < g_node_edge_size(top); i++) {
            Point e = g_node_edge_at(top, i);
            GNode a = graph_node_get(g, e.x, e.y);
            if (g_node_state(a) == NOT_VISITED) {
                double cost = g_node_cost_get(top);
                double dist = point_dist(e, p);
                g_node_cost_set(a, cost + dist);
                g_node_prio_set(a, cost + dist + point_dist(e, end));
                g_node_set_state(a, VISITED);
                g_node_prev_set(a, p);
                heap_insert(nodes, a);
            } else if (g_node_state(a) == VISITED) {
                double cost = g_node_cost_get(top);
                double dist = point_dist(e, p);
                if (cost + dist + point_dist(e, end) < g_node_prio(a)) {
                    g_node_cost_set(a, cost + dist);
                    g_node_prio_set(a, cost + dist + point_dist(e, end));
                    g_node_set_state(a, VISITED);
                    g_node_prev_set(a, p);
                    heap_insert(nodes, a);
                }
            }
        }
        *expanded += 1;
        if (point_cmp(p, end)) {
            result = 1;
            *cost  = g_node_cost_get(top);
            break;
        }
    }
    heap_destroy(nodes);
    map_destroy(indexes);
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
