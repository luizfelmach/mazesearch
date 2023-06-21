#include <mazesearch.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("usage: %s <maze.bin>\n", argv[0]);
        exit(1);
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        printf("error: can not open file '%s'\n", argv[1]);
        exit(1);
    }
    Maze m = maze_make(f);
    maze_show(m);
    Graph g = maze_to_graph(m);
    graph_show(g);

    dfs(g, 4, 0, 1, 1);

    graph_destroy(g);
    maze_destroy(m);
    fclose(f);
    return 0;
}
