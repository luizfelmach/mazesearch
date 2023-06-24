#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

#include <deque.h>
#include <g_node.h>
#include <graph.h>

void dfs(Graph g, Point start, Point end, Deque path, int *expanded, double *cost);
void bfs(Graph g, Point start, Point end, Deque path, int *expanded, double *cost);
void a_star(Graph g, Point start, Point end, Deque path, int *expanded);

#endif