#ifndef UTILS_H
#define UTILS_H

#include "./graph.h"

Graph *read_graph_informations(char **vsrc, char *path);
int get_nodes_amount(char *current_line);
int get_number_id(char *name);
float *djikstra(Graph *graph, int src);

#endif