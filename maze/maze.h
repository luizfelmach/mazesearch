#ifndef MAZE_H
#define MAZE_H

#include <deque.h>
#include <g_node.h>
#include <graph.h>
#include <stdio.h>

typedef struct _maze *Maze;

Maze  maze_make(FILE *f);
void  maze_show(Maze m);
Graph maze_to_graph(Maze m);
void  maze_destroy(Maze m);
void  maze_save_solution(FILE *out, Deque path, double cost, int expanded_nodes);
void  maze_draw_solution(Maze m, Deque path);

#endif