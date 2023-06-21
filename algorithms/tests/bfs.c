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

    Deque path     = deque(free);
    int   expanded = 0;
    Maze  m        = maze_make(f);
    // maze_show(m);
    Graph g = maze_to_graph(m);
    // graph_show(g);

    bfs(g, (Point){0, 0}, (Point){1, 4}, path, &expanded);

    graph_destroy(g);
    maze_destroy(m);
    deque_destroy(path);
    fclose(f);
    return 0;
}
