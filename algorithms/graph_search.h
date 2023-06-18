#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

#include <graph.h>

typedef void (*graph_search_routine)(Graph);

void dfs(Graph g, int start_x, int start_y, int dest_x, int dest_y,
         graph_search_routine routine);
void bfs(Graph g, int start_x, int start_y, int dest_x, int dest_y,
         graph_search_routine routine);
void a_star(Graph g, int i, int j);

#endif