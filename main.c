#include <deque.h>
#include <graph_search.h>
#include <maze.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    char input_path[1024];

    scanf("%s%*c", input_path);

    FILE *f = fopen(input_path, "rb");
    if (!f) {
        printf("error: can not open file '%s'\n", input_path);
        exit(1);
    }

    // char output_path[1024];
    // printf("output path: ");
    // scanf("%s", output_path);
    // FILE *output = fopen(output_path, "w");
    // if (!f) {
    //    printf("error: can not open file '%s'\n", output_path);
    //    exit(1);
    //}

    Maze  m = maze_make(f);
    Graph g = maze_to_graph(m);

    Deque  path     = deque(free);
    int    expanded = 0;
    double cost     = 0;
    Point  start;
    Point  end;

    // printf("your maze\n\n");
    // maze_show(m);

    // printf("start: ");
    scanf("%d %d", &start.x, &start.y);
    // printf("end: ");
    scanf("%d %d", &end.x, &end.y);

    char option[20];
    scanf("%s%*c", option);

    if (!strcmp(option, "DFS")) {
        dfs(g, start, end, path, &expanded, &cost);
    } else if (!strcmp(option, "BFS")) {
        bfs(g, start, end, path, &expanded, &cost);
    } else if (!strcmp(option, "A*")) {
    } else {
        printf("No algorithm was selected. Leaving.\n");
    }

    // maze_save_solution(output, path, cost, expanded);
    maze_save_solution(stdout, path, cost, expanded);

    graph_destroy(g);
    maze_destroy(m);
    deque_destroy(path);
    fclose(f);
    // fclose(output);
    return 0;
}
