#include <deque.h>
#include <maze.h>
#include <stdio.h>
#include <stdlib.h>

int neighborhood[8][2] = {{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                          {1, 0},  {1, -1}, {0, -1}, {-1, -1}};

struct _maze {
    int             row, column;
    unsigned char **maze;
};

Maze maze_make(FILE *f) {
    Maze m = calloc(1, sizeof(struct _maze));
    fread(&m->row, sizeof(int), 1, f);
    fread(&m->column, sizeof(int), 1, f);
    m->maze = calloc(m->row, sizeof(unsigned char *));
    int i;
    for (i = 0; i < m->row; i++) {
        m->maze[i] = calloc(m->column, sizeof(unsigned char));
        fread(m->maze[i], sizeof(unsigned char), m->column, f);
    }
    return m;
}

void maze_show(Maze m) {
    int i, j;

    printf("   ");
    for (j = 0; j < m->column; j++) {
        printf("%d ", j);
    }
    printf("\n\n");

    for (i = 0; i < m->row; i++) {
        printf("%d  ", i);
        for (j = 0; j < m->column; j++) {
            if (m->maze[i][j]) {
                printf("# ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

Graph maze_to_graph(Maze m) {
    int   i, j, k;
    int   row    = m->row;
    int   column = m->column;
    Graph g      = graph(row, column);
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            if (!m->maze[i][j]) {
                GNode gn = g_node(i, j);
                for (k = 0; k < 8; k++) {
                    int n_i = i + neighborhood[k][0];
                    int n_j = j + neighborhood[k][1];
                    if (n_i < 0 || n_i >= row) {
                        continue;
                    }
                    if (n_j < 0 || n_j >= column) {
                        continue;
                    }
                    if (m->maze[n_i][n_j]) {
                        continue;
                    }
                    g_node_edge(gn, n_i, n_j);
                }
                graph_node_add(g, i, j, gn);
            }
        }
    }
    return g;
}

void maze_destroy(Maze m) {
    int i;
    for (i = 0; i < m->row; i++) {
        free(m->maze[i]);
    }
    free(m->maze);
    free(m);
}

void maze_save_solution(FILE *out, Deque path, double cost, int expanded_nodes) {
    if (deque_size(path) == 0) {
        fprintf(out, "IMPOSSIVEL\n");
        return;
    }
    int i;
    for (i = 0; i < deque_size(path); i++) {
        Point *p = deque_at(path, i);
        fprintf(out, "%d %d\n", p->x, p->y);
    }
    fprintf(out, "%.2lf\n", cost);
    fprintf(out, "%d\n", deque_size(path));
    fprintf(out, "%d\n", expanded_nodes);
}
