#ifndef UTILS_H
#define UTILS_H

#include "./graph.h"

Graph *read_graph_informations(char **vsrc, char *path);
int get_nodes_amount(char *current_line);
int get_number_id(char *name);
void djikstra(Graph *graph, int src, float *dist, int *path);
void print_shortest_path(int *path, float *dist, int src, int nodeAmount, char *file_path);

#endif