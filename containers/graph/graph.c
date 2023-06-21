#include <g_node.h>
#include <graph.h>
#include <stdio.h>
#include <stdlib.h>

struct _graph {
    GNode **nodes;
    int     row, column;
};

Graph graph(int row, int column) {
    Graph g   = calloc(1, sizeof(struct _graph));
    g->row    = row;
    g->column = column;
    g->nodes  = calloc(row, sizeof(GNode **));
    int i;
    for (i = 0; i < row; i++) {
        g->nodes[i] = calloc(column, sizeof(GNode *));
    }
    return g;
}

void graph_node_add(Graph g, int x, int y, GNode gn) {
    g->nodes[x][y] = gn;
}

GNode graph_node_get(Graph g, int x, int y) {
    return g->nodes[x][y];
}

void graph_show(Graph g) {
    int i, j;
    for (i = 0; i < g->row; i++) {
        for (j = 0; j < g->column; j++) {
            if (g->nodes[i][j]) {
                g_node_show(g->nodes[i][j]);
                printf("\n");
            }
        }
    }
}

void graph_destroy(Graph g) {
    int i, j;
    for (i = 0; i < g->row; i++) {
        for (j = 0; j < g->column; j++) {
            if (g->nodes[i][j]) {
                g_node_destroy(g->nodes[i][j]);
            }
        }
        free(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
}
