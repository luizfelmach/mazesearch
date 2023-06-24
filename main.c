#include <deque.h>
#include <graph_search.h>
#include <maze.h>
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

    int option;
    printf("1 - DFS\n");
    printf("2 - BFS\n");
    printf("3 - A*\n");
    printf("option: ");
    scanf("%d", &option);

    char output_path[1024];
    printf("output path: ");
    scanf("%s", output_path);

    FILE *output = fopen(output_path, "w");
    if (!f) {
        printf("error: can not open file '%s'\n", output_path);
        exit(1);
    }

    Maze  m = maze_make(f);
    Graph g = maze_to_graph(m);

    Deque  path     = deque(free);
    int    expanded = 0;
    double cost     = 0;
    Point  start;
    Point  end;

    printf("your maze\n\n");
    maze_show(m);

    printf("start: ");
    scanf("%d %d", &start.x, &start.y);
    printf("end: ");
    scanf("%d %d", &end.x, &end.y);

    if (option == 1) {
        dfs(g, start, end, path, &expanded, &cost);
    } else if (option == 2) {
        bfs(g, start, end, path, &expanded, &cost);
    } else if (option == 3) {
    } else {
        printf("No algorithm was selected. Leaving.\n");
    }

    maze_save_solution(output, path, cost, expanded);
    maze_save_solution(stdout, path, cost, expanded);

    graph_destroy(g);
    maze_destroy(m);
    deque_destroy(path);
    fclose(f);
    fclose(output);
    return 0;
}
