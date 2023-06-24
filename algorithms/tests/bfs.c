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

    Maze  m = maze_make(f);
    Graph g = maze_to_graph(m);

    Deque  path     = deque(free);
    int    expanded = 0;
    double cost     = 0;
    Point  start    = {0, 0};
    Point  end      = {4, 4};

    bfs(g, start, end, path, &expanded, &cost);

    maze_save_solution(stdout, path, cost, expanded);

    graph_destroy(g);
    maze_destroy(m);
    deque_destroy(path);
    fclose(f);
    return 0;
}
