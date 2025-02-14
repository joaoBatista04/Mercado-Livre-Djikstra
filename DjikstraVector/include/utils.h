#ifndef UTILS_H
#define UTILS_H

#include "./graphVector.h"

GraphVector *read_graph_informations(char **vsrc, char *path);
int get_nodes_amount(char *current_line);
int get_number_id(char *name);
void djikstra(GraphVector *graph, int src, float *dist, int *path);
int __get_min_distance(float *dist, int *visited, int node_amount);
void print_shortest_path(int *path, float *dist, int src, int nodeAmount, char *file_path);

#endif