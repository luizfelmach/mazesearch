#include <g_node.h>
#include <graph.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _graph {
    GNode **nodes;
    int     row, column;
    time_t  start;
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
    g->start = time(NULL);
    return g;
}

void graph_node_add(Graph g, int i, int j, GNode gn) {
    g->nodes[i][j] = gn;
}

GNode graph_node_get(Graph g, int i, int j) {
    return g->nodes[i][j];
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

void graph_maze(Graph g) {
    int i, j;

    static int first = 0;

    if (!first) {
        for (i = 0; i < g->row; i++) {
            printf("\n");
        }
        first += 1;
    }

    time_t s = time(NULL);

    int red   = 255;
    int green = 100;

    printf("\033[%dA", g->row);
    for (i = 0; i < g->row; i++) {
        for (j = 0; j < g->column; j++) {
            if (g->nodes[i][j]) {
                if (g_node_state(g->nodes[i][j]) == VISITED) {
                    time_t v = g_node_time_visited(g->nodes[i][j]);
                    red      = ((s - v) * 20) > 255 ? 255 : ((s - v) * 20);
                    green    = (255 - (s - v) * 20) < 0 ? 0 : (255 - (s - v) * 20);
                    printf(
                        "\033[38;2;%d;%d;0m"
                        "*"
                        "\033[0m",
                        red, green);
                } else {
                    printf(" ");
                }
            } else {
                printf("#");
            }
        }
        printf("\n");
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
