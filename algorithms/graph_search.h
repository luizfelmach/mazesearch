#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

#include <deque.h>
#include <g_node.h>
#include <graph.h>

int dfs(Graph g, Point start, Point end, Deque path, int *expanded);
int bfs(Graph g, Point start, Point end, Deque path, int *expanded);
int a_star(Graph g, Point start, Point end, Deque path, int *expanded);

#endif